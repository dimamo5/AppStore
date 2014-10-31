/*
 * Vendas.cpp
 *
 *  Created on: 30/10/2014
 *      Author: Casa
 */

#include "Vendas.h"

	unsigned int Vendas::next_id=0;
Vendas::Vendas(){
	id=next_id;
	next_id++;
}

float Vendas::getPreco() const{
	return preco;
}

Cliente* Vendas::getCliente() const{
	return cliente;
}

App* Vendas::getApps() const{
	return app;
}

Date Vendas::getData() const{
	return data_venda;
}

int Vendas::getId() const {
	return id;
}
