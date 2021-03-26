// 只有子类型的指针，如何调用父类型的方法？用命名空间

#include <iostream>
using namespace std;

struct Father{
	virtual void say(){
		cout << "hello from father!\n";
	}
};
struct Mother{
	virtual void say(){
		cout << "hello from mother!\n";
	}
};
struct Derived1 : Father, Mother{
	void say(){
		Father::say();
		Mother::say();
		cout << "hello from derived1!\n";
	}
};
int main(){
	Derived1 *p = new Derived1{};
	p->say();// 调用子类型的方法
	
	p->Father::say();// 调用父类型的方法
}