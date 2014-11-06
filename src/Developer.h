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


class Developer{
protected:
	int id;
	static unsigned int next_id;
	string nome;
	double saldo=0;
	string id_pass;
	string morada;
public:
	Developer(string nome,string id_pass,string morada);
	Developer(int id,string nome,double saldo,string id_pass,string morada);
	string getNome() const;
	double getSaldo() const;
	void setSaldo(unsigned int s);
	static void setNextID(unsigned int i);
	virtual string getMorada() const=0;
	virtual bool setMorada(string morada)=0;
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
	string getMorada() const;
	bool setMorada(string morada);
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
	string getMorada() const;
	bool setMorada(string morada);
	bool setNIF(string nif);
	void setExtra(string info);
	bool isEmpresa();
};


#endif


