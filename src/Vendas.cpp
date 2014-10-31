/*
 * Vendas.cpp
 *
 *  Created on: 30/10/2014
 *      Author: Casa
 */

#include "Vendas.h"

Vendas::Vendas(){

}

float Vendas::getPreco() const{
	return preco;
}

Developer* Vendas::getDev() const{
	return dev;
}

App* Vendas::getApps() const{
	return app;
}

Date Vendas::getData() const{
	return data_venda;
}

