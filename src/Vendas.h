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
#include "Date.h"

using namespace std;

class App;

class Vendas{
private:
	int id;
	static unsigned int next_id;
	float preco;
	App* app;
	Date data_venda;
	bool retorno;
	string reclamacao; //TODO construtor e getters (aka cenas daa reclamacao)

public:
	Vendas(float preco,Date data_venda);
	Vendas(int id,float preco,Date data_venda,bool retorno,string reclamacao);
	int getId() const;
	float getPreco() const;
	Date getData() const;
	App* getApp() const;
	void setApp(App* app);
	Date getDataVenda() const;
	unsigned int getNextId() const;
	static void setNextId(unsigned int nextId);
	string getReclamacao() const;
	bool isRetorno() const;
	void reclamar(string reclamacao);
};

#endif /* VENDAS_H_ */
