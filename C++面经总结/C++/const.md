**const作用: “只读”**

**1.定义常量**

(1)const修饰变量，以下两种定义形式在本质上是一样的。它的含义是：const修饰的类型为TYPE的变量value是不可变的。

TYPE const ValueName = value;

const TYPE ValueName = value;

**2.指针使用const**

(1)指针本身是常量不可变

char * const pContent;

const (char*) pContent;

(2)指针所指向的内容是常量不可变

const char *pContent;

char const *pContent;

(3)两者都不可变

const char* const pContent;

**3.函数中使用const**

(1)const修饰函数参数

a.传递过来的参数在函数内不可以改变(无意义，因为Var本身就是形参)

void function(const int Var);

b.参数指针所指内容为常量不可变

void function(const char* Var);

c.参数指针本身为常量不可变(也无意义，因为char* Var也是形参)

void function(char* const Var);

d.参数为引用，为了增加效率同时防止修改。修饰引用参数时：

void function(const Class& Var); //引用参数在函数内不可以改变

void function(const TYPE& Var); //引用参数在函数内为常量不可变

这样的一个const引用传递和最普通的函数按值传递的效果是一模一样的,他禁止对引用的对象的一切修改,唯一不同的是按值传递会先建立一个类对象的副本, 然后传递过去,而它直接传递地址,所以这种传递比按值传递更有效.另外只有引用的const传递可以传递一个临时对象,因为临时对象都是const属性, 且是不可见的,他短时间存在一个局部域中,所以不能使用指针,只有引用的const传递能够捕捉到这个家伙.

(2)const 修饰函数返回值

const修饰函数返回值其实用的并不是很多，它的含义和const修饰普通变量以及指针的含义基本相同。

a. const int fun1() //这个其实无意义，因为参数返回本身就是赋值。

b. const int * fun2() //调用时

const int *pValue = fun2(); //我们可以把fun2()看作成一个变量，即指针内容不可变。

c. int* const fun3() //调用时

int * const pValue = fun2(); //我们可以把fun2()看作成一个变量，即指针本身不可变。