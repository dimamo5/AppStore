/*
 * developer.cpp
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */
#include "Developer.h"

unsigned int Developer::next_id = 1;

Developer::Developer(string nome, string id_pass) :
		nome(nome) {
	id = next_id;
	next_id++;
}

Developer::Developer(int id,string nome,double saldo,string id_pass):id(id),nome(nome),saldo(saldo),id_pass(id_pass){

}
//vector<Vendas*> Developer::get_vendas() {
//	return vendas;
//}
//
//vector<App *> Developer::get_apps() const {
//	return apps;
//}

string Developer::get_nome() const {
	return nome;
}
double Developer::get_saldo() const {
	return saldo;
}
void Developer::set_saldo(unsigned int s) {
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




Individual::Individual(string nome,string id_pass,string morada):Developer(nome,id_pass){
	this->morada = morada;
}

Individual::Individual(int id,string nome,double saldo,string id_pass,string morada):Developer(id,nome,saldo,id_pass),morada(morada){

}


void Developer::setNextID(unsigned int i) {
	next_id=i;
}


Empresa::Empresa(string nome,string id_pass,string NIF):Developer(nome,id_pass){
	this->NIF = NIF;
}

Empresa::Empresa(int id,string nome,double saldo,string id_pass,string NIF):Developer(id,nome,saldo,id_pass),NIF(NIF){

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
	return morada;
}

void Individual::setExtra(string info) {
	morada=info;
}

string Empresa::getExtra() const {
	return NIF;
}

void Empresa::setExtra(string info) {
	NIF=info;
}
