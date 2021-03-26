#include <iostream>
using namespace std;
 
class Father
{
public:
    Father(){cout<<"contructor Father!"<<endl;};
    virtual ~Father(){cout<<"destructor Father!"<<endl;};
};
 
class Son:public Father
{
public:
    Son(){cout<<"contructor Son!"<<endl;};
    ~Son(){cout<<"destructor Son!"<<endl;};
};
 
int main()
{
    Father *pfather=new Son;
    delete pfather;
    pfather=NULL;
 
    return 0;
}
/*输出结果为：
    contructor Father!
    contructor Son!
    destructor Father!
*/