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
#include "Date.h"

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


class App {
private:
	unsigned int id;/**< @brief ID unico de cada App*/
	static unsigned int next_id;/**< Proximo Id quando c se cria uma App */
	string nome;/**< Nome da App */
	string categoria;/**< Categoria em que se insere a App */
	string descricao;/**< Pequena descricao sobre a App */
	double preco;/**< Preco da App */
	double classificacao_final = 0;/**< Classificacao atribuida pelo clientes que compram a App */
	int num_classificacoes = 0; /**< Numero de Classificacaos ja lhe atribuidas */
	vector<Comentario> comentarios; /**< Vector com todos os Comentarios */
	Developer* dev; /**< Pointer para o developer que criou esta app */

	bool apagada;
	bool validada;/**< App Validada */
	Date data_submissao;

public:
	/**
	 * Construtor de App
	 * @param nome Nome
	 * @param categoria Categoria
	 * @param descricao Descricao
	 * @param preco Preco
	 */
	App(string nome, string categoria, string descricao, double preco,
				Date data);
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
	App(unsigned int id, string nome, string categoria, string descricao,
				double preco, double classificacao_final, int num_classificacoes,
				bool validada,Date data,bool apagada);
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
	 * Getter Classificacao
	 * @return Double Classificacao
	 */
	double getClassificacaoFinal() const;
	/**
	 * Setter Classificacao
	 * @param classificacao Classificacao a definir
	 */
	void setClassificacaoFinal(double classificacao);
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
	 * @param p Double Novo Preco
	 */
	void setPreco(double p);
	/**
	 * Setter Nome
	 * @param nome Novo Nome
	 */
	void setNome(string nome);
	/**
	 * Setter Categoria
	 * @param categoria Nova Categoria
	 */
	void setCategoria(string categoria);
	/**
	 * Setter Comentarios (usado para carregar dos ficheiros)
	 * @param comentarios Vector com novos Comentarios
	 */
	void setComentarios(const vector<Comentario>& comentarios);
	/**
	 *  Adiciona um comentario ao vetor de comentarios do developer e atualiza a classificacao total
	 * @param coment Comentario a adicionar ao vetor
	 */
	void addComentario(Comentario coment);
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
	static unsigned int getNextId();
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
	 * Incrementa por 1 o Num. total de classificacoes.
	 */
	void incNumClassificacoes();
	/**
	 * Setter Descricao
	 * @param descricao Nova Descricao
	 */
	void setDescricao(const string& descricao);
	/**
	 * Imprime de uma maneira legivel as infomacaos da App
	 * @return String como toda a informacao
	 */
	string imprime() const;
	/**
	 * Overloading do operador <
	 * @param appb App a comparar
	 * @return True se appa < appb ou False caso contrario
	 */
	bool operator<(const App& appb) const;

	/**
	 * Getter Validacao da App
	 * @return True se app aprovada ou False caso contrario
	 */
	bool isValidada() const;
	/**
	 * Altera o valor da flag apagada da app
	 * @param valor True ou False consoante o valor pretendido para validada
	 */
	void setValidada(bool valor);
	/**
	* Altera o valor da flag apagada da app
	* @param valor True ou False consoante o valor pretendido para validada
	*/
	void setApagada(bool valor);
	/**
	 * Getter Data de Submissao
	 * @return Data de Submissao da App
	 */
	const Date& getDataSubmissao() const;
	/**
	 * Setter Data de Submissao
	 * @param dataSubmissao Data da Submissao
	 */
	void setDataSubmissao(const Date& dataSubmissao);
	bool isApagada() const;
};

/**
 * @class AppPointer
 * @brief Encapsulamento do Pointer para uma App para ser usado na BST com o top 10 de apps
 */
class AppPointer{
public:
	/**
	 * Contrutor Vazio
	 */
	AppPointer(){app_pointer = NULL;}
	/**
	 * Construtor que aloca o apontador da app logo ao atributo da class
	 * @param apontador Apontador para App
	 */
	AppPointer(App* apontador){app_pointer = apontador;}
	App* app_pointer;
	/**
	 *
	 * @param app_p App a ser comparada na BST
	 * @return True caso se operador se verifique False o contrario
	 */
	bool operator<(const AppPointer& app_p) const;
	/**
	 * Faz exatamente o mesmo caso voce o objecto App mas aplicado a esta class
	 * @return App apontada por este objecto
	 */
	App operator*() const;
};


#endif /* APP_H_ */
