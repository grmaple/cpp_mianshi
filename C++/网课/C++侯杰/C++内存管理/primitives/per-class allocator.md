对new的调用，最终回到调用malloc。

对malloc的误解，认为它很慢，其实它不慢。

但是减少调用malloc的次数总是好的。

还想降低cookie的大小。



```c++
#include<cstddef>
#include<iostream>
using namespace std;

class Screen{
public:
    Screen(int x):i(x){}
    int get(){return i;}
    
    void* operator new(size_t);
    void operator delete(void*, size_t);
private:
    Screen* next;//多耗费了一个next指针
    static Screen* freeStore;
    static const int screenChunk;
private:
    int i;
};
Screen* Screen::freeStore = 0;
const int Screen::screenChunk = 24;

void* Screen::operator new(size_t size){
    Screen *p;
    if(!freeStore){
        size_t chunk = screenChunk * size;
        freeStore = p = reinterpret_cast<Screen*>(new char[chunk]);//没有对应的delete，一个一个new
        //将一大块分割成片，当作链表串接起来
        for(;p!=&freeStore[screenChunk-1];++p)
            p->next = p+1;
        p->next = 0;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}
void Screen::operator delete(void* p, size_t){
    //将deleted object插回free list前端
    (static_cast<Screen*>(p))->next = freeStroe;
    freeStore = static_cast<Screen*>(p);
}

cout<<sizeof(Screen)<<endl;//8
size_t const N = 100;
Screen *p[N];
for(int i = 0; i<N; ++i){
    p[i] = new Screen(i);
}
for(int i = 0; i<10; ++i){
    cout<<p[i]<<endl;
}
for(int i = 0; i<N; ++i){
    delete p[i];
}
//写了成员operator new/delete就是间隔8
//没写则调用全局operator new/delete就是间隔16，多了cookie
```

```c++
class Airplane{
private:
    struct AirplaneRep{
        unsigned long miles;
        char type;
    };
private:
    union{
        AirplaneRep rep;
        AirplaneRep* next;
    };
public:
    unsigned long getMiles(){
        return rep.miles;
    }
    char getType(){
        return rep.type;
    }
    void set(unsigned long m, char t){
        rep.miles = m;
        rep.type = t;
    }
public:
    static void* operator new(size_t size);
    static void operator delete(void* deadObject, size_t size);
private:
    static const int BLOCK_SIZE;
    static Airplane* headOfFreeList;
};
const int Airplane::BLOCK_SIZE = 512;
Airplane* Airplane::headOfFreeList;
void* Airplane::operator new(size_t size){
    //继承发送时才会大小有误
    if(size!=sizeof(Airplane)) return ::operator new(size);
    Airplane *p = headOfFreeList;
    //如果p有效就把list头部下移一个元素
    if(p) headOfFreeList = p->next;
    else{
        //freelist已空，申请分配一大块
        //只用到头尾两个cookie
        Airplane* newBlock = static_cast<Airplane*>(::operator new(BLOCK_SIZE * sizeof(Airplane)));
        //将小块串成一个freelist
        //但跳过#0， 因为它被传回作为本次成果
        for(int i = 1; i<BLOCK_SIZE-1; ++i)
            newBlock[i].next = &newBlock[i+1];
        newBlock[BLOCK_SIZE-1].next = 0;//结束list
        p = newBlock;
        headOfFreeList = &newBlock[1];
    }
    return p;
}
void Airplane::operator delete(void* deadObject, size_t size){
    if(deadObject == 0) return;
    if(size!=sizeof(Airplane)){
        ::operator delete(deadObject);
        return;
    }
    //不调用delete，但是没有内存泄漏
    Airplane* carcass = static_cast<Airplane*>(deadObject);
    carcass->next = headOfFreeList;
    headOfFreeList = carcass;
}
//写了成员operator new/delete就是间隔8
//没写则调用全局operator new/delete就是间隔16，多了cookie
```

