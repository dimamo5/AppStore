#include "app.h"

unsigned int app::next_id=1;

app::app(string nome,string categoria,string descricao,double preco):nome(nome),categoria(categoria),descricao(descricao),preco(preco){
	id=next_id;
};

string app::getCategoria() const {
	return categoria;
}

double app::getClassificacaoFinal() const {
	return classificacao_final;
}

vector<comentario *> app::getComentarios() const {
	return comentarios;
}
void app::update_classificacao(unsigned int clas){
	classificacao_final=(classificacao_final*num_classificacoes+clas)/(num_classificacoes+1);
	num_classificacoes++;
}
string app::getDescricao() const {
	return descricao;
}

string app::getNome() const {
	return nome;
}

void app::setPreco(double p){
	this->preco=p;
}

double app::getPreco() const {
	return preco;
}
/*
 * app.cpp
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */




