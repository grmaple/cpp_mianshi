#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"identity.h"
#include"computerRoom.h"
#include<vector>
class Student :public Identity {
public:
	Student();
	~Student();
	Student(int id, string name, string pwd);
	//菜单界面
	virtual void operMenu();
	//申请预约
	void applyOrder();
	//查看我的预约
	void showMyOrder();
	//查看所有预约
	void showAllOrder();
	//取消预约
	void cancelOrder();

	int m_Id;//学生学号
	vector<ComputerRoom> vCom;//机房容器
};