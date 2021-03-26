#include"manager.h"
#include"globalFile.h"
#include<fstream>
#include<algorithm>
Manager::Manager() {

}
Manager::~Manager() {

}
Manager::Manager(string name, string pwd) {
	m_Name = name;
	m_Pwd = pwd;
	//初始化容器
	initVector();
	//获取机房信息，因为机房不会改动，只用一次所以没有封装成函数
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum) {
		vCom.push_back(c);
	}
	cout << "当前机房数量为：" << vCom.size() << endl;
	ifs.close();
}
//菜单界面
void Manager::operMenu() {
	cout << "欢迎管理员：" << m_Name << "登录！" << endl;
	cout << "\t\t ------------------------------" << endl;
	cout << "\t\t|                              |" << endl;
	cout << "\t\t|          1.添加账号          |" << endl;
	cout << "\t\t|                              |" << endl;
	cout << "\t\t|          2.查看账号          |" << endl;
	cout << "\t\t|                              |" << endl;
	cout << "\t\t|          3.查看机房          |" << endl;
	cout << "\t\t|                              |" << endl;
	cout << "\t\t|          4.清空记录          |" << endl;
	cout << "\t\t|                              |" << endl;
	cout << "\t\t|          0.注销登录          |" << endl;
	cout << "\t\t|                              |" << endl;
	cout << "\t\t ------------------------------" << endl;
	cout << " 输入你的选择：" << endl;
}
//添加账号
void Manager::addPerson() {
	cout << "请输入添加账号的类型：" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加教师" << endl;
	string fileName;
	string tip;
	ofstream ofs;
	string errorTip;
	int select = 0;
	cin >> select;
	if (select == 1) {
		fileName = STUDENT_FILE;
		tip = "请输入学号";
		errorTip = "学号重复，请重新输入";
	}
	else {
		fileName = TEACHER_FILE;
		tip = "请输入职工编号";
		errorTip = "职工号重复，请重新输入";
	}
	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while (true) {
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret) {
			cout << errorTip << endl;
		}
		else {
			break;
		}
	}
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;
	system("pause");
	system("cls");
	ofs.close();
	//每次添加完，要更新容器
	initVector();
}
void printStudent(Student& s) {
	cout << "学号：" << s.m_Id << "\t" << "姓名：" << s.m_Name << "\t" << "密码：" << s.m_Pwd << endl;
}
void printTeacher(Teacher& t) {
	cout << "职工：" << t.m_EmpID << "\t" << "姓名：" << t.m_Name << "\t" << "密码：" << t.m_Pwd << endl;
}
//查看账号
void Manager::showPerson() {
	cout << "请选择查看的内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有教师" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else if (select == 2) {
		cout << "所有教师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}
//查看机房信息
void Manager::showComputer() {
	cout << "机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++) {
		cout << "机房编号：" << it->m_ComId << "\t机房最大容量" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
//清空预约记录
void Manager::cleanFile() {
	ofstream ofs(ORDER_FILE,ios::trunc);
	ofs.close();
	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}
void Manager::initVector() {
	//读取学生文件信息
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		return;
	}
	vStu.clear();
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
		vStu.push_back(s);
	}
	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();
	//读取教师文件信息
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		return;
	}
	vTea.clear();
	Teacher t;
	while (ifs >> t.m_EmpID && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		vTea.push_back(t);
	}
	cout << "当前教师数量为：" << vTea.size() << endl;
	ifs.close();
}

bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++) {
			if (id == it->m_Id) {
				return true;
			}
		}
	}
	else {
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++) {
			if (id == it->m_EmpID) {
				return true;
			}
		}
	}
	return false;
}