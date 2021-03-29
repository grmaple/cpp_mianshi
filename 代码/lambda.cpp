#include<iostream>
using namespace std;
int main()
{
    int a = 123;
    auto f = [&a] { cout << ++a << endl; }; 
    //a = 321;
    f(); // 输出：321
	cout<<a<<endl;
	f();
	cout<<a<<endl;
}