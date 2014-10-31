/*
 * Cliente.h
 *
 *  Created on: 31/10/2014
 *      Author: Moura
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "vendas.h"

class Cliente {
private:
	int id;
	static unsigned int next_id;
	string nome;
	unsigned int idade;
	string sexo;
	int cartao_credito;
	int saldo;
	vector<Vendas *> vendas;
public:
	Cliente(string nome,unsigned int idade,string sexo,int cartao_credito);
	int getCartaoCredito() const;
	int getId() const;
	unsigned int getIdade() const;
	string getNome() const;
	int getSaldo() const;
	void setSaldo(int saldo);
	string getSexo() const;
	vector<Vendas*> getVendas() const;
};

#endif /* CLIENTE_H_ */
