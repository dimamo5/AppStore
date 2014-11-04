/*
 * AppStore.h
 *
 *  Created on: 30/10/2014
 *      Author: Moura
 */

#ifndef APPSTORE_H_
#define APPSTORE_H_

#include "Developer.h"
#include "Vendas.h"
#include "Cliente.h"
#include "App.h"
#include "Date.h"
#include <string>
#include <fstream>

extern Developer* dev_act;
extern Cliente* cli_act;

using namespace std;

class AppStore {
public:
	AppStore();
	vector<App> apps;
	vector<Cliente> clientes;
	vector<Developer *> dev;
	vector<Vendas> vendas;
	Developer* find_dev_id(unsigned int id) const;
	Cliente* find_cliente_id(unsigned int id) ;
	App* find_app_id(unsigned int id);
	Vendas* find_vendas_id(unsigned int id);

	bool existeNomeDev(string nome) const;

	bool verificaLoginCliente(unsigned int id, string pass) const;
	// true - "faz login"  false - "combinacao errada" Alternativamente poderia ter feito -1 -> "cliente nao existe" 0 -> "login OK" 1 -> "password errada"
	bool verificaLoginDev(unsigned int id, string pass) const;

	bool save_all();
	bool load_all();
	bool save_app(ofstream &file);
	bool load_app(fstream &file);
	bool save_vendas(ofstream &file);
	bool load_vendas(fstream &file);
	bool save_clientes(ofstream &file);
	bool load_clientes(fstream &file);
	bool save_dev(ofstream &file);
	bool load_dev(fstream &file);
};

#endif /* APPSTORE_H_ */
