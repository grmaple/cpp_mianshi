## 关于Dynamic Binding动态绑定

动态绑定三个条件：

指针调用

虚函数

向上转型

![image-20200831113526251](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200831113526251.png)

```cpp
B b;
A a = (A)b;
a.vfunc1();//对象调用，静态绑定，A::vfunc1

A* pa = new B;//向上转型
pa->vfunc1();//指针调用，虚函数，动态绑定，B::vfunc1

//A* pa; B b;
pa = &b;//向上转型
pa->vfunc1();//指针调用，虚函数，动态绑定，B::vfunc1
```

### 探谈const

常量成员函数

double real() const {return re;}

告诉编译器，const修饰成员函数(全局函数不能这样放const)，成员函数不打算修改数据。

一般成员函数都是操作数据，常量成员函数操作数据，但是不改数据

```cpp
//const member fuctions and non-const object
double real () const {return re;}
int main()
{
	complex c1(2,1);
    cout << c1.real;
}
//non-const member fuctions and non-const object
double real () {return re;}
int main()
{
	complex c1(2,1);
    cout << c1.real;
}
//const member fuctions and const object
double real () const {return re;}
int main()
{
	const complex c1(2,1);
    cout << c1.real;
}
//non-const member fuctions and const object
double real () {return re;}//没有const，可能会修改re
int main()
{
	const complex c1(2,1);//const说明要求re=2不能变
    cout << c1.real;//出错，编译器认为real可能修改re
}
```

![image-20200831122350276](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200831122350276.png)

另一种情况

class template std::basic_string<...>有如下两个成员函数。

std::basic_string其实就是String

```cpp
//COW写时复制
//当成员函数的const和non-const版本同时存在，
//const object只会调用const member fuctions，
//non-const object只会调用non-const member fuctions

//const object常量字符串不可能改变内容，调用const member fuctions
charT operator[](size_type pos) const {
    //不必考虑COW
}
//non-const object，调用non-const member fuctions
reference operator[](size_type pos) {
    //必须考虑COW
}
```

函数重载，考虑函数签名。

函数签名：函数名+参数+const