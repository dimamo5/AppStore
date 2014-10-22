#ifndef DEVELOPER_H_
#define DEVELOPER_H_

#include <vector>
#include <string>
#include "login.h"

using namespace std;

class developer{
private:
	static long id;
	string nome;
	double saldo;
	//vector <* venda> vendas;
	//vector <* app> apps;
	login * data;
public:
	developer(string nome,double saldo,string id_login,string id_pass);
	//vector<* venda> get_vendas();
	//vector<* app> get_apps();
	login* get_login();
	string get_nome();
	double get_saldo();
};

#endif
