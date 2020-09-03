/*************************************************************************
	> 作者: grmaple
	> 名字：员工分组
	> 功能: 创建10名员工，放到vector
			遍历vector容器，取出每个员工，进行随机分组
			分组后将员工部门编号作为key，具体员工作为value，放入multimap容器
			分部门显示员工信息
	> 时间: 2020.9.3
 ************************************************************************/

#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<map>
#include<ctime>
#define CEHUA 0
#define MEISHU 1
#define YANFA 2

class Worker {
public:
	string m_Name;
	int m_Salary;
};

void createWorker(vector<Worker>& v){
	string nameSeed = "ABCDEFGHIJ";
	for (int i = 0; i < 10; i++){
		Worker worker;
		worker.m_Name = "员工";
		worker.m_Name += nameSeed[i];
		worker.m_Salary = rand()%10000+10000;//10000-19999
		v.push_back(worker);
	}
}
void setGroup(vector<Worker>& v,multimap<int,Worker>& m){
	for(vector<Worker>::iterator it = v.begin();it!=v.end();it++){
		//cout<<it->m_Name<<" "<<it->m_Salary<<endl;
		//随机产生部门
		int deptId = rand()%3;//0,1,2
		m.insert(make_pair(deptId,*it));
	}
}
void showWorkerByGroup(multimap<int,Worker>& m){
	cout <<"策划部门："<<endl;
	multimap<int,Worker>::iterator pos = m.find(CEHUA);
	int count = m.count(CEHUA);
	for (int index = 0; pos!= m.end()&&index<count;pos++,index++){
		cout<<pos->second.m_Name<<" "<<pos->second.m_Salary<<endl;
	}
	cout<<"--------------"<<endl;
	cout <<"美术部门："<<endl;
	pos = m.find(MEISHU);
	count = m.count(MEISHU);
	for (int index = 0; pos!= m.end()&&index<count;pos++,index++){
		cout<<pos->second.m_Name<<" "<<pos->second.m_Salary<<endl;
	}
	cout<<"--------------"<<endl;
	cout <<"研发部门："<<endl;
	pos = m.find(YANFA);
	count = m.count(YANFA);
	for (int index = 0; pos!= m.end()&&index<count;pos++,index++){
		cout<<pos->second.m_Name<<" "<<pos->second.m_Salary<<endl;
	}
}
int main() {
	srand(time(NULL));
	//创建员工
	vector<Worker> vWorker;
	createWorker(vWorker);
	//员工分组
	multimap<int,Worker> mWorker;
	setGroup(vWorker,mWorker);
	//分组显示员工
	showWorkerByGroup(mWorker);
	return 0;
}