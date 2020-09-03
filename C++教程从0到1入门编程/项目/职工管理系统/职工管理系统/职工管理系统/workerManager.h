#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
#include<fstream>
#define FILENAME "empFile.txt"
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
