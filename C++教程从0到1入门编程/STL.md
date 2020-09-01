## STL

- 长久以来，软件界一直希望建立一种可重复利用的东西。
- C++的面向对象和泛型编程思想，目的就是复用性的提升

面向对象三大特性：封装，继承，多态

封装：把一些属性和行为类似的东西给它抽象出来作为一个整体，来实现这些事和物。提高复用性

继承：子类继承父类，把父类所有属性和行为都拿过来，不用重新声明。提高代码复用

多态：一个函数名称有多个接口。而这都是一个名称，由于对象的不同，父类指针指向子类对象，对象创建不同，调用同一个接口会产生不同形态。提高复用性

泛型编程：模板。模板将我们类型参数化，我们可以把它变得更有通用性。

- 大多数情况下，数据结构和算法都未能有一套标准，导致被迫从事大量重复工作
- 为了建立数据结构和算法的一套标准，诞生了STL

##### STL标准模板库

STL从广义上分为：容器，算法，迭代器

容器和算法之间提高迭代器进行无缝连接

STL几乎所有代码都采用模板类或者模板函数

##### STL六大组件

容器，算法，迭代器，仿函数，适配器(配接器)，空间配置器(分配器)



容器：各种数据结构，

算法：各种常用的算法

迭代器：扮演了容器与算法之间的胶合剂

仿函数：行为类似函数，可作为算法的某种策略

适配器：一种用来修饰容器或者仿函数或迭代器接口的东西

空间配置器：负责空间的配置与管理



分配器给容器分配存储空间，

算法通过迭代器获取容器中的内容，

仿函数可以协助算法完成各种操作，

配接器用来套接适配仿函数

##### 容器

STL容器就是将应用最广泛的一些数据结构实现出来

常用的数据结构：数组，链表，栈，队列，树，集合， 映射表等

这些容器分为顺序容器和关联容器两种：

​	顺序容器：强调值的排序，顺序容器中的每个元素均有固定的位置

​	关联容器：二叉树结构，各元素间没有严格的物理上的顺序关系

##### 算法

有限的步骤，解决逻辑或者数学上的问题

算法分为质变算法和非质变算法：

​	质变算法：是指运算过程中会更改区间内的元素的内容，如拷贝，替换，增加，删除等

​	非质变算法：是指运算过程中不会更改区间内的元素内容，如查找，计数，遍历，寻找最值等

##### 迭代器

算法通过迭代器才能访问容器中的元素

提供一种方法，使之能够依序寻找某个容器所含的各个元素，而又无需暴露该容器的内部表示方式。

每个容器都有自己专属的迭代器

迭代器使用非常类似指针。

![image-20200901111454879](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200901111454879.png)

常用的容器中迭代器种类为双向迭代器和随机访问迭代器。

### 容器算法迭代器初始

Vector，可以理解为动态数组

##### vector存放内置数据类型

容器：vector

算法：for_each

迭代器：vector\<int>::iterator

```cpp
#include<vector>
#include<algorithm>
//创建容器对象
vector<int> v;
//插入数据
v.push_back(10);
v.push_back(20);

//遍历数据方法一
vector<int>::iterator itBegin = v.begin();//起始迭代器，指向容器中的第一个元素
vector<int>::iterator itEnd = v.end();//结束迭代器，指向容器中最后一个元素的下一个位置
while (itBegin != itEnd) {
    cout<<*itBegin<<endl;
    itBegin++;
}
//遍历数据方法二
for (vector<int>::iterator it = v.begin();it != v.end();it++) {
    cout<<*it<<endl;
}
//遍历数据方法三
void print(int val) {cout<<val<<endl;}
for_each(v.begin(),v.end(),print);
//为什么使用函数名就可以了？因为使用了回调技术
//print一开始不调用，而是在遍历期间才调用函数
```

vector存放自定义数据类型

```cpp
#include<vector>
class Person {
public:
    Person(string name, int age)
        :m_name(name),m_age(age){}
    string m_name;
    int m_age;
};
//创建容器对象
vector<Person> v;

vector<Person*> p;

Person p1("a",10);
Person p2("b",20);
//插入数据
v.push_back(p1);
v.push_back(p2);

p.push_back(&p1);
p.push_back(&p2);
//遍历数据
for (vector<Perosn>::iterator it = v.begin();it != v.end();it++) {
    cout<< (*it).m_name << (*it).m_age <<endl;
    cout<< it->m_name << it->m_age <<endl;
}//it是Person*类型。

for (vector<Perosn*>::iterator it = v.begin();it != v.end();it++) {
    cout<< (*it)->m_name << (*it)->m_age <<endl;
}//it是Person**类型。
```

##### vector容器嵌套容器

相当于二维数据

```cpp
#include<vector>
//创建大容器
vector<verctor<int>> v;//二维数组
//创建小容器
verctor<int> v1;//第一行
verctor<int> v2;//第二行
//向小容器里面添加元素
v1.push_back(10);
v1.push_back(20);
v2.push_back(30);
v2.push_back(40);
//将小容器插入到大容器
v.push_back(v1);
v.push_back(v2);
//提供大容器，把所有数据遍历一遍
for (vector<verctor<int>>::iterator it = v.begin();it != v.end();it++) {
    ////(*it)是verctor<int>
    for (verctor<int>::iterator vit = (*it).begin();vit != (*it).end();vit++) {
        cout<<*vit<<" ";
    }
    cout<<endl;
}//it是verctor<int>*
```

### STL常用容器

#### string容器

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

### vector

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
int num = 0;//统计开辟内存次数
int* p = Null;
for (int i = 0; i<100000; i++) {
    v.push_back(i);
    if (p != &v[0]) {
        p = &v[0]);
        num++;
    }
}
```

