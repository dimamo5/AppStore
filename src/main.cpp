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
	try {
		MIEIC_Play.load_all();
	} catch (File_Exp& exp) {
		cor(BLACK, RED);
		cerr << "Error" + exp.getIdErro() << endl;
		cerr << exp.getDescricaoErro();
		cor(BLACK, WHITE); //reset à cor
	}
//VARIAVEIS PARA TESTES

//	 Date data_venda1(2014, 11, 7, 10, 10);
//	 Vendas* venda1 = new Vendas(10, data_venda1, "App-Fixe-Vendida-1"); //preco - data - nome
//	 venda1->setAppVendidaId(1);
//	 MIEIC_Play.vendas.push_back(venda1);
//	 cli_temp.adicionarVenda(venda1); // puxa o pointer do ultimo elemento do vetor a ser adicionado
//
//	 Vendas* venda2 = new Vendas(20, data_venda1, "App-Fixe-Vendida-2"); //preco - data - nome
//	 venda2->setAppVendidaId(2);
//	 MIEIC_Play.vendas.push_back(venda2);
//
//	 cli_temp.adicionarVenda(venda2);

/*  Cliente cli_temp("Diogo Cliente", 19, "M", 123456789, "1");

	MIEIC_Play.clientes.push_back(cli_temp);

	Cliente cli_temp2("Pedro Cliente", 18, "M", 123123123, "2");
	MIEIC_Play.clientes.push_back(cli_temp2);

	Developer* individ1 = new Individual("Diogo Dev Ind", "1", "Rio de Loba",
			"Diogo Moura Lda");
	MIEIC_Play.dev.push_back(individ1);

	Developer* empresa1 = new Empresa("Pedro Dev Emp", "1",
			"Rua do Francial, lote 5, Rio de Loba", "123123123",
			"CPedro  AT Inc.");
	MIEIC_Play.dev.push_back(empresa1);

	App app1("FPS", "Jogos", "jogo-accao", 2);
	MIEIC_Play.apps.push_back(app1);
	App app2("MOBA", "Jogos", "jogo-aventura", 3);
	MIEIC_Play.apps.push_back(app2);
	App app3("Hunter Games", "Livros", "Livro-Aventura", 8);
	MIEIC_Play.apps.push_back(app3);
	App app4("Warriors", "Musica", "Musica-rock", 1);
	MIEIC_Play.apps.push_back(app4);
	App app5("Wallpapers", "Utilidade", "Wallpaper de Gatos", 1);
	MIEIC_Play.apps.push_back(app5);

	MIEIC_Play.apps[0].setDev(individ1);
	MIEIC_Play.apps[1].setDev(empresa1);
	MIEIC_Play.apps[2].setDev(individ1);
	MIEIC_Play.apps[3].setDev(individ1);
	MIEIC_Play.apps[4].setDev(empresa1);
*/

	menuInicial(MIEIC_Play);

	return 0;
}
