#include "SpeechManager.h"
#include <ctime>

int main(){
	// �ݽ��������
	SpeechManager sm;

	// ���������
	srand((unsigned int)time(NULL));
	int select = 0;
	while (true){	
		sm.showMeau();
		cout << "����������ִ�еĲ����� " << endl;
		cin >> select;
		switch (select){
		case 1:  // ��ʼ����
			sm.startSpeech();
			break;
		case 2:  // �鿴�����¼
			sm.showRecord();
			break;
		case 3:  // ��������¼
			sm.clearRecord();   
			break;
		case 0:  // �˳�ϵͳ
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
