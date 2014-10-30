/*
 * comentario.cpp
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */

#include "comentario.h"

Comentario::Comentario(string descricao,unsigned int id_cliente,double classificacao):descricao(descricao),id_cliente(id_cliente),classificacao(classificacao) {}

double Comentario::getClassificacao() const {
	return classificacao;
}

void Comentario::setClassificacao(double classificacao) {
	this->classificacao = classificacao;
}

string Comentario::getDescricao() const {
	return descricao;
}

void Comentario::setDescricao(const string& descricao) {
	this->descricao = descricao;
}

unsigned int Comentario::getIdClient() const {
	return id_cliente;
}

void Comentario::setIdClient(unsigned int idClient) {
	id_cliente = idClient;
}
