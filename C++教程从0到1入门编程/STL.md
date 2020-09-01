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

