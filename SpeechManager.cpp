#include "SpeechManager.h"

SpeechManager::SpeechManager(){
	// 初始化演讲比赛
	initSpeech();

	// 创建选手
	createSpeaker();

	// 加载往届记录
	loadRecord();
}

SpeechManager::~SpeechManager(){}


// 菜单功能
void SpeechManager::showMeau(){
	cout << "************************************************" << endl;
	cout << "**************  欢迎参加演讲比赛   *************" << endl;
	cout << "**************  1.开始演讲比赛     *************" << endl;
	cout << "**************  2.查看往届记录     *************" << endl;
	cout << "**************  3.清空往届记录     *************" << endl;
	cout << "**************  0.退出比赛         *************" << endl;
	cout << "************************************************" << endl;
	cout << endl;
}

// 退出系统
void SpeechManager::exitSystem(){
	cout << "退出成功，欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

// 初始化演讲比赛
void SpeechManager::initSpeech(){
	// 容器置空
	v1.clear();
	v2.clear();
	vwin.clear();
	_speaker.clear();
	_record.clear();

	// 第一轮
	_index = 1;
}

// 创建选手
void SpeechManager::createSpeaker(){
	// 12个选手
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++){
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp._name = name;
		
		for (int j = 0; j < 2; j++)
			sp._scores[j] = 0;

		// 创建选手编号
		v1.push_back(i + 10001);
		
		// 关联编号和选手
		_speaker.insert(make_pair(i + 10001, sp));
	}
}

// 抽签
void SpeechManager::speechDraw(){
	cout << "第 << " << _index << " >> 轮比赛选手正在抽签" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "抽签后演讲顺序如下: " << endl;
	if (_index == 1){
		// 第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (auto v : v1)
			cout << v << " ";
		cout << endl;
	}
	else if (_index == 2){
		// 第二轮比赛
		random_shuffle(v2.begin(), v2.end());
		for (auto v : v2)
			cout << v << " ";
		cout << endl;
	}
	cout << "----------------------------------" << endl;
	system("pause");
	cout << endl;
}

// 比赛
void SpeechManager::speechContest(){
	cout << "---------------第" << _index << " 轮比赛正式开始------------------" << endl;
	// 临时容器,由于选手得分可能相同，故使用multimap
	// key :平均分，value: 选手编号，降序排序
	multimap<double, int, greater<double>> groupScore;

	// 记录人员个数
	int num = 0;

	vector<int> v_src;  //参赛组
	if (_index == 1) v_src = v1;
	if (_index == 2) v_src = v2;

	// 遍历所有选手进行比赛
	for (auto vi:v_src){
		num++;
		// 10 个评委打分，用队列保存
		deque<double> d;
		for (int i = 0; i < 10; i++){
			double score = (rand() % 401 + 600) / 10.f;   // 60 ~ 100
			d.push_back(score);
		}
		// 降序，这里使用到仿函数
		sort(d.begin(), d.end(), greater<double>());
		// 去除最高分
		d.pop_front();
		// 去除最低分
		d.pop_back();

		// 求和 
		double sum = accumulate(d.begin(), d.end(),0.0f);
		// 平均分
		double avg = sum / (double)d.size();

		//将平均分保存
		_speaker[vi]._scores[_index - 1] = avg;

		// key：得分  value:编号
		groupScore.insert(make_pair(avg, vi));

		// 6 人分组
		if (num % 6 == 0){
			cout <<"第"<< num / 6 << "小组比赛名次\n" << endl;
			for (auto elem : groupScore){
				cout << "  编号：" << elem.second
					 << "  姓名：" << _speaker[elem.second]._name
					 << "  分数：" << _speaker[elem.second]._scores[_index - 1] << endl;
			}
			// 取出前三名
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

// 显示分数
void SpeechManager::showScore(){
	cout << "--------------第 " << _index << " 轮晋级选手信息如下： ---------------" << endl;
	// 临时容器
	vector<int> v;
	if (_index == 1) v = v2;
	else v = vwin;

	for (auto elem : v){
		cout << "编号：" << elem << " 姓名： " << _speaker[elem]._name << " 得分：" << _speaker[elem]._scores[_index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	showMeau();
}

// 保存比赛数据
void SpeechManager::saveRecord(){
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (auto elem : vwin){
		ofs << elem << "," << _speaker[elem]._scores[1] << ",";
	}
	ofs << endl;
	ofs.close();

	cout << "记录已经保存完毕！" << endl;
	fileIsEmpty = false;
}

// 加载往届记录
void SpeechManager::loadRecord(){
	// 检查文件
	ifstream ifs("speech.csv", ios::in);
	// 文件不存在
	if (!ifs.is_open()){
		fileIsEmpty = true;
		ifs.close();
		return;
	}
	// 文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof()){
		fileIsEmpty = true;
		ifs.close();
		return;
	}
	// 文件不为空
	fileIsEmpty = false;

	// 将上面取出的单词放回来
	ifs.putback(ch);

	int index = 1;
	string data;
	while (ifs >> data)    // 默认按行读
	{
		vector<string> v;  // 存放6个string 字符串

		int pos = -1;      //查找到逗号的位置
		int start = 0;
		while (true){
			// 找不到逗号，返回-1
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

// 显示往届记录
void SpeechManager::showRecord(){
	if (fileIsEmpty){
		cout << "文件不存在或者记录为空！" << endl;
	}
	else{
		for (auto elem : _record){
			cout << "第" << elem.first << "届 \n"
				<< " 冠军编号：" << elem.second[0] << " 得分：" << elem.second[1] << endl
				<< " 亚军编号：" << elem.second[2] << " 得分：" << elem.second[3] << endl
				<< " 季军编号：" << elem.second[4] << " 得分：" << elem.second[5] << endl;
		}
	}

}

// 清空数据
void SpeechManager::clearRecord(){
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.取消" << endl;
	
	int choice;
	cin >> choice;
	if (choice == 1){
		// 销毁后又创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		// 初始化
		initSpeech();
		createSpeaker();
		loadRecord();

		cout << "清空成功！" << endl;
	}
		system("pause");
		system("cls");
}

// 开始比赛
void SpeechManager::startSpeech(){
	// 第一轮比赛
	speechDraw();      // 1.抽签
	speechContest();   // 2.比赛
	showScore();       // 3.显示晋级结果

	// 第二轮比赛
	_index++;
	
	speechDraw();      // 1.抽签
	speechContest();   // 2.比赛
	showScore();       // 3.显示最终结果
	saveRecord();      // 4.保存分数到文件

	cout << "本届比赛完毕！" << endl;

	// 初始化
	initSpeech();
	createSpeaker();
	loadRecord();

	system("pause");
	system("cls");
}
