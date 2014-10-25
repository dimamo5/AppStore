/*
 * login.c
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */
#include "login.h"

unsigned int login::next_id=1;

login::login(string pass):pass(pass){
	id=next_id;
	next_id++;
};

unsigned int login::get_id() const{
	return id;
}
string login::get_pass() const{
	return pass;
}

bool login::set_id(unsigned int i){
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
