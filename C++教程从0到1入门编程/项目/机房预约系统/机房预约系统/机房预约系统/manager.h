#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include<vector>
#include"computerRoom.h"
class Manager :public Identity {
public:
	Manager();
	~Manager();
	Manager(string name, string pwd);
	//菜单界面
	virtual void operMenu();
	//添加账号
	void addPerson();
	//查看账号
	void showPerson();
	//查看机房信息
	void showComputer();
	//清空预约记录
	void cleanFile();
	//初始化容器
	void initVector();
	//去重函数
	bool checkRepeat(int id, int type);

	vector<Student> vStu;//学生容器
	vector<Teacher> vTea;//教师容器
	vector<ComputerRoom> vCom;//机房容器
};