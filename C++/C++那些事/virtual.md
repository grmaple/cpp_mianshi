## virtual

虚函数的调用取决于指向或引用的对象的类型，而不是指针或引用自身的类型。

### 虚函数和默认参数

默认参数是静态绑定的，而虚函数是动态绑定的。

默认参数的使用需要看指针或引用本身的类型，而不是对象的类型。

```cc
/**
 * @file first_example.cpp
 * @brief 虚函数中默认参数
 * 规则：虚函数是动态绑定的，默认参数是静态绑定的。默认参数的使用需要看指针或者应用本身的类型，而不是对象的类型！
 */

#include <iostream> 
using namespace std; 

class Base 
{ 
    public: 
        virtual void fun ( int x = 10 ) 
        { 
            cout << "Base::fun(), x = " << x << endl; 
        } 
}; 

class Derived : public Base 
{ 
    public: 
        virtual void fun ( int x=20 ) 
        { 
            cout << "Derived::fun(), x = " << x << endl; 
        } 
}; 


int main() 
{ 
    Derived d1; 
    Base *bp = &d1; 
    bp->fun();  // 10
    return 0; 
} 
```

### 静态函数可以声明为虚函数吗？

**静态函数不可以声明为虚函数，同时也不能被const 和 volatile关键字修饰**

static成员函数不属于任何类对象或类实例，所以即使给此函数加上virutal也是没有任何意义

虚函数依靠vptr指针来处理。vptr是一个指针，在类的构造函数中创建生成，并且只能用this指针来访问它，**静态成员函数没有this指针**，所以无法访问vptr。

### 构造函数可以是虚函数吗？

构造函数不能声明为虚函数，并且除了inline或explicit之外不允许使用其他的关键字。

经过vtable在编译期就生成，但是vptr是在运行期实例化对象时才产生的。如果类中有虚函数，就会在构造函数中创建vptr。

如果构造函数是虚的，它需要vptr访问vtable，而这时候vptr还没产生，因此构造函数不能是虚函数。

### 析构函数可以是虚函数吗?

析构函数可以声明为虚函数。如果我们需要删除一个指向派生类的基类指针时，我们应该把析构函数声明为虚函数。事实上，只要一个类是基类，就应该声明虚析构函数。

### 虚函数可以是私有函数吗?

可以。

int main()必须声明为Base类的友元，否则编译失败。 编译器报错： ptr无法访问私有函数。 

当然，把基类声明为public， 继承类为private，该问题就不存在了。

### 虚函数可以被内联吗？

通常类成员函数都会被编译器考虑是否进行内联。 

但通过基类指针或者引用调用的虚函数必定不能被内联。 (多态性)

当然，实体对象调用虚函数或者静态调用时可以被内联，虚析构函数的静态调用也一定会被内联展开。

### RTTI与dynamic_cast

RTTI（Run-Time Type Identification)，通过**运行时类型信息**程序能够使用**基类的指针或引用**来检查这些指针或引用所指的对象的**实际派生类型**。

在面向对象程序设计中，有时我们需要在运行时查询一个对象是否能作为某种多态类型使用。C++提供了dynamic_cast函数用于动态转型。

相比C风格的强制类型转换和C++ reinterpret_cast，dynamic_cast提供了类型安全检查，是一种基于能力查询(Capability Query)的转换，所以在多态类型间进行转换更提倡采用dynamic_cast。

### 纯虚函数和抽象类

纯虚函数：没有函数体的虚函数

抽象类：包含纯虚函数的类

抽象类只能作为基类派生新类使用，不能创建抽象类的对象

如果我们不在派生类中覆盖所有纯虚函数，那么派生类也会变成抽象类

抽象类可以有构造函数，子类继承时构造函数调用。

