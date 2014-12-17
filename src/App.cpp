#include "App.h"

unsigned int App::next_id = 1;

App::App(string nome, string categoria, string descricao, double preco,Date data) :
		nome(nome), categoria(categoria), descricao(descricao), preco(preco),
		validada(0),data_submissao(data) {
	this->id = next_id;
	next_id++;
}
;

App::App(unsigned int id, string nome, string categoria, string descricao,
		double preco, double classificacao_final, int num_classificacoes,
		bool validada,Date data) :
		id(id), nome(nome), categoria(categoria), descricao(descricao), preco(
				preco), classificacao_final(classificacao_final), num_classificacoes(
				num_classificacoes), validada(false),data_submissao(data) {

}

string App::getCategoria() const {
	return categoria;
}

double App::getClassificacaoFinal() const {
	return classificacao_final;
}

void App::setClassificacaoFinal(double classificacao) {
	classificacao_final = classificacao;
}

vector<Comentario> App::getComentarios() const {
	return comentarios;
}
void App::update_classificacao(unsigned int clas) {
	classificacao_final = (classificacao_final * num_classificacoes + clas)
			/ (num_classificacoes + 1);
	num_classificacoes++;
}
string App::getDescricao() const {
	return descricao;
}

string App::getNome() const {
	return nome;
}

Developer* App::getDev() const {
	return dev;
}

void App::setComentarios(const vector<Comentario>& comentarios) {
	this->comentarios = comentarios;
}

void App::addComentario(Comentario coment) {
	comentarios.push_back(coment);
	App::update_classificacao(coment.getClassificacao());
}

void App::setDev(Developer* dev) {
	this->dev = dev;
}

unsigned int App::getId() const {
	return id;
}

unsigned int App::getNextId() {
	return next_id;
}

void App::setNextId(unsigned int nextId) {
	next_id = nextId;
}

void App::setDescricao(const string& descricao) {
	this->descricao = descricao;
}

int App::getNumClassificacoes() const {
	return num_classificacoes;
}

void App::incNumClassificacoes() {
	num_classificacoes++;
}

void App::setPreco(double p) {
	this->preco = p;
}

void App::setNome(string nome) {
	this->nome = nome;
}

void App::setCategoria(string categoria) {
	this->categoria = categoria;
}

double App::getPreco() const {
	return preco;
}

bool App::isValidada() const {
	return validada;
}

const Date& App::getDataSubmissao() const {
	return data_submissao;
}

void App::setDataSubmissao(const Date& dataSubmissao) {
	data_submissao = dataSubmissao;
}

void App::setValidada() {
	this->validada = true;
}

string App::imprime() const {

	stringstream ss;
	string str_preco;
	string str_class;
	string ret = "";

	ss << this->preco;  // Transformar preco de double para string
	ss >> str_preco;
	ss.clear();
	ss << this->classificacao_final;
	ss >> str_class;

	ret += "  Nome: " + this->nome + "\n\n" + "  Categoria: " + this->categoria
			+ "\n\n" + "  Descricao: " + this->descricao + "\n\n"
			+ "  Developer: " + dev->getNome() + "\n\n" + "  Preco: "
			+ str_preco + "\n\n" + "  Classificacao: " + str_class;

	return ret;
}

/*
 * app.cpp
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */

