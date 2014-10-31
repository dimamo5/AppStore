/*
 * Cliente.cpp
 *
 *  Created on: 31/10/2014
 *      Author: Moura
 */

#include "Cliente.h"

unsigned int Cliente::next_id=1;

int Cliente::getCartaoCredito() const {
	return cartao_credito;
}

int Cliente::getId() const {
	return id;
}

unsigned int Cliente::getIdade() const {
	return idade;
}

string Cliente::getNome() const {
	return nome;
}

int Cliente::getSaldo() const {
	return saldo;
}

void Cliente::setSaldo(int saldo) {
	this->saldo = saldo;
}

string Cliente::getSexo() const {
	return sexo;
}

vector<Vendas*> Cliente::getVendas() const {
	return vendas;
}

Cliente::Cliente(string nome,unsigned int idade,string sexo,int cartao_credito):nome(nome),idade(idade),sexo(sexo),cartao_credito(cartao_credito) {
	id=next_id;
	next_id++;
}

