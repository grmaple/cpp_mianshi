#include<iostream>
#include<string>
using namespace std;
class Building;//前向声明
class Good {
public:
	Good();
    void good();
private:
    Building* building;
};

class Building {
    //Good类的good函数是Building类的友元，可以访问Building类的私有成员
    friend void Good::good();
public:
	Building();
private:
    string m_room;
};

Building::Building()
{
	this->m_room = "卧室";
}
Good::Good(){
	building = new Building;
}
void Good::good() {
    cout<<building->m_room<<endl;
}
int main() {
    Good g;
    g.good();
}