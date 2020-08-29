## 复习string类的实现过程

```cpp
//mystring.h
#inndef __MYSTRING__
#define __MYSTRING__
//类声明
class String { 
public:
    String (const char* cstr = 0);
    String (const String& str);//拷贝构造
    String& operator = (const String& str);//拷贝赋值
    ~String();
    char* get_c_str() const {return m_data;}
private:
    char* m_data;
};
//类定义
#include <cstring>
inline
String::String(const char* cstr = 0) {
    if (cstr) {
        m_data = new char[strlen(cstr)+1];
        strcpy(m_data, cstr);
    }
    else {
        m_data = new char[1];
        *m_data = '\0';
    }
}

inline
String::~String() {
    delete[] m_data;
}

inline
String::String(const String& str) {
    m_data = new char[strlen(str.m_data)+1];
    strcpy(m_data, str.m_data);
}

//连续赋值时，返回值不能void
inline String& 
String operator = (const String& str){
    //检测自我赋值
    //&str是取地址，得到的是指针
    if (this == &str) return *this;
    delete[] m_data;
    m_data = new char[strlen(str.m_data)+1];
    strcpy(m_data, str.m_data);
    //*this是取值，得到的是指针指向的内容
    return *this;
}
#endif
```

```cpp
//string_test.cpp
#include <iostream>
#include "mystring.h"
using namespace std;
ostream&
operator << (ostream& os, const String& str){
    //得到指向内存空间的指针m_data。
    os << str.get_c_str();
    return os;
}
int main(){
	String s1();//没有初值的构造函数
    String s2("hello");//有初值的构造函数
    String s3(s1);//以s1为初值，创建s3，拷贝
    cout << s3 << endl;
    s3 = s2;//s2赋值给s3
    cout << s3;
}
```

带指针的类。需要考虑。

拷贝构造函数，拷贝赋值函数，析构函数。

new动态分配内存，记得delete。