#pragma once
#include<iostream>
using namespace std;
#include<map>
#include"globalFile.h"
#include<string>
class OrderFile {
public:
	OrderFile();
	~OrderFile();
	//更新预约记录
	void updateOrder();
	//map<string, string> key代表属性，value代表实值
	//map<int, map<string, string>> key代表记录条数
	map<int, map<string, string>> m_orderData;//记录的容器
	int m_Size;//预约记录条数
};