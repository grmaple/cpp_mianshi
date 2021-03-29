#include<iostream>
using namespace std;

class Base
{
public:
    Base()
    {
       Function();
    }

    virtual void Function()
    {
        cout << "Base::Fuction" << endl;
    }
	~Base()
	{
		Function();
	}
};

class A : public Base
{
public:
    A()
    {
      Function();
    }

    virtual void Function()
    {
        cout << "A::Function" << endl;
    }
	~A()
	{
		Function();
	}
};

int main()
{
    Base* a = new Base;
	delete a;
	cout << "-------------------------" <<endl;
	Base* b = new A;//语句1
	cout << "-------------------------" <<endl;
	delete b;
}