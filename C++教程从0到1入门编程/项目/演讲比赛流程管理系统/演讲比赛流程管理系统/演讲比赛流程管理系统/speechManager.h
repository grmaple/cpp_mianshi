#pragma once
#include<iostream>
using namespace std;
#include"speaker.h"
#include<map>
#include<vector>

class SpeechManager {
public:
	SpeechManager();
	~SpeechManager();
	//菜单界面
	void show_Menu();
	//退出系统
	void exitSystem();
	//初始化属性
	void initSpeech();
	//创建选手
	void createSpeaker();
	//开始比赛
	void startSpeech();
	//抽签
	void speedDraw();
	//比赛
	void speechContest();
	//显示分数
	void showScore();
	//保存记录
	void saveRecord();
	//读取记录
	void loadRecord();

	bool fileIsEmpty;//文件标志为空的标志
	map<int,vector<string>> m_Record;//往届记录
	vector<int> v1;//比赛选手总数 12
	vector<int> v2;//第二轮比赛选手 6
	vector<int> vVictory;//决赛前三名 3
	map<int, Speaker> m_Speaker;//存放编号，以及对应选手
	int m_Index;//记录比赛轮数
};
