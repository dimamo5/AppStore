/*
 * app.h
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */
#ifndef APP_H_
#define APP_H_

#include <string>
#include <vector>
#include "comentario.h"

using namespace std;

class App{
private:
	unsigned int id;
	static unsigned int next_id;
	string nome;
	string categoria;
	string descricao;
	double preco;
	double classificacao_final;
	int num_classificacoes=0;
	vector<Comentario *> comentarios;
public:
	App(string nome,string categoria,string descricao,double preco);
	void update_classificacao(unsigned int clas);
	string getCategoria() const;
	double getClassificacaoFinal() const;
	vector<Comentario *> getComentarios() const;
	unsigned int get_id()const;
	string getDescricao() const;
	string getNome() const;
	double getPreco() const;
	void setPreco(double p);
};


#endif /* APP_H_ */
