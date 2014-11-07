/*
 * Vendas.cpp
 *
 *  Created on: 30/10/2014
 *      Author: Casa
 */

#include "Vendas.h"

unsigned int Vendas::next_id = 1;

Vendas::Vendas(float preco, Date data_venda, string app_removida_nome) :
		preco(preco), data_venda(data_venda),nome_app_momento_venda(app_removida_nome) {
	id = next_id;
	next_id++;
	retorno = false;
	reclamacao = "";
}

Vendas::Vendas(int id, float preco, Date data_venda, bool retorno,
		bool app_apagada, int id_app_vendida, string reclamacao,
		string app_removida_nome) :
		id(id), preco(preco), data_venda(data_venda), retorno(retorno), reclamacao(
				reclamacao), nome_app_momento_venda(app_removida_nome), app_apagada(
				app_apagada), id_app_vendida(id_app_vendida) {
}

float Vendas::getPreco() const {
	return preco;
}

Date Vendas::getData() const {
	return data_venda;
}

int Vendas::getId() const {
	return id;
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
	if (retorno) {
		//throw Venda_Exp("App já foi retornada"); //TODO exception
	} else {
		retorno = true;
		this->reclamacao = reclamacao;
	}
}

string Vendas::getAppVendidaNome() const {
	return nome_app_momento_venda;
}

void Vendas::setAppVendidaNome(string nome_app_momento_venda) {
	this->nome_app_momento_venda = nome_app_momento_venda;
}

int Vendas::getAppVendidaId() const {
	return id_app_vendida;
}
void Vendas::setAppVendidaId(int id_app_vendida) {
	this->id_app_vendida = id_app_vendida;

}

bool Vendas::getAppApagada() const {
	return app_apagada;
}

void Vendas::setAppApagada(bool value) {
	this->app_apagada = value;
}
