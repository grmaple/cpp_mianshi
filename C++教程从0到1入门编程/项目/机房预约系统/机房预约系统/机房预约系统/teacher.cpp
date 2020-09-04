#include"teacher.h"
#include<string>
#include"orderFile.h"
#include<vector>
Teacher::Teacher() {

}
Teacher::~Teacher() {

}
Teacher::Teacher(int id, string name, string pwd) {
	m_EmpID = id;
	m_Name = name;
	m_Pwd = pwd;
}
//菜单界面
void Teacher::operMenu() {
	cout << "欢迎教师：" << m_Name << "登录！" << endl;
	cout << "\t\t ------------------------------" << endl;
	cout << "\t\t|                              |" << endl;
	cout << "\t\t|          1.查看所有预约      |" << endl;
	cout << "\t\t|                              |" << endl;
	cout << "\t\t|          2.审核预约          |" << endl;
	cout << "\t\t|                              |" << endl;
	cout << "\t\t|          0.注销登录          |" << endl;
	cout << "\t\t|                              |" << endl;
	cout << "\t\t ------------------------------" << endl;
	cout << " 输入你的选择：" << endl;
}
//查看所有预约
void Teacher::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++) {
		cout << i + 1 << "、 ";
		cout << "预约日期:周" << of.m_orderData[i]["date"] << "\t";
		cout << "时段:" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "\t";
		cout << "学号:" << of.m_orderData[i]["stuId"] << "\t";
		cout << "姓名:" << of.m_orderData[i]["stuName"] << "\t";
		cout << "机房:" << of.m_orderData[i]["roomId"] << "\t";
		string status = "状态:";//0取消的预约，1审核中，2已预约，3预约失败
		if (of.m_orderData[i]["status"] == "1") {
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2") {
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "3") {
			status += "审核未通过，预约失败";
		}
		else {
			status += "预约已取消";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}
//待审核的预约记录
int toBeReviewed() {
	OrderFile of;
	vector<int> v;//存放符合条件的记录
	int index = 0;
	for (int i = 0; i < of.m_Size; i++) {
		if (of.m_orderData[i]["status"] == "1") {
			v.push_back(i);
		}
	}
	return v.size();
}
//审核预约
void Teacher::validOrder() {
	OrderFile of;
	int n = toBeReviewed();
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	if (n == 0) {
		cout << "无需要审核的预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "待审核的预约记录如下：" << endl;
	vector<int> v;//存放符合条件的记录
	int index =0;
	for (int i = 0; i < of.m_Size; i++) {
		if (of.m_orderData[i]["status"] == "1") {
			v.push_back(i);
			cout << ++index << "、 ";
			cout << "预约日期:周" << of.m_orderData[i]["date"] << "\t";
			cout << "时段:" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "\t";
			cout << "机房:" << of.m_orderData[i]["roomId"] << "\t";
			string status = "状态:";//0取消的预约，1审核中，2已预约，-1预约失败
			if (of.m_orderData[i]["status"] == "1") {
				status += "审核中";
			}
			cout << status << endl;
		}
	}
	cout << "请输入审核的预约记录，0表示返回" << endl;
	int select = 0;
	int ret = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				cout << "请输入审核结果" << endl;
				cout << "1、通过" << endl;
				cout << "2、不通过" << endl;
				cin >> ret;
				if (ret == 1) {
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else if (ret == 2) {
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "审核完毕！" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}