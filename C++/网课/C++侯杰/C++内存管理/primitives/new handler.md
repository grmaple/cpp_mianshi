当operator没有能力为你分配出你所申请的memory，它会抛出一个std::bad_alloc 异常。有的编译器会返回0，下面是一定返回0不抛出异常

new(nothrow) Foo;nothrow形式

抛出异常之前会先（不止一次）调用一个可由client指定的handler

```c
typedef void(*new_handler)();
new_handler set_new_handler(new_handler p)throw();
```

设计良好的new handler只有两个选择

让更多的memory可用，或者调用abort()/exit()

```c++
void* operator new(size_t size, const std::nothrow_t&)_THROW0(){
    void *p;
    while((p=malloc(size))==0){
        _TRY_BEGIN
            if(_callnewh(size) == 0) break;
        _CATCH(std::bad_alloc) return(0);
        _CATCH_END
    }
    return(p);
}
```

```c++
void noMoreMemory(){
    cerr<<"out of memory";
    abort();
}
set_new_handler(noMoreMemory);
```

=default，调用默认版本

=delete，删除函数

```c++
class Foo{
public:
    Foo()=default;
    Foo(const Foo&)=delete;
    Foo& operator(const Foo&)=delete;
    ~Foo()=default;
}
```

也适用于operator new/delete

其实只能=delete

