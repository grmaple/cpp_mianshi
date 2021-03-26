## reference

C++变量有三种，值，指针，引用。

指针就是地址，地址就是指针。

![image-20200831101522195](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200831101522195.png)

```cpp
int x = 0;
int* p = &x;//指向x
int& r = x;//代表x
int x2 = 5;

r = x2;//r就是x，x就是r。相当于r = x = 5;
int& r2 = r;//给x的别名r再起别名r2.r = x = r2
```

引用一定要有初值。并且不能再变。

C++引用底部是用指针实现。

虽然r是引用，大小应该是指针，并且有自己的地址。

但是编译器会制造一种假象：

sizeof(r) == sizeof(x)大小相同

&x == &r地址相同

Java里面所有变量都是引用。

### reference 的常见用途

reference就是一种漂亮的pointer

reference通常不用于声明变量，而用于参数类型和返回类型的描述。

```cpp
//被调用端，写法最容易的是值传递和引用传递。
void func1(Cls* pobj) {pobj->xxx();}
void func2(Cls obj) {obj.xxx();}
void func3(Cls& obj) {obj.xxx();}
...
Cls obj;
//调用端，写法最容易的是值传递和引用传递。
func1(&obj);
func2(obj);
func3(obj);

//综上所述，是值传递和引用传递是最方便的。
//因为值传递传的数据很大，而引用传递只是传指针，所以引用传递更快，更好。
```

以下被视为same signature，所以二者不能同时存在

函数签名指imag(const double& im)

const算不算签名的一部分?是。一个有const，一个没有，可以共存。

```cpp
//两个相同函数，函数重载。
double imag(const double& im) {...}
double imag(const double im) {...}
//imag(obj) 时，不知道调用谁。Ambiguity
```

