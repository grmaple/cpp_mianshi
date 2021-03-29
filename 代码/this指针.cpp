#include<iostream>
using namespace std;
 
class Test {
public:
    //Test(int = 0);
    void print();
private:
    static int x;
};
int Test::x = 0;
//Test::Test(int value) : x(value) { }
void Test::print() {
	x = 10;
    cout << "\tx = " << x
    << "\nthis -> x = " << this -> x
    << "\n(*this).x = " << (*this).x << endl;
}
 
int main() {
    Test test;
    test.print();
    return 0;
}
