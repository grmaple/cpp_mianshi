// 类函数引用修饰符
// 不同于const，noexcept这样仅修饰类方法本身行为的修饰符
// &和&&修饰符会根据*this是左值还是右值引用来选择合适的重载
#include<iostream>
using namespace std;
struct echoer{
	void echo() const &{
		cout << "I have long live!\n";
	}
	void echo() const &&{
		cout << "I am dying!\n";
	}
};

int main(){
	echoer e;
	e.echo();// *this是左值，调用&版本的重载
	
	echoer().echo();// *this是右值，调用&&版本的重载
}