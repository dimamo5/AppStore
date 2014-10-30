#ifndef DEVELOPER_H_
#define DEVELOPER_H_

#include <vector>
#include <string>
#include "login.h"
#include "app.h"

using namespace std;

class Developer{
private:
	int id;
	static unsigned int next_id;
	string nome;
	double saldo;
	//vector <* venda> vendas;
	vector <App *> apps;
	Login * data;
public:
	Developer(string nome,double saldo,string id_pass);
	//vector<* venda> get_vendas();
	vector<App *> get_apps();
	Login* get_login();
	//vector <* app> apps;
	string get_nome();
	double get_saldo() const;
	void set_saldo(unsigned int s);
};

#endif
