/*************************************************************************
	> 作者: grmaple
	> 名字：点和圆的关系
	> 功能: 设计圆类和点类，计算点和圆关系
	> 时间: 2020.9.2
 ************************************************************************/

#include<iostream>
using namespace std;
#include <cmath>
#include"Point.h"
#include"Circle.h"

void isInCircle(Circle& c, Point& p) {
	//计算两点之间距离平方
	int distance =
		pow((c.getCenter().getX() - p.getX()), 2) +
		pow((c.getCenter().getY() - p.getY()), 2);
	//计算半径平方
	int r_distance = pow(c.getR(), 2);
	//判断关系
	if (distance == r_distance) { cout << "点在圆上" << endl; }
	else if (distance > r_distance) { cout << "点在圆外" << endl; }
	else { cout << "点在圆内" << endl; }
}
int main() {
	Circle c;
	c.setR(10);
	Point center;
	center.setX(10);
	center.setY(0);
	c.setCenter(center);

	Point p;
	p.setX(10);
	p.setY(11);

	isInCircle(c, p);
	system("pause");
	return 0;
}