/*
 * login.c
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */
#include "login.h"

unsigned int Login::next_id=1;

Login::Login(string pass):pass(pass){
	id=next_id;
	next_id++;
};

unsigned int Login::get_id() const{
	return id;
}
string Login::get_pass() const{
	return pass;
}


bool Login::set_id(unsigned int i){
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
