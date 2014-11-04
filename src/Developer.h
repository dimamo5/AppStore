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
public:
	Developer(string nome,string id_pass);
	Developer(int id,string nome,double saldo,string id_pass);
	string getNome() const;
	double getSaldo() const;
	void setSaldo(unsigned int s);
	static void setNextID(unsigned int i);
	virtual string getType() const =0;
	virtual string getExtra() const=0;
	virtual void setExtra(string info)=0;
	int getId() const;
	void setId(int id);
	string getIdPass() const;
	unsigned int getNextId() const;
};



class Individual: public Developer{
	string morada;
public:
	Individual(string nome,string id_pass,string morada);
	Individual(int id,string nome,double saldo,string id_pass,string morada);
	string getExtra() const;
	void setExtra(string info);
	string getType() const;

};

class Empresa: public Developer{
	string NIF;
public:
	Empresa(string nome,string id_pass,string NIF);
	Empresa(int id,string nome,double saldo,string id_pass,string NIF);
	string getExtra() const;
	string getType() const;
	void setExtra(string info);
};


#endif


