## 认识header、版本、重要资源

使用一个东西，却不明白它的道理，不高明！

### 我们的目标

- 使用C++标准库
- 认识C++标准库
- 良好使用C++标准库
- 扩充C++标准库

### C++标准库和STL标准模板库

标准库以header files形式呈现

C++标准库的header files不带.h，如#include\<vector>

新式C header files不带.h，如#include\<cstdio>

旧式C header files带.h仍然可用，如#include<stdio.h>

新式header内的组件封装于namespace std;

using namespace std; 或 using std::cout;

旧式header内的组件不封装于namespace std;

因此，当使用<iostream.h>时，相当于在c中调用库函数，使用的是全局命名空间，也就是早期的c++实现；当使用\<iostream>的时候，该头文件没有定义全局命名空间，必须使用namespace std；这样才能正确使用cout。

### 重要网页

cplusplus.com

cppreference.com

gcc.gnu.org

### 书籍

《c++标准库》(第二版)

《STL源码剖析》