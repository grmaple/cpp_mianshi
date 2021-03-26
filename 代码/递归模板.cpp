// 模板在一定程度上就是编译期的函数，支持递归是理所应当的
// 利用类的继承和模板的特化可以实现很多递归和匹配操作
// 下面是不用内建数组实现的数组功能
#include<iostream>
using namespace std;
// 类的继承
template<class T, size_t Size>
struct flex_array : flex_array<T, Size-1> {
private: T v;
};
// 模板的特化
template<class T>
struct flex_array<T,1>{
	T &operator[](size_t i) {return *(&v+i);}
private:T v;
};

int main(){
	flex_array<unsigned, 4> arr;// unsigned arr[4]
	arr[0] = 10;
	cout << arr[0] <<endl;
	cout << sizeof arr[0] <<endl;// 4
	cout << sizeof arr << endl;// 16
}