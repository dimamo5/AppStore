#include "app.h"

app::app(string nome,string categoria,string descricao,double preco):nome(nome),categoria(categoria),descricao(descricao),preco(preco){};

string app::getCategoria() const {
	return categoria;
}

double app::getClassificacaoFinal() const {
	return classificacao_final;
}

vector<comentario> app::getComentarios() const {
	return comentarios;
}

string app::getDescricao() const {
	return descricao;
}

string app::getNome() const {
	return nome;
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




