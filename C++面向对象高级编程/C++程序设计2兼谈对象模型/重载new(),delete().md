## 重载new(),delete()

class member operator new()有可以说是placement new()

我们可以重载class member operator new(),写出多个版本，前提是每一个版本的声明都必须有独一无二的的参数列，第一参数一定要是size_t，其余参数以new所指定的placement arguments为初值。

placement arguments就是出现在new(...)小括号里面的内容

```cpp
class Foo {
public:
    Foo() {cout<<"Foo::Foo()"<<endl;}
    Foo(int) {
        cout<<"Foo::Foo(int)"<<endl;
        throw Bad();//这里故意抛出exception，测试class member operator delete()
    }
    //重载new,一般形式，只改内容
    void* operator new(size_t size) {
        return malloc(size);
    }
    //重载new，修改参数
    void* operator new(size_t size, void* start) {
        return start;
    }
    void* operator new(size_t size, long extra) {
        return malloc(size+extra);
    }
    void* operator new(size_t size, long extra, char init) {
        return malloc(size+extra);
    }
	//重载delete,一般形式，只改内容
    void operator delete(void *, size_t) {
        cout<<"operator delete(void *, size_t)"<<endl;
    }
    //重载delete，修改参数
    //当ctor抛出异常时，这里的operator delete会被调用
    //用途是释放对应的operator new分配所得的memory
    void operator delete(void *, void*) {
        cout<<"operator delete(void *, void*)"<<endl;
    }
    void operator delete(void *, long) {
        cout<<"operator delete(void *, long)"<<endl;
    }
    void operator delete(void *, long, char) {
        cout<<"operator delete(void *, long, char)"<<endl;
    }
    //如果operator delete未能找到对应的operator new，也不会报错，这样会放弃处理ctor抛出的异常
private:
    int m_i;
}

Foo* pf = new(300,'c')Foo;
```

我们也可以重载class member operator delete()。但它们不会被delete调用。

只有当new所调用的构造函数抛出exception，才会调用这些重载版的operator delete()。

它只可能这样被调用，主要用来归还未能完全创建成功的object所占用的memory

### basic_string使用new(extra)扩充申请量

来看看标准库的例子，看看怎么改变placement new()

```cpp
template<...>
class basic_string {
private:
    struct Rep {
        ...
        void release() {if (--ref == 0) delete this;}
        inline static void* operator new (size_t, size_t);
        inline static void operator delete (void*);
        inline static Rep* create(size_t);
    }
}
template<class charT, class traits, class Allocator>
inline basic_string<charT,traits,Allocator>::Rep*
base_string<charT,traits,Allocator>::Rep::create(size_t extra) {
    extra = frob_size(extra + 1);
    Rep *p = new(extra)Rep;
    ...
    return p;
}
template<class charT, class traits, class Allocator>
inline void*
base_string<charT,traits,Allocator>::Rep::operator new(size_t s,size_t extra) {
    return Allocator::allocate(s+extra*sizeof(charT));
}
template<class charT, class traits, class Allocator>
inline void
base_string<charT,traits,Allocator>::Rep::operaror delete(void* ptr) {
    Allocator::deallocate(ptr,sizeof(Rep)+reinterpret_cast<Rep*>(ptr)->res*sizeof(charT));
}
```

![image-20200831150258697](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200831150258697.png)

当Rep，create()时，是分配一个Rep，加上extra。这一整包代表一个basic_string。字符串其实放在那里呢？放在extra里面。

Rep是作控制用的，一个计数器，有什么人和我共享。

当我想无声无息，不知不觉地多分配一些东西的时候，可以借鉴这种做法。