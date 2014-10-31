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
	int saldo; //TODO mudar para float saldo e custo e preco
	vector<Vendas *> historico;
	//TODO numero de voucher
public:
	Cliente(int id,string nome,unsigned int idade,string sexo,int cartao_credito,int saldo);//construtor para clientes ficheiro
	Cliente(string nome,unsigned int idade,string sexo,int cartao_credito);
	unsigned int getNext_id() const;
	int getCartaoCredito() const;
	int getId() const;
	unsigned int getIdade() const;
	string getNome() const;
	int getSaldo() const;
	void setSaldo(int saldo);
	string getSexo() const;
	bool adicionarVenda(Vendas* v);
	vector<Vendas *> getHistorico() const;
	static void setNextID(unsigned int i);
};

#endif /* CLIENTE_H_ */
