
#include<iostream>
using namespace std;

class A{
public:
	A(int a):a(a){}
	const int func(){
		return a;
	}
private:
	int a;
	
};

int main(){
	A a(1);
	
	int b = a.func();
	cout<<b<<endl;
}