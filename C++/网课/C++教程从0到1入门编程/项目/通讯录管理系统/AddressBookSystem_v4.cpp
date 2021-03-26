/*************************************************************************
	> 作者: grmaple
	> 名字：通讯录管理系统
	> 功能: 显示联系人
	> 时间: 2020.9.2
 ************************************************************************/

#include<iostream>
using namespace std;
#include<string>
#define MAX 1000

void showMenu() {
	cout << "*************************" << endl;
	cout << "***** 1、添加联系人 *****" << endl;
	cout << "***** 2、显示联系人 *****" << endl;
	cout << "***** 3、删除联系人 *****" << endl;
	cout << "***** 4、查找联系人 *****" << endl;
	cout << "***** 5、修改联系人 *****" << endl;
	cout << "***** 6、清空联系人 *****" << endl;
	cout << "***** 0、清空通讯录 *****" << endl;
	cout << "*************************" << endl;
}
struct Person {
	string m_Name;
	int m_Sex;
	int m_Age;
	string m_Phone;
	string m_Addr;
};
struct Addressbooks {
	struct Person personArray[MAX];
	int m_Size;
};
//添加联系人
void addPerson(Addressbooks& abs) {
	//先判断通讯录有没有满
	if (abs.m_Size == MAX) {
		cout << "通讯录已满，无法添加！" <<endl;
		return ;
	} else {
		//姓名
		string name;
		cout << "请输入姓名：" <<endl;
		cin >> name;
		abs.personArray[abs.m_Size].m_Name = name;
		//性别
		int sex = 0;
		cout << "请输入性别(1:男,2:女)：" <<endl;
		while (1) {
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs.personArray[abs.m_Size].m_Sex = sex;
				break;
			}
			cout << "输入有误，请重新输入" <<endl;
		}
		//年龄
		int age = 0;
		cout << "请输入年龄：" <<endl;
		while (1) {
			cin >> age;
			if (age >= 0 && age <= 100) {
				abs.personArray[abs.m_Size].m_Age = age;
				break;
			}
			cout << "输入有误，请重新输入" <<endl;
		}
		//联系电话
		string phone;
		cout << "请输入联系电话：" <<endl;
		cin >> phone;
		abs.personArray[abs.m_Size].m_Phone = phone;
		//家庭住址
		string address;
		cout << "请输入家庭住址：" <<endl;
		cin >> address;
		abs.personArray[abs.m_Size].m_Addr = address;
		//更新通讯录人数
		abs.m_Size++;
		cout<< "添加成功" <<endl;
		system("pause");//按任意键继续
		system("cls");//清屏
	}
}
//显示联系人
void showPerson(Addressbooks& abs) {
	if (abs.m_Size == 0) {
		cout << "当前记录为空" <<endl;
	} else {
		for (int i = 0; i < abs.m_Size; i++) {
			cout << "姓名：" << abs.personArray[i].m_Name <<'\t';
			cout << "性别：" << (abs.personArray[i].m_Sex == 1 ? "男":"女") <<'\t';
			cout << "年龄：" << abs.personArray[i].m_Age <<'\t';
			cout << "电话：" << abs.personArray[i].m_Phone <<'\t';
			cout << "住址：" << abs.personArray[i].m_Addr <<endl;
		}
	}
	system("pause");
	system("cls");
}
int main() {
	int select = 0;
	Addressbooks abs;
	abs.m_Size = 0;
	
	while (true) {
		showMenu();
		cin >> select;
		switch (select) {
		case 1://1、添加联系人
			addPerson(abs);
			break;
		case 2://2、显示联系人
			showPerson(abs);
			break;
		case 3://3、删除联系人
			break;
		case 4://4、查找联系人
			break;
		case 5://5、修改联系人
			break;
		case 6://6、清空联系人
			break;
		case 0://0、清空通讯录
			cout << "欢迎下次使用" << endl;
			return 0;
		default:
			break;
		}
	}
	
	
	//system("pause");
	return 0;
}