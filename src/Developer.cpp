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
	data = new Login(id_pass);
}
//vector<Vendas*> Developer::get_vendas() {
//	return vendas;
//}
//
//vector<App *> Developer::get_apps() const {
//	return apps;
//}
Login* Developer::get_login() const {
	return data;
}
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

string Individual::getMorada() const {
	return morada;
}

void Individual::setMorada(string morada) {
	this->morada = morada;
}




Empresa::Empresa(string nome,string id_pass,unsigned int NIF):Developer(nome,id_pass){
	this->NIF = NIF;
}

unsigned int Empresa::getNIF() const{
	return NIF;
}

void Empresa::setNIF(unsigned int NIF){
	this->NIF = NIF;
}
