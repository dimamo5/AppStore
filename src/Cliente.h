/*
 * Cliente.h
 *
 *  Created on: 31/10/2014
 *      Author: Moura
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string>
#include "Vendas.h"
#include "Developer.h"
#include "App.h"

using namespace std;

class App;
class Vendas;
/**
 * @class Cliente
 * @brief Classe responsavel pela Gestao de Cliente
 */
class Cliente {
private:
	int id;
	static unsigned int next_id;
	string nome;
	unsigned int idade;
	string sexo;
	int cartao_credito;
	float saldo;
	vector<Vendas *> historico;
	vector<int> cesto_compras;
	unsigned int nr_vouchers;
	string id_pass; //TODO: implementar nos ficheiros
public:
	/**
	 * Construtor Cliente (usado para carregar objectos do ficheiros)
	 * @param id Id unico dos clientes
	 * @param nome Nome
	 * @param idade Idade
	 * @param sexo Sexo
	 * @param cartao_credito Cartao Credito
	 * @param saldo Saldo
	 * @param nr_vouchers Nr. Vouchers
	 * @param id_pass Pass para Login
	 */
	Cliente(int id, string nome, unsigned int idade, string sexo,
			int cartao_credito, float saldo, unsigned int nr_vouchers,
			string id_pass); //construtor para clientes ficheiro
	/**
	 * Construtor Cliente
	 * @param nome Nome
	 * @param idade Idade
	 * @param sexo Sexo
	 * @param cartao_credito Cartao Credito
	 * @param id_pass Pass para Login
	 */
	Cliente(string nome, unsigned int idade, string sexo, int cartao_credito,
			string id_pass);
	/**
	 * Getter Next Id
	 * @return Int Next Id
	 */
	unsigned int getNext_id() const;
	/**
	 * Getter Cartao Credito
	 * @return Int Cartao Credito
	 */
	int getCartaoCredito() const;
	/**
	 * Getter Id
	 * @return Int Id
	 */
	int getId() const;
	/**
	 * Getter Idade
	 * @return Int Idade
	 */
	unsigned int getIdade() const;
	/**
	 * Getter Nome
	 * @return String Nome
	 */
	string getNome() const;
	/**
	 * Getter Cesto das Compras<Id App> do Cleinte
	 * @return vector Cesto Compras
	 */
	vector<int> getCesto() const;
	/**
	 * Adiciona uma App ao cesto de compras
	 * @param app_id Id da app a adicionar
	 * @return True em sucesso caso contrario False
	 */
	bool adicionaAppCesto(int app_id);
	/**
	 * Elimina uma App do Cesto de Compras
	 * @param i Id da App a remover
	 * @return True em sucesso caso contrario False
	 */
	bool eliminaAppCesto(unsigned int i);
	/**
	 * Getter Saldo
	 * @return Float Saldo
	 */
	float getSaldo() const;
	/**
	 * Getter Pass
	 * @return String Pass
	 */
	string getIdPass() const;
	/**
	 * Setter Pass
	 * @param id_pass Nova Pass do login
	 */
	void setIdPass(string id_pass);
	/**
	 * Getter Voucher
	 * @return Int Nr. Vouchers
	 */
	unsigned int getVouchers() const;
	/**
	 * Setter Voucher
	 * @param voucher Nr. Voucher que o Cliente passa a ter
	 */
	void setVouchers(unsigned int voucher);
	/**
	 * Adiciona 1 Voucher ao numero total de Vouchers
	 */
	void addVoucher();
	/**
	 * Remove 1 Voucher ao numero total de Vouchers
	 */
	void removeVoucher();
	/**
	 * Setter Saldo
	 * @param saldo Novo Saldo do Cliente
	 */
	void setSaldo(float saldo);
	/**
	 * Setetr Cartao de Credito
	 * @param cartao_credito Novo Cartao de Credito
	 */
	void setCartao(int cartao_credito);
	/**
	 * Getter Sexo
	 * @return String Masculino/ Feminino
	 */
	string getSexo() const;
	/**
	 * Adiciona uma Venda ao Cliente
	 * @param v Venda a ser adiciona ao vector
	 */
	void adicionarVenda(Vendas* v);
	/**
	 * Getter Historico
	 * @return Historico de Transacoes do Cliente
	 */
	vector<Vendas *> getHistorico() const;
	/**
	 * Setter Historico
	 * @param v Novo Historico de Transacoes
	 */
	void setHistorico(vector<Vendas *> v);
	/**
	 * Esvazia o Cesto de compras. E normalmente usado apos checkout do cesto.
	 */
	void emptyCesto();
	/**
	 * Setter Next Id
	 * @param i Proximo Id de um novo Cliente Criado
	 */
	static void setNextID(unsigned int i);
	/**
	 * Verifica se o Cliente ja comprou uma determinada App
	 * @param app_option App a ser verificada
	 * @return True caso ja tenha comprado ou False no contrario
	 */
	bool jaComprou(App app_option);
	/**
	 * Verifica se o Historico de um Cliente está Vazio
	 * @return True em sucesso caso contrario False
	 */
	bool historicoVazio();
	/**
	 * Imprime de uma maneira legivel as infomacaos do cliente
	 * @return String como toda a informacao
	 */

};

#endif /* CLIENTE_H_ */
