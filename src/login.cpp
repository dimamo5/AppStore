/*
 * login.c
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */
#include "login.h"

login::login(string id,string pass):id(id),pass(pass){};

string login::get_id() const{
	return id;
}
string login::get_pass() const{
	return pass;
}

bool login::set_id(string i){
	if(id==i){
		return true;
	}
	else id=i;
	return true;
}

bool login::set_pass(string p){
	if(pass==p){
		return false;
	}
	else pass=p;
	return true;
}
