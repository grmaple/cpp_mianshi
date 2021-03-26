```c++
#include<new>
char* buf = new char[sizeof(Complex)*3];//事先分配内存，调用默认构造函数
Complex* pc = new(buf)Complex(1,2);//不分配内存，调用有参构造函数
delete []buf;//只是new调用delete，定位new不用调用
```

placement new没有对应的delete，因为它根本没有分配内存。

```c++
Complex* pc = new(buf)Complex(1,2);
//编译器转为
Complex *pc;
try{
    void* mem = operator new(sizeof(Complex), buf);
    //和普通new不一样，多了个参数buf，返回buf
    pc = static_cast<Complex*>(mem);
    pc->Complex::Complex(1,2);
}
catch(std::bad_alloc){
    
}
void* operator new(size_t, void* loc){return loc};
```

placement new等同于调用构造函数

placement new或指new(p)或指::operator new(size_t, void*)