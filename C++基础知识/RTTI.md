## RTTI

*RTTI*是”Runtime Type Information”的缩写,意思是运行时类型信息,它提供了运行时确定对象类型的方法。

运行时类型检查，在C++层面主要体现在dynamic_cast和typeid,VS中虚函数表的-1位置存放了指向type_info的指针。

对于存在虚函数的类型，typeid和dynamic_cast都会去查询type_info

它使程序能够获取由基指针或引用所指向的对象的实际派生类型，即允许“用指向基类的指针或引用来操作对象”的程序能够获取到“这些指针或引用所指对象”的实际派生类型。

### typeid关键字

运行时获知变量类型名称，等同于sizeof这类的操作符。

typeid操作符的返回结果是名为type_info的标准库类型的对象的引用。可以使用 typeid(变量).name()

cout << typeid(a).name() << endl;

需要注意不是所有编译器都输出”int”、”float”等之类的名称。

cout<<abi::__cxa_demangle(typeid(a).name(),0,0,0 )<<endl;

int ia = 3;
if(typeid(ia) == typeid(int))
{
    cout <<"int" <<endl;
}

typeid操作符的作用就是获取一个表达式的类型。返回结果是const type_info&。不同编译器实现的type_info class各不相同。但c++标准保证它会实现一个name()方法，该方法返回类型名字的c-style字符串。

**1.使用type_info类中的name()函数返回对象的类型名称；**

如果typeid的操作数不是类类型或者是没有虚函数的类，则typeid指出该操作数的静态类型。如果操作数是定义了至少一个虚函数的类类型，则在运行时计算类型。

```cpp
#include <iostream>
#include <typeinfo>
using namespace std;
  
class A
{
public:
     void Print() { cout<<"This is class A."<<endl; }
};
  
class B : public A
{
public:
     void Print() { cout<<"This is class B."<<endl; }
};
  
int main()
{
     A *pA = new B();
     cout<<typeid(pA).name()<<endl; // class A *
     //当类中不存在虚函数时，typeid是编译时期的事情，也就是静态类型
     cout<<typeid(*pA).name()<<endl; // class A
     return 0;
}
```

明明pA实际指向的是B，为什么得到的却是class A呢？

```cpp
#include <iostream>
#include <typeinfo>
using namespace std;
  
class A
{
public:
     virtual void Print() { cout<<"This is class A."<<endl; }
};
  
class B : public A
{
public:
     void Print() { cout<<"This is class B."<<endl; }
};
  
int main()
{
	 A *pA = new B();
     cout<<typeid(pA).name()<<endl; // class A *
     //*当类中存在虚函数时，typeid是运行时期的事情，也就是动态类型
     cout<<typeid(*pA).name()<<endl; // class B
     return 0;
}
```

当Print函数变成了虚函数，输出结果就不一样了，这说明什么？这就是RTTI在捣鬼了

当类中不存在虚函数时，typeid是编译时期的事情，也就是静态类型，就如上面的cout<<typeid(*pA).name()<<endl;输出class A一样；*

*当类中存在虚函数时，typeid是运行时期的事情，也就是动态类型，就如上面的cout<<typeid(*pA).name()<<endl;输出class B一样，

**2.使用type_info类中重载的==和!=比较两个对象的类型是否相等**

这个会经常用到，通常用于比较两个带有虚函数的类的对象是否相等

```cpp
#include <iostream>
#include <typeinfo>
using namespace std;
  
class A
{
public:
     virtual void Print() { cout<<"This is class A."<<endl; }
};
  
class B : public A
{
public:
     void Print() { cout<<"This is class B."<<endl; }
};
  
class C : public A
{
public:
     void Print() { cout<<"This is class C."<<endl; }
};
  
void Handle(A *a)
{
     if (typeid(*a) == typeid(A))
     {
          cout<<"I am a A truly."<<endl;
     }
     else if (typeid(*a) == typeid(B))//dynamic_cast<B*>(a)
     {
          cout<<"I am a B truly."<<endl;
     }
     else if (typeid(*a) == typeid(C))//dynamic_cast<C*>(a)
     {
          cout<<"I am a C truly."<<endl;
     }
     else
     {
          cout<<"I am alone."<<endl;
     }
}
  
int main()
{
     A *pA = new B();
     Handle(pA);
     delete pA;
     pA = new C();
     Handle(pA);
     return 0;
}
/*
这里输出的结果为：
I am a B truly.
I am a C truly.
*/
```



### dynamic_cast

强制类型转换的一种

允许运行时刻进行类型转换，从而使程序能够在一个类层次结构中安全地转化类型，与之相对应的还有一个非安全的转换操作符static_cast。

向下转化时，会进行检查，检查转换是否会返回一个被请求的有效的完整对象。检测在运行时进行。如果是非法的，对于指针返回NULL，对于引用抛*bad_cast*异常。

当类中存在虚函数时，编译器就会在类的成员变量中添加一个指向虚函数表的vptr指针，每一个class所关联的type_info object也经由virtual table被指出来，通常这个type_info object放在表格的第一个slot。当我们进行dynamic_cast时，编译器会帮我们进行语法检查。如果指针的静态类型和目标类型相同，那么就什么事情都不做；否则，首先对指针进行调整，使得它指向vftable，并将其和调整之后的指针、调整的偏移量、静态类型以及目标类型传递给内部函数。其中最后一个参数指明转换的是指针还是引用。**两者唯一的区别是，如果转换失败，前者返回NULL，后者抛出bad_cast异常**。