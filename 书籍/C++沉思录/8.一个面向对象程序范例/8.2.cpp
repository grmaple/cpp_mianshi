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
class Expr;
// 公共基类
class Expr_node{
	friend ostream& operator<<(ostream&, const Expr&);//使用<<调用print
	friend class Expr;
	int use;// 引用计数
protected:
	Expr_node():use(1){}
	virtual void print(ostream&) const = 0;//动态绑定操作，只能用于成员函数
	virtual ~Expr_node(){}
};

ostream& operator<<(ostream& o, const Expr& t){
	t.p->print(o);
	return o;
}
// 整数
class Int_node:public Expr_node{
	friend class Expr;
	int n;
	Int_node(int k):n(k){}
	void print(ostream& o)const{o<<n;}
};
// 一元运算符
class Unary_node:public Expr_node{
	friend class Expr;
	string op;
	Expr opnd;
	Unary_node(const string& a, Expr b):op(a), opnd(b){}
	void print(ostream& o)const{o<<"("<<op<<opnd<<")";}
};
// 二元运算符
class Binary_node:public Expr_node{
	friend class Expr;
	string op;
	Expr left;
	Expr right;
	Binary_node(const string& a, Expr b, Expr c):
		op(a), left(b), right(c){}
	void print(ostream& o)const{o<<"("<<left<<op<<right<<")";}
};

// 句柄类
// 我们需要句柄类来管理指针。

class Expr{
	friend ostream& operator<<(ostream&, const Expr&);
	Expr_node* p;
public:
	Expr(int);// 整数
	Expr(const string&, Expr);// 一元运算符
	Expr(const string&, Expr, Expr);// 二元运算符

	Expr(const Expr& t){p = t.p; ++p->use;}
	Expr& operator=(const Expr&);
	~Expr(){if(--p->use == 0)delete p;}
};
Expr::Expr(int n){
	p = new Int_node(n);
}
Expr::Expr(const string& op, Expr t){
	p = new Unary_node(op,t);
}
Expr::Expr(const string& op, Expr left, Expr right){
	p = new Binary_node(op, left, right);
}
// 考虑复制操作，我们是否真的需要复制?
// 避免复制的常用方法是使用引用计数

Expr& Expr::operator=(const Expr& rhs){
	rhs.p->use++;
	if(--p->use == 0) delete p;
	p = rhs.p;
	return *this;
}

int main(){
	Expr t = Expr("*", Expr("-", 5), Expr("+", 3, 4));
	cout << t << endl;
	t = Expr("*", t, t);
	cout << t << endl;
}