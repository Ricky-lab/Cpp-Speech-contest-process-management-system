#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>
using namespace std;


class SpeechManager
{
public:

	SpeechManager();

	vector<int>v1;// 12 speechers

	vector<int>v2;// 6 speechers

	vector<int>vVectory;// 3 speechers

	map<int, Speaker> m_Speaker;

	int m_Index;// speech round

	void Show_Menu();

	void exitSystem();

	void initSpeech();

	void creatSpeaker();

	void startSpeech();

	void speechDraw();

	void speechContest();

	void showScore();

	void saveRecord();

	void loadRecord();

	bool fileIsEmpty;

	void showRecord();

	void clearRecord();

	map<int, vector<string>> m_Record;

	~SpeechManager();

};
