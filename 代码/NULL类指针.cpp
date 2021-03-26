#include<iostream>
using namespace std;

class Demo{
public:
	Demo():count(0){}
	~Demo(){}
	void say(const string& msg){
		fprintf(stderr, "%s\n", msg.c_str());
	}
	int getCount(){
		return this->count;
	}
private:
	int count;
};

int main(){
	Demo* v = NULL;
	// 初始化为NULL的类指针，可以安全调用没有使用类成员的成员函数
	v->say("hello world");//true

	cout<< v->getCount() << endl;//false
	
}