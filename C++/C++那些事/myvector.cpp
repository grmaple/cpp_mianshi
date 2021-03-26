#include<iostream>
#include<assert.h>
#define DOUBLE_SIZE   
using namespace std;

class MyVector{
private:
    const int ADD_SIZE = 64;
    int *array;
    unsigned int vsize;
    unsigned int vcapacity;
    int *allocator(unsigned int size);
    void destory(int *array);
public:
    MyVector():array(nullptr),vsize(0),vcapacity(0){}
    MyVector(const int &t, unsigned int n);
    MyVector(const MyVector &other);
    MyVector &operator=(MyVector &other);
    int &operator[](unsigned int pos);
    unsigned int size(){return vsize;}
    unsigned int capacity(){return vcapacity;}
    bool empty(){return (vsize==0);}
    void clear();
    void push_back(const int &t);
    void insert_after(int pos, const int &t);
    void push_front(const int &t);
    void insert_before(int pos, const int &t);
    void erase(unsigned int pos);
    void print();
    ~MyVector(){
        clear();
    }
};
MyVector::MyVector(const int &t, unsigned int n):array(0),vsize(0),vcapacity(0){
    while(n--){
         push_back(t);
    }
}
MyVector::MyVector(const MyVector &other){
    
    array = other.array;// 浅拷贝，只是复制指针，指向的内存是同一块
    vsize = other.vsize;
    vcapacity = other.vcapacity;
}
MyVector &MyVector::operator=(MyVector &other){
    if(this == &other) return *this;
    clear();
    vsize = other.size();
    vcapacity = other.capacity();
    array = new int[vcapacity];
    for(unsigned int i = 0; i<vsize; ++i){// 逐字节复制（深拷贝）
        array[i] = other[i];// other[i]调用[]重载运算符
    }
    return *this;

}
int &MyVector::operator[](unsigned int pos){
    assert(pos<vsize);
    return array[pos];
}
void MyVector::clear(){
    destory(array);
    array = nullptr;
    vsize = 0;
    vcapacity = 0;
}
void MyVector::push_back(const int &t){
    insert_after(vsize-1, t);
}
void MyVector::insert_after(int pos, const int &t){
    insert_before(pos+1, t);
}
void MyVector::push_front(const int &t){
    insert_before(0, t);
}
void MyVector::insert_before(int pos, const int &t){
    if(vsize == vcapacity){
        int *old_array = array;
#ifdef DOUBLE_SIZE
        if(vcapacity == 0) vcapacity = 1;
        vcapacity = vcapacity << 1;
#else
        vcapacity += ADD_SIZE;
#endif
        array = allocator(vcapacity);
        for(unsigned int i = 0; i<vsize; ++i){
            array[i] = old_array[i];
        }
        destory(old_array);
    }
    for(int i = (int)vsize++; i>pos; --i){
        array[i] = array[i-1];
    }
    array[pos] = t;
}
void MyVector::erase(unsigned int pos){
    if(pos<vsize){
        --vsize;
        for(unsigned int i = pos; i<vsize; ++i){
            array[i] = array[i+1];
        }
    }
}
void MyVector::print(){
    for(unsigned int i = 0; i<size(); ++i){
        cout<<array[i]<<" ";
    }
    cout<<endl;
    cout<<"Real time size = "<<size()<<endl;
    cout<<"The capacity = "<<capacity()<<endl;
}
int *MyVector::allocator(unsigned int size){
    return new int[size];
}
void MyVector::destory(int *array){
    if(array){
        delete[] array;
    }
}

int main() {
    MyVector my_vector;
    // 插入元素
    my_vector.push_back(1);
    my_vector.push_back(2);
    my_vector.push_back(3);
    my_vector.push_front(0);
    if(my_vector.size() == 4)
        my_vector.print();

    // 删除元素(i为下标)
    my_vector.erase(1);
    if((!my_vector.empty()) && my_vector.capacity() == 64)
        my_vector.print();

    // 清空
    my_vector.clear();
    if(my_vector.empty())
        cout << "Vector is empty !" << endl << endl;

    // 测试动态扩展
    for(int i = 0; i < 100; i++)
        my_vector.push_back(i);
    my_vector.print();

    // 测试拷贝构造函数(浅拷贝)
    MyVector my_vector_2(my_vector);
    // my_vector.clear();
    /*
     * my_vector.clear();
     * 调用此句会出错，my_vector指向的内存被释放
     * my_vector_2中array指针为野指针
     */
    my_vector_2.print();

    // 测试=重载运算符
    MyVector my_vector_1(0, 10);
    my_vector_1.print();
    my_vector_1 = my_vector;
    my_vector_1.print();

    // 测试[]重载运算符
    int n;
    cin >> n;
    cout << "The " << n << "th element = " << my_vector[n] << endl << endl;

    return 0;
}