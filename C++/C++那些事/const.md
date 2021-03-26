## const

### const作用

1. 定义常量

   const int a = 100;//常量表达式

   const double b = 2.0;//常量

   只有变量是枚举类型或者整数，并且以常量表达式初始化才是常量表达式。

2. 检查类型

   #define宏定义没有类型，const常量有类型，编译器可以进行安全检查

3. 防止修改

   限制函数参数不能修改

4. 可以节省空间

   从汇编角度来看，const常量只是给出地址，而不是像#define一样给出立即数，因此在运行时只有一份拷贝

### const对象默认为文件局部变量

非const默认为extern，可以不需要extern显示声明。

const想要在其他文件可见，需要加extern，并且需要初始化

因为常量在定义后不能被修改，所以定义时必须初始化

### const和指针

```cc
const char *a;// 常量指针，指向常量的指针
char *const a;// 指针常量，指针本身是常量
const char * const a;// 指针本身是常量，并且指向常量
```

如果*const*位于`*`的左侧，则const就是用来修饰指针所指向的变量，即指针指向为常量；

如果const位于`*`的右侧，*const*就是修饰指针本身，即指针本身是常量。

对于指向常量的指针，

1. 不能通过指针来修改对象的值。
2. 也不能使用void`*`指针保存const对象的地址，必须使用const void`*`类型的指针保存const对象的地址。
3. 允许把非const对象的地址赋值给const对象的指针，如果要修改指针所指向的对象值，必须通过其他方式修改，不能直接通过当前指针直接修改。

经验：const变成non-const不行，non-const可以变成const

### 函数中使用const

1. const修饰函数返回值

2. const修饰函数参数

   1. void fun(int *const var)// 指针本身不可变，无意义
   2. void fun(const char *dst)//参数指针所指内容为常量不可变
   3. void fun(const A &a)//提高效率，同时防止修改

3. const修饰成员函数

   1. 任何不会修改数据成员的成员函数都应该声明为const类型

   2. 只有常成员函数才有资格操作常量或常对象

   3. 类中的const成员变量必须通过初始化列表进行初始化

      还可以通过与static结合在类外定义，或者在定义处初始化

   4. const对象只能访问const成员函数,而非const对象可以访问任意的成员函数,包括const成员函数.

      

