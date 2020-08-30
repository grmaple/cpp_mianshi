## non-explicit-one-argument ctor

### non-explicit-one-argument ctor

non-explicit 就是没有加explicit 关键字的。

实参是一个的情况。这是one-argument，不是two parameter。

```cpp
class Fraction {
public:
    //这是两个参数，但是只要一个实参就够了。
    Fraction(int num, int den = 1)
        :m_numerator(num),m_denominator(den) {}
    Fraction operator + (const Fraction& f) {
        return Fraction(...);
    }
private:
    int m_numerator;
    int m_denominator;
};
int main() {
    Fraction f(3,5);
    Fraction d2 = f + 4;//调用non-explicit ctor将4转换为Fraction(4,1),然后调用operator +
}
```

编译器先看看有没有对+进行重载的函数，看到了operator +，这个+作用于f，发现需要右部是一个Fraction对象。因此编译器看看能不能将4转换成Fraction对象。发现Fraction有一个non-explicit-one-argument ctor，因此可以转换成Fraction对象。

所以，non-explicit-one-argument ctor就可以把某种类型转换成Fraction对象



### conversion function vs. non-explicit-one-argument ctor

```cpp
class Fraction {
public:
    //non-explicit-one-argument ctor
    Fraction(int num, int den = 1)
        :m_numerator(num),m_denominator(den) {}
    //conversion function
    operator double() const {
        return (double)(m_numerator / m_denominator);
    }
    Fraction operator + (const Fraction& f) {
        return Fraction(...);
    }
private:
    int m_numerator;
    int m_denominator;
};
int main() {
    Fraction f(3,5);
    Fraction d2 = f + 4;//[Error]ambiguous
}
```

如果两个函数并存呢？那编译器就会因为不知道调用哪个而出错。

ambiguous二义

多于一条路线可行，编译器就不知道走哪条路了。

### explicit-one-argument ctor

明确的，告诉编译器，不用自动帮我做事情了。

explicit 说明这个ctor就是构造函数，不要把4变成f(4)当作4/1

```cpp
class Fraction {
public:
    //explicit-one-argument ctor
    explicit Fraction(int num, int den = 1)
        :m_numerator(num),m_denominator(den) {}
    //conversion function
    operator double() const {
        return (double)(m_numerator / m_denominator);
    }
    Fraction operator + (const Fraction& f) {
        return Fraction(...);
    }
private:
    int m_numerator;
    int m_denominator;
};
int main() {
    Fraction f(3,5);
    Fraction d2 = f + 4;//[Error]conversion from 'double' to 'Fraction'requested.
}
```

explicit一般都是用在声明构造函数。

### conversion function转换函数

看看标准库里面的转换函数

![image-20200830130039869](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200830130039869.png)

template\<class Alloc>
class vector<bool, Alloc>{};

模板的偏特化

模板分为类模板与函数模板，特化分为全特化与偏特化，函数模板只有全特化。

全特化就是限定死模板实现的具体类型，偏特化就是如果这个模板有多个类型，那么只限定其中的一部分。

我们看reference operator[]函数，应该返回bool值，但是返回的是reference，reference 是__bit——reference的别名。这种手法叫代理proxy。

代理模式（Proxy Pattern）一个类代表另一个类的功能。这种类型的设计模式属于结构型模式。 在代理模式中，我们创建具有现有对象的对象，以便向外界提供功能接口。

应该返回bool值，却返回的是reference。我们认为reference内有转换函数。果不其然有转换函数

 operator bool() const {return !(!(*p & mask));}