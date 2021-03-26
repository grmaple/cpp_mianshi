/*************************************************************************
	> 作者: grmaple
	> 名字：制作饮品
	> 功能: 多态技术，提供抽象制作饮品基类，
			提供子类制作咖啡，茶叶
	> 时间: 2020.9.3
 ************************************************************************/

#include<iostream>
using namespace std;

class AbstractDrinking {
public:
	virtual void Name() = 0;
	//煮水
	virtual void Boil() = 0;
	//冲泡
	virtual void Brew() = 0;
	//倒入杯中
	virtual void PourInCup() = 0;
	//加入辅助佐料
	virtual void PutSomething() = 0;
	//制作饮品
	void makeDrink() {
		Name();
		Boil();
		Brew();
		PourInCup();
		PutSomething();
	}
};
//制作咖啡
class Coffee:public AbstractDrinking {
public:
	virtual void Name() {
		cout << "制作咖啡" <<endl;
	}
	//煮水
	virtual void Boil() {
		cout << "煮农夫山泉" <<endl;
	}
	//冲泡
	virtual void Brew() {
		cout << "冲泡咖啡" <<endl;
	}
	//倒入杯中
	virtual void PourInCup() {
		cout << "倒入杯中" <<endl;
	}
	//加入辅助佐料
	virtual void PutSomething() {
		cout << "加入糖和牛奶" <<endl;
	}
};
//制作茶水
class Tea:public AbstractDrinking {
public:
	virtual void Name() {
		cout << "制作茶水" <<endl;
	}
	//煮水
	virtual void Boil() {
		cout << "煮矿泉水" <<endl;
	}
	//冲泡
	virtual void Brew() {
		cout << "冲泡茶叶" <<endl;
	}
	//倒入杯中
	virtual void PourInCup() {
		cout << "倒入杯中" <<endl;
	}
	//加入辅助佐料
	virtual void PutSomething() {
		cout << "加入柠檬" <<endl;
	}
};
//制作函数
void dowork(AbstractDrinking * abs) {
	abs->makeDrink();
	delete abs;
}
int main() {
	//一个接口(makeDrink)有多种形态(不同饮品)，
	//因为传入对象不一样，会制作不一样的饮品
	dowork(new Coffee);//AbstractDrinking * abs = new Coffee
	cout<<"---------"<<endl;
	dowork(new Tea);//AbstractDrinking * abs = new Tea
	
	return 0;
}