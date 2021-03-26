## sizeof

类对象的计算

- 空类大小为1字节
- 一个类中，虚函数本身、成员函数和静态成员数据不占用类对象存储空间
- 包含了虚函数的类，只有一个虚指针vptr的大小
- 普通继承，派生类继承了基类的函数和成员，要按照字节对齐来计算大小
- 虚函数继承，都是继承的基类的vptr
- 虚继承，继承基类的vptr

```cc
/**
 * @file blackclass.cpp
 * @brief 空类的大小为1字节
 */
#include<iostream>
using namespace std;
class A{};
int main()
{
    cout<<sizeof(A)<<endl;
    return 0;
}
```

```cc
/**
 * @file static.cpp
 * @brief 静态数据成员
 * 静态数据成员被编译器放在程序的一个global data members中，它是类的一个数据成员，但不影响类的大小。不管这个类产生了多少个实例，还是派生了多少新的类，静态数据成员只有一个实例。静态数据成员，一旦被声明，就已经存在。 
 */
#include<iostream>
using namespace std;
class A
{
    public:
        char b;
        virtual void fun() {};
        static int c;
        static int d;
        static int f;
};

int main()
{
    /**
     * @brief 16  字节对齐、静态变量不影响类的大小、vptr指针=8
     */
    cout<<sizeof(A)<<endl; 
    return 0;
}
```

```cc
/**
 * @file morevir.cpp
 * @brief 对于包含虚函数的类，不管有多少个虚函数，只有一个虚指针,vptr的大小。
 */
#include<iostream>
using namespace std;
class A{
    virtual void fun();
    virtual void fun1();
    virtual void fun2();
    virtual void fun3();
};
int main()
{
    cout<<sizeof(A)<<endl; // 8
    return 0;
}
```

```cc
/**
 * @file geninhe.cpp
 * @brief 1.普通单继承,继承就是基类+派生类自身的大小(注意字节对齐)
 * 注意：类的数据成员按其声明顺序加入内存，无访问权限无关，只看声明顺序。
 * 2.虚单继承，派生类继承基类vptr
 */

#include<iostream>

using namespace std;

class A
{
    public:
        char a;// 1->4
        int b;// 4
};

/**
 * @brief 此时B按照顺序：
 * char a	1->4
 * int b	4
 * short a	2->4
 * long b	4
 * 根据字节对齐4+4+4+4=16
 */
class B:A
{
    public:
        short a;
        long b;
};
class C
{
    A a;//8
    char c;//1->4
};
class A1
{
    virtual void fun(){}// vptr 8
};
class C1:public A
{// vptr 8
};

int main()
{
    cout<<sizeof(A)<<endl; // 8
    cout<<sizeof(B)<<endl; // 16
    cout<<sizeof(C)<<endl; // 12
    /**
     * @brief 对于虚单函数继承，派生类也继承了基类的vptr，所以是8字节
     */
    cout<<sizeof(C1)<<endl; // 8 
    return 0;
}
```

```cc
/**
 * @file virnhe.cpp
 * @brief 虚继承
 */

#include<iostream>
using namespace std;
class A
{
    virtual void fun() {}
};
class B
{
    virtual void fun2() {}
};
class C : virtual public  A, virtual public B
{
    public:
        virtual void fun3() {}
};

int main()
{
    /**
     * @brief 8 8 16  派生类虚继承多个虚函数，会继承所有虚函数的vptr
     */
    cout<<sizeof(A)<<" "<<sizeof(B)<<" "<<sizeof(C);

    return 0;
}
```

