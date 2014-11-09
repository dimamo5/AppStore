/*
 * Vendas.h
 *
 *  Created on: 30/10/2014
 *      Author: Casa
 */

#ifndef VENDAS_H_
#define VENDAS_H_

#include <vector>
#include <string>
#include "App.h"
#include "Date.h"
#include "Developer.h"
#include "Cliente.h"

using namespace std;

class Cliente;
class Developer;

extern Developer* dev_act;
extern Cliente* cli_act;

class App;
/**
 * @class Vendas
 * @brief Classe responsavel pela transacao entre um cliente e um developer,tendo esta associada uma app.
 *
 */
class Vendas {
private:
	int id;
	static unsigned int next_id;
	float preco;
	Date data_venda;
	int id_app_vendida;
	bool app_apagada;
	bool retorno;
	string reclamacao;
	string nome_app_momento_venda = "";

public:
	/**
	 *Construtor Venda
	 * @param preco Preco da App na altura da compra
	 * @param data_venda Data da Compra
	 * @param app_removida_nome Nome da App Comprada
	 */
	Vendas(float preco, Date data_venda, string app_removida_nome);
	/**
	 * Construtor Venda (usada da carregar objecto dos ficheiros)
	 * @param id Id unco da Venda
	 * @param preco Preco da App na altura da compra
	 * @param data_venda Data da Compra
	 * @param retorno Venda retornada ou nao
	 * @param app_apagada App ainda existe ou ja foi removida pelo developer
	 * @param id_app_vendida Nome da App associada à venda
	 * @param reclamacao Reclamacao escrita pelo cliente quando este devolveu a compra da app
	 * @param app_removida_nome Nome da App Comprada
	 */
	Vendas(int id, float preco, Date data_venda, bool retorno, bool app_apagada,
			int id_app_vendida, string reclamacao, string app_removida_nome);
	/**
	 *Getter Id
	 * @return Int id
	 */
	int getId() const;
	/**
	 * Getter Preco
	 * @return float preco
	 */
	float getPreco() const;
	/**
	 * Getter Data
	 * @return Data Venda
	 */
	Date getData() const;
	/**
	 * Getter AppId
	 * @return Int AppId
	 */
	unsigned int getAppId() const;
	/**
	 * Getter Next Id
	 * @return Int Proximo Id
	 */
	static unsigned int getNextId();
	/**
	 * Setter Next Id
	 * @param nextId Id da proxima Venda criada
	 */
	static void setNextId(unsigned int nextId);
	/**
	 * Getter Reclamacao
	 * @return String Reclamacao
	 */
	string getReclamacao() const;
	/**
	 * Analisa se a Venda foi retornada ou nao
	 * @return True or false
	 */
	bool isRetorno() const;
	/**
	 * Reclamacao ao retornar uma Venda
	 * @param reclamacao
	 */
	void reclamar(string reclamacao);
	/**
	 * Getter Flag App Apagada
	 * @return True se App for apagada da AppStore, False caso contrario
	 */
	bool getAppApagada() const;
	/**
	 * Setter Flag App Apagada
	 * @param value True se App for apagada da AppStore, False caso contrario
	 */
	void setAppApagada(bool value);
	/**
	 * Getter Nome da App associada com a Venda
	 * @return String Nome
	 */
	string getAppVendidaNome() const;
	/**
	 * Getter Id da App associada com a venda
	 * @return Int Id da App
	 */
	int getAppVendidaId() const;
	/**
	 * Setter Id da App associada com a Venda
	 * @param id Id da App
	 */
	void setAppVendidaId(int id);
	/**
	 * Setter Nome da App associada com a venda
	 * @param appRemovidaNome Nome da App
	 */
	void setAppVendidaNome(string appRemovidaNome);
};

#endif /* VENDAS_H_ */

