/*
 * Cliente.cpp
 *
 *  Created on: 31/10/2014
 *      Author: Moura
 */

#include "Cliente.h"

unsigned int Cliente::next_id = 1;

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

float Cliente::getSaldo() const {
	return saldo;
}

string Cliente::getIdPass() const {
	return id_pass;
}

void Cliente::setIdPass(string id_pass) {
	this->id_pass = id_pass;
}

void Cliente::setSaldo(float saldo) {
	this->saldo = saldo;
}

void Cliente::setCartao(int cartao_credito) {
	this->cartao_credito = cartao_credito;
}

Cliente::Cliente(int id, string nome, unsigned int idade, string sexo,
		int cartao_credito, float saldo, unsigned int nr_vouchers,
		string id_pass) :
		nome(nome), idade(idade), sexo(sexo), cartao_credito(cartao_credito), nr_vouchers(
				nr_vouchers), id_pass(id_pass) {
	this->id = id;
	this->saldo = saldo;
}

string Cliente::getSexo() const {
	return sexo;
}

unsigned int Cliente::getNext_id() const {
	return next_id;
}

Cliente::Cliente(string nome, unsigned int idade, string sexo,
		int cartao_credito, string id_pass) :
		nome(nome), idade(idade), sexo(sexo), cartao_credito(cartao_credito), id_pass(
				id_pass) {
	this->id = next_id;
	next_id++;
	saldo = 0;
	nr_vouchers = 0;
}

void Cliente::adicionarVenda(Vendas* v) {
	historico.push_back(v);
}

vector<Vendas*> Cliente::getHistorico() const {
	return historico;
}

void Cliente::setHistorico(vector<Vendas*> v) {
	historico = v;
}

void Cliente::emptyCesto() {
	cesto_compras.clear();
}

void Cliente::setNextID(unsigned int i) {
	next_id = i;
}

unsigned int Cliente::getVouchers() const {
	return nr_vouchers;
}

void Cliente::setVouchers(unsigned int voucher) {
	nr_vouchers = voucher;
}

void Cliente::removeVoucher() {
	if (nr_vouchers > 1) {
		nr_vouchers = nr_vouchers - 1;
	}
}

void Cliente::addVoucher() {
	nr_vouchers++;
}

bool Cliente::adicionaAppCesto(int app_id) {
	cesto_compras.push_back(app_id);
}

bool Cliente::eliminaAppCesto(unsigned int i) {
	cesto_compras.erase(cesto_compras.begin() + i);
}

vector<int> Cliente::getCesto() const {
	return cesto_compras;
}

bool Cliente::jaComprou(App app_option) {
	for (unsigned int i = 0; i < historico.size(); i++) {
		if (app_option.getId() == historico[i]->getAppVendidaId()) //se a app a ser analisada ja esta em alguma venda do historico
			return true;
	}
	return false;
}

bool Cliente::historicoVazio() {
	if (historico.size() == 0)
		return true;
	else
		return false;
}
