#ifndef DEVELOPER_H_
#define DEVELOPER_H_

#include <vector>
#include <string>
#include "login.h"
#include "app.h"

using namespace std;

class developer{
private:
	int id;
	static unsigned int next_id;
	string nome;
	double saldo;
	//vector <* venda> vendas;
	vector <app *> apps;
	login * data;
public:
	developer(string nome,double saldo,string id_pass);
	//vector<* venda> get_vendas();
	vector<app *> get_apps();
	login* get_login();
	string get_nome();
	double get_saldo() const;
	void set_saldo(unsigned int s);
};

#endif
