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
#include "Cliente.h"
#include "Date.h"

using namespace std;

class Cliente;
class App;

class Vendas{
private:
	int id;
	static unsigned int next_id;
	float preco;
	App* app;
	Date data_venda;
	string reclamacao; //TODO construtor e getters (aka cenas daa reclamacao)

public:
	Vendas();
	int getId() const;
	float getPreco() const;
	Cliente* getCliente() const;
	App* getApps() const;
	Date getData() const;

};

#endif /* VENDAS_H_ */
