当你受困于必须为不同class重写一遍近乎相同的成员成员operator new/delete时，应该有方法将一个总是分配特定尺寸的区间的memory allocator概念包装起来，使之容易被重复使用。

每个allocator object 是一个分配器，它体内维护了一个freelist。

```c++
class allocator{
private:
    struct obj{
        struct obj* next;
    }
public:
    void* allocate(size_t);
    void deallocate(void*, size_t);
private:
    obj* freeStore = nullptr;
    const int CHUNK = 5;
};
void* allocator::allocate(size_t size){
    obj *p;
    if(!freeStore){
        //linkedlist为空，于是申请一大块
        size_t chunk = CHUNK * size;
        freeStore = p = (obj*)malloc(chunk);
        // 将分配的来的一大块当作linkedlist
        // 小块小块串接起来
        for(int i = 0; i<(CHUNK-1); ++i){
            p->next = (obj*)((char*)p+size);
            p = p->next;
        }
        p->next = nullptr;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}
void allocator::deallocate(void* p, size_t size){
    //将*p收回插入freelist前端
    ((obj*)p)->next = freeStore;
    freeStore = (obj*)p;
}
```



```c++
class Foo{
public:
    long L;
    string str;
    static allocator myAlloc;
public:
    Foo(long l):L(l){}
    static void* operator new(size_t size){
        return myAlloc.allocate(size);
    }
    static void operator delete(void* pdead, size_t size){
        return myAlloc.deallocate(pdead,size);
    }
};
allocator Foo::myAlloc;
```

这个比之前的设计干净多了。所有细节都让allocator去处理。



macro for static allocator

```c++
#define DECLARE_POOL_ALLOC() \
public:\
void* operator new(size_t size){return myAlloc.allocate(size);}\
void operator delete(void* pdead, size_t size){return myAlloc.deallocate(pdead,size);}\
protected:\
static allocator myAlloc;
#define IMPLEMENT_POOL_ALLOC(class_name) \
allocator class_name::myAlloc;

class Foo{
    DECLARE_POOL_ALLOC()
public:
    long L;
    string str;
public:
    Foo(long l):L(l){}
};
IMPLEMENT_POOL_ALLOC(Foo)
```

将前述alloc进一步发展为具有16条freelist，并不再以application classes内的static呈现，而是一个global allocator，这就是标准库的std::alloc



