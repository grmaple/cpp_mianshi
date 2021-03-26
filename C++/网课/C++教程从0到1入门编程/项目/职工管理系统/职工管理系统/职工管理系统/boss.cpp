#include"boss.h"

Boss::Boss(int id, string name, int dId) {
	m_Id = id;
	m_Name = name;
	m_DeptId = dId;
}

void Boss::showInfo() {
	cout << "职工编号：" << m_Id << "\t";
	cout << "职工姓名：" << m_Name << "\t";
	cout << "岗位：" << getDeptName() << "\t";
	cout << "职工职责：管理公司所有事务" << endl;
}

string Boss::getDeptName() {
	return string("老板");
}