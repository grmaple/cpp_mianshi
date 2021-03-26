## STL常用算法

算法注意由头文件\<algorithm>\<functional>\<numeric>组成

\<algorithm>是所有STL文件中最大的一个，范围涉及到比较、交换、查找、遍历操作、复制、修改等

\<functional>定义了一些模板类，用以声明函数对象

\<numeric>体积很小，只包括几个在序列行面进行简单数学运算的模板函数

### 常用遍历算法

for_each();//遍历容器

transform();//搬运容器到另一个容器中

##### for_each()

遍历容器

for_each(iterator beg, iterator end,_func);

beg:开始迭代器

end:结束迭代器

_func:函数或者函数对象

```cpp
vector<int> v;
for(int i = 0; i<10; i++) {
    v.push_back(i);
}
//_func为函数
void print(int val) {
    cout<<val<<endl;
}
for_each(v.begin(),v.end(),print);
```

```cpp
vector<int> v;
for(int i = 0; i<10; i++) {
    v.push_back(i);
}
//_func为函数对象
class Print {
    void operator()(int val) {
	    cout<<val<<endl;
	}
};
for_each(v.begin(),v.end(),Print());
```

##### transform()

搬运容器到另一个容器中

transform(iterator beg1,iterator end1,iterator beg2,_func);

beg1:源容器开始迭代器

end1:源容器结束迭代器

beg2:目标容器开始迭代器

_func:函数或者函数对象

```cpp
vector<bool> v;
for(int i = 0; i<10; i++) {
    v.push_back(i);
}
class Transform {
    int operator()(int v){
        return v+1;
    }
}
vector<int> v2;
v2.resize(v.size());//目标容器需要提前开辟空间
transform(v.begin(),v.end(),v2.begin(),Transform());
```

### 常用查找算法

find();//查找元素

find_if();//按条件查找元素

adjacent_find();//查找相邻重复元素

binary_search();//二分查找法

count();//统计元素个数

count_if();//按条件统计元素个数

##### find()

查找指定元素，找到返回指定元素的迭代器，找不到返回结束迭代器end()

find(iterator beg, iterator end, value);

beg:开始迭代器

end:结束迭代器

value:查找的元素

```cpp
//查找内置数据类型
vector<int> v;
for(int i = 0; i<10; i++) {
    v.push_back(i);
}
vector<int>::iterator it = find(v.begin(),v.end(),5);
if (it == v.end()) {cout<<"没有找到"<<endl;}
else {cout<<"找到了"<<*it<<endl;}
```

```cpp
//查找自定义数据类型
class Person {
    Person(string name,int age){
        m_name = name;
        m_age = age;
    }
    //重载==，让底层find知道如何对比Person数据类型
    bool operator==(const Person& p) {
        return (this->m_age == p.m_age)&&(this->m_name == p.m_name);
    }
    string m_name;
    int m_age;
}
vector<Person> v;
Person p1("刘备",24);
Person p2("关羽",28);
Person p3("张飞",25);
Person p4("赵云",21);
v.insert(p1);
v.insert(p2);
v.insert(p3);
v.insert(p4);
vector<Person>::iterator it = find(v.begin(),v.end(),p2);
if (it == v.end()) {cout<<"没有找到"<<endl;}
else {cout<<"找到了">> it->m_name << it->m_age<<endl;}
```

##### find_if()

按条件查找元素

找到返回指定元素的迭代器，找不到返回结束迭代器

find_if(iterator beg, iterator end, _Pred);

beg:开始迭代器

end:结束迭代器

_Pred:函数或者谓词(返回bool类型)

```cpp
//内置类型
class GreaterFive {
public:
    bool operator()(int val) {
        return val > 5;
    }
}
vector<int> v;
for(int i = 0; i<10; i++) {
    v.push_back(i);
}
vector<int>::iterator it = find_if(v.begin(),v.end(),GreaterFive());
if (it == v.end()) {cout<<"没有找到"<<endl;}
else {cout<<"找到了"<<*it<<endl;}
```

```cpp
//自定义类型
class Person {
    Person(string name,int age){
        m_name = name;
        m_age = age;
    }
    string m_name;
    int m_age;
}
class Greater25 {
public:
    bool operator()(Person& p) {
        return p.m_age>25;
    }
}
vector<Person> v;
Person p1("刘备",24);
Person p2("关羽",28);
Person p3("张飞",25);
Person p4("赵云",21);
v.insert(p1);
v.insert(p2);
v.insert(p3);
v.insert(p4);
vector<Person>::iterator it = find_if(v.begin(),v.end(),Greater25());
if (it == v.end()) {cout<<"没有找到"<<endl;}
else {cout<<"找到了">> it->m_name << it->m_age<<endl;}
```

##### adjacent_find()

查找相邻重复元素

找到返回相邻元素的第一个位置的迭代器

找不到返回返回end迭代器

adjacent_find(iterator beg, iterator end);

beg:开始迭代器

end:结束迭代器

```cpp
vector<int> v;
v.push_back(0);
v.push_back(3);
v.push_back(0);
v.push_back(3);
v.push_back(1);
v.push_back(4);
v.push_back(3);
v.push_back(3);
vector<int>::iterator it = adjacent_find(v.begin(),v.end());
if (it == v.end()) {cout<<"没有找到"<<endl;}
else {cout<<"找到了"<<*it<<endl;}
```

##### binary_search()

查找指定元素是否存在，存在返回true，否则返回false

在无序序列中不可用

bool binary_search(iterator beg, iterator end，value);

beg:开始迭代器

end:结束迭代器

value:查找的元素

```cpp
vector<int> v;
for(int i = 0; i<10; i++) {
    v.push_back(i);
}
bool ret = binary_search(v.begin(),v.end(),9);
if (ret) {cout<<"找到了"<<endl;}
else {cout<<"没有找到"<<endl;}
```

##### count()

统计元素个数(出现次数)

count(iterator beg, iterator end, value);

beg:开始迭代器

end:结束迭代器

value:统计的元素

```cpp
//内置数据类型
vector<int> v;
v.push_back(10);
v.push_back(40);
v.push_back(30);
v.push_back(20);
v.push_back(40);
v.push_back(20);
int num = count(v.begin(),v.end(),40);
cout<<"40出现次数"<<num<<endl;
```

```cpp
//自定义类型
class Person {
    Person(string name,int age){
        m_name = name;
        m_age = age;
    }
    //重载==，让底层find知道如何对比Person数据类型
    bool operator==(const Person& p) {
        return (this->m_age == p.m_age);
    }
    string m_name;
    int m_age;
}
vector<Person> v;
Person p1("刘备",24);
Person p2("关羽",28);
Person p3("张飞",25);
Person p4("赵云",21);
v.insert(p1);
v.insert(p2);
v.insert(p3);
v.insert(p4);
Person p("诸葛亮",21);
int num = count(v.begin(),v.end(),p);
cout<<"和诸葛亮同岁的人员个数"<<num<<endl;
```

##### count_if()

按条件统计元素个数

count_if(iterator beg, iterator end,_Pred)

找到返回指定元素的迭代器，找不到返回结束迭代器

beg:开始迭代器

end:结束迭代器

_Pred:谓词(返回bool类型)

```cpp
//内置数据类型
class Greater20 {
public:
    bool operator()(int val) {
        return val > 20;
    }
}
vector<int> v;
v.push_back(10);
v.push_back(40);
v.push_back(30);
v.push_back(20);
v.push_back(40);
v.push_back(20);
int num = count(v.begin(),v.end(),Greater20);
cout<<"大于20的元素出现次数"<<num<<endl;
```

```cpp
//自定义类型
class Person {
    Person(string name,int age){
        m_name = name;
        m_age = age;
    }
    string m_name;
    int m_age;
}
class AgeGreater20 {
public:
    bool operator()(const Person& p) {
        return p.m_age > 20;
    }
}
vector<Person> v;
Person p1("刘备",24);
Person p2("关羽",28);
Person p3("张飞",25);
Person p4("赵云",21);
v.insert(p1);
v.insert(p2);
v.insert(p3);
v.insert(p4);
int num = count(v.begin(),v.end(),AgeGreater20());
cout<<"年龄大于20的人员个数"<<num<<endl;
```

### 常用的排序算法

sort();//对容器内元素进行排序

random_shuffle();//洗牌，指定范围内的元素随机调整次序

merge();//容器元素合并，并存储到另一个容器中

reverse();//反转指定范围的元素

##### sort()

对容器内元素进行排序

sort(interator beg, iterator end, _Pred);

beg:开始迭代器

end:结束迭代器

_Pred:谓词(返回bool类型)

```cpp
vector<int> v;
v.push_back(10);
v.push_back(30);
v.push_back(50);
v.push_back(20);
v.push_back(40);
sort(v.begin(),v.end());//默认升序

sort(v.begin(),v.end(),greater<int>());//使用内建函数对象，降序

class MyCompare {
public:
    bool operator()(int val1,int val2) {
        return val1 > val2;
    }
}
sort(v.begin(),v.end(),MyCompare());//使用谓词，降序
```

##### random_shuffle()

洗牌，指定范围内的元素随机调整次序

random_shuffle(interator beg, iterator end)

beg:开始迭代器

end:结束迭代器

```cpp
#include<ctime>
//没有随机种子的话，每次打乱顺序都是一样的。
srand((unsigned int)time(NULL));//初始化随机种子
vector<int> v;
for(int i = 0; i<10; i++) {
    v.push_back(i);
}
random_shuffle(v.begin(), v.end());
```

##### merge()

容器元素合并，并存储到另一个容器中

两个容器必须是有序的,合并后也是有序

merge(interator beg1, iterator end1, interator beg2, iterator end2,iterator dest);

beg1:容器1开始迭代器

end2:容器1结束迭代器

beg1:容器2开始迭代器

end2:容器2结束迭代器

dest:目标容器开始迭代器

```cpp
vector<int> v;
vector<int> v2;
for(int i = 0; i<10; i++) {
    v.push_back(i);
    v2.push_back(i+1);
}
vector<int>vTarget;
//提前给目标容器分配空间
vTarget.resize(v1.size()+v2.size());
merge(v1.begin(),v1.end(),v2.begin(),v2.end(),vTarget.begin())
```

##### reverse()

反转指定范围的元素

reverse(interator beg, iterator end);

beg:开始迭代器

end:结束迭代器

```cpp
vector<int> v;
v.push_back(10);
v.push_back(30);
v.push_back(50);
v.push_back(20);
v.push_back(40);
reverse(v.begin(), v.end());//首尾对调
```

### 常用拷贝和替换算法

copy();//容器内指定范围的元素拷贝到另一个容器

replace();//将容器内指定范围的旧元素修改为新元素

replace_if();//将容器内指定范围满足条件的旧元素修改为新元素

swap();//互换两个容器的元素

##### copy()

容器内指定范围的元素拷贝到另一个容器

copy(interator beg, iterator end, iterator dest);

beg:开始迭代器

end:结束迭代器

dest:目标开始迭代器

```cpp
vector<int> v1;
for(int i = 0; i<10; i++) {
    v1.push_back(i);
}
vector<int> v2;
v2.resize(v1.size());
copy(v1.begin(),v1.end(),v2.begin());
```

##### replace()

将容器内指定范围的旧元素修改为新元素

replace(interator beg, iterator end, oldvalue, newvalue);

beg:开始迭代器

end:结束迭代器

oldvalue:旧元素

newvalue:新元素

```cpp
vector<int> v;
v.push_back(20);
v.push_back(30);
v.push_back(50);
v.push_back(30);
v.push_back(40);
v.push_back(20);
v.push_back(10);
v.push_back(20);
replace(v.begin(),v.end(),20,2000);//20替换成2000
```

##### replace_if()

将容器内指定范围满足条件的旧元素修改为新元素

replace_if(interator beg, iterator end, _Pred, newvalue);

beg:开始迭代器

end:结束迭代器

_Pred:谓词

newvalue:新元素

```cpp
class Greater30 {
public:
    bool operator()(int val) {
        return val >= 30;
    }
};
vector<int> v;
v.push_back(10);
v.push_back(40);
v.push_back(20);
v.push_back(40);
v.push_back(50);
v.push_back(20);
v.push_back(30);
replace_if(v.begin(),v.end(),Greater30,3000);//大于等于30的替换成3000
```

##### swap()

互换两个容器的元素

交换容器需要同种类型

swap(container c1, container c2);

c1:容器1

c2:容器2

```cpp
vector<int> v1;
vector<int> v2;
for(int i = 0; i<10; i++) {
    v1.push_back(i);
    v2.push_back(i+100);
}
swap(v1,v2);
```

### 常用算术生成算法

\<numeric>

accumulate();//计算容器元素累计总和

fill();//向容器中添加元素

##### accumulate()

计算容器元素累计总和

accumulate(iterator beg, iterator end, value);

beg:开始迭代器

end:结束迭代器

value:起始累加值

```cpp
#include<numeric>
vector<int> v;
for(int i = 0; i<=100; i++) {
    v.push_back(i);
}
accumulate(v.begin(),v.end(),0);
```

##### fill()

向容器中添加元素

fill(iterator beg, iterator end, value);

beg:开始迭代器

end:结束迭代器

value:填充的值

```cpp
#include<numeric>
vector<int> v;
v.resize(10);
accumulate(v.begin(),v.end(),1);//10个1
```

利用fill可以将容器区间内元素填充为指定的值

##### 常用集合算法

set_intersection();//求两个容器的交集

set_union();//求两个容器的并集

set_difference();//求两个容器的差集

##### set_intersection()

求两个容器的交集,返回一个迭代器

两个集合需要是有序的

set_intersection(interator beg1, iterator end1, interator beg2, iterator end2,iterator dest);

beg1:容器1开始迭代器

end2:容器1结束迭代器

beg1:容器2开始迭代器

end2:容器2结束迭代器

dest:目标容器开始迭代器

```cpp
void print(int val) {cout<<val<<endl;}
vector<int> v1;
vector<int> v2;
for(int i = 0; i<10; i++) {
    v1.push_back(i);
    v2.push_back(i+5);
}
vector<int> vTarget;
//开辟空间，取两者小值
vTarget.resize(min(v1.size(),v2.size()));
//返回值是交集中最后一个元素的位置
vector<int>::iterator itEnd = set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),vTarget.begin());
for_each(vTarget.begin(),itEnd,print);
//这里用itEnd而不用vTarget.end()是因为。开辟空间时，是往大了的开的。比如v1.size()=10，v2.size()=10，所以vTarget.size()=10.但是这时候交集元素有5个，那么如果用vTarget.end()就会输出10个数据。
```

##### set_union()

求两个容器的并集

两个集合需要是有序的

set_union(interator beg1, iterator end1, interator beg2, iterator end2,iterator dest);

beg1:容器1开始迭代器

end2:容器1结束迭代器

beg1:容器2开始迭代器

end2:容器2结束迭代器

dest:目标容器开始迭代器

```cpp
void print(int val) {cout<<val<<endl;}
vector<int> v1;
vector<int> v2;
for(int i = 0; i<10; i++) {
    v1.push_back(i);
    v2.push_back(i+5);
}
vector<int> vTarget;
//开辟空间，取两者大值
vTarget.resize(max(v1.size(),v2.size()));
//返回值是并集中最后一个元素的位置
vector<int>::iterator itEnd = set_union(v1.begin(),v1.end(),v2.begin(),v2.end(),vTarget.begin());
for_each(vTarget.begin(),itEnd,print);
```

##### set_difference()

求两个容器的差集

两个集合需要是有序的

set_difference(interator beg1, iterator end1, interator beg2, iterator end2,iterator dest);

beg1:容器1开始迭代器

end2:容器1结束迭代器

beg1:容器2开始迭代器

end2:容器2结束迭代器

dest:目标容器开始迭代器

```cpp
void print(int val) {cout<<val<<endl;}
vector<int> v1;
vector<int> v2;
for(int i = 0; i<10; i++) {
    v1.push_back(i);
    v2.push_back(i+5);
}
vector<int> vTarget;
//开辟空间，取两者之和
vTarget.resize(v1.size()+v2.size());
//返回值是差集中最后一个元素的位置
vector<int>::iterator itEnd = set_difference(v1.begin(),v1.end(),v2.begin(),v2.end(),vTarget.begin());
for_each(vTarget.begin(),itEnd,print);
```