#include <iostream>
using namespace std;

class Person{
public:
    Person(){
        cout << "Person的构造函数" << endl;
    }
    ~Person()    {
        cout << "删除Person对象 " << endl;
    }
private:
    int name;

};
class Student:public Person{
public:
    Student(){
        cout << "Student的构造函数" << endl;
    }
    ~Student()    {
        cout << "删除Student对象 " << endl;
    }
private:
    int name;
    string no;
};

int main() {
    Student student;

    return 0;
}