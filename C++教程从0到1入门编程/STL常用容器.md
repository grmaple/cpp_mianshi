## STL常用容器

### string容器

string本质上是一个类

string和char*的区别：

- char*是一个指针
- string是一个类，类内部封装了char*管理整个字符串，是一个char\*的容器

特点：

- string类内部封装了很多成员方法

  如：查找find，拷贝copy，删除delete，替换replace，插入insert

- string管理char*所分配的内存，不用担心复制越界和取值越界，由类内部进行负责

##### string构造函数

```cpp
#include<string>
class string {
    string();//创建一个空字符串
    string(const char* s);//使用字符串s初始化
    string(const string& str);//使用string对象初始化另一个string对象
    string(int n, char c);//使用n个字符c初始化
};
int main() {
    string s1;//""
    
    const char* str = "hello";
    string s2(str);//"hello"
    
    string s3(s2);//"hello"
    
    string(2,"a");//"aa"
}
```

##### string赋值操作

```cpp
#include<string>
class string {
    string& operator=(const char* s);//char*类型字符串赋值给当前字符串
    string& operator=(const string& s);//把字符串s赋值给当前字符串
    string& operator=(char c);//字符赋值给当前字符串
    
    string& assign(const char* s);//把char*类型字符串赋给当前字符串
    
    string& assign(const char* s,int n);//把char*类型字符串的前n个字符赋给当前字符串
    string& assign(const string& s);//把字符串s赋给当前字符串
    string& assign(int n,char c);//使用n个字符c赋给当前字符串
};
int main() {
    string s1;
    s1 = "hello";//"hello"

    string s2;
    s2 = s1;//"hello"
    
    string s3;
    s3 = 'a';//"a"
    
    string s4;
    s4.assign("hello");//"hello"

    string s5;
    s5.assign("hello",2);//"he"
    
    string s6;
    s6.assign(s4);//"hello"
    
    string s7;
    s7.assign(2,'a');//"aa"
}
```

##### string字符串拼接

```cpp
#include<string>
class string {
    string& operator+=(const char* s);//char*类型字符串拼接在当前字符串后面
    string& operator+=(const string& s);//把字符串s拼接在当前字符串后面
    string& operator+=(char c);//字符拼接在当前字符串后面
    
    string& append(const char* s);//把char*类型字符串拼接在当前字符串后面
    
    string& append(const char* s,int n);//把char*类型字符串的前n个字符拼接在当前字符串后面
    string& append(const string& s);//把字符串s拼接在当前字符串后面
    string& append(const string& s,int pos, int n);//字符串s中从pos开始的n个字符拼接在当前字符串后面
};
int main() {
    string s1 = "say";
    s1 += "hello";//"sayhello"

    string s2 = "I";
    s2 += s1;//"Isayhello"
    
    string s3 = "n";
    s3 += '!';//"n!"
    
    string s4 = "say";
    s4.append("hello");//"sayhello"

    string s5 = "I";
    s5.append("sayyy",3);//"Isay"
    
    string s6 = "!";
    s6.append(s5);//"Isay!"
    
    string s7 = "I say";
    string s8 = "say hello";//从位置3开始的6个字符
    s7.append(s8,3,6);//"I say hello"
}
```

##### string查找和替换

```cpp
#include<string>
class string {
    int find(const string& s, int pos = 0) const;//查找s第一次出现位置，从0开始查找
    int find(const char* s, int pos = 0) const;//查找s第一次出现位置，从0开始查找
    int find(const char* s, int pos, int n) const;//从pos位置查找查找s第一次出现位置，
    int find(const char c, int pos = 0) const;//查找字符c第一次出现位置，从0开始查找
    int rfind(const string& s, int pos = npos) const;//查找s最后一次出现位置，从0开始查找
    int rfind(const char* s, int pos = npos) const;//查找s最后一次出现位置，从0开始查找
    int rfind(const char* s, int pos, int n) const;//从pos位置查找查找s最后一次出现位置，
    int rfind(const char c, int pos = 0) const;//查找字符c最后一次出现位置，从0开始查找
    
    string& replace(int pos, int n, const string& s) const;//把原字符串从pos开始n个字符替换为字符串s
    string& replace(int pos, int n, const char* s) const;//把原字符串从pos开始n个字符替换为字符串s
};
```

##### string字符串比较

字符串比较是按字符的ASCII码进行比较

字典序

=返回0

\>返回1

<返回-1

```cpp
#include<string>
class string {
    int compare(const string& s)const;
    int compare(const char* s)const;
};
```

##### string字符获取

```cpp
#include<string>
class string {
    char& operator[](int n);
    char& at(int n);
};
```

##### string插入和删除

```cpp
#include<string>
class string {
    string& insert(int pos, const char* s);//插入字符串
    string& insert(int pos, const string& str);//插入字符串
    string& insert(int pos, int n, char c);//在指定位置插入n个字符c
    
    string& erase(int pos, int n = npos);//删除从pos开始的n个字符
};
```

##### string子串

```cpp
#include<string>
class string {
    string substr(int pos = 0, int n = npos) const;//返回由pos开始的n个字符组成的字符串
};
int main() {
    string str = "abcdef";
    string subStr = str.substr(1,3);//"bcd"
    
    //实用操作
    string email = "grample126@163.com";
    //从邮箱地址中，获取用户名信息
    int pos = email.find("@");
    string usrName = email.substr(0,pos);//"grample126"
}
```

### vector容器

功能：

vector数据结构和数组非常相似，也称为单端数组

vector和普通数组的区别：

不同之处在于数组是静态空间，而vector可以动态扩展

动态扩展不是在原空间之后续接新空间，而是找到更大的内存空间，然后将原数据拷贝到新空间，释放原空间。

![image-20200901134040262](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200901134040262.png)

vector容器的迭代器是支持随机访问的迭代器

##### vector构造函数

```cpp
#include<vector>
int main() {
    //vector();
    //采用模板实现类实现，默认构造函数
    vector<int> v1;
    
    //vector(v.begin(),v.end());
    //将v[begin(),end()]区间的元素拷贝给自身
    vector<int> v2(v1.begin(),v1.end());
    
    //vector(n,elem);
    //构造函数将n个elem拷贝给自身
    vector<int> v3(10,100);
    
    //vector(const vector &vec);
    //拷贝构造函数
    vector<int> v4(v4);
}
```

##### vector赋值操作

```cpp
#include<vector>
int main() {
    vector<int> v1;
    
    //vector& operator=(const vector& vec);
    //重载等号操作符
    vector<int> v2;
    v2 = v1;
    
    //assign(beg，end);
    //将[beg,end]区间的元素拷贝赋值给本身
    vector<int> v3;
    v3.assign(v1.begin(),v2.end());
    
	//assign(n,elem);
    //将n个elem拷贝赋值给本身
    vector<int> v4;
    v4.assign(10,100);
    
}
```

##### vector容量和大小

```cpp
#include<vector>
int main() {
    vector<int> v1;
    
    //empty()
    //判断容器是否为空
    if (v1.empty()) {
        cout<<"v1为空"<<endl;
    } else {
        cout<<"v1不为空"<<endl;
    }
    
    //capacity();
    //容器的容量
    v1.capacity();
    
	//size();
    //返回容器中元素的个数
    v1.size();
    
    //resize(int num);
    //重新指定容器的长度为num，如果容器变长则以默认值填充，如果容器变短，则末尾超出容器长度的元素被删除
    v1.resize(10);//填充值默认为0
    
    //resize(int num, elem);
    //重新指定容器的长度为num，如果容器变长则以elem值填充，如果容器变短，则末尾超出容器长度的元素被删除
    v1.size(10,1);//填充值为1
}
```

##### vector插入和删除

```cpp
//push_back(ele);
//尾部插入元素ele
v1.push_back(100);

//pop_back();
//删除最后一个元素
v1.pop_back();
    
//insert(const_iterator pos, ele);
//迭代器指向位置pos插入元素ele
v1.insert(v1.begin(),1000);

//insert(const_iterator pos, int count, ele);
//迭代器指向位置插入count个元素ele
v1.insert(v1.begin(),2,1000);
    
//erase(const_iterator pos);
//删除迭代器指向的元素
v1.erase(v1.begin());

//erase(const_iterator start, const_iterator end);
//删除迭代器从start到end之间的元素
v1.erase(v1.begin(),v2.end());

//clear();
//删除容器中所有元素
v1.clear();
```

##### vector数据存取

```cpp
//at(int idx);
//返回索引idx所指的数据
v1.at(0);

//operator[](int idx);
//返回索引idx所指的数据
v1[0];
    
//front();
//返回容器中第一个数据元素
v1.front();

//back();
//返回容器中最后一个数据元素
v1.back();
```

##### vector互换容器

实现两个容器内元素进行互换

swap(vec);//将vec与本身的元素互换

```cpp
vector<int> v1;
vector<int> v2;
v1.swap(v2);//v1元素和v2元素互换

//实际用途
//巧用swap可以收缩内存空间
vector<int> v;
for (int i = 0; i<100000; i++) {v.push_back(i);}
//size=100000,capacity=138255

v.resize(3);
//size=3,capacity=138255
//分配了这么大的空间，却用这么少空间，所以很浪费空间

vector<int> (v).swap.(v);
//size=3,capacity=3，收缩了内存空间
//vector<int> (v)//使用拷贝构造函数生成了匿名对象，用v.size()来分配内存给匿名对象。
//所以匿名对象的size=3,capacity=3
//(v).swap.(v)，交换匿名对象和v。
//现在匿名对象的size=3,capacity=138255，然后当前行结束了，匿名对象内存立刻被回收掉。
```

##### vector预留空间

减少vector在动态扩展容量时的开展次数

reserve(int len);

容器预留len个元素长度,预留位置不初始化，元素不可访问。它不会生成元素，只是确定这个容器允许放入多少对象。

如果len的值大于当前的capacity()，那么会重新分配一块能存len个对象的空间，然后把之前size()个对象通过copy construtor复制过来，销毁之前的内存

如果len的值小了，那么不会改变capacity()

```cpp
vector<int> v;
v.reserve(100000);//num=1
int num = 0;//统计开辟内存次数
int* p = Null;
for (int i = 0; i<100000; i++) {
    v.push_back(i);
    if (p != &v[0]) {
        p = &v[0]);
        num++;
    }
}
count<<num<<endl;//num=30
```

### dequer容器

功能：双端数组，可以对头端进行插入删除操作

deque与vector的区别：

- vector对于头部的插入删除效率低，数据量越大，效率越低。
- deque相对而言，对头部的插入删除速度会比vector快
- vector访问元素时的速度会被deque快，这和两者内部实现有关

![image-20200901190538950](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200901190538950.png)

deque内部工作原理：

deque内部有一个中控器，维护每段缓冲区中的内容，缓冲区中存放大量真实数据

中控器维护的是每个缓冲区的地址，使得使用deque时像一片连续的内存空间

![image-20200901190934926](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200901190934926.png)

deque容器的迭代器也是支持随机访问的

##### deque构造函数

```cpp
deque<T> deqT;//默认构造函数
deque(beg,end);//拷贝函数将[beg，end]区间中的元素拷贝给本身
deque(n,elem);//构造函数将n个elem拷贝给本身
deque(const deque& deq);//拷贝构造函数

//注意如果想限定容器中的数据是只读状态，那么迭代器需要使用const_iterator
void print(const deque<int>& d) {
    for(deque<int>::const_iterator it = d.begin(); it!=d.end(); it++) {
        cout<<*it<<endl;
    }
}
```

##### deque赋值操作

```cpp
deque& operator=(const deque& deq);//重载等号操作符
assign(beg,end);//将[beg，end]区间中的数据拷贝赋值给本身
assign(n,elem);//将n个elem拷贝赋值给本身
```

##### deque大小操作

```cpp
empty();//判断容器是否为空
size();//返回容器中元素的个数
resize(num);//重新指定容器的长度为num，如果容器变长则以默认值填充，如果容器变短，则末尾超出容器长度的元素被删除
resize(num,elem);//重新指定容器的长度为num，如果容器变长则以elem值填充，如果容器变短，则末尾超出容器长度的元素被删除
```

deque没有容量的概念，因为它可以无限的往里面放数据

##### deque插入和删除

```cpp
push_back(elem);//在容器尾部添加一个数据
push_front(elem);//在容器头部插入一个数据
pop_back();//删除容器最好有个数据
pop_front();//删除容器第一个数据

insert(pos,elem);//在pos位置插入有个elem元素的拷贝，返回新数据的位置
insert(pos,n,elem);//在pos位置插入n个elem元素，无返回值
insert(pos,beg,end);//在pos位置插入[beg,end]区间的数据，无返回值
clear();//清空容器的所有数据
erase(beg,end);//删除[beg，end]区间的数据，返回下一个数据的位置
erase(pos);//删除pos位置的数据，返回下一个数据的位置
```

##### deque数据存取

```cpp
at(int idx);//返回索引idx所指的数据
operator[];//返回索引idx所指的数据
front();//返回容器中第一个数据元素
back();//返回容器中最后有个数据
```

##### deque排序

利用算法实现对deque容器进行排序

```cpp
#include<deque>
#include<algorithm>
deque<int> d;
d.push_back(10);
d.push_back(20);
d.push_back(30);
d.push_front(100);
d.push_front(200);
d.push_front(300);
//300-200-100-10-20-30
sort(d.begin(),d.end());//默认从小到大
//对于支持随机访问的迭代器容器，都可以使用sort算法排序
//deque，vector都可以
```

### stack容器

先进后出FILO，只有一个出口

![image-20200901194040808](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200901194040808.png)

栈中只有顶端的元素才可以被外界使用，因此栈不允许有遍历行为

栈中进入数据称为入栈push

栈中弹出数据称为出栈pop

##### 构造函数

```cpp
stack<T> stk;//采用模板类实现，stack对象的默认构造形式
stack(const stack& stk);//拷贝构造函数
```

##### 赋值操作

```cpp
stack& operator=(const stack& stk);//重载等号操作符
```

##### 数据存取

```cpp
push(elem);//向栈顶添加元素
pop();//从栈顶移除第一个元素
top();//返回栈顶元素
```

##### 大小操作

```cpp
empty();//判断栈是否为空
size();//返回栈的大小
```

### queue容器

先进先出FIFO，它有两个出口

![image-20200901200835294](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200901200835294.png)

队列容器允许从一端新增元素，从另一端移除元素

队列中只有队头和队尾才可以被外界使用，因此队列不允许有遍历行为

队列中进数据称为入队push

队列中出数据称为出队pop

##### 构造函数

```cpp
queue<T> que;//采用模板类实现，queue对象的默认构造形式
queue(const queue& que);//拷贝构造函数
```

##### 赋值操作

```cpp
queue& operator=(const queue& que);//重载等号操作符
```

##### 数据存取

```cpp
push(elem);//向队尾添加元素
pop();//从队头移除第一个元素
back();//返回最后一个元素
front();//返回第一个元素
```

##### 大小操作

```cpp
empty();//判断队列是否为空
size();//返回队列的大小
```

### list容器

将数据进行链式存储

链表list是一种物理存储单元上非连续的存储结构，数据元素的理解顺序是提过链表中的指针链接实现的

链表的组成：链表由一系列结点组成

结点的组成：一个是存储数据元素的数据域，另一个是存储下一个结点地址的指针域

STL中的链表是一个双向循环链表

![image-20200901201615307](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200901201615307.png)

由于链表的存储方式并不是连续的内存空间，因此链表list中的迭代器只支持前移和后移，属于双向迭代器

list的优点

- 采用动态存储分配，不会造成内存浪费和溢出
- 链表执行插入和删除操作十分方便，修改指针即可，不需要移动大量元素

list的缺点

- 链表灵活，但是空间(指针域)和时间(遍历)额外耗费较大

list有个重要的性质，插入操作和删除操作都不会造成原有list迭代器的失效，这在vector是不成立的

总结：STL的list和vector是两个最常被使用的容器。各有优缺点。

##### 构造函数

```cpp
list<T> lst;//list采用模板类实现，对象的默认构造形式
list(beg,end);//构造函数将[beg，end]区间中的元素拷贝给本身
list(n,elem);//构造函数将n个elem拷贝给本身
list(const list& lst);//拷贝构造函数
```

##### 赋值操作

```cpp
assign(beg,end);//将[beg，end]区间中的数据拷贝赋值给本身
assign(n,elem);//将n个elem拷贝赋值给本身
list& operator=(const list& lst);//重载等号操作符
swap(lst);//将lst与本身的元素互换
```

##### 插入和删除

```cpp
push_back(elem);//在容器尾部添加一个数据
push_front(elem);//在容器头部插入一个数据
pop_back();//删除容器最好有个数据
pop_front();//删除容器第一个数据

insert(pos,elem);//在pos位置插入有个elem元素的拷贝，返回新数据的位置
insert(pos,n,elem);//在pos位置插入n个elem元素，无返回值
insert(pos,beg,end);//在pos位置插入[beg,end]区间的数据，无返回值
clear();//清空容器的所有数据
erase(beg,end);//删除[beg，end]区间的数据，返回下一个数据的位置
erase(pos);//删除pos位置的数据，返回下一个数据的位置
remove(elem);//删除容器中所有与elem值匹配的元素
```

##### 数据存取

```cpp
back();//返回最后一个元素
front();//返回第一个元素
//不可以使用at()和[]访问元素
//迭代器不支持随机访问
//list<int>::iterator it = l.begin();
//it++;可以
//it=it+1;不可以
```

##### 大小操作

```cpp
empty();//判断容器是否为空
size();//返回容器中元素的个数
resize(num);//重新指定容器的长度为num，如果容器变长则以默认值填充，如果容器变短，则末尾超出容器长度的元素被删除
resize(num,elem);//重新指定容器的长度为num，如果容器变长则以elem值填充，如果容器变短，则末尾超出容器长度的元素被删除
```

##### 反转和排序

```cpp
list<int> L;
//下面的sort是list的成员函数
L.reverse();//反转链表
L.sort();//链表排序，升序
//sort(L.begin(),L.end());出错
//底层用的算法，会根据数据量来更改排序算法

bool myCompare(int v1, int v2) {
    //降序，就要第一个数>第二个数
    return v1>v2;
}
L.sort(myCompare);//链表排序，降序
```

所有不支持随机访问迭代器的容器， 不能使用标准算法

不支持随机访问迭代器的容器，内部会提供对应一些算法

### set/multiset容器

所有元素都会在插入时自动被排序

本质：set/multiset属于关联容器，底层结构是红黑树

set和multiset的区别

- set不允许容器中有重复元素
- multiset允许容器中有重复元素

##### set构造和赋值

```cpp
set<T> st;//默认构造函数
set(const set& st);//拷贝构造函数

set& operator=(const set& st);//重载等号操作符
```

##### set插入和删除

```cpp
insert(elem);//在容器中插入元素
clear();//清空容器的所有数据
erase(beg,end);//删除[beg，end]区间的数据，返回下一个数据的迭代器
erase(pos);//删除pos位置的数据，返回下一个数据的迭代器
erase(elem);//删除容器中值为elem的元素
```

##### set大小和交换

```cpp
empty();//判断容器是否为空
size();//返回容器中元素的数目
swap(st);//交换两个集合容器
```

##### set查找和统计

```cpp
find(key);//查找key是否存在，若存在，返回该键的元素的迭代器；若不存在返回set.end()；
count(key);//统计key的元素个数,对于set要么0要么1

set<int> s;
set<int>::iterator pos = s.find(30);
if (pos != s.end()) {cout<<"找到元素"<<*pos<<endl;}
else {cout<<"没找到元素"<<endl；}
```

##### set和multiset的区别

区别：

- set不可以插入重复数据，multiset可以
- set插入数据的同时会返回插入结果，表示插入是否成功
- multiset不会检测数据，所以可以插入重复数据

```cpp
//set插入数据的同时会返回插入结果，表示插入是否成功
set<int> s;
pair<set<int>::iterator,bool> ret = s.insert(10);
if (ret.second) {cout<<"第一次插入成功"<<endl;}//成功
else {cout<<"第一次插入失败"<<endl;}
ret = s.insert(10);
if (ret.second) {cout<<"第二次插入成功"<<endl;}
else {cout<<"第二次插入失败"<<endl;}//失败

//multiset不会检测数据，所以可以插入重复数据
multiset<int> ms;
multiset<int>::iterator ret = ms.insert(10);
```

##### pair对组创建

成对出现的数据，利用对组可以返回两个数据

```cpp
//不用头文件
//创建方式
pair<int,int> p(1,2);
pair<int,int> p2 = make_pair(1,2);

p.first;
p.second;
```

##### set容器排序

set容器默认排序规则为从小到大，如何改变排序规则?

利用仿函数，可以改变排序规则

```cpp
//set存放内置数据类型
set<int> s1;
s1.insert(10);
s1.insert(40);
s1.insert(20);
s1.insert(50);
s1.insert(30);
//10-20-30-40-50,自动排序，默认升序
for (set<int>::iterator it = s1.begin(); it != s1.end(); it++) {
    cout<<*it<<endl;
}

//仿函数，本质是一个类类型
class MyCompare {
public:
    bool operator()(int v1, int v2) {
        return v1>v2;
    }
}
set<int,MyCompare> s2;
s2.insert(10);
s2.insert(40);
s2.insert(20);
s2.insert(50);
s2.insert(30);
//50-40-30-20-10,利用仿函数，变成降序
for (set<int，MyCompare>::iterator it = s2.begin(); it != s2.end(); it++) {
    cout<<*it<<endl;
}
```

```cpp
//set存放自定义数据类型
//自定义类型，需要指定排序规则，利用仿函数
class Person {
    Person(string name,int age){
        m_name = name;
        m_age = age;
    }
    string m_name;
    int m_age;
}
//仿函数，本质是一个类类型
class comparePerson {
public:
    bool operator()(const Person& p1, const Person& p2) {
        //按照年龄。降序
        return p1.m_age > p2.m_age;
    }
}
set<Person,comparePerson> s;
Person p1("刘备",24);
Person p2("关羽",28);
Person p3("张飞",25);
Person p4("赵云",21);
s.insert(p1);
s.insert(p2);
s.insert(p3);
s.insert(p4);
for (set<Person,comparePerson>::iterator it = s.begin(); it != s.end(); it++) {
    cout<< it->m_name << it->m_age <<endl;
}
```

### map/multimap容器

map中所有元素都是pair对组

pair中第一个元素为key键值，起到索引作用，第二个元素为value值

所有元素都会根据元素的键值自动排序

本质：map/multimap属于关联容器，底层结构是用红黑树实现

优点：可以根据key值快速找到value值

map和multimap的区别

- map不允许容器中有重复key值元素
- multimap允许容器中有重复key值元素

##### map构造和赋值

```cpp
map<T,T> mp;//map默认构造函数
map(const map &mp);//拷贝构造函数
map& operator=(const map& mp);//重载等号操作符
```

##### map插入和删除

```cpp
insert(elem);//在容器中插入元素
//m.insert(pair<int,int>(1,10));//匿名对组做插入
//m.insert(make_pair(2,20));
//m.insert(map<int,int>::value_type(3,30));
//m[4] = 40;[]不建议插入，可以用key访问value

clear();//清空容器的所有数据
erase(beg,end);//删除[beg，end]区间的数据，返回下一个数据的迭代器
erase(pos);//删除pos位置的数据，返回下一个数据的迭代器
erase(key);//删除容器中值为key的元素
```

##### map大小和交换

```cpp
empty();//判断容器是否为空
size();//返回容器中元素的数目
swap(mp);//交换两个map容器
```

##### map查找和统计

```cpp
find(key);//查找key键值是否存在，若存在，返回该键的元素的迭代器；若不存在返回set.end()；
count(key);//统计key的元素个数,对于map要么0要么1

map<int,int> m;
m.insert(pair<int,int>(1,10));
m.insert(pair<int,int>(2,20));
m.insert(pair<int,int>(3,30));
map<int,int>::iterator pos = m.find(3);
if (pos != m.end()) {cout<<"找到元素"<< pos->second <<endl;}
else {cout<<"没找到元素"<<endl；}
```

##### map容器排序

map容器默认排序规则为从小到大，如何改变排序规则?

利用仿函数，可以改变排序规则

```cpp
//仿函数，本质是一个类类型
class MyCompare {
public:
    bool operator()(int v1, int v2) {
        //降序
        return v1 > v2;
    }
}
map<int,int,MyCompare> m;
m.insert(pair<int,int>(1,10));
m.insert(pair<int,int>(2,20));
m.insert(pair<int,int>(3,30));
m.insert(pair<int,int>(4,40));
m.insert(pair<int,int>(5,50));
//默认排序规则是升序
for (map<int,int,MyCompare>::iterator it = m.begin(); it != m.end(); it++) {
    cout<< it->first << it->second <<endl;
}
```

