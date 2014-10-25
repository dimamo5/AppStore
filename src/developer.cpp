/*
 * developer.cpp
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */
#include "developer.h"

unsigned int developer::next_id=1;

developer::developer(string nome,double saldo,string id_pass):nome(nome),saldo(saldo){
	id=next_id;
	next_id++;
	data= new login(id_pass);
}

	//vector<* venda> get_vendas();
	vector<app *> get_apps();
	login* get_login();
	string get_nome();
	double get_saldo() const;
	void set_saldo(unsigned int s);

