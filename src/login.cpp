/*
 * login.c
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */
#include "login.h"

Login::Login(string id,string pass):id(id),pass(pass){};

string Login::get_id() const{
	return id;
}
string Login::get_pass() const{
	return pass;
}

bool Login::set_id(string i){
	if(id==i){
		return true;
	}
	else id=i;
	return true;
}

bool Login::set_pass(string p){
	if(pass==p){
		return false;
	}
	else pass=p;
	return true;
}
