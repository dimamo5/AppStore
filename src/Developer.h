#ifndef DEVELOPER_H_
#define DEVELOPER_H_

#include <vector>
#include <string>
#include "Login.h"
#include "App.h"
#include "Vendas.h"

using namespace std;

class Developer{
private:
	int id;
	static unsigned int next_id;
	string nome;
	double saldo=0;
	vector <Vendas*> vendas;
	vector <App *> apps;
	Login * data;
public:
	Developer(string nome,string id_pass);
	vector<Vendas*> get_vendas();
	vector<App *> get_apps() const;
	Login* get_login() const;
	string get_nome() const;
	double get_saldo() const;
	void set_saldo(unsigned int s);
	bool adiciona_app(App &a);
};

#endif
