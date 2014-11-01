#ifndef DEVELOPER_H_
#define DEVELOPER_H_

#include <vector>
#include <string>
#include "Login.h"
#include "App.h"
#include "Vendas.h"

using namespace std;

class Vendas;
class App;

class Developer{
private:
	int id;
	static unsigned int next_id;
	string nome;
	double saldo=0;
	Login * data; //TODO remove pointer
public:
	Developer(string nome,string id_pass);
//	vector<Vendas*> get_vendas();
//	vector<App *> get_apps() const;
	Login* get_login() const;
	string get_nome() const;
	double get_saldo() const;
	void set_saldo(unsigned int s);
//	bool adiciona_app(App &a);
	//TODO polimorfismo
};



class Individual: public Developer{
	string morada;
public:
	Individual(string nome,string id_pass,string morada);
	string getMorada() const;
	void setMorada(string morada);

};

class Empresa: public Developer{
	unsigned int NIF;
public:
	Empresa(string nome,string id_pass,unsigned int NIF);
	unsigned int getNIF() const;
	void setNIF(unsigned int NIF);
};


#endif


