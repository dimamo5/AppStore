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
void Developer::addSaldo(double saldo_add){
	saldo = saldo + saldo_add;
}

//bool Developer::adiciona_app(App &a) {
//	for (unsigned int i; i < apps.size(); i++) {
//		if (apps[i]->get_id() == a.get_id()) {
//			//throw DeveloperError("App j� existente");
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

void Developer::setIdPass(string id_pass){
	this->id_pass = id_pass;
}

unsigned int Developer::getNextId() {
	return next_id;
}

string Individual::getExtra() const {
	return NomePessoal;
}

void Individual::setExtra(string info) {
	NomePessoal = info;
}

string Empresa::getExtra() const {
	return NomeEmpresa;
}

void Empresa::setExtra(string info) {
	NomeEmpresa = info;
}


bool Individual::isEmpresa(){
	return false;
}

string Developer::getMorada() const {
	return morada;
}

bool Developer::setMorada(string morada) {
	this->morada=morada;
	return true;
}

bool Empresa::isEmpresa(){
	return true;
}

string Empresa::getNIF() const{
	return NIF;
}

bool Empresa::setNIF(string nif){
	NIF=nif;
}

string Individual::getNIF() const{
	//throw Dev_Exp("") TODO exception
}

bool Individual::setNIF(string nif){
	//throw Dev_Exp("") TODO exception
}

