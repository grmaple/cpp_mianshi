## STL函数对象

### 函数对象

函数对象：

- 重载函数调用符的类，其对象常称为函数对象
- 函数对象使用重载的()时，其行为类似函数调用，也叫**仿函数**

本质：函数对象(仿函数)实际是一个类，不是函数

##### 函数对象的特点

- 函数对象在使用时，可以像普通函数那样调用，可以有参数，可以有返回值
- 函数对象超出普通函数的概念，函数对象内部可以有自己的状态
- 函数对象可以作为参数传递

```cpp
class MyAdd {
public:
    //可以有参数，可以有返回值
    int operator()(int v1, int v2) {
        return v1+v2;
    }
}
MyAdd myAdd;
myAdd(1,2);//可以像普通函数那样调用

//函数对象内部可以有自己的状态
class MyPrint {
public:
    MyPrint(){count = 0;}
    void operator()(string test) {
        cout<<test<<endl;
        count++;
    }
    int count;
}
MyPrint myPrint;
myPrint("hello world");
myPrint("hello world");
myPrint("hello world");
myPrint("hello world");
//现在像记录myPrint函数调用了多少次，如果是普通函数需要使用一个全局变量来记录，函数对象加个成员变量就可以了。
cout<<"myPrint调用次数"<<myPrint.count<<endl;

//函数对象可以作为参数传递
void doPrint(MyPrint& mp, string test) {
    mp(test);
}
MyPrint myPrint;
doPrint(myPrint,"hello");
```

### 谓词

返回bool类型的仿函数称为谓词Predicate

如果operator()接受一个参数，那么叫做一元谓词

如果operator()接受两个参数，那么叫做二元谓词

##### 一元谓词

```cpp
class GreaterFive {
public:
    //operator(),返回bool，接受一个参数
    bool operator()(int val) {
        return val > 5;
    }
}
vector<int> v;
//查找容器中有没有大于5的数字
//find_if(),按照条件来查找
//GreaterFive()是一个匿名对象
vector<int>::iterator it = find_if(v.begin(),v.end(),GreaterFive());
if (it == v.end()) {cout<<"没有找到"<<endl;}
else {cout<<"找到了"<<*it<<endl;}
```

##### 二元谓词

```cpp
class MyCompare {
public:
    //operator(),返回bool，接受两个参数
    bool operator()(int val1,int val2) {
        return val1 > val2;
    }
}
vector<int> v;
sort(v.begin(),v.end());//默认排序为升序

//使用函数对象，改变排序规则为降序
sort(v.begin(),v.end(),MyCompare());
```

### 内建函数对象

STL内建了一些函数对象

分类

- 算术仿函数
- 关系仿函数
- 逻辑仿函数

用法

- 这些仿函数所产生的对象，用法和一般函数完全相同
- 使用这些内建函数对象，需要引入头文件\<functional>

##### 算术仿函数

实现四则运算

```cpp
#include<functional>
template<class T> T plus<T>;//加法仿函数
template<class T> T minus<T>;//减法仿函数
template<class T> T multiplies<T>;//乘法仿函数
template<class T> T divides<T>;//除法仿函数
template<class T> T modulus<T>;//取模仿函数
template<class T> T negate<T>;//取反仿函数

//一元运算
negate<int> n;
n(50);//-50
//二元运算
plus<int> p;
p(50,100);//150
```

##### 关系仿函数

实现关系对比

```cpp
#include<functional>
template<class T> bool equal_to<T>;//等于仿函数
template<class T> bool not_equal_to<T>;//不等于仿函数
template<class T> bool greater<T>;//大于仿函数
template<class T> bool greater_equal<T>;//大于等于仿函数
template<class T> bool less<T>;//小于仿函数
template<class T> bool less_equal<T>;//小于等于仿函数


vector<int> v;
sort(v.begin(),v.end());//默认排序为升序，less<int>()
//使用内建函数对象,创建匿名对象，排序为降序
sort(v.begin(),v.end(),greater<int>());
```

##### 逻辑仿函数

实现逻辑运算

```cpp
#include<functional>
template<class T> bool logical_and<T>;//逻辑与仿函数
template<class T> bool logical_or<T>;//逻辑或仿函数
template<class T> bool logical_not<T>;//逻辑非仿函数

vector<bool> v;
//利用逻辑非，将容器v搬运到容器v2，并执行取反操作
vector<bool> v2;
v2.resize(v.size());//transform()前需要开辟空间
//transform()可以将函数应用到序列的元素上，并将这个函数返回的值保存到另一个序列中，它返回的迭代器指向输出序列所保存的最后一个元素的下一个位置。
transform(v.begin(),v.end(),logical_not<bool>())
```

