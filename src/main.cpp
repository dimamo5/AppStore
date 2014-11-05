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
Developer* individ = new Individual("Pedro", "1", "Rua do Francial, lote 5, Rio de Loba");
MIEIC_Play.dev.push_back(individ);

App app1("app1","jogos","jogo-accao",1);
MIEIC_Play.apps.push_back(app1);
App app2("app2","filmes","filme-aventura",2);
MIEIC_Play.apps.push_back(app2);
App app3("app3","livros","livro-policial",3);
MIEIC_Play.apps.push_back(app3);
App app4("app4","musica","musica-rock",4);
MIEIC_Play.apps.push_back(app4);

for(unsigned int i = 0; i< MIEIC_Play.apps.size(); i++){
	MIEIC_Play.apps[i].setDev(individ);
}


	int opc=0;
		do
		{
			opc=menuInicial(MIEIC_Play);
		} while (opc); // so acaba o programa quando opc == 0


	return 1;
}
