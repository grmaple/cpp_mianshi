#include<iostream>
using namespace std;
class A
{
public:
	A() {
		cout << "default constructor is called" << endl;
	};
	A(const A& a)
	{
		cout << "copy constructor is called" << endl;
	};
	~A() {};
};

void useClassA(A a) {}

A getClassA()//此时会发生拷贝构造函数的调用，虽然发生NRV优化，但是依然调用拷贝构造函数
{
	A a;
	return a;
}


//A& getClassA2()//  VS2019下，此时编辑器会进行（Named return Value优化）NRV优化,不调用拷贝构造函数 ，如果是引用传递的方式返回当前函数体内生成的对象时，并不发生拷贝构造函数的调用
//{
//	A a;
//	return a;
//}


int main()
{
	A a1,a3,a4;
	A a2 = a1;  //调用拷贝构造函数,对应情况1
	useClassA(a1);//调用拷贝构造函数，对应情况2
	a3 = getClassA();//发生NRV优化，但是值返回，依然会有拷贝构造函数的调用 情况3
	//a4 = getClassA2(a1);//发生NRV优化，且引用返回自身，不会调用
    return 0;
}
