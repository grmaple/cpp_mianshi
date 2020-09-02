/*************************************************************************
	> 作者: grmaple
	> 名字：学生类
	> 功能: 创建学生类
	> 时间: 2020.9.2
 ************************************************************************/

#include<iostream>
using namespace std;
#include<string>

class Student {
public:
	void setName(const string& name) {
		m_Name = name;
	}
	void setID(const int& id) {
		m_id = id;
	}
	void showStudent(){
		cout << "姓名：" << m_Name <<endl;
		cout << "学号：" << m_id <<endl;
	}
private:
	string m_Name;
	int m_id;
};

int main() {
	Student stu;
	stu.setName("xu");
	stu.setID(1920);
	stu.showStudent();
	return 0;
}