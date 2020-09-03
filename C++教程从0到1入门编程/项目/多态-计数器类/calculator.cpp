/*************************************************************************
	> 作者: grmaple
	> 名字：计算器类
	> 功能: 多态技术实现两个操作数进行运算
	> 时间: 2020.9.3
 ************************************************************************/

#include<iostream>
using namespace std;
#include<string>
class Calculator {
public:
	int getResult(string oper) {
		if (oper == "+") {
			return m_Num1+m_Num2;
		} else if (oper == "-") {
			return m_Num1-m_Num2;
		} else if (oper == "*") {
			return m_Num1*m_Num2;
		}
		//如果新添加新操作，需要修改源码
		//在开发中，我们提倡开闭原则
		//开闭原则：对扩展进行开放，对修改进行关闭
	}
	int m_Num1;
	int m_Num2;
};

//多态实现计算器
class AbstractCalculator {
public:
	virtual int getResult(){return 0;}
	int m_Num1;
	int m_Num2;
};
class AddCalculator :public AbstractCalculator {
public:
	int getResult(){return m_Num1+m_Num2;}
};
class SubCalculator :public AbstractCalculator {
public:
	int getResult(){return m_Num1-m_Num2;}
};
class MulCalculator :public AbstractCalculator {
public:
	int getResult(){return m_Num1*m_Num2;}
};
int main() {
	Calculator c;
	c.m_Num1 = 10;
	c.m_Num2 = 10;	
	cout<<c.m_Num1<<"+"<<c.m_Num2<<"="<<c.getResult("+")<<endl;
	cout<<c.m_Num1<<"-"<<c.m_Num2<<"="<<c.getResult("-")<<endl;
	cout<<c.m_Num1<<"*"<<c.m_Num2<<"="<<c.getResult("*")<<endl;
	
	//多态好处
	//1.组织结构清晰
	//2.可读性强
	//3.对于扩展以及维护性高
	
	AbstractCalculator* abc = new AddCalculator;
	abc->m_Num1 = 10;
	abc->m_Num2 = 10;
	cout<<abc->m_Num1<<"+"<<abc->m_Num2<<"="<<abc->getResult()<<endl;
	delete abc;
	
	abc = new SubCalculator;
	abc->m_Num1 = 10;
	abc->m_Num2 = 10;
	cout<<abc->m_Num1<<"-"<<abc->m_Num2<<"="<<abc->getResult()<<endl;
	delete abc;
	
	abc = new MulCalculator;
	abc->m_Num1 = 10;
	abc->m_Num2 = 10;
	cout<<abc->m_Num1<<"*"<<abc->m_Num2<<"="<<abc->getResult()<<endl;
	delete abc;
	return 0;
}