#include<iostream>
using namespace std;
#include<fstream>
#include<string>
#include"identity.h"
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"

void LoginIn(string fileName, int type);
void managerMenu(Identity* &manager);
void studentMenu(Identity* &student);
void teacherMenu(Identity* &teacter);

//登录函数
void LoginIn(string fileName, int type) {
	Identity* person = NULL;
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		ifs.close();
		return ;
	}
	int id = 0;
	string name;
	string pwd;
	if (type == 1) {
		cout << "请输入你的学号" << endl;
		cin >> id;
	}
	else if (type == 2) {
		cout << "请输入你的职工号" << endl;
		cin >> id;
	}
	cout << "请输入用户名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;
	if (type == 1) {
		//学生登录验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (id == fId && name == fName && pwd == fPwd) {
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//进入学生身份的子菜单
				studentMenu(person);
				return ;
			}
		}
	}
	else if (type == 2) {
		//教师登录验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (id == fId && name == fName && pwd == fPwd) {
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//进入教师身份的子菜单
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3) {
		//管理员登录验证
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd) {
			if (name == fName && pwd == fPwd) {
				cout << "验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				//进入管理员身份的子菜单
				managerMenu(person);
				return;
			}
		}
	}
	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");
	return ;
}
//管理员菜单
void managerMenu(Identity* &manager) {
	while (true) {
		manager->operMenu();
		Manager* man = (Manager*)manager;
		int select = 0;
		cin >> select;
		switch (select) {
		case 1://添加账号
			cout << "添加账号" << endl;
			man->addPerson();
			break;
		case 2://查看账号
			cout << "查看账号" << endl;
			man->showPerson();
			break;
		case 3://查看机房
			cout << "查看机房" << endl;
			man->showComputer();
			break;
		case 4://清空预约
			cout << "清空预约" << endl;
			man->cleanFile();
			break;
		default:
			delete manager;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return ;
		}
	}
}
//学生菜单
void studentMenu(Identity* &student) {
	while (true) {
		student->operMenu();
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		switch (select) {
		case 1://申请预约
			cout << "申请预约" << endl;
			stu->applyOrder();
			break;
		case 2://查看我的预约
			cout << "查看我的预约" << endl;
			stu->showMyOrder();
			break;
		case 3://查看所有预约
			cout << "查看所有预约" << endl;
			stu->showAllOrder();
			break;
		case 4:///取消预约
			cout << "取消预约" << endl;
			stu->cancelOrder();
			break;
		default:
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//教师菜单
void teacherMenu(Identity* &teacter) {
	while (true) {
		teacter->operMenu();
		Teacher* man = (Teacher*)teacter;
		int select = 0;
		cin >> select;
		switch (select) {
		case 1://查看所有预约
			cout << "查看所有预约" << endl;
			man->showAllOrder();
			break;
		case 2://审核预约
			cout << "审核预约" << endl;
			man->validOrder();
			break;
		default:
			delete teacter;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
int main() {
	int select = 0;

	while (true) {
		cout << "=====================欢迎来到机房预约系统=====================" << endl;
		cout << "请输入你的身份" << endl;
		cout << "\t\t ------------------------------" << endl;
		cout << "\t\t|                              |" << endl;
		cout << "\t\t|          1.学生代表          |" << endl;
		cout << "\t\t|                              |" << endl;
		cout << "\t\t|          2.老    师          |" << endl;
		cout << "\t\t|                              |" << endl;
		cout << "\t\t|          3.管 理 员          |" << endl;
		cout << "\t\t|                              |" << endl;
		cout << "\t\t|          0.退    出          |" << endl;
		cout << "\t\t|                              |" << endl;
		cout << "\t\t ------------------------------" << endl;
		cout << " 输入你的选择：" << endl;

		cin >> select;
		switch (select) {
		case 1://学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://退出系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			exit(0);
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}