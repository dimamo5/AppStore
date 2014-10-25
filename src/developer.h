#ifndef DEVELOPER_H_
#define DEVELOPER_H_

#include <vector>
#include <string>
#include "login.h"

using namespace std;

class Developer{
private:
	static long id;
	string nome;
	double saldo;
	//vector <* venda> vendas;
	//vector <* app> apps;
	Login * data;
public:
	Developer(string nome,double saldo,string id_login,string id_pass);
	//vector<* venda> get_vendas();
	//vector<* app> get_apps();
	Login* get_login();
	string get_nome();
	double get_saldo();
};

#endif
