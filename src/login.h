/*
 * login.h
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */

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
	string get_id();
	string get_pass();
	bool set_pass();
	bool set_id();
};




#endif /* LOGIN_H_ */
