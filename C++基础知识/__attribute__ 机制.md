\_\_attribute__ 机制

GNU C 的一大特色就是\_\_attribute__ 机制。\_\_attribute__ 可以设置函数属性（Function Attribute ）、变量属性（Variable Attribute ）和类型属性（Type Attribute ）。

\__attribute__ 书写特征是：\_\_attribute__ 前后都有两个下划线，并切后面会紧跟一对原括弧，括弧里面是相应的\_\_attribute__ 参数。

\__attribute__ 语法格式为：\_\_attribute__ ((attribute-list))

其位置约束为：放于声明的尾部“ ；” 之前。

### 类型属性（Type Attribute ）

关键字\__attribute__ 也可以对结构体（struct ）或共用体（union ）进行属性设置。大致有六个参数值可以被设定，即：aligned, packed, transparent_union, unused, deprecated 和 may_alias 。

**aligned (alignment)**

该属性设定一个指定大小的对齐格式（以字节 为单位）

aligned 属性使被设置的对象占用更多的空间

\__attribute__((aligned(m)))

\__attribute__ ((aligned))

**packed**

 使用该属性对struct 或者union 类型进行定义，设定其类型的每一个变量的内存约束。当用在enum 类型 定义时，暗示了应该使用最小完整的类型（it indicates that the smallest integral type should be used）。

使用packed 可以减小对象占用的空间。

\__attribute__ ((packed))

##### deprecated

作用：使编译会给出过时的警告。

用法：

\__attribute__ ((deprecated))

\__attribute__ ((deprecated(s)))

### 函数属性（Function Attribute）

函数属性可以帮助开发者把一些特性添加到函数声明中，从而可以使编译器在错误检查方面的功能更强大。\__attribute__机制也很容易同非GNU应用程序做到兼容之功效。

GNU CC需要使用 –Wall编译器来击活该功能，这是控制警告信息的一个很好的方式。下面介绍几个常见的属性参数。

##### format

该\__attribute__属性可以给被声明的函数加上类似printf或者scanf的特征，它可以使编译器检查函数声明和函数实际调用参数之间的格式化字符串是否匹配。该功能十分有用，尤其是处理一些很难发现的bug。

\_\_attribute\_\_((format(printf,m,n)))
\_\_attribute\_\_((format(scanf,m,n)))

format属性告诉编译器，按照printf, scanf, strftime或strfmon的参数表格式规则对该函数的参数进行检查。“archetype”指定是哪种风格；“string-index”指定传入函数的第几个参数是格式化字符串；“first-to-check”指定从函数的第几个参数开始按上述规则进行检查。

##### noreturn

该属性通知编译器函数从不返回值，当遇到类似函数需要返回值而却不可能运行到返回值处就已经退出来的情况，该属性可以避免出现错误信息。C库函数中的abort（）和exit（）的声明格式就采用了这种格式，如下所示：

extern void exit(int)   \_\_attribute\_\_((noreturn));

extern void abort(void)  \_\_attribute\_\_((noreturn));

##### const

该属性只能用于带有数值类型参数的函数上。当重复调用带有数值参数的函数时，由于返回值是相同的，所以此时编译器可以进行优化处理，除第一次需要运算外， 其它只需要返回第一次的结果就可以了，进而可以提高效率。该属性主要适用于没有静态状态（static state）和副作用的一些函数，并且返回值仅仅依赖输入的参数。

extern int square(int n)  \_\_attribute\_\_((const));

##### constructor与destructor

若函数被设定为constructor属性，则该函数会在main（）函数执行之前被自动的执行。类似的，若函数被设定为destructor属性，则该 函数会在main（）函数执行之后或者exit（）被调用后被自动的执行。拥有此类属性的函数经常隐式的用在程序的初始化数据方面。

作用：

**\__attribute__((constructor)) 在main函数之前执行,**

**\__attribute__((destructor)) 在main函数之后执行。**

```cpp
void __attribute__((constructor))  before() {
    printf("before main\n");
}
 
void __attribute__((destructor)) after() {
     printf("after main\n");
}

```

