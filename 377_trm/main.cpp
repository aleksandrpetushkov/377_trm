#include <iostream>
#include <fstream>
#include <string>
#include "dbpost.h"
#include "gtest/gtest.h"

using namespace std;


TEST(DB)
{
	Dbpost dbp;
	//��������� � �� 3 �����
	dbp.add("1422748800 1 theater;"); 
	dbp.add("1422835200 2 cinema;");
	dbp.add("1422921600 1 cinema;");
	
	
	EXPECT_EQ(3, dbp.Size());   //��������� ��� � �� 3 �����
	//cout << "---\n" << dbp.get_date(0) << "\n---\n";
	//��������� ��� ������ ���� � �� ������������� ���� ��� �� �������� ������ �������, �� ��� ����
	EXPECT_EQ("1 theater", dbp[0]); 
	EXPECT_EQ("2015 February 01", dbp.get_date(0)); //��������� ���� ������� ����� ������������ �� UNIX TIME stamp


}

int main(int argc, char* argv[])
{
	unsigned int user_id(0);
	unsigned int menu(0),N(0);
	string trenUser;
	string filename = "in_data.txt";
	fstream inFile(filename, ios::in);
	if (!inFile)
	{
		cout << "Error open file \"" << filename << "\". " << "Resolve this problem and to begin again." << endl;
		cin.get();
		return 0;
	}
	Dbpost dbpost;
	cout << "Load list posts..." << endl;
	for (string tmp; !inFile.eof();)
	{
		getline(inFile, tmp);
		dbpost.add(tmp);
	}
	cout << "Load completed." << endl;
	for (unsigned int i = 0; i != dbpost.Size(); ++i)
	{
		cout << i + 1 << " - " << dbpost[i]<<endl;
	}
	while (menu!=10)
	{
		
		cout << "Menu program:\n"
			<< "#1 Search tom-N hash.\n"
			<< "#2 Trend user on top-N hash.\n"
			<< "For exit enter 10.\n"
			<< "Enter number of menu: ";
		cin >> menu;
		unsigned int dateB(0), dateE(0);
		switch (menu)
		{
		case 1:
			cout << "Enter N: ";
			while (true)
			{
				cin >> N;
				if (cin.fail() || N < 1)
				{
					cin.sync();
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cerr << "Error: incorrect enter, reenter: ";
				}
				else
				{
					break;
				}
			}


			for (unsigned int i(0); i < dbpost.Size(); ++i)
			{
				cout << i + 1 << " - " << dbpost.get_date(i) << endl;
			}
			
			cout << "Enter number date begin: ";
			cin >> dateB;
			cout << "Enter number date end: ";
			cin >> dateE;
			map<unsigned int, string> *massTop;
			massTop = dbpost.top(N, dateB-1, dateE-1); //
	
			for (unsigned int i(0);(*massTop).size()>i;++i)  //
			{
				map<unsigned int, string>::iterator iter = (*massTop).begin();
				for (unsigned int k = (*massTop).size()-1; k - i > 0; --k, ++iter){}
				cout << iter->first << " " << iter->second << endl;
			}
			break;
		case 2:
			cout << "Enter user ID: ";
			while(true)
			{
				cin >> user_id;
				if(!dbpost.user_exist(user_id))
				{
					cout << "User not exist, re enter: ";
				}
				else
				{
					break;
				}
			}
			cout << "Enter N:";
			cin >> N;
			trenUser = dbpost.trend_user(user_id, N);
			cout << trenUser << endl;
			break;
		case 10:
			break;
		default:
			break;
		}
	}
	
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	cin.get();
}