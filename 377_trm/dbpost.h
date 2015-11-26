#include <map>
#include "post.h"
#include <time.h>
#include <string>

using namespace std;


class Dbpost
{
public:
	void add(string _in_string)
	{
		post tmp;
		unsigned int tm;
		size_t pos(0), pos1(0);
		pos1 = _in_string.find_first_of(" \t", pos);
		tm = atoi(_in_string.substr(pos, pos1 - pos).c_str());

		pos = _in_string.find_first_not_of(" \t", pos1);
		pos1 = _in_string.find_first_of(" \t", pos);
		massPost[tm].set_user_id(atoi(_in_string.substr(pos, pos1 - pos).c_str())); 

		pos = _in_string.find_first_not_of(" \t", pos1);
		pos1 = _in_string.find_first_of(";", pos);
		massPost[tm].set_hashtag(_in_string.substr(pos, pos1 - pos));
	}


	string operator[](unsigned int i)
	{
		map<unsigned int, post>::iterator iter=massPost.begin();
		for (; i != 0; --i, ++iter);

		return iter->second.get_string();
	}


	unsigned int Size()
	{
		return massPost.size();
	}

	void del(unsigned int _i) 
	{
		if(_i>massPost.size())
		{
			throw " id more array\n";
		}
		map<unsigned int, post>::iterator iter = massPost.begin();
		while(_i > 0)
		{
			++iter;
		}
		massPost.erase(iter);

	}
	void clear()
	{
		massPost.clear();
	}

	map<unsigned int, string>* top(unsigned int _N, unsigned int _dateB, unsigned int _dateE)
	{
		map<unsigned int, post>::iterator iter = massPost.begin();
		for (unsigned int i=_dateB;i>0;--i)
		{
			++iter;
		}
		map<unsigned int, string> *result = new map<unsigned int, string>();
		map<string, unsigned int> tmp;
		for (; iter != massPost.end()&&_dateE>=_dateB; ++iter, ++_dateB)
		{
			//cout << iter->first << "  -  " << iter->second.get_hashtag() << endl;
			tmp[iter->second.get_hashtag()] += 1;
		}
		for (map<string, unsigned int>::iterator iter = tmp.begin(); iter != tmp.end(); ++iter)
		{
			(*result)[iter->second] = iter->first;
		}
		//*
		if(_N<(*result).size())
		{
			_N = (*result).size() - _N;
			for (map<unsigned int, string>::iterator iter = (*result).begin(); _N != 0; iter = (*result).begin(), --_N)
			{
				(*result).erase(iter);
			}
		
		}
		//*/
		return result;


	}
	map<unsigned int, string>* top(unsigned int _N)
	{
		unsigned int i(0);
		return top(_N, i, i - 1);
	
	}
	string get_date(unsigned int _i)
	{
		std::string result;
		std::map<unsigned int, post>::iterator iter = massPost.begin();
		for (; _i != 0; --_i)
		{
			++iter;
		}
		char buffer[80];
		char* format = "%Y %B %d";
		time_t seconds = iter->first;
		tm* timeinfo = localtime(&seconds);
		strftime(buffer, 80, format, timeinfo);
		result = buffer;
		return result;
	}
	bool user_exist(unsigned int _user_id)
	{
		bool result = false;
		for (map<unsigned int, post>::iterator iter = massPost.begin(); iter != massPost.end(); ++iter)
		{
			if(iter->second.get_user_id()==_user_id)
			{
				result = true;
				break;
			}
		}
		return result;
	}


	string trend_user(unsigned int _user_id, unsigned int _N)
	{
		unsigned int sizeofTrend(0), sizeCommon_post(0);
		map<unsigned int, string> *massTop;
		massTop = top(_N);
		/*
		for (map<unsigned int, string>::iterator iter = (*massTop).begin(); iter != (*massTop).end(); ++iter)
		{
			for (map<unsigned int, post>::iterator iter = massPost.begin(); iter != massPost.end(); ++iter)
			{
				if (iter->second.get_user_id() == _user_id)
				{
					if(iter->second.get_hashtag)
				}
			}
				
		}
		//*/
		for (map<unsigned int, post>::iterator iter = massPost.begin(); iter != massPost.end(); ++iter)
		{
			if(iter->second.get_user_id() == _user_id)
			{
				for (map<unsigned int, string>::iterator iter1 = (*massTop).begin(); iter1 != (*massTop).end(); ++iter1)
				{
					if (iter->second.get_hashtag() == iter1->second)
					{
						++sizeofTrend;
					}
				}
				++sizeCommon_post;
			}
			
			
		}
		//cout << sizeCommon_post << endl << endl << sizeofTrend << endl;
		return to_string((float)sizeofTrend/(float)sizeCommon_post);
	}




protected:
	map<unsigned int, post> massPost;
	
};
