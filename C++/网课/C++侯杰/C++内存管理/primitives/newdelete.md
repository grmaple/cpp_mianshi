new

分配内存然后调用构造函数

```c++
Complex* pc = new Complex(1,2);
// 编译器转化为
Complex  *pc;
try{
    //分配内存
    void* mem = operator new(sizeof(Compele));//如果Complex没有重载operator new()，则调用::operator new()
    //operator new()实际上不断调用malloc()
    pc = static_cast<Complex *>(mem);//转型
    //调用构造函数
    pc->Complex::Complex(1,2);//编译器才可以这样调用
}
catch(std::bad_alloc){
    //若allocation失败就不执行constructor
}
```

delete

先调用析构函数再释放内存

```c++
Complex *pc = new Complex(1,2);
...
delete pc;
// 编译器转为
pc->~Complex();//析构，可以直接调用
operator delete(pc);//释放内存，内部调用free()
```



构造函数不能被直接调用，析构函数可以被直接调用

