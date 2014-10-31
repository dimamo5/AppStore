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

Cliente::Cliente(int id, string nome, unsigned int idade, string sexo,int cartao_credito, int saldo):
	id(id),nome(nome),idade(idade),sexo(sexo),cartao_credito(cartao_credito),saldo(saldo){
}

string Cliente::getSexo() const {
	return sexo;
}

unsigned int Cliente::getNext_id() const {
	return next_id;
}


Cliente::Cliente(string nome,unsigned int idade,string sexo,int cartao_credito):nome(nome),idade(idade),sexo(sexo),cartao_credito(cartao_credito) {
	id=next_id;
	next_id++;
}

void Cliente::setNextID(unsigned int i) {
	next_id=i;
}