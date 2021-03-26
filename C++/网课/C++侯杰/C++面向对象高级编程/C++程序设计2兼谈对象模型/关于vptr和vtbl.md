## 关于vptr和vtbl

```cpp
class A {
public:
    virtual void vfunc1();
    virtual void vfunc2();
    void func1();
    void func2();
private:
    int m_data1, m_data2;
};

class B : public A {
public:
    virtual void vfunc1();
    void func2();
private:
    int m_data3;
};

class C : public B {
public:
    virtual void vfunc1();
    void func2();
private:
    int m_data1, m_data4;
};
```

![image-20200831104206814](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200831104206814.png)

只要你的类有虚函数，对象内就会多一个指针vptr。

子类有父类的数据，函数的调用权(不是内存大小)。

父类有虚函数，那么子类也会有虚函数。

vptr虚指针指向vtbl虚表，vtbl里面放的都是虚函数的函数指针。

静态绑定：C的调用函数，编译器看到调用动作，编译器编译成一个特定语法call，编译器会跳到哪个地方，将来再return回来。

动态绑定：通过指针调用虚函数。这就是面向对象的关键点。通过指针找到vptr，然后找到vtbl，然后找到对应函数。

通过内存地址进行函数调用，将动态绑定写成C语法，虚机制

C* p = new C;//得到指向C首地址的p指针，可以向上转型

(*(p->vptr)[0])(p);//通过p调用vfunc1虚函数

有个叫A的父类表示形状类，其下面有各种形状的子类。

现在写一个容器 list<A*> myLst;

容器因为放的是大小相同的元素。所以不能放类，而是放类指针。

现在想重画性质draw()，这个draw()是虚函数，各个形状有自己的draw()

虚函数能做到，指针指向什么类型，就调用那种类型的draw()

虚函数这种用法，就是多态。

list<A*> myLst;

A* pb = new B;(*(p->vptr)[0])(p);//调用B::draw()

A* pc = new C;(*(p->vptr)[0])(p);//调用C::draw()

myLst.push_back(pb);

myLst.push_back(pc);

同样是A*，但是实际上指向了不同的东西(B/C)，不过这些东西都必须是以A为基础的。我们说指针有很多类型，很多形态。这就是多态。