#include<iostream>
using namespace std;

class Base{
public:
	Base(){++count;}
	Base(const Base& b){++count;}
	~Base(){--count;}
	static int getCount(){return count;}
private:
	static int count;
};
int Base::count = 0;

class Son:public Base{
	
};
void testCount(){
	Son s1, s2;
	cout<<Son::getCount()<<endl;
}
int main(){
	Son s1;
	Son s2 = s1;
	cout<<Son::getCount()<<endl;
	testCount();
	cout<<Son::getCount()<<endl;
}