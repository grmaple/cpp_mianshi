#pragma once
#include<iostream>
using namespace std;
#include<string>
//身份抽象类
class Identity {
public:
	//操作菜单
	virtual void operMenu() = 0;

	string m_Name;//姓名
	string m_Pwd;//密码
};