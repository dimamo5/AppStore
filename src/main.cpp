#include <iostream>
#include "menu.h"
#include "Developer.h"
#include "App.h"
#include "Vendas.h"
#include "Cliente.h"
#include "AppStore.h"
using namespace std;

Developer* dev_act = NULL;
Cliente* cli_act = NULL;

int main() {
	AppStore MIEIC_Play;
	Cliente c1(1,"Moura",19,"M",1234,0);
	Cliente c2(1,"Pedro",19,"M",4321,0);
	ofstream file;
	file.open("files/clients.txt");
	MIEIC_Play.clientes.push_back(c1);
	MIEIC_Play.clientes.push_back(c2);
	cout<<MIEIC_Play.clientes.size();
	MIEIC_Play.save_clientes(file);
	menu();
	file.close();
	return 1;

}
