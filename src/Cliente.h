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

using namespace std;

class Vendas;

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
	vector<string> cesto_compras;
	unsigned int nr_vouchers;
	string id_pass; //TODO: implementar nos ficheiros
public:
	Cliente(int id,string nome,unsigned int idade,string sexo,int cartao_credito,float saldo,unsigned int nr_vouchers,string id_pass);//construtor para clientes ficheiro
	Cliente(string nome,unsigned int idade,string sexo,int cartao_credito, string id_pass);
	unsigned int getNext_id() const;
	int getCartaoCredito() const;
	int getId() const;
	unsigned int getIdade() const;
	string getNome() const;
	bool adicionaAppCesto(string app_name);
	bool eliminaAppCest(unsigned int i);
	float getSaldo() const;
	string getIdPass() const;
	void setIdPass(string id_pass);
	unsigned int getVouchers() const;
	void setVouchers(unsigned int voucher);
	void addVoucher();
	void removeVoucher();
	void setSaldo(float saldo);
	string getSexo() const;
	bool adicionarVenda(Vendas* v);
	vector<Vendas *> getHistorico() const;
	void setHistorico(vector<Vendas *> v);
	static void setNextID(unsigned int i);
};

#endif /* CLIENTE_H_ */
