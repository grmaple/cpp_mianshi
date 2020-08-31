## 关于new和delete

### new：先分配内存，再调用构造函数

```cpp
Complex* pc = new Complex(1,2);

//被编译器转换成
Complex* pc;
//operator new 内部调用malloc(n)
void* mem = operator new(sizeof(Complex));//分配内存
pc = static_cast<Complex*>(mem);//转型void*转Complex*
pc->Complex::Complex(1,2);//构造函数
//Complex::Complex(pc,1,2);谁调用成员函数，谁就是this
```

### delete：先调用析构函数，再释放内存

```cpp
String* ps = new String("hello");
delete ps;
//被编译器转换成
String::~String(ps);//析构函数
//析构函数把m_data申请的内存"hello"释放掉
//operator delete 内部调用free(ps)
operator delete(ps);//释放内存,释放了ps申请的内存String对象
```

### array new 一定要搭配array delete

new和delete都是表达式，不能重载。

operator new，operator delete才是函数，可以重载

class可以重载这些函数，可以用来内存管理，内存池设计

### 重载::operator new，::operator delete

```cpp
void* myAlloc(size_t size) {
    return malloc(size);
}
void myFree(void* ptr) {
    return free(ptr);
}

//他们不能被声明在一个namespace
inline void* operator new(size_t size) {
    cout<<"global new() \n";
    return myAlloc(size);
}
inline void* operator new[](size_t size) {
    cout<<"global new[]() \n";
    return myAlloc(size);
}
inline void operator delete(void* ptr) {
    cout<<"global delete() \n";
    return myFree(ptr);
}
inline void operator delete[](void* ptr) {
    cout<<"global delete() \n";
    return myFree(ptr);
}
```

现在重载的函数是全局的东西，所以印象很深。

### 重载member operator new/delete

```cpp
class Foo {
public:
    void* operator new(size_t);
	void operator delete(void*, size_t);//第二参数可以省略
}

Foo* p = new Foo;
//void* mem = operator new(sizeof(Foo));
//p = static_cast<Foo*>(mem);
//p->Foo::Foo();
...
delete p;
//p->~Foo();
//operator delete(p);
```

### 重载member operator new[]/delete[]

```cpp
class Foo {
public:
    void* operator new[](size_t);
	void operator delete[](void*, size_t);//第二参数可以省略
}

Foo* p = new Foo[N];
//void* mem = operator new(sizeof(Foo)*N+4);
//p = static_cast<Foo*>(mem);
//p->Foo::Foo();//N次
...
delete[] p;
//p->~Foo();//N次
//operator delete(p);
```

### 示例

```cpp
class Foo {
public://大小：4+4+4=12
    int _id;
    long _data;
    string _str;
public:
    Foo():_id(0) {
        cout<<"default ctor.this="<<this<<"id="<<_id<<endl;
    }
    Foo(int i):_id(i) {
        cout<<"ctor.this="<<this<<"id="<<_id<<endl;
    }
    ~Foo() {
        cout<<"dtor.this="<<this<<"id="<<_id<<endl;
    }
    static void* operator new(size_t size);
    static void operator delete(void* pdead, size_t size);
    static void* operator new[](size_t size);
    static void operator delete[](void* pdead, size_t size);
}

void* Foo::operator new(size_t size) {
    Foo* p = (Foo*)malloc(size);
    cout<<"global new() \n";
    return p;
}
void* Foo::operator new[](size_t size) {
    Foo* p = (Foo*)malloc(size);
    cout<<"global new[]() \n";
    return p;
}
void Foo::operator delete(void* pdead, size_t size) {
    cout<<"global delete() \n";
    return free(pdead);
}
void Foo::operator delete[](void* pdead, size_t size) {
    cout<<"global delete() \n";
    return free(pdead);
}

Foo* pf = new Foo;
delete pf;

//下面强制性采用全局函数
Foo* pf = ::new Foo;
//void* ::operator new(size_t)
::delete pf;
//void ::operator delete(void*)
```

array new和delete的[]收到的大小，有没有什么值得关注的地方。

```cpp
cout<<"sizeof(Foo)="<<sizeof(Foo)<<endl;
//12,如果有虚函数就是16，多个指针
Foo* p = new Foo(7);
delete p;

Foo* pArray = new Foo[5];//12*5+4，多出来的4，就是用来记录数组大小的
delete[] pArray;
```

![image-20200831141607372](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200831141607372.png)

调用五次构造函数，五次析构函数。

