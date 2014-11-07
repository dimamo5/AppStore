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

//VARIAVEIS PARA TESTES

Cliente cli_temp("APedro Cliente", 18, "M", 123123123, "1");
MIEIC_Play.clientes.push_back(cli_temp);

Developer* individ1 = new Individual("APedro", "1", "Rua do Francial, lote 5, Rio de Loba", "Pedro Costa");
MIEIC_Play.dev.push_back(individ1);

Developer* individ2 = new Individual("BPedro", "1", "Rua do Francial, lote 5, Rio de Loba", "Pedro Costa");
MIEIC_Play.dev.push_back(individ2);

Developer* individ3 = new Individual("CPedro", "1", "Rua do Francial, lote 5, Rio de Loba", "Pedro Costa");
MIEIC_Play.dev.push_back(individ3);

Developer* empresa1 = new Empresa("CPedro", "1","Rua do Francial, lote 5, Rio de Loba", "123123123", "CPedro  AT Inc.");
MIEIC_Play.dev.push_back(empresa1);

App app1("aaa","jogos","jogo-accao",4);
MIEIC_Play.apps.push_back(app1);
App app2("bbb","filmes","filme-aventura",3);
MIEIC_Play.apps.push_back(app2);
App app3("ccc","livros","livro-policial",2);
MIEIC_Play.apps.push_back(app3);
App app4("ddd","musica","musica-rock",1);
MIEIC_Play.apps.push_back(app4);
App app5("abc","musica","musica-rock",1);
MIEIC_Play.apps.push_back(app5);
App app6("cdd","musica","musica-rock",1);
MIEIC_Play.apps.push_back(app6);


for(unsigned int i = 0; i< MIEIC_Play.apps.size(); i++){
	MIEIC_Play.apps[i].setDev(individ1);
}
MIEIC_Play.apps[4].setDev(individ2);
MIEIC_Play.apps[5].setDev(individ3);

	int opc=0;
		do
		{
			opc=menuInicial(MIEIC_Play);
		} while (opc); // so acaba o programa quando opc == 0


	return 1;
}
