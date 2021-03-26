// 表示算术表达式的树
// 一个表达式树包括表示常数、一元运算符、二元运算符的节点
// 
// #include<iostream>
// using namespace std;
// int main(){
	// Expr t = Expr("*", Expr("-", 5), Expr("+", 3, 4));
	// cout << t << endl;
	// t = Expr("*", t, t);
	// cout << t << endl;
// }
// 打印
// ((-5)*(3+4))
// (((-5)*(3+4))*((-5)*(3+4)))
#include<iostream>
#include<string>
using namespace std;
// 面向对象的解决方案
// 公共基类
class Expr_node{
	friend ostream& operator<<(ostream&, const Expr_node&);//使用<<调用print
protected:
	virtual void print(ostream&) const = 0;//动态绑定操作，只能用于成员函数
	virtual ~Expr_node(){}
};

ostream& operator<<(ostream& o, const Expr_node& e){
	e.print(o);
	return o;
}
// 整数
class Int_node:public Expr_node{
	int n;
	Int_node(int k):n(k){}
	void print(ostream& o)const{o<<n;}
};
// 一元运算符
class Unary_node:public Expr_node{
	string op;
	Expr_node* opnd;
	Unary_node(const string& a, Expr_node* b):op(a), opnd(b){}
	void print(ostream& o)const{o<<"("<<op<<*opnd<<")";}
};
// 二元运算符
class Binary_node:public Expr_node{
	string op;
	Expr_node* left;
	Expr_node* right;
	Binary_node(const string& a, Expr_node* b, Expr_node* c):
		op(a), left(b), right(c){}
	void print(ostream& o)const{o<<"("<<*left<<op<<*right<<")";}
};
// 问题是这里接受的参数是指针，而不是值，而且需要我们分配和释放对象。
// Binary_node *t = new Binary_node("*",
// 	new Unary_node("-", new Int_node(5)),
// 	new Binary_node("+", new Int_node(3), new Int_node(4)));