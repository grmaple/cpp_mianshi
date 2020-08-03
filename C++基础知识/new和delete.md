## new/delete

### new

##### 1．new() 

分配这种类型的一个大小的内存空间,并以括号中的值来初始化这个变量;

##### 2．new[] 

分配这种类型的n个大小的内存空间,并用默认构造函数来初始化这些变量;

char* p=new char[6];

//p="Hello";不能将字符串直接赋值，指针p指向的是字符串的第一个字符

strcpy(p,"Hello");

##### 3．开辟单变量地址空间

1)new int; //开辟一个存放数组的存储空间,返回一个指向该存储空间的地址.int *a = new int 即为将一个int类型的地址赋值给整型指针a.

2)int *a = new int(5) 作用同上,但是同时将整数赋值为5

##### 4．开辟数组空间

一维: int *a = new int[100];开辟一个大小为100的整型数组空间

二维: int **a = new int\[5][6]

三维及其以上:依此类推.

一般用法: new 类型 [初值]

##### 6．new运算符

最常用的是作为运算符的new，比如：

string *str = new string(“test new”);

作为运算符，new和sizeof一样，是C 内置的，你不能对它做任何的改变，除了使用它。

new会在堆上分配一块内存，并会自动调用类的构造函数。

### delete

##### 1.回收new分配的单个对象的内存空间的时候用delete，

int *a = new int;

delete a; //释放单个int的空间

##### 2.回收new[ ]分配的一组对象的内存空间的时候用 delete[ ];

int *a = new int[5];

delete [] a; //释放int数组空间



基本类型的对象没有析构函数，所以回收基本类型组成的数组空间用 delete 和 delete[] 都是应该可以的；

但是对于类对象数组，只能用 delete[]。

对于 new 的单个对象，只能用 delete 不能用 delete[] 回收空间。

 **所以一个简单的使用原则就是：new 和 delete、new[] 和 delete[] 对应使用。**

### new/delete与malloc/free的区别

new/delete是C++的关键字，

而malloc/free是C语言的库函数，

后者使用必须指明申请内存空间的大小，

对于类类型的对象，后者不会调用构造函数和析构函数

