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

using namespace std;

class AppStore {
public:
	AppStore();
	vector<App> apps;
	vector<Cliente> clientes;
	vector<Developer *> dev;
	vector<Vendas> vendas;
	Developer* find_dev_id(unsigned int id) const;
	App* find_app_id(unsigned int id);
	Vendas* find_vendas_id(unsigned int id);

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
