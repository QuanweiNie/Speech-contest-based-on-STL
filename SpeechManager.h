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

// ����ݽ�������
class SpeechManager {
public:
	SpeechManager();
	~SpeechManager();

	void showMeau();         // �˵�����
	void initSpeech();       // ��ʼ������
	void createSpeaker();    // ����ѡ��
	void startSpeech();      // ��ʼ����
	void speechDraw();       // ��ǩ
	void speechContest();    // ���б���
	void showScore();        // ��ʾ����

	void saveRecord();       // �����������
	void loadRecord();       // ����������Ϣ
	void showRecord();       // ��ʾ������Ϣ
	void clearRecord();      // �������
	void exitSystem();       // �˳�ϵͳ

	// ��Ա����
	vector<int> v1;          // ��һ�ֱ�����Ա
	vector<int> v2;          // �ڶ��ֱ�����Ա
	vector<int> vwin;        // ���ջ��Ա

	// ����ѡ�ֺͱ��
	map<int, Speaker> _speaker;

	// �����¼
	map<int, vector<string>> _record;

    // ��������
	int _index;

	// ��������ļ���־
	bool fileIsEmpty;    
};
