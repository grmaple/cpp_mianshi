/*************************************************************************
	> 作者: grmaple
	> 名字：立方体类
	> 功能: 创建立方体类
	> 时间: 2020.9.2
 ************************************************************************/

#include<iostream>
using namespace std;

class Cube {
public:
	void setL(int l) {m_L = l;}
	int getL() {return m_L;}
	void setW(int w) {m_W = w;}
	int getW() {return m_W;}
	void setH(int h) {m_H = h;}
	int getH() {return m_H;}
	int calculateS() {
		return 2*m_L*m_H + 2*m_H*m_W + 2*m_L*m_W;
	}
	int calculateV() {
		return m_H*m_L*m_W;
	}
	//成员函数，判断两个立方体是否相等
	bool isSameByClass(Cube& c) {
		if(this->getL() == c.getL() && this->getW() == c.getW() && this->getH() == c.getH()) {
			return true;
		} else {
			return false;
		}
	}
	
private:
	int m_H, m_L, m_W;
};
//全局函数，判断两个立方体是否相等
bool isSame(Cube& c1, Cube& c2) {
	if(c1.getL() == c2.getL() && c1.getW() == c2.getW() && c1.getH() == c2.getH()) {
		return true;
	} else {
		return false;
	}
}
int main() {
	Cube c1;
	c1.setL(10);
	c1.setW(10);
	c1.setH(10);
	cout << c1.calculateS() <<endl;
	cout << c1.calculateV() <<endl;
	
	Cube c2;
	c2.setL(10);
	c2.setW(10);
	c2.setH(11);
	bool ret = isSame(c1,c2);
	if (ret) {cout<<"c1和c2是相等的"<<endl;}
	else {cout<<"c1和c2是不相等的"<<endl;}
	
	ret = c2.isSameByClass(c1);
	if (ret) {cout<<"c1和c2是相等的"<<endl;}
	else {cout<<"c1和c2是不相等的"<<endl;}
	return 0;
}