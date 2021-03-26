// 枚举类，是一种类型，该类型能取的值已经确定了
// 这些值是常量

#include<iostream>
using namespace std;
enum class sizes : size_t{
	ZERO = 0,
	LITTLE = 1ULL << 10,// 2^10
	MEDIUM = 1ULL << 20,// 2^20
	MANY = 1ULL << 30,// 2^30
	JUMBO = 1ULL << 40// 2^40
};
enum other{// 默认为int
	A = 1,
	B = 2
};
int main(){
	sizes c = sizes::MEDIUM;
	cout << static_cast<size_t>(c) << endl; // 枚举类不能隐式转化，必须强转
	cout <<  sizeof sizes::JUMBO << endl; // 8 size_t的大小
	
	other o = A;
	cout << o << endl;
	cout << sizeof A << endl;// 4 int的大小
}