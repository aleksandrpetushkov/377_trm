#include <string>

using namespace std;

class post
{
public:
	post(){}

	post(string _hashtag, unsigned int _user_id)
	{
		hashtag = _hashtag;
		user_id = _user_id;
	}
	void set_user_id(unsigned int _user_id)
	{
		user_id = _user_id;
	}
	void set_hashtag(string _hashtag)
	{
		hashtag = _hashtag;
	}
	string get_string()
	{
		string result;
		result = to_string(user_id) + " " + hashtag;
		return result;
	}
	string get_hashtag()
	{
		return hashtag;
	}
	unsigned int get_user_id()
	{
		return user_id;
	}
protected:
	unsigned int user_id=0;
	string hashtag;
	
};
