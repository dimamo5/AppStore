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
#include "Developer.h"
#include "Cliente.h"
#include "Comentario.h"

using namespace std;

class Developer;

extern Developer* dev_act;
extern Cliente* cli_act;



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
	vector<Comentario> comentarios;
	Developer* dev;
public:
	App(string nome,string categoria,string descricao,double preco);
	App(unsigned int id,string nome,string categoria,string descricao,double preco,double classificacao_final,int num_classificacoes);
	void update_classificacao(unsigned int clas);
	string getCategoria() const;
	double getClassificacaoFinal() const;
	vector<Comentario> getComentarios() const;
	unsigned int get_id()const;
	string getDescricao() const;
	string getNome() const;
	Developer* getDev() const;
	double getPreco() const;
	void setPreco(double p);
	void setComentarios(const vector<Comentario>& comentarios);
	void setDev(Developer* dev);
	unsigned int getId() const;
	unsigned int getNextId() const;
	static void setNextId(unsigned int nextId);
	int getNumClassificacoes() const;
	void setDescricao(const string& descricao);
};


#endif /* APP_H_ */
