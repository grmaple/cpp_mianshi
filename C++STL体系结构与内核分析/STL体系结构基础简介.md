## STL体系结构基础简介

### 我们的第一个C++STL应用

##### STL六大部件

容器、分配器、算法、迭代器、适配器、仿函数

![image-20200905220006087](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200905220006087.png)

分配器给容器分配存储空间，

算法通过迭代器获取容器中的内容，

仿函数可以协助算法完成各种操作，

配接器用来修饰容器或者仿函数或迭代器

![image-20200905220834747](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200905220834747.png)

```cpp
#include<vector>
#include<algorithm>
#include<functional>
#include<iostream>
using namespace std;

int main() {
    int ia[6] = {27,21-,12,47,109,83};
    vector<int,allocator<int>> vi(ia,ia+6);
    cout<<count_if(vi.begin(),vi.end(),notl(bind2nd(less<int>(),40)));//计算大于等于40的数量
    return 0;
}
```

### 复杂度

大O表示法

O(1)常数时间

O(logn)次线性时间

O(n)线性时间

O(nlogn)介于线性时间于平方时间之间

O(n^2)平方时间

O(n^3)立方时间

O(2^n)指数时间

### 前闭后开区间

迭代器

begin()指向容器第一个元素

end()指向容器最后一个元素的下一个元素

```cpp
vector<double> vec;
vector<double>::iterator ite = vec.begin();
for(;ite!=vec.end();ite++) {
    cout<<elem<<endl;
}
```

### range-based for statement

```cpp
for (int i : {1,2,3,4}) {
    cout<<i<<endl;
}

vector<double> vec;
for(auto elem : vec) {
    cout<<elem<<endl;
}//值传递，形参不影响实参
for(auto elem& : vec) {
    elem *= 3;
}//引用传递，形参影响实参
```

### auto

```cpp
list<string> c;
list<string>::iterator ite;
ite = find(c.begin(),c.end(),target);
```

```cpp
list<string> c;
auto ite;
ite = find(c.begin(),c.end(),target);
```

