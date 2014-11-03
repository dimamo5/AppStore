/*
 * Cliente.h
 *
 *  Created on: 31/10/2014
 *      Author: Moura
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "Vendas.h"

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
	unsigned int nr_vouchers;
public:
	Cliente(int id,string nome,unsigned int idade,string sexo,int cartao_credito,float saldo,unsigned int nr_vouchers);//construtor para clientes ficheiro
	Cliente(string nome,unsigned int idade,string sexo,int cartao_credito);
	unsigned int getNext_id() const;
	int getCartaoCredito() const;
	int getId() const;
	unsigned int getIdade() const;
	string getNome() const;
	float getSaldo() const;
	unsigned int getVouchers() const;
	void setVouchers(unsigned int voucher);
	void addVoucher();
	void removeVoucher();
	void setSaldo(float saldo);
	string getSexo() const;
	bool adicionarVenda(Vendas* v);
	vector<Vendas *> getHistorico() const;
	static void setNextID(unsigned int i);
};

#endif /* CLIENTE_H_ */
