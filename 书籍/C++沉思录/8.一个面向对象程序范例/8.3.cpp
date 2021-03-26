// 添加新操作
// 1.equal求值
#include<iostream>
#include<string>
using namespace std;
ostream& operator<<(ostream& o, const Expr& t){
	t.p->print(o);
	return o;
}
// 公共基类
class Expr_node{
	friend ostream& operator<<(ostream&, const Expr&);//使用<<调用print
	friend class Expr;
	int use;// 引用计数
protected:
	Expr_node():use(1){}
	virtual void print(ostream&) const = 0;//动态绑定操作，只能用于成员函数
	virtual ~Expr_node(){}
	virtual int eval() const = 0;
};


// 整数
class Int_node:public Expr_node{
	friend class Expr;
	int n;
	Int_node(int k):n(k){}
	void print(ostream& o)const{o<<n;}
	int eval() const {return n;}
};
// 一元运算符
class Unary_node:public Expr_node{
	friend class Expr;
	string op;
	Expr opnd;
	Unary_node(const string& a, Expr b):op(a), opnd(b){}
	void print(ostream& o)const{o<<"("<<op<<opnd<<")";}
	int eval() const;
};
int Unary_node::eval() const{
	if(op == "-") return -opnd.eval();
	throw "error, bad op " + op + " int UnaryNode";
}
// 二元运算符
class Binary_node:public Expr_node{
	friend class Expr;
	string op;
	Expr left;
	Expr right;
	Binary_node(const string& a, Expr b, Expr c):
		op(a), left(b), right(c){}
	void print(ostream& o)const{o<<"("<<left<<op<<right<<")";}
	int eval() const;
};
int Binary_node::eval() const{
	int op1 = left.eval();
	int op2 = right.eval();
	if(op == "-") return op1 - op2;
	if(op == "+") return op1 + op2;
	if(op == "*") return op1 * op2;
	if(op == "/" && op2 != 0) return op1 / op2;
	throw "error, bad op " + op + " int BinaryNode";
}
// 句柄类
// 我们需要句柄类来管理指针。

class Expr{
	friend class Expr_node;
	friend ostream& operator<<(ostream&, const Expr&);
	Expr_node* p;
public:
	Expr(int);// 整数
	Expr(const string&, Expr);// 一元运算符
	Expr(const string&, Expr, Expr);// 二元运算符

	Expr(const Expr& t){p = t.p; ++p->use;}
	Expr& operator=(const Expr&);
	~Expr(){if(--p->use == 0)delete p;}

	int eval()const {return p->eval();}
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
	cout << t << "=" << t.eval() << endl;
	t = Expr("*", t, t);
	cout << t << "=" << t.eval() << endl;
}
