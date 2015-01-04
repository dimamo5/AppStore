#include "App.h"

unsigned int App::next_id = 1;

App::App(string nome, string categoria, string descricao, double preco,
		Date data):nome(nome),categoria(categoria),descricao(descricao),preco(preco),validada(false),data_submissao(data),apagada(false) {
	this->id = next_id;
	next_id++;
};

App::App(unsigned int id, string nome, string categoria, string descricao,
		double preco, double classificacao_final, int num_classificacoes,
		bool validada, Date data,bool apagada) :
		id(id), nome(nome), categoria(categoria), descricao(descricao), preco(
				preco), classificacao_final(classificacao_final), num_classificacoes(
				num_classificacoes), validada(validada), data_submissao(data),apagada(apagada) {

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

//	if (validada)
//	{
//		ret += "\n\n Esta app foi validada.";
//	}

	return ret;
}

bool App::isValidada() const {
	return validada;
}

void App::setValidada(bool valor) {
	validada = valor;
}

const Date& App::getDataSubmissao() const {
	return data_submissao;
}

void App::setApagada(bool valor){
	apagada = valor;
}

bool App::isApagada() const {
	return apagada;
}

void App::setDataSubmissao(const Date& dataSubmissao) {
	data_submissao = dataSubmissao;
}

bool App::operator<(const App& appb) const
{
	if(this->classificacao_final > appb.classificacao_final)
		return true;
	else
	{
		if(appb.classificacao_final > this->classificacao_final)
			return false;
		else
		{
			if(this->preco > appb.preco)
				return true;
			else
			{
				if(appb.preco > this->preco)
					return false;
				else
				{
					if(this->categoria > appb.categoria)
						return true;
					else
					{
						if(appb.categoria > this->categoria)
							return false;
						else
						{
							if(this->nome > appb.nome)
								return true;
							else
								return false;
						}
					}
				}
			}
		}
	}
}

bool AppPointer::operator<(const AppPointer& app_p) const{
	if(this->app_pointer->getClassificacaoFinal() > app_p.app_pointer->getClassificacaoFinal())
		return true;
	else
	{
		if(app_p.app_pointer->getClassificacaoFinal() > this->app_pointer->getClassificacaoFinal())
			return false;
		else
		{
			if(this->app_pointer->getPreco() > app_p.app_pointer->getPreco())
				return true;
			else
			{
				if(app_p.app_pointer->getPreco() > this->app_pointer->getPreco())
					return false;
				else
				{
					if(this->app_pointer->getCategoria() > app_p.app_pointer->getCategoria())
						return true;
					else
					{
						if(app_p.app_pointer->getCategoria() > this->app_pointer->getCategoria())
							return false;
						else
						{
							if(this->app_pointer->getNome() > app_p.app_pointer->getNome())
								return true;
							else
								return false;
						}
					}
				}
			}
		}
	}
}

App AppPointer::operator*() const{
	return *(this->app_pointer);
}

/*
 * app.cpp
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */

