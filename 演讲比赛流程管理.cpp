#include "SpeechManager.h"
#include <ctime>

int main(){
	// 演讲管理对象
	SpeechManager sm;

	// 随机数种子
	srand((unsigned int)time(NULL));
	int select = 0;
	while (true){	
		sm.showMeau();
		cout << "请输入您想执行的操作： " << endl;
		cin >> select;
		switch (select){
		case 1:  // 开始比赛
			sm.startSpeech();
			break;
		case 2:  // 查看往届记录
			sm.showRecord();
			break;
		case 3:  // 清空往届记录
			sm.clearRecord();   
			break;
		case 0:  // 退出系统
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
