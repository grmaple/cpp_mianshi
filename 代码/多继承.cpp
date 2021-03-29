#include<iostream>
using namespace std;

class Base
{
public:
    double a;
	virtual void f();//
};
class Base1:public virtual Base
{
};
class Base2:public virtual Base
{
};
class Derived:public Base1,public Base2
{
private:
    double b;
public:
	//virtual void g();//这是Derived类自己新添加的虚函数
};
int main(){
	cout<<sizeof(Base)<<endl;//16,vptr+a
	cout<<sizeof(Base1)<<endl;//24,bptr1+vptr+a
	cout<<sizeof(Base2)<<endl;//24,bptr2+vptr+a
	cout<<sizeof(Derived)<<endl;//40,bptr1+bptr2+vptr+b+a
}