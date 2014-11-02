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
	bool save_all();
	bool load_all();
	bool save_app(ofstream &file);
	bool load_app(fstream &file);
	bool save_vendas();
	bool load_vendas();
	bool save_clientes(ofstream &file);
	bool load_clientes(fstream &file);
	bool save_dev(ofstream &file);
	bool load_dev(fstream &file);
};

#endif /* APPSTORE_H_ */
