#include<iostream>
using namespace std;
#include"speechManager.h"
#include<string>
#include<algorithm>
#include<deque>
#include<numeric>
#include<map>
#include<fstream>
SpeechManager::SpeechManager() {
	initSpeech();
	createSpeaker();
	loadRecord();
}
SpeechManager::~SpeechManager() {

}
void SpeechManager::show_Menu() {
	cout << "****************************" << endl;
	cout << "***** 欢迎参加演讲比赛 *****" << endl;
	cout << "***** 1、开始演讲比赛 ******" << endl;
	cout << "***** 2、查看往届记录 ******" << endl;
	cout << "***** 3、清空比赛记录 ******" << endl;
	cout << "***** 0、退出比赛程序 ******" << endl;
	cout << "****************************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
void SpeechManager::initSpeech() {
	v1.clear();
	v2.clear();
	vVictory.clear();
	m_Speaker.clear();
	m_Index = 1;
}
void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++) {
			sp.m_Score[i] = 0;
		}
		//12名选手编号
		v1.push_back(i + 10001);
		//选手编号以及对应选手，存放到map中
		m_Speaker.insert(make_pair(i + 10001, sp));
	}
}
void SpeechManager::startSpeech() {
	//第一轮比赛
	//1.抽签
	speedDraw();
	//2.比赛
	speechContest();
	//3.显示晋级结果
	showScore();
	//第二轮比赛
	m_Index++;
	//1.抽签
	speedDraw();
	//2.比赛
	speechContest();
	//3.显示最终结果
	showScore();
	//4.保存分数
	saveRecord();
	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::speedDraw() {
	cout << "第<<" << m_Index << ">>轮比赛选手正在抽签" << endl;
	cout << "-------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (m_Index == 1) {//第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout<<*it<<" ";
		}
		cout << endl;
	}
	else {//第二轮比赛
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-------------------" << endl;
	system("pause");
	cout << endl;
}
void SpeechManager::speechContest() {
	cout << "------------第<<" << m_Index << ">>轮比赛正式开始------------" << endl;
	//临时容器，存放小组成绩，key为成绩，value为编号，
	//greater<double>为从大到小排序
	multimap<double, int, greater<double>> groupScore;
	int num = 0;//记录人员数
	vector<int> v_Src;//比赛人员数组
	if (m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}
	//遍历所有参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		//打分
		deque<double> d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		//求平均分
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		//将平均分放进map
		m_Speaker[*it].m_Score[m_Index - 1] = avg;
		//分数放进临时小组groupScore
		groupScore.insert(make_pair(avg, *it));
		//每6人取前三名
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, Speaker>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "编号：" << it->second << "\t";
				cout << "姓名：" << m_Speaker[it->second].m_Name << "\t";
				cout << "成绩：" << m_Speaker[it->second].m_Score[m_Index-1] << endl;
			}
			int count = 0;
			//取前三名
			for (multimap<double, int, Speaker>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {
				if (m_Index == 1) {
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "------------第<<" << m_Index << ">>轮比赛完毕------------" << endl;
	system("pause");
}
void SpeechManager::showScore() {
	cout << "------------第<<" << m_Index << ">>轮晋级选手信息如下：------------" << endl;
	vector<int> v;//比赛人员数组
	if (m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "编号：" << *it << "\t";
		cout << "姓名：" << m_Speaker[*it].m_Name << "\t";
		cout << "成绩：" << m_Speaker[*it].m_Score[m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	show_Menu();
}
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已经保存" << endl;
}
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		fileIsEmpty = true;
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空" << endl;
		fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在，并且有记录
	fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 0;
	while (ifs >> data) {
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			start = pos + 1;
		}
		m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}


int main() {
	SpeechManager sm;
	int choice = 0;
	while (true) {
		sm.show_Menu();
		cout << "请输入你的选择：" << endl;
		cin >> choice;
		switch (choice) {
		case 1://开始比赛
			sm.startSpeech();
			break;
		case 2://查看记录
			
			break;
		case 3://清空记录
			
			break;
		case 0://退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}