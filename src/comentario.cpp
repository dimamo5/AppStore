/*
 * comentario.cpp
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */

#include "comentario.h"

comentario::comentario(string descricao,unsigned int id_cliente,double classificacao):descricao(descricao),id_cliente(id_cliente),classificacao(classificacao) {}

double comentario::getClassificacao() const {
	return classificacao;
}

void comentario::setClassificacao(double classificacao) {
	this->classificacao = classificacao;
}

string comentario::getDescricao() const {
	return descricao;
}

void comentario::setDescricao(const string& descricao) {
	this->descricao = descricao;
}

unsigned int comentario::getIdClient() const {
	return id_cliente;
}

void comentario::setIdClient(unsigned int idClient) {
	id_cliente = idClient;
}
