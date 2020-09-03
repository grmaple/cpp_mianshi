/*************************************************************************
	> 作者: grmaple
	> 名字：职工管理系统
	> 功能: 职工管理系统
	> 时间: 2020.9.3
 ************************************************************************/

#include<iostream>
using namespace std;
#include<fstream>
#define FILENAME "empFile.txt"
class Worker {
public:
	//显示个人信息
	virtual void showInfo() = 0;
	//获取岗位名称
	virtual string getDeptName() = 0;

	int m_Id;//职工编号
	string m_Name;//职工姓名
	int m_DeptId;//职工所在部门名称编号
};
class Employee:public Worker {
public:
	Employee(int id, string name, int dId);
	virtual void showInfo();
	virtual string getDeptName();
};
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
class Manager :public Worker {
public:
	Manager(int id, string name, int dId);
	virtual void showInfo();
	virtual string getDeptName();
};
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
class Boss :public Worker {
public:
	Boss(int id, string name, int dId);
	virtual void showInfo();
	virtual string getDeptName();
};
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
class WorkerManager {
public:
	WorkerManager();
	~WorkerManager();
	//展示菜单
	void Show_Menu();
	//退出功能
	void exitSystem();
	//增加职工
	void Add_Emp();
	//保存文件
	void save();
	//统计文件中人数
	int get_EmpNum();
	//初始化员工
	void init_Emp();
	//显示职工
	void Show_Emp();
	//按照职工编号判断职工是否存在
	int IsExist(int id);
	//删除职工
	void Del_Emp();
	//修改职工
	void Mod_Emp();
	//查找职工
	void Find_Emp();
	//排序职工
	void Sort_Emp();
	//清空文件
	void Clean_File();

	int m_EmpNum;//记录文件中的人数
	Worker** m_EmpArray;//员工数组的指针
	bool m_FileIsEmpty;//标志文件是否为空
};
WorkerManager::WorkerManager(){
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//文件不存在
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		m_EmpNum = 0;
		m_FileIsEmpty = true;
		m_EmpArray = NULL;
		ifs.close();
		return ;
	}
	//文件存在，并且没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空" << endl;
		m_EmpNum = 0;
		m_FileIsEmpty = true;
		m_EmpArray = NULL;
		ifs.close();
		return;
	}
	//文件存在，并且有记录
	int num = get_EmpNum();
	//cout << "职工个数为：" << num << endl;
	m_EmpNum = num;
	m_EmpArray = new Worker*[m_EmpNum];
	init_Emp();
	//for (int i = 0; i < m_EmpNum; i++) {
	//	cout << m_EmpArray[i]->m_Id << " "
	//		<< m_EmpArray[i]->m_Name << " "
	//		<< m_EmpArray[i]->m_DeptId << endl;
	//}
}
WorkerManager::~WorkerManager(){
	if (m_EmpArray != NULL) {
		for (int i = 0; i < m_EmpNum; i++) {
			if (m_EmpArray[i] != NULL) {
				delete m_EmpArray[i];
			}
		}
		//m_EmpNum = 0;
		delete[] m_EmpArray;
		m_EmpArray = NULL;
		//m_FileIsEmpty = true;
	}
}
void WorkerManager::Show_Menu() {
	cout << "*********************************" << endl;
	cout << "***** 欢迎使用职工管理系统! *****" << endl;
	cout << "******** 0、退出管理程序 ********" << endl;
	cout << "******** 1、增加职工信息 ********" << endl;
	cout << "******** 2、显示职工信息 ********" << endl;
	cout << "******** 3、删除离职职工 ********" << endl;
	cout << "******** 4、修改职工信息 ********" << endl;
	cout << "******** 5、查找职工信息 ********" << endl;
	cout << "******** 6、按照编号排序 ********" << endl;
	cout << "******** 7、清空所有文档 ********" << endl;
	cout << "*********************************" << endl;
	cout << endl;
}
void WorkerManager::exitSystem() {
	cout << "欢迎下次使用" <<endl;
	system("pause");
	exit(0);
}
void WorkerManager::Add_Emp() {
	cout << "请输入增加职工数量" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		//计算新空间大小
		int newSize = m_EmpNum + addNum;
		//开辟新空间
		Worker** newSpace = new Worker*[newSize];
		//将原空间下内容存放到新空间下
		if (m_EmpArray != NULL) {
			for (int i = 0; i < m_EmpNum; i++) {
				newSpace[i] = m_EmpArray[i];
			}
		}
		//输入新数据
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i+1 << "个新职工编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
			cin >> name;
			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect){
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[m_EmpNum + i] = worker;
		}
		//释放原有空间
		delete[] m_EmpArray;
		//更改新空间的指向
		m_EmpArray = newSpace;
		//更新新的职工人数
		m_EmpNum = newSize;
		//更新职工不为空标志
		m_FileIsEmpty = false;
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工！" <<endl;
		//保存到文件中
		save();
	}
	else {
		cout << "输入有误" <<endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < m_EmpNum; i++) {
		ofs << m_EmpArray[i]->m_Id << " "
			<< m_EmpArray[i]->m_Name << " "
			<< m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		//读入一条数据，人数+1
		num++;
	}
	ifs.close();
	return num;
}
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;
		if (dId == 1) {
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {
			worker = new Manager(id, name, dId);
		}
		else {
			worker = new Boss(id, name, dId);
		}
		//存放在数组中
		m_EmpArray[index] = worker;
		index++;
	}
}
void WorkerManager::Show_Emp() {
	if (m_FileIsEmpty) {
		cout << "文件不存在或者记录为空！" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			//利用多态调用接口
			m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < m_EmpNum; i++) {
		if (m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}
void WorkerManager::Del_Emp() {
	if (m_FileIsEmpty) {
		cout << "文件不存在或者记录为空！" << endl;
	}
	else {
		cout << "请输入想要删除的职工号：" << endl;
		int id = 0;
		cin >> id;
		int index = IsExist(id);
		if (index != -1) {
			for (int i = index; i < m_EmpNum; i++) {
				m_EmpArray[i] = m_EmpArray[i + 1];
			}
			m_EmpNum--;
			save();
			cout << "删除成功" << endl;
		}
		else {
			cout << "删除失败，查无此人！" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Mod_Emp() {
	if (m_FileIsEmpty) {
		cout << "文件不存在或者记录为空！" << endl;
	}
	else {
		cout << "请输入想要修改的职工号：" << endl;
		int id = 0;
		cin >> id;
		int index = IsExist(id);
		if (index != -1) {
			delete m_EmpArray[index];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "查到：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newId;
			cout << "请输入新姓名：" << endl;
			cin >> newName;
			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(newId, newName, 1);
				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}
			//更改数据到数组中
			m_EmpArray[index] = worker;
			cout << "修改成功" << m_EmpArray[index]->m_DeptId << endl;
			//保存到文件
			save();
		}
		else {
			cout << "修改失败，查无此人！" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Find_Emp() {
	if (m_FileIsEmpty) {
		cout << "文件不存在或者记录为空！" << endl;
	}
	else {
		cout << "请输入查找方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "请输入想要查找的职工号：" << endl;
			cin >> id;
			int index = IsExist(id);
			if (index != -1) {
				cout << "查找成功!该职工信息如下：" << endl;
				m_EmpArray[index]->showInfo();
			}
			else {
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "请输入想要查找的职工姓名：" << endl;
			cin >> name;
			bool flag = false;//查找到的标志
			for (int i = 0; i < m_EmpNum; i++) {
				if (m_EmpArray[i]->m_Name == name) {
					cout << "查找成功,该职工编号为：" << m_EmpArray[i]->m_Id << ",其信息如下：" << endl;
					flag = true;
					m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false) {
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else {
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::Sort_Emp() {
	if (m_FileIsEmpty) {
		cout << "文件不存在或者记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请输入排序方式：" << endl;
		cout << "1、按职工编号进行升序" << endl;
		cout << "2、按职工编号进行降序" << endl;
		int select = 0;
		cin >> select;
		//选择排序
		for (int i = 0; i < m_EmpNum; i++) {
			int minOrMax = i;
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (select == 1) {//升序
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else {//降序
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax) {
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功，排序后结果为：" << endl;
		save();
		Show_Emp();
	}
}
void WorkerManager::Clean_File() {
	cout << "确定清空？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		//打开模式，如果存在则删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (m_EmpArray != NULL) {
			for (int i = 0; i < m_EmpNum; i++) {
				if (m_EmpArray[i] != NULL) {
					delete m_EmpArray[i];
				}
			}
			m_EmpNum = 0;
			delete[] m_EmpArray;
			m_EmpArray = NULL;
			m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

int main() {
	WorkerManager wm;
	int choice = 0;
	while (true) {
		wm.Show_Menu();
		cout << "请输入你的选择：" <<endl;
		cin >> choice;
		switch (choice){
		case 0://退出系统
			wm.exitSystem();
			break;
		case 1://添加职工
			wm.Add_Emp();
			break;
		case 2://显示职工
			wm.Show_Emp();
			break;
		case 3://删除职工
			wm.Del_Emp();
			break;
		case 4://修改职工
			wm.Mod_Emp();
			break;
		case 5://查找职工
			wm.Find_Emp();
			break;
		case 6://排序职工
			wm.Sort_Emp();
			break;
		case 7://清空文件
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}