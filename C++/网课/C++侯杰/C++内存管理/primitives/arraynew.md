```c++
Complex *pca = new Complex[3];
// 调用三次ctor，无法由参数给予初值，调用默认构造函数
delete[] pca;//注意不要漏了[]，否则只调用一次dtor
// 对没有指针成员的类可能没有影响，因为其dtor是不重要的
// 对带有指针成员的类通常有影响
string* psa = new string[3];//调用三次ctor，申请了三块内存
delete psa;//只调用一次dtor，三块内存只释放了一块，内存泄露
```

没有办法直接调用构造函数设初值，但是可以通过定位new来设置

```c++
class A{
public:
    int id;
    A():id(0){}
    A(int i):id(i){}
    ~A(){}
};
A* buf = new A[3];//先[0]再[1]再[2]
A *tmp = buf;
for(int i = 0; i<3; ++i) new(tmp++)A(i);
// 在tmp这个位置上有一块内存，在其上创建对象
delete []buf;//先[2]再[1]再[0]，次序颠倒
```



内存布局

![image-20210228153956636](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20210228153956636.png)

```c++
int *pi = new int[10];
delete pi;//基本类型，加不加[]无所谓，因为其析构函数没意义
```

分配内存时，不止分配了对象，还分配了cookie