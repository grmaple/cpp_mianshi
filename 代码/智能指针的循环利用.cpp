#include <iostream>
#include<memory>
using namespace std;

template <typename T>
class Node
{
public:
	Node(const T& value)
		:_pPre(NULL)
		, _pNext(NULL)
		, _value(value)
	{
		cout << "Node()" << endl;
	}
	~Node()
	{
		cout << "~Node()" << endl;
		cout << "this:" << this << endl;
	}

	shared_ptr<Node<T>> _pPre;
	shared_ptr<Node<T>> _pNext;
	T _value;
};

void Funtest()
{
	shared_ptr<Node<int>> sp1(new Node<int>(1));
	shared_ptr<Node<int>> sp2(new Node<int>(2));

	cout << "sp1.use_count:" << sp1.use_count() << endl;
	cout << "sp2.use_count:" << sp2.use_count() << endl;

	sp1->_pNext = sp2; //sp1的引用+1
	sp2->_pPre = sp1; //sp2的引用+1

	cout << "sp1.use_count:" << sp1.use_count() << endl;
	cout << "sp2.use_count:" << sp2.use_count() << endl;
}
int main()
{
	//shared_ptr<Node<int>> sp1(new Node<int>(1));
	Funtest();
	system("pause");
	return 0;
}
//输出结果
//Node()
//Node()
//sp1.use_count:1
//sp2.use_count:1
//sp1.use_count:2
//sp2.use_count:2
//无法析构