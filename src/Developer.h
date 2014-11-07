#ifndef DEVELOPER_H_
#define DEVELOPER_H_

#include <vector>
#include <string>
#include "App.h"
#include "Vendas.h"
#include "Cliente.h"

class Developer;
class Cliente;

extern Developer* dev_act;
extern Cliente* cli_act;

using namespace std;
/*
 * @class Developer
 * @brief Classe referente a developers.
 * Contem 2 subclasses - Individual e Empresa
 */

class Developer{
protected:
	int id;
	static unsigned int next_id;
	string nome;
	double saldo=0;
	string id_pass;
	string morada;
public:
	/**
	 * Construtor Developer
	 * @param nome Nome
	 * @param id_pass Password de acesso à AppStore
	 * @param morada Morada
	 */
	Developer(string nome,string id_pass,string morada);
	/**
	 *  Construtor Developer(usado para carregar objectos dos ficheiros)
	 * @param id Id unico de cada Developer
	 * @param nome Nome
	 * @param saldo Saldo da conta
	 * @param id_pass Password de acesso à AppStore
	 * @param morada Morada
	 */
	Developer(int id,string nome,double saldo,string id_pass,string morada);
	/**
	 * Getter Nome
	 * @return String Nome
	 */
	string getNome() const;
	/**
	 * Getter Saldo
	 * @return Double Saldo
	 */
	double getSaldo() const;
	/**
	 * Setter Saldo
	 * @param s Novo Saldo
	 */
	void setSaldo(unsigned int s);
	/**
	 * Setter Next Id
	 * @param i Id do proximo objecto criado por esta classe
	 */
	static void setNextID(unsigned int i);
	/**
	 * Getter de Morada
	 * @return String Morada
	 */
	virtual string getMorada() const;
	virtual bool setMorada(string morada);
	virtual string getExtra() const=0;
	virtual string getNIF() const =0;
	virtual bool setNIF(string nif) =0;
	virtual void setExtra(string info)=0;
	virtual bool isEmpresa() = 0;
	int getId() const;
	void setId(int id);
	string getIdPass() const;
	void setIdPass(string id_pass);
	unsigned int getNextId() const;

};



class Individual: public Developer{
	string NomePessoal;
public:
	Individual(string nome,string id_pass,string morada,string NomePessoal);
	Individual(int id,string nome,double saldo,string id_pass,string morada,string NomePessoal);
	string getExtra() const;
	void setExtra(string info);
	bool setNIF(string nif);
	string getNIF() const;
	bool isEmpresa();

};

class Empresa: public Developer{
	string NIF;
	string NomeEmpresa;
public:
	Empresa(string nome,string id_pass,string morada,string NIF, string NomeEmpresa);
	Empresa(int id,string nome,double saldo,string id_pass,string morada,string NIF, string NomeEmpresa);
	string getExtra() const;
	string getNIF() const;
	bool setNIF(string nif);
	void setExtra(string info);
	bool isEmpresa();
};


#endif


