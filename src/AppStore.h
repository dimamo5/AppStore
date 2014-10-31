/*
 * AppStore.h
 *
 *  Created on: 30/10/2014
 *      Author: Moura
 */

#ifndef APPSTORE_H_
#define APPSTORE_H_

#include "Developer.h"
#include "App.h"

class AppStore {
public:
	AppStore();
	vector<App> apps;
	//vector<Cliente> clientes;
	vector<Developer> dev;
	//vector<Vendas> vendas;
	bool save_all();
	bool load_all();
	bool save_app();
	bool load_app();
	bool save_vendas();
	bool load_vendas();
	bool save_clientes();
	bool load_clientes();
	bool save_dev();
	bool load_dev();
};

#endif /* APPSTORE_H_ */
