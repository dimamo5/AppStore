#ifndef LOGIN_H_
#define LOGIN_H_

#include <string>

using namespace std;

class login{
private:
	string id;
	string pass;
public:
	login(string id,string pass);
	string get_id() const;
	string get_pass()const;
	bool set_pass(string p);
	bool set_id(string i);
};

#endif /* LOGIN_H_ */
