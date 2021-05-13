#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>
#include "speaker.h"

using namespace std;

// 设计演讲管理类
class SpeechManager {
public:
	SpeechManager();
	~SpeechManager();

	void showMeau();         // 菜单功能
	void initSpeech();       // 初始化比赛
	void createSpeaker();    // 创建选手
	void startSpeech();      // 开始比赛
	void speechDraw();       // 抽签
	void speechContest();    // 进行比赛
	void showScore();        // 显示分数

	void saveRecord();       // 保存比赛数据
	void loadRecord();       // 加载往届信息
	void showRecord();       // 显示往届信息
	void clearRecord();      // 清空数据
	void exitSystem();       // 退出系统

	// 成员属性
	vector<int> v1;          // 第一轮比赛成员
	vector<int> v2;          // 第二轮比赛成员
	vector<int> vwin;        // 最终获成员

	// 关联选手和编号
	map<int, Speaker> _speaker;

	// 往届记录
	map<int, vector<string>> _record;

    // 比赛轮数
	int _index;

	// 往届比赛文件标志
	bool fileIsEmpty;    
};
