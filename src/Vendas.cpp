/*
 * Vendas.cpp
 *
 *  Created on: 30/10/2014
 *      Author: Casa
 */

#include "Vendas.h"

unsigned int Vendas::next_id=1;

Vendas::Vendas(float preco, Date data_venda):preco(preco),data_venda(data_venda) {
	id=next_id;
	next_id++;
	retorno=false;
	reclamacao="";
}

Vendas::Vendas(int id, float preco, Date data_venda, bool retorno,string reclamacao):id(id),preco(preco),
		data_venda(data_venda),retorno(retorno),reclamacao(reclamacao) {
}


float Vendas::getPreco() const{
	return preco;
}


Date Vendas::getData() const{
	return data_venda;
}

int Vendas::getId() const {
	return id;
}

App* Vendas::getApp() const {
	return app;
}

void Vendas::setApp(App* app) {
	this->app = app;
}

Date Vendas::getDataVenda() const {
	return data_venda;
}

unsigned int Vendas::getNextId() const {
	return next_id;
}

void Vendas::setNextId(unsigned int nextId) {
	next_id = nextId;
}

string Vendas::getReclamacao() const {
	return reclamacao;
}


bool Vendas::isRetorno() const {
	return retorno;
}

void Vendas::reclamar(string reclamacao) {
	if(retorno){
		//throw Venda_Exp("App já foi retornada"); //TODO exception
	}
	else{
		retorno=true;
		this->reclamacao=reclamacao;
	}
}
