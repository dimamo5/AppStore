#include "App.h"


App::App(string nome,string categoria,string descricao,double preco):nome(nome),categoria(categoria),descricao(descricao),preco(preco){};

string App::getCategoria() const {
	return categoria;
}

double App::getClassificacaoFinal() const {
	return classificacao_final;
}

vector<Comentario> App::getComentarios() const {
	return comentarios;
}
void App::update_classificacao(unsigned int clas){
	classificacao_final=(classificacao_final*num_classificacoes+clas)/(num_classificacoes+1);
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

void App::setPreco(double p){
	this->preco=p;
}

double App::getPreco() const {
	return preco;
}

unsigned int App::get_id()const{
	return id;
}


/*
 * app.cpp
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */




