#ifndef LOGIN_H_
#define LOGIN_H_

#include <string>

using namespace std;

class login{
private:
	unsigned int id;
	static unsigned int next_id;
	string pass;
public:
	login(string pass);
	unsigned int get_id() const;
	string get_pass()const;
	bool set_pass(string p);
	bool set_id(unsigned int i);
};

#endif /* LOGIN_H_ */
