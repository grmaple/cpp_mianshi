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



## const

常量在C++里的定义就是一个const加上对象类型，常量定义必须初始化。

对于局部对象，常量存放在栈区，

对于全局对象，常量存放在全局/静态存储区，编译期一般不分配内存，放在符号表中以提高访问效率，

对于字面值常量，比如字符串，常量存放在常量存储区。



### const修饰成员函数的目的

const修饰的成员函数表明函数调用不会对对象做出任何更改，事实上，如果确认不会对对象做更改，就应该为函数加上const限定，这样无论const对象还是普通对象都可以调用该函数。

### 以下四行代码的区别是什么？ 

const char * arr = "123";

//字符串123保存在常量区，const本来是修饰arr指向的值不能通过arr去修改，但是字符串“123”在常量区，本来就不能改变，所以加不加const效果都一样

char * brr = "123";

//字符串123保存在常量区，这个arr指针指向的是同一个位置，同样不能通过brr去修改"123"的值

const char crr[] = "123";

//这里123本来是在栈上的，但是编译器可能会做某些优化，将其放到常量区

char drr[] = "123";

//字符串123保存在栈区，可以通过drr去修改