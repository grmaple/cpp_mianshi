# extern

### 基本解释

extern可以置于变量或者函数前，以标示变量或者函数的定义在别的文件中，提示编译器遇到此变量和函数时在其他模块中寻找其定义。此外extern也可用来进行链接指定。

### 作用

##### 第一,

当它与"C"一起连用时，如: extern "C" void fun(int a, int b);则告诉编译器在编译fun这个函数名时按着C的规则去翻译相应的函数名而不是C++的，C++的规则在翻译这个函数名时会把fun这个名字变得面目全非，可能是fun@aBc_int_int#%$也可能是别的，这要看编译器的"脾气"了(不同的编译器采用的方法不一样)，为什么这么做呢，因为C++支持函数的重载。

**extern “C”**

在C++环境下使用C函数的时候，常常会出现编译器无法找到obj模块中的C函数定义，从而导致链接失败的情况，应该如何解决这种情况呢？
C++语言在编译的时候为了解决函数的多态问题，会将函数名和参数联合起来生成一个中间的函数名称，而C语言则不会，因此会造成链接时找不到对应函数的情况，此时C函数就需要用extern “C”进行链接指定，这告诉编译器，请保持我的名称，不要给我生成用于链接的中间函数名。

下面是一个标准的写法：
//在.h文件的头上

```C++
#ifdef __cplusplus
#if __cplusplus
extern "C"{
　#endif
　#endif /* __cplusplus */ 
　…
　…
　//.h文件结束的地方
　#ifdef __cplusplus
　#if __cplusplus
}
#endif
#endif /* __cplusplus */ 
```



#####  第二，

当extern不与"C"在一起修饰变量或函数时，如在头文件中: extern int g_Int; 它的作用就是声明函数或全局变量的作用范围的关键字，其声明的函数和变量可以在本模块或其他模块中使用，**记住它是一个声明不是定义**!也就是说B模块(编译单元)要是引用模块(编译单元)A中定义的全局变量或函数时，它只要包含A模块的头文件即可,在编译阶段，模块B虽然找不到该函数或变量，但它不会报错，它会在连接时从模块A生成的目标代码中找到此函数。用extern关键字告诉编译器，这个变量我在后面定义了，先别急着报错。

extern用在变量声明中常常有这样一个作用，你在\*.c文件中声明了一个全局的变量，这个全局的变量如果要被引用，就放在\*.h中并用extern来声明。

常常见extern放在函数的前面成为函数声明的一部分，那么，C语言的关键字extern在函数的声明中起什么作用

如果函数的声明中带有关键字extern，仅仅是暗示这个函数可能在别的源文件里定义，没有其它作用。

**例子1**

  (1) 在test1.h中有下列声明:
  \#ifndef TEST1H
  \#define TEST1H
  extern char g_str[]; // 声明全局变量g_str
  void fun1();
  \#endif
  (2) 在test1.cpp中
  \#include "test1.h"
    char g_str[] = "123456"; // 定义全局变量g_str
    void fun1() { cout << g_str << endl; }
  (3) 以上是test1模块， 它的编译和连接都可以通过,如果我们还有test2模块也想使用g_str,只需要在原文件中引用就可以了
  \#include "test1.h"

   void fun2()  { cout << g_str << endl;  }
  以上test1和test2可以同时编译连接通过，如果你感兴趣的话可以用ultraEdit打开test1.obj,你可以在里面找到"123456"这个字符串,但是你却不能在test2.obj里面找到，这是因为g_str是整个工程的全局变量，在内存中只存在一份,test2.obj这个编译单元不需要再有一份了，不然会在连接时报告重复定义这个错误!

**例子2**.在*.h文件把全局变量的声明和定义放在一起

  (1) 在test1.h中有下列声明:
  \#ifndef TEST1H
  \#define TEST1H
   extern char g_str[] = "123456"; // 这个时候相当于没有extern
  void fun1();
  \#endif
  (2) 在test1.cpp中
  \#include "test1.h"
    void fun1() { cout << g_str << endl; }
  (3) 以上是test1模块， 它的编译和连接都可以通过,如果我们还有test2模块也想使用g_str,那么就把test2的代码中#include "test1.h"去掉 换成:
  extern char g_str[];
  void fun2()  { cout << g_str << endl;  }

但是我想说这样做非常糟糕，因为你由于无法在test2.cpp中使用#include "test1.h",那么test1.h中声明的其他函数你也无法使用了，除非也用都用extern修饰，这样的话你光声明的函数就要一大串，而且头文件的作用就是要给外部提供接口使用的，所以 请记住，  **只在头文件中做声明，真理总是这么简单**。

###  extern 和 static

 (1) extern 表明该变量在别的地方已经定义过了,在这里要使用那个变量.
 (2) static 表示静态的变量，分配内存的时候, 存储在静态区,不存储在栈上面.

  static 作用范围是内部连接的关系, 和extern有点相反.它和对象本身是分开存储的,extern也是分开存储的,但是extern可以被其他的对象用extern 引用,而static 不可以,只允许对象本身用它. 具体差别首先，static与extern是一对“水火不容”的家伙，也就是说extern和static不能同时修饰一个变量；其次，static修饰的全局变量声明与定义同时进行，也就是说当你在头文件中使用static声明了全局变量后，它也同时被定义了；最后，static修饰全局变量的作用域只能是本身的编译单元，也就是说它的“全局”只对本编译单元有效，其他编译单元则看不到它

正是因为static有以上的特性，所以一般**定义static全局变量时，都把它放在原文件中而不是头文件**，这样就不会给其他模块造成不必要的信息污染，同样记住这个原则吧！

### extern 和const

  C++中const修饰的全局常量据有跟static相同的特性，即它们只能作用于本编译模块中，但是const可以与extern连用来声明该常量可以作用于其他编译模块中, 如extern const char g_str[];
  然后在原文件中别忘了定义:   const char g_str[] = "123456"; 

  所以当const单独使用时它就与static相同，而当与extern一起合作的时候，它的特性就跟extern的一样了！所以对const我没有什么可以过多的描述，我只是想提醒你，const char* g_str = "123456" 与 const char g_str[] ="123465"是不同的， 前面那个const 修饰的是char \*而不是g_str,它的g_str并不是常量，它被看做是一个定义了的全局变量（可以被其他编译单元使用）， 所以如果你像让char\*g_str遵守const的全局常量的规则，最好这么定义const char* const g_str="123456".

const char* g_str = "123456" 

const 修饰的是char \*，g_str不是常量

const char g_str[] ="123465" 

const 修饰的是 g_str，g_str是常量

const char* const g_str="123456"  

第一个const 修饰的是char \*，第二个修饰的是 g_str，g_str是常量

 

