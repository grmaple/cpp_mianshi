/*************************************************************************
	> 作者: grmaple
	> 名字：电脑组装
	> 功能: 使用不同的厂商零件组装电脑
	> 时间: 2020.9.3
 ************************************************************************/

#include<iostream>
using namespace std;
//电脑零件
class AbstractCPU {
public:
	virtual void calculate() = 0;
};
class AbstractVideoCard {
public:
	virtual void display() = 0;
};
class AbstractMemory {
public:
	virtual void storage() = 0;
};
//厂商
//Intel
class IntelCPU:public AbstractCPU {
public:
	virtual void calculate() {
		cout<< "IntelCPU开始计算了" <<endl;
	}
};
class IntelMemory:public AbstractMemory {
public:
	virtual void storage() {
		cout<< "IntelMemory开始存储了" <<endl;
	}
};
class IntelVideoCard:public AbstractVideoCard {
public:
	virtual void display() {
		cout<< "IntelVideoCard开始显示了" <<endl;
	}
};
//Lenovo
class LenovoCPU:public AbstractCPU {
public:
	virtual void calculate() {
		cout<< "LenovoCPU开始计算了" <<endl;
	}
};
class LenovoMemory:public AbstractMemory {
public:
	virtual void storage() {
		cout<< "LenovoMemory开始存储了" <<endl;
	}
};
class LenovoVideoCard:public AbstractVideoCard {
public:
	virtual void display() {
		cout<< "LenovoVideoCard开始显示了" <<endl;
	}
};
//电脑
class Computer {
public:
	Computer(AbstractCPU* cpu,AbstractVideoCard* vc,AbstractMemory* mem){
		m_cpu = cpu;
		m_mem = mem;
		m_vc = vc;
	}
	void dowork() {
		m_cpu->calculate();
		m_vc->display();
		m_mem->storage();
	}
	~Computer() {
		if (m_cpu != NULL) {
			delete m_cpu;
			m_cpu = NULL;
		}
		if (m_mem != NULL) {
			delete m_mem;
			m_mem = NULL;
		}
		if (m_vc != NULL) {
			delete m_vc;
			m_vc = NULL;
		}
	}
private:
	AbstractCPU* m_cpu;
	AbstractMemory* m_mem;
	AbstractVideoCard* m_vc;
};
int main() {
	//组装第一台电脑
	AbstractCPU* intelCPU = new IntelCPU;
	AbstractVideoCard* intelVideoCard = new IntelVideoCard;
	AbstractMemory* intelMemory = new IntelMemory;
	Computer* computer1 = new Computer(intelCPU,intelVideoCard,intelMemory);
	computer1->dowork();
	delete computer1;
	cout<<"------"<<endl;
	//组装第二台电脑
	Computer* computer2 = new Computer(new LenovoCPU,new LenovoVideoCard,new LenovoMemory);
	computer2->dowork();
	delete computer2;
	cout<<"------"<<endl;
	//组装第三台电脑
	Computer* computer3 = new Computer(new IntelCPU,new LenovoVideoCard,new IntelMemory);
	computer3->dowork();
	delete computer3;
	
	return 0;
}