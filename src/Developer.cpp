/*
 * developer.cpp
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */
#include "Developer.h"

unsigned int Developer::next_id = 1;

Developer::Developer(string nome, string id_pass, string morada) :
		nome(nome), id_pass(id_pass), morada(morada) {
	id = next_id;
	next_id++;
}

Developer::Developer(int id, string nome, double saldo, string id_pass, string morada) :
		id(id), nome(nome), saldo(saldo), id_pass(id_pass), morada(morada) {

}
//vector<Vendas*> Developer::get_vendas() {
//	return vendas;
//}
//
//vector<App *> Developer::get_apps() const {
//	return apps;
//}

string Developer::getNome() const {
	return nome;
}
double Developer::getSaldo() const {
	return saldo;
}
void Developer::setSaldo(unsigned int s) {
	saldo = s;
}

//bool Developer::adiciona_app(App &a) {
//	for (unsigned int i; i < apps.size(); i++) {
//		if (apps[i]->get_id() == a.get_id()) {
//			//throw DeveloperError("App já existente");
//		}
//	}
//	apps.push_back(&a);
//	return true;
//}

Individual::Individual(string nome, string id_pass, string morada, string NomePessoal) :
		Developer(nome, id_pass, morada) {
	this->NomePessoal = NomePessoal;
}

Individual::Individual(int id, string nome, double saldo, string id_pass,string morada,
		string NomePessoal) :
		Developer(id, nome, saldo, id_pass, morada), NomePessoal(NomePessoal) {

}

void Developer::setNextID(unsigned int i) {
	next_id = i;
}

Empresa::Empresa(string nome, string id_pass,string morada, string NIF, string NomeEmpresa) :
		Developer(nome, id_pass, morada) {
	this->NIF = NIF;
	this->NomeEmpresa = NomeEmpresa;
}

Empresa::Empresa(int id, string nome, double saldo, string id_pass,string morada, string NIF, string NomeEmpresa) :
		Developer(id, nome, saldo, id_pass,morada), NIF(NIF), NomeEmpresa(NomeEmpresa) {

}

int Developer::getId() const {
	return id;
}

void Developer::setId(int id) {
	this->id = id;
}

string Developer::getIdPass() const {
	return id_pass;
}

unsigned int Developer::getNextId() const {
	return next_id;
}

string Individual::getExtra() const {
	return NomePessoal;
}

void Individual::setExtra(string info) {
	NomePessoal = info;
}

string Empresa::getExtra() const {
	return NIF;
}

string Empresa::getType() const {
	return "emp";
}

void Empresa::setExtra(string info) {
	NIF = info;
}

string Individual::getType() const {
	return "ind";
}

bool Individual::isEmpresa(){
	return false;
}

bool Empresa::isEmpresa(){
	return true;
}

