/**
 * @file myString.cpp
 * @brief 设计一个字符串类MyString，运算符重载
 * @author grmaple
 * @version v1
 * @date 2020-12-10
 */
#include<iostream>
#include<cstring>
using namespace std;
class MyString{
private:
    int length;
    char *sptr;
public:
    MyString(const char *str = "");
    const MyString &operator=(const MyString &s);
    const MyString &operator+=(const MyString &s);
    bool operator==(const MyString &s);
    bool operator!=(const MyString &s);
    bool operator!();
    bool operator<(const MyString &s) const;
    bool operator<=(const MyString &s);
    bool operator>(const MyString &s);
    bool operator>=(const MyString &s);
    char &operator[](int i);
    ~MyString();
};
MyString::MyString(const char *str){
    length = strlen(str);
    sptr = new char[strlen(str)+1];
    strcpy(sptr, str);
}
const MyString &MyString::operator=(const MyString &s){
    length = s.length;
    strcpy(sptr, s.sptr);
    return *this;
}
const MyString &MyString::operator+=(const MyString &s){
    char *temp = sptr;
    length += s.length;
    sptr = new char[length+1];
    strcpy(sptr, temp);
    strcat(sptr,s.sptr);
    delete[] temp;
    return *this;
}
bool MyString::operator==(const MyString &s){
    return strcmp(sptr,s.sptr) == 0;
}
bool MyString::operator!=(const MyString &s){
    return !(*this == s);//调用重载==函数
}
bool MyString::operator!(){
    return length == 0;
}
// 定义为const函数，const对象就能调用它。
bool MyString::operator<(const MyString &s) const{
    return strcmp(sptr, s.sptr)<0;
}
bool MyString::operator<=(const MyString &s){
    return !(*this>s);
}
bool MyString::operator>(const MyString &s){
    return s<*this;// 需要<是const函数
}
bool MyString::operator>=(const MyString &s){
    return !(*this<s);
}
char &MyString::operator[](int i){
    return sptr[i];
}
MyString::~MyString(){
    delete[] sptr;
}
