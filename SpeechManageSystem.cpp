#include <iostream>
using namespace std;
#include "speechManager.h"
#include <string>
#include <ctime>
int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager sm;

	/*for (map<int,Speaker>::iterator it =sm.m_Speaker.begin();  it != sm.m_Speaker.end(); it++)
	{
		cout << "Speaker : " << it->first
			<< "\t\tName : " << it->second.m_Name
			<< "\t\tScore : " << it->second.m_Score[0] << endl;
	}*/

	int choise = 0;
	while (true)
	{
		sm.Show_Menu();

		cout << "Please enter your option:	" << endl;
		cin >> choise;
		switch (choise)
		{
		case 1://begin
			sm.startSpeech();
			break;
		case 2://show
			sm.showRecord();
			break;
		case 3://clean
			sm.clearRecord();
			break;
		case 0://exit
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}

	sm.Show_Menu();

	system("pause");
	return 0;
}