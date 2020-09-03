#include"employee.h"

Employee::Employee(int id, string name, int dId) {
	m_Id = id;
	m_Name = name;
	m_DeptId = dId;
}

void Employee::showInfo() {
	cout << "职工编号：" << m_Id << "\t";
	cout << "职工姓名：" << m_Name << "\t";
	cout << "岗位：" << getDeptName() << "\t";
	cout << "职工职责：完成经理交给的任务" << endl;
}

string Employee::getDeptName() {
	return string("员工");
}