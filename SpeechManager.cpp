#include "SpeechManager.h"

SpeechManager::SpeechManager(){
	// ��ʼ���ݽ�����
	initSpeech();

	// ����ѡ��
	createSpeaker();

	// ���������¼
	loadRecord();
}

SpeechManager::~SpeechManager(){}


// �˵�����
void SpeechManager::showMeau(){
	cout << "************************************************" << endl;
	cout << "**************  ��ӭ�μ��ݽ�����   *************" << endl;
	cout << "**************  1.��ʼ�ݽ�����     *************" << endl;
	cout << "**************  2.�鿴�����¼     *************" << endl;
	cout << "**************  3.��������¼     *************" << endl;
	cout << "**************  0.�˳�����         *************" << endl;
	cout << "************************************************" << endl;
	cout << endl;
}

// �˳�ϵͳ
void SpeechManager::exitSystem(){
	cout << "�˳��ɹ�����ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

// ��ʼ���ݽ�����
void SpeechManager::initSpeech(){
	// �����ÿ�
	v1.clear();
	v2.clear();
	vwin.clear();
	_speaker.clear();
	_record.clear();

	// ��һ��
	_index = 1;
}

// ����ѡ��
void SpeechManager::createSpeaker(){
	// 12��ѡ��
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++){
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp._name = name;
		
		for (int j = 0; j < 2; j++)
			sp._scores[j] = 0;

		// ����ѡ�ֱ��
		v1.push_back(i + 10001);
		
		// ������ź�ѡ��
		_speaker.insert(make_pair(i + 10001, sp));
	}
}

// ��ǩ
void SpeechManager::speechDraw(){
	cout << "�� << " << _index << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "��ǩ���ݽ�˳������: " << endl;
	if (_index == 1){
		// ��һ�ֱ���
		random_shuffle(v1.begin(), v1.end());
		for (auto v : v1)
			cout << v << " ";
		cout << endl;
	}
	else if (_index == 2){
		// �ڶ��ֱ���
		random_shuffle(v2.begin(), v2.end());
		for (auto v : v2)
			cout << v << " ";
		cout << endl;
	}
	cout << "----------------------------------" << endl;
	system("pause");
	cout << endl;
}

// ����
void SpeechManager::speechContest(){
	cout << "---------------��" << _index << " �ֱ�����ʽ��ʼ------------------" << endl;
	// ��ʱ����,����ѡ�ֵ÷ֿ�����ͬ����ʹ��multimap
	// key :ƽ���֣�value: ѡ�ֱ�ţ���������
	multimap<double, int, greater<double>> groupScore;

	// ��¼��Ա����
	int num = 0;

	vector<int> v_src;  //������
	if (_index == 1) v_src = v1;
	if (_index == 2) v_src = v2;

	// ��������ѡ�ֽ��б���
	for (auto vi:v_src){
		num++;
		// 10 ����ί��֣��ö��б���
		deque<double> d;
		for (int i = 0; i < 10; i++){
			double score = (rand() % 401 + 600) / 10.f;   // 60 ~ 100
			d.push_back(score);
		}
		// ��������ʹ�õ��º���
		sort(d.begin(), d.end(), greater<double>());
		// ȥ����߷�
		d.pop_front();
		// ȥ����ͷ�
		d.pop_back();

		// ��� 
		double sum = accumulate(d.begin(), d.end(),0.0f);
		// ƽ����
		double avg = sum / (double)d.size();

		//��ƽ���ֱ���
		_speaker[vi]._scores[_index - 1] = avg;

		// key���÷�  value:���
		groupScore.insert(make_pair(avg, vi));

		// 6 �˷���
		if (num % 6 == 0){
			cout <<"��"<< num / 6 << "С���������\n" << endl;
			for (auto elem : groupScore){
				cout << "  ��ţ�" << elem.second
					 << "  ������" << _speaker[elem.second]._name
					 << "  ������" << _speaker[elem.second]._scores[_index - 1] << endl;
			}
			// ȡ��ǰ����
			int count = 0;
			for (auto val : groupScore){
				if (count < 3){
					if (_index == 1){
						v2.push_back(val.second);
					}
					else if (_index == 2){
						vwin.push_back(val.second);
					}
				}
				count++;
			}
			groupScore.clear();
			cout << endl;
 		}
	}
	system("pause");
}

// ��ʾ����
void SpeechManager::showScore(){
	cout << "--------------�� " << _index << " �ֽ���ѡ����Ϣ���£� ---------------" << endl;
	// ��ʱ����
	vector<int> v;
	if (_index == 1) v = v2;
	else v = vwin;

	for (auto elem : v){
		cout << "��ţ�" << elem << " ������ " << _speaker[elem]._name << " �÷֣�" << _speaker[elem]._scores[_index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	showMeau();
}

// �����������
void SpeechManager::saveRecord(){
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (auto elem : vwin){
		ofs << elem << "," << _speaker[elem]._scores[1] << ",";
	}
	ofs << endl;
	ofs.close();

	cout << "��¼�Ѿ�������ϣ�" << endl;
	fileIsEmpty = false;
}

// ���������¼
void SpeechManager::loadRecord(){
	// ����ļ�
	ifstream ifs("speech.csv", ios::in);
	// �ļ�������
	if (!ifs.is_open()){
		fileIsEmpty = true;
		ifs.close();
		return;
	}
	// �ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()){
		fileIsEmpty = true;
		ifs.close();
		return;
	}
	// �ļ���Ϊ��
	fileIsEmpty = false;

	// ������ȡ���ĵ��ʷŻ���
	ifs.putback(ch);

	int index = 1;
	string data;
	while (ifs >> data)    // Ĭ�ϰ��ж�
	{
		vector<string> v;  // ���6��string �ַ���

		int pos = -1;      //���ҵ����ŵ�λ��
		int start = 0;
		while (true){
			// �Ҳ������ţ�����-1
			pos = data.find(",", start);
			if (pos == -1)  break;

			string temp = data.substr(start, pos - start);
			v.push_back(temp);

			start = pos + 1;
		}
		_record.insert(make_pair(index,v));
		index++;
	}
	ifs.close();
}

// ��ʾ�����¼
void SpeechManager::showRecord(){
	if (fileIsEmpty){
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else{
		for (auto elem : _record){
			cout << "��" << elem.first << "�� \n"
				<< " �ھ���ţ�" << elem.second[0] << " �÷֣�" << elem.second[1] << endl
				<< " �Ǿ���ţ�" << elem.second[2] << " �÷֣�" << elem.second[3] << endl
				<< " ������ţ�" << elem.second[4] << " �÷֣�" << elem.second[5] << endl;
		}
	}

}

// �������
void SpeechManager::clearRecord(){
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.ȡ��" << endl;
	
	int choice;
	cin >> choice;
	if (choice == 1){
		// ���ٺ��ִ���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		// ��ʼ��
		initSpeech();
		createSpeaker();
		loadRecord();

		cout << "��ճɹ���" << endl;
	}
		system("pause");
		system("cls");
}

// ��ʼ����
void SpeechManager::startSpeech(){
	// ��һ�ֱ���
	speechDraw();      // 1.��ǩ
	speechContest();   // 2.����
	showScore();       // 3.��ʾ�������

	// �ڶ��ֱ���
	_index++;
	
	speechDraw();      // 1.��ǩ
	speechContest();   // 2.����
	showScore();       // 3.��ʾ���ս��
	saveRecord();      // 4.����������ļ�

	cout << "���������ϣ�" << endl;

	// ��ʼ��
	initSpeech();
	createSpeaker();
	loadRecord();

	system("pause");
	system("cls");
}
