#include<iostream>
#include<sstream>
#include<string>
using namespace std;

int main(){
	string str = "i 1am  2   2 \
	2a \
	boy";
	istringstream is(str);
	string s;
	while(is>>s){
		cout<<s<<endl;
	}
}