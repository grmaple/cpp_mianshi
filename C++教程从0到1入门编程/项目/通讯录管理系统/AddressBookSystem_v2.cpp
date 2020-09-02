/*************************************************************************
	> 作者: grmaple
	> 名字：通讯录管理系统
	> 功能: 退出通讯录
	> 时间: 2020.9.2
 ************************************************************************/

#include<iostream>
using namespace std;
void showMenu() {
	cout << "*************************" <<endl;
	cout << "***** 1、添加联系人 *****" << endl;
	cout << "***** 2、显示联系人 *****" << endl;
	cout << "***** 3、删除联系人 *****" << endl;
	cout << "***** 4、查找联系人 *****" << endl;
	cout << "***** 5、修改联系人 *****" << endl;
	cout << "***** 6、清空联系人 *****" << endl;
	cout << "***** 0、清空通讯录 *****" << endl;
	cout << "*************************" << endl;
}

int main() {
	int select = 0;
	
	while (true) {
		showMenu();
		cin >> select;
		switch (select) {
		case 1://1、添加联系人
			break;
		case 2://2、显示联系人
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