#include "speechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();

	this->creatSpeaker();

	this->loadRecord();

}

void SpeechManager::Show_Menu()
{
		cout << "*******************************************" << endl;
		cout << "******** Welcome to Speech Contest ********" << endl;
		cout << "******** 1.Begin to Speech Contest ********" << endl;
		cout << "******** 2.Show History Recond     ********" << endl;
		cout << "******** 3.Clean the History       ********" << endl;
		cout << "******** 0.Exit the Program        ********" << endl;
		cout << "*******************************************" << endl;
		cout << endl;

}

void SpeechManager::exitSystem()
{
	cout << "See you next time! " << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVectory.clear();
	this->m_Speaker.clear();

	this->m_Index = 1;

	this->m_Record.clear();
}

void SpeechManager::creatSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "Speaker";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;
		}

		this->v1.push_back(i + 10001);

		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

void SpeechManager::startSpeech()
{
	//first round
	//1.draw
	speechDraw();
	//2.contest
	speechContest();
	//3.result and promote
	showScore();
	//second round
	this->m_Index++;
	//1.draw
	speechDraw();

	//2.contest
	speechContest();

	//3.result and final result
	showScore();

	//4.save
	this->saveRecord();
	//reset the game
	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();

	cout << "The contest is over!" << endl;
	system("pause");
	system("cls");

}

void SpeechManager::speechDraw()
{
	if (this->m_Index == 1)
	{
		cout << "The first time to draw, drawing processing" << endl;
		cout << "----------------------" << endl;
		cout << "the contesting order is the following: " << endl;

	}
	else if (this->m_Index == 2)
	{
		cout << "The second time to draw, drawing processing" << endl;
		cout << "----------------------" << endl;
		cout << "the contesting order is the following: " << endl;
	}

	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << "\t";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << "\t";
		}
		cout << endl;
	}

	cout << "----------------------" << endl;
	system("pause");
	system("cls");
	cout << endl;
}

void SpeechManager::speechContest()
{
	if (this->m_Index == 1)
	{
		cout << "-------- The first round contest has begun: -------" << endl;
	}
	else
	{
		cout << "-------- The second round contest has begun: -------" << endl;
	}

		multimap<double, int, greater<double>> groupScore;

		int num = 0;

		vector <int> v_Src;
		if (this->m_Index == 1)
		{
			v_Src = v1;
		}
		else
		{
			v_Src = v2;
		}

		for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
		{
			num++;

			deque<double>d;
			for (int i = 0; i < 10; i++)
			{
				double score = (rand() % 401 + 600) / 10.f;
				d.push_back(score);
			}

			sort(d.begin(), d.end(),greater<double>());
			d.pop_front();
			d.pop_back();

			double sum = accumulate(d.begin(), d.end(), 0.0f);
			double avg = sum / (double)d.size();

			this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

			groupScore.insert(make_pair(avg, *it));

			if (num % 6 == 0)
			{
				cout << "Group " << num / 6 << " 's ranking is the following: " << endl;
					for (multimap<double, int, greater<double>>::iterator it = groupScore.begin() ;it != groupScore.end() ; it ++)
					{
						cout << "Number: " << it->second
							<< "\tName: " << this->m_Speaker[it->second].m_Name
							<< "\tScore: " << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
					}

					//get the top three
					int count = 0;
					for ( multimap<double, int , greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++,count ++)
					{
						if (this->m_Index == 1)
						{
							v2.push_back((*it).second);
						}
						else
						{
							vVectory.push_back((*it).second);
						}
					}
					groupScore.clear();
					cout << endl;
			}
		}
		cout << "---------Round " << this->m_Index << " has been completed ---------" << endl;
		system("pause");
	}

void SpeechManager::showScore()
{
	cout << "====== Round " << this->m_Index << " promoting speakers are the following: ======" << endl;
	vector<int> v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVectory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "Number: " << *it
			<< "\tName: " << m_Speaker[*it].m_Name
			<< "\tScore: " << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	//this->Show_Menu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = vVectory.begin(); it != vVectory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "===== It has been recorded completely! =====" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << " File is not exist! " << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << " File is empty! " << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;

	ifs.putback(ch);

	string data;
	int index = 0;
	while (ifs>>data)
	{
		vector<string>v;

		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string tmp = data.substr(start, pos - start);

			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	for ( map<int,vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	{
		cout <<"The "<<  it->first+1 <<  " Champion Number: " << it->second[0] << "\tScore: " << it->second[1] << endl;
	}
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "File is not exist or the record is empty!" << endl;
		cout <<  endl;
	}
	else 
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "The " << i << " Period" <<
				"The 1st prize: " << this->m_Record[i][0] << " Score: " << this->m_Record[i][1] << " "
				"The 2nd prize: " << this->m_Record[i][2] << " Score: " << this->m_Record[i][3] << " "
				"The 3rd prize: " << this->m_Record[i][4] << " Score: " << this->m_Record[i][5] << endl;
		}
		system("pause");
		system("cls");
	}

}

void SpeechManager::clearRecord()
{
	cout << " ======================================= " << endl;
	cout << " == Are you sure to empty the record? == " << endl;
	cout << " ======================================= " << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();
		this->creatSpeaker();
		this->loadRecord();

		cout << " ================================= " << endl;
		cout << " == The record has been cleared == " << endl;
		cout << " ================================= " << endl;
	}
	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager()
{

}