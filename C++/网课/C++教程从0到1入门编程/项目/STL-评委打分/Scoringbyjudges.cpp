/*************************************************************************
	> 作者: grmaple
	> 名字：评委打分
	> 功能: 创建五名选手
			遍历vector容器，取出来每一个选手，执行for循环，可以把十个评分存到deque容器
			sort算法对deque容器中分数排序，去掉最高分和最低分
			deque容器遍历一遍
			获取平均分
	> 时间: 2020.9.3
 ************************************************************************/

#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<ctime>
#include<deque>
#include<algorithm>
class Person {
public:
	Person(string name, int score):m_Name(name),m_Score(score){}
	string m_Name;
	int m_Score;//平均分
};
void createPerson(vector<Person>& v) {
	string nameSeed = "ABCDE";
	for (int i = 0; i < 5; i++) {
		string name = "选手";
		name += nameSeed[i];
		int score = 0;
		Person p(name,score);
		v.push_back(p);
	}
}
void setScore(vector<Person>& v) {
	for (vector<Person>::iterator it = v.begin(); it!=v.end(); it++) {
		//把十个评分存到deque容器
		deque<int> d;
		for (int i = 0; i < 10; i++) {
			int score = rand()%41 + 60;//rand()%41=0-40
			d.push_back(score);
		}
		for (deque<int>::iterator dit = d.begin(); dit!=d.end(); dit++) {
			cout<<*dit<<" ";
		}
		cout<<endl;
		//去掉最高分和最低分
		sort(d.begin(),d.end());
		d.pop_back();
		d.pop_front();
		//获取平均分
		int sum = 0;
		for (deque<int>::iterator dit = d.begin(); dit!=d.end(); dit++) {
			sum+= *dit;
		}
		int avg = sum / d.size();
		it->m_Score = avg;
	}
}
int main() {
	//srand(time(NULL));
	//创建5名选手
	vector<Person> v;//存放选手的容器
	createPerson(v);
	//给五人打分
	setScore(v);
	for (vector<Person>::iterator it = v.begin(); it!=v.end(); it++) {
		cout<< it->m_Name << "\t" <<it->m_Score<<endl;
	}
	return 0;
}