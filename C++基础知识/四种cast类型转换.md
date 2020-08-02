# 四种cast类型转换

### 1、const_cast

用于将const变量转为非const

这个转换类型操纵传递对象的const属性，或者是设置或者是移除

```cpp
class C {};

const C *a = new C;

C *b = const_cast<C *>(a);
```

其它三种操作符是不能修改一个对象的常量性的。
注意：'const_cast'也能改变一个类型的volatile qualifier。

### 2、static_cast

用于各种隐式转换，比如非const转const，void*转指针等, static_cast能用于多态向上转换，如果向下转换能成功但是不安全，结果未知；

```cpp
class C {};

const C *a = new C;

C *b = const_cast<C *>(a);
```

*其它三种操作符是不能修改一个对象的常量性的。
注意：'const_cast'也能改变一个类型的volatile qualifier。*

应用到类的指针上，意思是说它允许子类类型的指针转换为父类类型的指针（这是一个有效的隐式转换），同时，也能够执行相反动作：转换父类为它的子类，但是被转换的父类没有被检查是否与目的类型相一致。

'static_cast'除了操作类型指针，也能用于执行类型定义的显式的转换，以及基础类型之间的标准转换:

**向下转换：指的是基类向子类的转换**

### 3、dynamic_cast

用于动态类型转换。只能用于含有虚函数的类，用于类层次间的向上和向下转化。只用于对象的指针和引用。向下转化时，会进行检查，检查转换是否会返回一个被请求的有效的完整对象。检测在运行时进行。如果是非法的，对于指针返回NULL，对于引用抛*bad_cast*异常。

它通过判断在执行到该语句的时候变量的运行时类型和要转换的类型是否相同来判断是否能够进行向下转换。

```cpp
//向下转换
class Base { virtual dummy() {} };
class Derived : public Base {};

Base* b1 = new Derived;
Base* b2 = new Base;
//指针
Derived* d1 = dynamic_cast<Derived *>(b1);          // succeeds
Derived* d2 = dynamic_cast<Derived *>(b2);          // fails: returns 'NULL'
//引用
Derived d1 = dynamic_cast<Derived &*>(b1);          // succeeds
Derived d2 = dynamic_cast<Derived &*>(b2);          // fails: exception thrown
```



### 4、reinterpret_cast

就像传统的类型转换一样对待所有指针的类型转换。几乎什么都可以转，比如将int转指针，可能会出问题，尽量少用；

### 5、为什么不使用C的强制转换？

C的强制转换表面上看起来功能强大什么都能转，但是转化不够明确，不能进行错误检查，容易出错。

转换的含义是通过改变一个变量的类型为别的类型从而改变该变量的表示方式。为了类型转换一个简单对象为另一个对象你会使用传统的类型转换操作符。比如，为了转换一个类型为doubole的浮点数的指针到整型：i = (int) d;或者：i = int (d);对于具有标准定义转换的简单类型而言工作的很好。

### 6、四种强制转型形式

用于将const变量转为非const

dynamic_cast 主要用于执行“安全的向下转型（safe downcasting）”，也就是说，要确定一个对象是否是一个继承体系中的一个特定类型。它是唯一不能用旧风格语法执行的强制转型，也是唯一可能有重大运行时代价的强制转型。

static_cast 可以被用于强制隐型转换（例如，non-const 对象转型为 const 对象，int 转型为 double，等等），它还可以用于很多这样的转换的反向转换（例如，void\* 指针转型为有类型指针，基类指针转型为派生类指针），但是它不能将一个 const 对象转型为 non-const 对象（只有 const_cast 能做到），它最接近于C-style的转换。

const_cast 一般用于强制消除对象的常量性。它是唯一能做到这一点的 C++ 风格的强制转型。 

reinterpret_cast 是特意用于底层的强制转型，导致实现依赖（implementation-dependent）（就是说，不可移植）的结果，例如，将一个指针转型为一个整数。这样的强制转型在底层代码以外应该极为罕见。