# CRTP奇异的递归模板模式

https://zhuanlan.zhihu.com/p/136258767

**什么是CRTP？**

简单来说，CRTP有两大特性：

1. 继承自模板类。
2. 派生类将自身作为参数传给模板类。

翻译成代码，长这样：

```c++
// 我们先定义一个模板类作为基类
template <typename T>
class Base
{
    ...
};
 // 定义一个派生类，这个类继承以自身作为参数的基类
class Derived : public Base<Derived>
{
    ...
};
```

**问题来了，为什么要这样做呢？**

这样做的目的其实很明确，从基类对象的角度来看，派生类对象其实就是本身，这样的话只需要用一个static_cast就可以把基类转化成派生类，从而实现基类对象对派生对象的访问。

我们还是来看看代码：

```cpp
template <typename T>
class Base
{
public:
    void doSomething()
    {
        T& derived = static_cast<T&>(*this);
    }
};

class Derived : public Base<Derived>
{
public:
    void doSomething()
    {
         std::cout << " Derived class " << std::endl;
    }  
};
```

很多小伙伴可能发现了，这里将基类转换成派生类用的是static_cast*静态绑定，而普通基类转派生类用的是*dynamic_cast动态绑定。动态绑定的目的是为了确保你所转化的派生类是正确的，而对于CRTP来说，基类是继承于模板类的参数，也就是派生类本身。这也正是CRTP这种设计的目的。

**CRTP的优点是什么呢？**

多态是个很好的特性，但是动态绑定比较慢，因为要查虚函数表。而使用 CRTP，完全消除了动态绑定，降低了继承带来的虚函数表查询开销。

### c++ 中CRTP的用途

https://zhuanlan.zhihu.com/p/137879448

1. **静态多态（Static polymorphism）。**

下面通过一个例子来进行说明。

```cpp
template <class T> 
struct Base
{
    void interface()
    {
        // ...
        static_cast<T*>(this)->implementation();
        // ...
    }

    static void static_func()
    {
        // ...
        T::static_sub_func();
        // ...
    }
};

struct Derived : Base<Derived>
{
    void implementation()；

    static void static_sub_func();
};
```

以`Base<Derived>::interface()` 为例，在`Derived : Base<Derived>`中，`Base<Derived>`是先于`Derived`而存在的，所以当`Base<Derived>::interface()`被申明时，编译器并不知道`Derived`的存在的，但由于此时` Base<Derived>::interface()` 并不会被实例化。只有当`Base<Derived>::interface()`被调用时，才会被实例化，而此时编译器也已经知道了 `Derived::implementation()`的声明了。

这里等同于通过查询虚函数动态绑定以达到多态的效果，但省略了动态绑定虚函数查询的时间。

**2. 轻松地实现各个子类实例创建和析构独立的计数。**

```cpp
template <typename T>
struct counter
{
    static int objects_created;
    static int objects_alive;

    counter()
    {
        ++objects_created;
        ++objects_alive;
    }
    
    counter(const counter&)
    {
        ++objects_created;
        ++objects_alive;
    }
protected:
    ~counter() // objects should never be removed through pointers of this type
    {
        --objects_alive;
    }
};
template <typename T> int counter<T>::objects_created( 0 );
template <typename T> int counter<T>::objects_alive( 0 );

class X : counter<X>
{
    // ...
};

class Y : counter<Y>
{
    // ...
};
```

每次X或者Y实例化时，`counter<X>`或者` counter<Y>`就会被调用，对应的就会增加对创建对象的计数。同样，每次X或者Y悉构后，对应的减少`objects_alive`。这里最重要的是实现了对不同子类单独的计数。

**3. 多态链（Polymorphic chaining）。**

还是通过一个具体的例子来对此进行说明。

```cpp
class Printer
{
public:
    Printer(ostream& pstream) : m_stream(pstream) {}
 
    template <typename T>
    Printer& print(T&& t) { m_stream << t; return *this; }
 
    template <typename T>
    Printer& println(T&& t) { m_stream << t << endl; return *this; }
private:
    ostream& m_stream;
};

class CoutPrinter : public Printer
{
public:
    CoutPrinter() : Printer(cout) {}

    CoutPrinter& SetConsoleColor(Color c)
    {
        // ...
        return *this;
    }
};
```

上面Printer定义打印的方法，`CoutPrinter`是`Printer`的子类，并且添加了一个设置打印颜色的方法。接下来我们看看下面这行代码：

```cpp
CoutPrinter().print("Hello ").SetConsoleColor(Color.red).println("Printer!");
```

前半段`CoutPrinter().print("Hello ")`调用的是`Printer`实例，后面接着`SetConsoleColor(Color.red)`实际上又需要调用`CoutPrinter`实例，这样编译器就会报错。

而CRTP就可以很好的解决这个问题，代码如下：

```cpp
// Base class
template <typename ConcretePrinter>
class Printer
{
public:
    Printer(ostream& pstream) : m_stream(pstream) {}
 
    template <typename T>
    ConcretePrinter& print(T&& t)
    {
        m_stream << t;
        return static_cast<ConcretePrinter&>(*this);
    }
 
    template <typename T>
    ConcretePrinter& println(T&& t)
    {
        m_stream << t << endl;
        return static_cast<ConcretePrinter&>(*this);
    }
private:
    ostream& m_stream;
};
 
// Derived class
class CoutPrinter : public Printer<CoutPrinter>
{
public:
    CoutPrinter() : Printer(cout) {}
 
    CoutPrinter& SetConsoleColor(Color c)
    {
        // ...
        return *this;
    }
};
 
// usage
CoutPrinter().print("Hello ").SetConsoleColor(Color.red).println("Printer!");
```

**4. 多态的复制构造体（Polymorphic copy construction）。**

当我们用到多态时，经常会需要通过基类的指针来复制子对象。通常我们可以通过在基类里面构造一个`clone()`虚函数，然后在每个子类里面定义这个`clone()`函数。使用CRTP可以让我们避免反复地在子类中去定义`clone()`函数。

```cpp
// Base class has a pure virtual function for cloning
class AbstractShape {
public:
    virtual ~AbstractShape () = default;
    virtual std::unique_ptr<AbstractShape> clone() const = 0;
};

// This CRTP class implements clone() for Derived
template <typename Derived>
class Shape : public AbstractShape {
public:
    std::unique_ptr<AbstractShape> clone() const override {
        return std::make_unique<Derived>(static_cast<Derived const&>(*this));
    }

protected:
   // We make clear Shape class needs to be inherited
   Shape() = default;
   Shape(const Shape&) = default;
};

// Every derived class inherits from CRTP class instead of abstract class

class Square : public Shape<Square>{};

class Circle : public Shape<Circle>{};
```