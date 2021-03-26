// 函数域try/catch
// 很少有人知道函数，构造函数，析构函数可以声明全局的异常捕获。
#include<iostream>
#include<exception>
using namespace std;

int bad_func(){
	throw runtime_error("hahaha I crashed");
	return 0;
}

struct try_struct{
	int x, y;
	try_struct() try : x{0}, y{bad_func()} {}
	catch(...){
		cerr << "it is crashing! I can't stop it." <<  endl;
	}
};

int main() try{
	try_struct t;
}
catch(exception &e){
	cerr << "program crashed. reason: " << e.what() << endl;
	return 1;
}