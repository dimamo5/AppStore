/*
 * Vendas.h
 *
 *  Created on: 30/10/2014
 *      Author: Casa
 */

#ifndef VENDAS_H_
#define VENDAS_H_

#include <vector>
#include <string>
#include "App.h"
#include "Developer.h"
#include "Date.h"

using namespace std;

class Vendas{
private:
	int id;
	static unsigned int next_id;
	float preco;
	Developer* dev;
	App* app;
	Date data_venda;

public:
	Vendas();
	float getPreco() const;
	Developer* getDev() const;
	App* getApps() const;
	Date getData() const;

};

#endif /* VENDAS_H_ */
