/*************************************************************************
	> 作者: grmaple
	> 名字：点和圆的关系
	> 功能: 设计圆类和点类，计算点和圆关系
	> 时间: 2020.9.2
 ************************************************************************/

#include<iostream>
using namespace std;
#include <cmath>
class Point {
public:
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();
private:
	int m_X;
	int m_Y;
};
void Point::setX(int x){m_X = x;}
int Point::getX() {return m_X;}
void Point::setY(int y){m_Y = y;}
int Point::getY() {return m_Y;}
class Circle {
public:
	void setR(int r);
	int getR();
	void setCenter(const Point& center);
	Point getCenter();
private:
	int m_R;//半径
	Point m_Center;//圆心
};
void Circle::setR(int r){m_R = r;}
int Circle::getR() {return m_R;}
void Circle::setCenter(const Point& center){m_Center = center;}
Point Circle::getCenter() {return m_Center;}

void isInCircle(Circle& c, Point& p) {
	//计算两点之间距离平方
	int distance = 
	pow((c.getCenter().getX() - p.getX()),2) + 
	pow((c.getCenter().getY() - p.getY()),2);
	//计算半径平方
	int r_distance = pow(c.getR(),2);
	//判断关系
	if (distance == r_distance) {cout <<"点在圆上"<<endl;}
	else if (distance > r_distance) {cout <<"点在圆外"<<endl;}
	else {cout <<"点在圆内"<<endl;}
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
	
	isInCircle(c,p);
	return 0;
}