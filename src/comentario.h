/*
 * comentario.h
 *
 *  Created on: 22/10/2014
 *      Author: Moura
 */

#ifndef COMENTARIO_H_
#define COMENTARIO_H_

#include <string>

using namespace std;

class comentario {
private:
	unsigned int id_cliente;
	string descricao;
	double classificacao;
public:
	comentario(string descricao,unsigned int id_cliente,double classificacao);
	double getClassificacao() const;
	void setClassificacao(double classificacao);
	string getDescricao() const;
	void setDescricao(const string& descricao);
	unsigned int getIdClient() const;
	void setIdClient(unsigned int idClient);
};

#endif /* COMENTARIO_H_ */
