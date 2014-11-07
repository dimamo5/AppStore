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

Cliente cli_temp2("BPedro Cliente", 19, "M", 123123123, "1");
MIEIC_Play.clientes.push_back(cli_temp2);

Date data_venda1(2014,11,7,10,10);
Vendas venda1(10, data_venda1,"App-Fixe-Vendida");
venda1.setAppVendidaId(1);
MIEIC_Play.vendas.push_back(venda1);
cli_temp2.adicionarVenda(&MIEIC_Play.vendas[MIEIC_Play.vendas.size()-1]); // puxa o pointer do ultimo elemento do vetor a ser adicionado

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

Comentario comment1("app muito boa",1,5); // app muito boa, cliente 1, 5 estrelas
Comentario comment2("app awesome",1,4);

MIEIC_Play.apps[0].addComentario(comment1);
MIEIC_Play.apps[0].addComentario(comment2);


	int opc=0;
		do
		{
			opc=menuInicial(MIEIC_Play);
		} while (opc); // so acaba o programa quando opc == 0


	return 1;
}
