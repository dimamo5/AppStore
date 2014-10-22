/*
 * app.h
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */
#ifndef APP_H_
#define APP_H_

#include <string>

using namespace std;

struct comentario{
	string nome_cliente;
	string comentario;
};



class app{
private:
	string nome;
	string categoria;
	string descricao;
	double preco;
	double classificacao_final;
	int num_classificacoes;
	vector<comentario> comentarios;
public:
	app(string nome,string categoria,string descricao,double preco);
	bool update_classificacao(unsigned int clas);
	string getCategoria() const;
	double getClassificacaoFinal() const;
	vector<comentario> getComentarios() const;
	string getDescricao() const;
	string getNome() const;
	double getPreco() const;
};


#endif /* APP_H_ */
