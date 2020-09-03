#include"manager.h"

Manager::Manager(int id, string name, int dId) {
	m_Id = id;
	m_Name = name;
	m_DeptId = dId;
}

void Manager::showInfo() {
	cout << "职工编号：" << m_Id << "\t";
	cout << "职工姓名：" << m_Name << "\t";
	cout << "岗位：" << getDeptName() << "\t";
	cout << "职工职责：完成老板交给的任务，并下发任务给员工" << endl;
}

string Manager::getDeptName() {
	return string("经理");
}