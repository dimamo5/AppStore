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
/**
 * @class Comentario
 * @brief Classe para criar um comentario que esta associado a um cliente que e includo na App
 */

class Comentario {
private:
	unsigned int id_cliente;
	string descricao;
	double classificacao;
public:
	/**
	 * Construtor de Comentario
	 * @param descricao Pequeno testo de apreciacao da App
	 * @param id_cliente Id do cliente que criou a app
	 * @param classificacao Classificao que atribui a uma App
	 */
	Comentario(string descricao,unsigned int id_cliente,double classificacao);
	/**
	 * Getter Classificao
	 * @return Classificao atribuida na avaliacao
	 */
	double getClassificacao() const;
	/**
	 * Setter Classificao
	 * @param classificacao Nova Classificacao
	 */
	void setClassificacao(double classificacao);
	/**
	 * Getter Descricao
	 * @return Descricao da avaliacao
	 */
	string getDescricao() const;
	/**
	 * Setter Descricao
	 * @param descricao Nova Descricao
	 */
	void setDescricao(const string& descricao);
	/**
	 * Getter Id do Cliente
	 * @return Id do Cliente que fez o Comentario
	 */
	unsigned int getIdClient() const;
	/**
	 * Setter Id Cliente
	 * @param idClient Novo Id da Avaliacao
	 */
	void setIdClient(unsigned int idClient);
};

#endif /* COMENTARIO_H_ */
