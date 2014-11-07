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
#include <sstream>
#include "Developer.h"
#include "Cliente.h"
#include "Comentario.h"

using namespace std;

class Developer;

extern Developer* dev_act;
extern Cliente* cli_act;

/**
 * @class App
 *
 * @brief Classe que contem informacao sofre apps
 *
 */

class App{
private:
	unsigned int id;/**< ID unico de cada App*/
	static unsigned int next_id;/**< Proximo Id quando c se cria uma App */
	string nome;/**< Nome da App */
	string categoria;/**< Categoria em que se insere a App */
	string descricao;/**< Pequena descricao sobre a App */
	double preco;/**< Preco da App */
	double classificacao_final;/**< Classificacao atribuida pelo clientes que compram a App */
	int num_classificacoes=0; /**< Numero de Classificacaos ja lhe atribuidas */
	vector<Comentario> comentarios; /**< Vector com todos os Comentarios */
	Developer* dev; /**< Pointer para o developer que criou esta app */
public:
	/**
	 * Construtor de App
	 * @param nome Nome
	 * @param categoria Categoria
	 * @param descricao Descricao
	 * @param preco Preco
	 */
	App(string nome,string categoria,string descricao,double preco);
	/**
	 * Construtor usado na para carregar informacao dos ficheiros
	 * @param id Id
	 * @param nome Nome
	 * @param categoria Categoria
	 * @param descricao Descricao
	 * @param preco Preco
	 * @param classificacao_final Classificao Final
	 * @param num_classificacoes Nr. Classificacoes
	 */
	App(unsigned int id,string nome,string categoria,string descricao,double preco,double classificacao_final,int num_classificacoes);
	/**
	 * Recalcula a classificao da App quando lhe e adicionada uma classificacao
	 * @param clas Classificacao atribuida por um cliente
	 */
	void update_classificacao(unsigned int clas);
	/**
	 * Getter Categoria
	 * @return String Categoria
	 */
	string getCategoria() const;
	/**
	 * Getter Classificao
	 * @return Double Classificao
	 */
	double getClassificacaoFinal() const;
	/**
	 * Getter de todos os Comentarios/Classificacoes feitas
	 * @return Vector Comentarios
	 */
	vector<Comentario> getComentarios() const;
	/**
	 * Getter Descricao
	 * @return String Descricao
	 */
	string getDescricao() const;
	/**
	 * Getter Nome
	 * @return String Nome
	 */
	string getNome() const;
	/**
	 * Getter Pointer para o Developer que criou a  App
	 * @return Pointer Developer
	 */
	Developer* getDev() const;
	/**
	 * Getter Preco
	 * @return Double Preco
	 */
	double getPreco() const;
	/**
	 * Setter Preco
	 * @param Double Novo Preco
	 */
	void setPreco(double p);
	/**
	 * Setter Nome
	 * @param Novo Nome
	 */
	void setNome(string nome);
	/**
	 * Setter Categoria
	 * @param Nova Categoria
	 */
	void setCategoria(string categoria);
	/**
	 * Setter Comentarios (usado para carregar dos ficheiros)
	 * @param Vector com novos Comentarios
	 */
	void setComentarios(const vector<Comentario>& comentarios);
	/**
	 * Setter Developer(usado principalmente para carregar os ficheiros)
	 * @param Novo developer responsavel pela App
	 */
	void setDev(Developer* dev);
	/**
	 * Getter Id
	 * @return Unsigned Int Id App
	 */
	unsigned int getId() const;
	/**
	 * Getter Next Id
	 * @return Unsigned Int Id da proxima app a ser criada
	 */
	unsigned int getNextId() const;
	/**
	 * Setter Next Id
	 * @param nextId Id da proxima App a ser criada
	 */
	static void setNextId(unsigned int nextId);
	/**
	 * Getter Nr. Classificao
	 * @return
	 */
	int getNumClassificacoes() const;
	/**
	 * Setter Descricao
	 * @param descricao Nova Descricao
	 */
	void setDescricao(const string& descricao);
	/**
	 * Imprime de uma maneira legivel as infomacaos da App
	 * @return String como toda a informcao
	 */
	string imprime() const;
};


#endif /* APP_H_ */
