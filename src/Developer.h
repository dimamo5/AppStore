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

class Developer {
protected:
	int id;
	static unsigned int next_id;
	string nome;
	double saldo = 0;
	string id_pass;
	string morada;
public:
	/**
	 * Construtor Developer
	 * @param nome Nome
	 * @param id_pass Password de acesso à AppStore
	 * @param morada Morada
	 */
	Developer(string nome, string id_pass, string morada);
	/**
	 *  Construtor Developer(usado para carregar objectos dos ficheiros)
	 * @param id Id unico de cada Developer
	 * @param nome Nome
	 * @param saldo Saldo da conta
	 * @param id_pass Password de acesso à AppStore
	 * @param morada Morada
	 */
	Developer(int id, string nome, double saldo, string id_pass, string morada);
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
	 * Metodo para adicionar saldo a um developer
	 * @param saldo_add Saldo a adicionar ao saldo ja existente do developer
	 */
	void addSaldo(double saldo_add);
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
	/**
	 * Setter Morada
	 * @param morada Nova Morada
	 * @return True em sucesso caso contrario False
	 */
	virtual bool setMorada(string morada);
	/**
	 * Metodo Virtual Puro para obter nome individual ou de empresa
	 * @return String Nome
	 */
	virtual string getExtra() const=0;
	/**
	 * Metodo Virtual Puro para obter NIF da empresa
	 * @return String NIF
	 */
	virtual string getNIF() const =0;
	/**
	 * Metodo Virtual Puro para atribuir NIF a uma empresa
	 * @param nif
	 * @return True em sucesso caso contrario False
	 */
	virtual bool setNIF(string nif) =0;
	/**
	 * Metodo Virtual Puro para atribuir Nome Individual ou de Empresa
	 * @param info Novo Nome
	 */
	virtual void setExtra(string info)=0;
	/**
	 * Metodo Virtual Puro para saber se SubClasse é Empresa ou Individual
	 * @return
	 */
	virtual bool isEmpresa() = 0;
	/**
	 * Getter Id
	 * @return Int Id
	 */
	int getId() const;
	/**
	 * Setter Id
	 * @param id Novo Id
	 */
	void setId(int id);
	/**
	 * Getter Pass para o login
	 * @return String Pass
	 */
	string getIdPass() const;
	/**
	 * Setter Pass para o login
	 * @param id_pass Nova Pass
	 */
	void setIdPass(string id_pass);
	/**
	 * Getter Next Id
	 * @return Int Next Id
	 */
	static unsigned int getNextId();

};
/**
 * @class Individual
 * @brief Sub classe de Developer
 */
class Individual: public Developer {
	string NomePessoal;
public:
	/**
	 * Construtor Developer Individual
	 * @param nome Nome
	 * @param id_pass Pass para Login
	 * @param morada Morada
	 * @param NomePessoal Nome Pessoal
	 */
	Individual(string nome, string id_pass, string morada, string NomePessoal);
	/**
	 * Construtor Developer Individual(usado para carregar objectos da classe dos ficheiros)
	 *
	 * @param id Id unico de cada Developer
	 * @param nome Nome
	 * @param saldo Saldo
	 * @param id_pass Pass para Login
	 * @param morada Morada
	 * @param NomePessoal Nome Pessoal
	 */
	Individual(int id, string nome, double saldo, string id_pass, string morada,
			string NomePessoal);
	/**
	 * Getter Nome Pessoal
	 * @return String Nome Pessoal
	 */
	string getExtra() const;
	/**
	 * Setter Nome Pessoal
	 * @param info Novo Nome Pessoal
	 */
	void setExtra(string info);
	/**
	 * Setter NIF
	 * @param nif NIF
	 * @return retorna falso pois nao é possivel haver NIF no developer individual
	 */
	bool setNIF(string nif);
	/**
	 * Getter NIF
	 * @return Retorna String vazia
	 */
	string getNIF() const;
	/**
	 * Testa se e Empresa
	 * @return False
	 */
	bool isEmpresa();

};
/**
 * @class Empresa
 * @brief Sub class de Developer
 */
class Empresa: public Developer {
	string NIF;
	string NomeEmpresa;
public:
	/**
	 * Construtor Developer Empresa
	 * @param nome Nome
	 * @param id_pass Pass para Login
	 * @param morada Morada
	 * @param NIF NIF
	 * @param NomeEmpresa Nome Empresa
	 */
	Empresa(string nome, string id_pass, string morada, string NIF,
			string NomeEmpresa);
	/**
	 * Construtor Developer Empresa(usado para carregar objectos da classe dos ficheiros)
	 * @param id Id
	 * @param nome Nome
	 * @param saldo Saldo
	 * @param id_pass Pass para Login
	 * @param morada Morada
	 * @param NIF NIF
	 * @param NomeEmpresa Nome Empresa
	 */
	Empresa(int id, string nome, double saldo, string id_pass, string morada,
			string NIF, string NomeEmpresa);
	/**
	 * Getter Nome Empresa
	 * @return String Nome Empresa
	 */
	string getExtra() const;
	/**
	 * Getter NIF
	 * @return String NIF
	 */
	string getNIF() const;
	/**
	 * Setter NIF
	 * @param nif Novo NIF
	 * @return True
	 */
	bool setNIF(string nif);
	/**
	 * Setter Nome Empresa
	 * @param info Novo Nome de Empresa
	 */
	void setExtra(string info);
	/**
	 * Testa se Developer é Empresa ou Individual
	 * @return True
	 */
	bool isEmpresa();
};

#endif

