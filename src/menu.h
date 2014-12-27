/*
 * menu.h
 *
 *  Created on: 02/11/2014
 *      Author: Moura
 */

/**
 * @file menu.h Ficheiro com funcoes do menu
 */

#ifndef MENU_H_
#define MENU_H_

/**< Macros de cores para usar no menu */
#define BLACK 0  // 0000
#define BLUE 1   // 0001
#define GREEN 2  // 0010
#define AQUA 3   // 0011
#define RED 4    // 0100        ----> MSB is the intensity and 3 LSB are the colors
#define PURPLE 5 // 0101
#define YELLOW 6 // 0110       Windows API has 8 bits for colors, 4 for the background and
#define WHITE 7  // 0111       then 4 for the foreground
#define GRAY 8   // 1000
#define LIGHT_GREEN 10 // 1010  -> GREEN with intensity at 1
#define LIGHT_RED 12  // 1100  -> RED with intensity at 1

/** Maximo de items a mostar no ecra, quando se usa o scroll */
const unsigned int MAX_PER_SCREEN = 6;
/** Pass de Administrador para validacao */
const std::string ADMIN_PASS = "123";

#include "AppStore.h"
#include "Cliente.h"
#include "App.h"


class Date;

/**
 * Pointer para o developer atual, apos ele fazer login
 */
extern Developer* dev_act;

/**
 * Pointer para o cliente atual, apos ele fazer login
 */
extern Cliente* cli_act;

/**
 * Mete o cursor numa posicao do ecra, para se poder escrever nesse local diretamente
 *
 * @param xpos  Coluna para a qual o cursor vai
 * @param ypos  Linha para a qual o cursor vai
 */
void gotoxy(int xpos, int ypos);
/**
 * Escreve a data atual na posicao indicada nos parametros
 * @param xpos Coluna onde e escrita a data
 * @param ypos Linha onde e escrita a data
 */
void porDataNoCanto(int xpos, int ypos);
/**
 * Pega num vetor de apps e cria um vetor de strings com o nome das apps
 * @param apps Vetor com objetos do tipo App
 * @return Devolve o vetor (de strings) com os nomes das apps inseridas como argumento
 */
vector<string> getAppNames(vector<App> apps);
/**
 * Pega num vetor de comentarios e forma frases do tipo "Cliente x - classificacao - comentario"
 * @param comentarios Vetor com objetos do tipo Comentario
 * @return Devolve o vetor (de strings) com a concatenacao de Cliente - classificacao - comentario
 */
vector<string> getAppComentarios(vector<Comentario> comentarios);
/**
 *
 * @param devs Vetor com objetos do tipo Developer*
 * @return Devolve o vetor (de strings) com os nomes dos developers inseridos como argumento
 */
vector<string> getDevNames(vector<Developer*> devs);

/**
 * Janela/Menu para verificacao da password do cliente ou dev, consoante quem estiver logged in
 * @param dev_or_cli  Pointer para o cliente ou developer que estiver logged in
 * @return True, se a pass foi corretamente escrita. False, se a password estava errada
 */
template<typename T>
bool verificaPass(T* dev_or_cli);
/**
 * Funcao que imprime opcoes de um vetor, sendo possivel ao user fazer scroll atraves das opcoes.
 * Se houver mais opcoes do que as maximas que consegue mostrar, funciona como menu de scroll (como as mensagens num telemovel)
 * @param options Vetor de opcoes que vao ser exibidas no ecra
 * @param selected_option Opcao actual do vetor em que se esta - esta opcao esta highlighted com cor branca
 * @param max_per_screen Maximo de opcoes mostradas de cada vez no ecra
 */
void printMenuScroll(vector<string> options, int selected_option, const unsigned int max_per_screen);
/**
 *  Altera a cor do background e foreground para os valores/cores especificadas
 * @param background Cor para o fundo do API - usa-se aqui uma das macros definidas
 * @param foreground Cor para o foreground/letra do API - usa-se aqui uma das macros definidas
 */
void cor(int background, int foreground);
/**
 * Retorna um numero consoante a tecla premida
 * @return Se premir as setas de cima ou baixo, retorna 1 ou -1. Se premir as de lado, retorna 2 ou -2. Se premir enter, retorna 13.
 */
int teclas();
/**
 * Nos menus onde se chama a funcao teclas(), vai restringir as opcoes de maneira a que,
 * quando se chega a ultima opcao, volta a primeira, e quando se passa para cima da primeira, volta a ultima
 * @param min Nr. da opcao minima
 * @param max Nr. (valor absoluto) da opcao maxima
 * @param opcao Opcao atual em que se encontra o menu
 * @return Opcao na qual vai estar depois das restricoes
 */
int RestringeOpcaoTeclas(int min, int max, int opcao);
/**
 * Menu inicial onde sao exibidas opcao de login, registo, visita de appstore ou sair do programa, gravando alteracoes
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuInicial(AppStore& mieic);
/**
 * Menu para login, onde o user escolhe qual o tipo de login a efetuar, se de Developer ou Cliente
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuLogin(AppStore& mieic);
/**
 * Menu para registo, onde o user escolhe qual o tipo de registo a efetuar, se de Developer ou Cliente
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuRegistar(AppStore& mieic);
/**
 * Menu para Login do cliente, onde este fornece o seu ID e password
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuLoginCliente(AppStore& mieic);
/**
 * Menu para Login do developer, onde este fornece o seu ID e password
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuLoginDeveloper(AppStore& mieic);
/**
 * Menu para registo do cliente, onde este fornece as suas informacoes
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuRegistarCliente(AppStore& mieic);
/**
 * Menu para registo do developer individual, onde este fornece as suas informacoes
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuRegistarDeveloperIndividual(AppStore& mieic);
/**
 * Menu para registo do developer empresarial, onde este fornece as suas informacoes
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuRegistarDeveloperEmpresa(AppStore& mieic);
/**
 * Menu principal de cliente, onde sao exibidas os submenus: visitar appstore,
 * mexer nas transacoes e credito, alterar definicoes, ver os atributos e fazer logout.
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuCliente(AppStore& mieic);
/**
 * Menu principal de developer, onde sao exibidas os submenus: visitar appstore, gestao de apps,
 * alterar definicoes, ver os atributos e fazer logout.
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuDeveloper(AppStore& mieic);
/**
 * Menu do Cliente onde este pode escolher os submenus de Adicionar Credito, ver o seu cesto de compras,
 * rever o seu historico de vendas/compras ou regressar ao menu anterior.
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuClienteTransacoes(AppStore& mieic);
/**
 * Menu do Cliente onde ele pode escolher os submenus de Alterar Password, Alterar Nr. Cartao de Credito,
 * e apagar a sua conta
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuClienteDefinicoes(AppStore& mieic);
/**
 * Menu do Developer onde ele pode escolher os submenus de Alterar Password, Alterar morada e
 * apagar a sua conta
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuDeveloperDefinicoes(AppStore& mieic);
/**
 * Menu do Developer onde este tem opcoes de gestao de Apps que estao na store. Pode criar uma App, remover uma app
 * ou entrar no menu para alterar uma app
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuDeveloperGerirApps(AppStore& mieic);

/**
 * Menu onde, apos verificacao do Nr. de cartao de credito, o Cliente escolhe o credito a
 * adicionar a sua conta, podendo regressar sem adicionar credito.
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuClienteAddCredito(AppStore& mieic);
/**
 * Menu do Cliente onde sao exibidos os submenus do cesto de compras: Ver cesto/checkout,
 * remover items do cesto e regressao ao menu anterior (menu Cliente)
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuCestoCompras(AppStore& mieic);
/**
 * Menu onde lista as vendas todas existentes do cliente. Ao carregar Esc regressa ao
 * menu de Transacoes
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuHistoricoVendas(AppStore& mieic);
/**
 * Menu onde, apos chamar a confirmacao da Password, o cliente pode alterar a sua password.
 * Regressa depois ao menu de definicoes de cliente.
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuAlterarPassCli(AppStore& mieic);
/**
 * Menu onde, apos chamar a confirmacao da Password, o cliente pode alterar o seu Nr. Cartao de Credito.
 * Regressa depois ao menu de definicoes de cliente.
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuAlterarCartao(AppStore& mieic);
/**
 * Opcao do menu onde, apos confirmacao da pass, o Cliente apaga a conta.
 * Regressa depois ao menu Inicial.
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuApagarContaCli(AppStore& mieic);
/**
 * Opcao do menu de definicoes de developer onde, apos confirmacao da pass, o developer
 * pode escolher alterar a sua pass ou regressar para o menu de definicoes do developer.
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuAlterarPassDev(AppStore& mieic);
/**
 * Menu onde, apos chamar a confirmacao da Password, o developer pode alterar a sua morada
 * Regressa depois ao menu de definicoes do developer
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuAlterarMorada(AppStore& mieic);
/**
 * Menu onde, apos chamar a confirmacao da Password, o developer pode alterar a sua morada
 * Regressa depois ao menu de definicoes do developer
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuAlterarNIF(AppStore& mieic);
/**
 * Opcao do menu onde, apos confirmacao da pass, o Developer apaga a password.
 * Regressa depois ao menu Inicial.
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuApagarContaDev(AppStore& mieic);
/**
 * Menu que faz display dos atributos do developer. Ao carregar Esc regressa ao menu principal
 * do developer
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuVerDev(AppStore& mieic);
/**
 * Menu que faz display dos atributos do cliente. Ao carregar Esc regressa ao menu principal
 * do cliente
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuVerCli(AppStore& mieic);
/**
 * Menu onde o Developer pode criar uma app, introduzindo os dados desta.
 * Regressa depois ao menu de gestao de apps
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuCriarApp(AppStore& mieic);
/**
 * Menu onde o Developer pode escolher uma app da lista das suas apps para remover.
 * Apos confirmacao de password, a app e apagada e o menu faz refresh, mostrando as
 * apps restantes. Se o user carregar enter apaga outra app selecionada, se carregar
 * Esc regressa ao menu de gestao de apps
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuRemoverApp(AppStore& mieic);
/**
 * Menu do Developer onde sao listadas as suas apps. Apos escolher uma app e verificar password,
 * vai ter os submenus/opcoes para mudar nome, mudar preco, mudar categoria e mudar descricao
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuModificarApp(AppStore& mieic);
/**
 * Menu onde sao listadas as apps e o user pode carregar enter para remover a selecionada do cesto.
 * Ao acontecer isto o menu e refreshed. Para sair do menu, o user pode carregar Esc
 * para regressar ao menu do Cesto de Compras
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuTiraAppsCesto(AppStore& mieic);
/**
 * Menu onde sao mostradas as apps do cesto, o seu preco total, o seu preco total se for
 * usado um Voucher e o saldo que o cliente tem disponivel. O cliente pode entao escolher
 * fazer o checkout ou regressar. Ao fazer checkout, se tiver Vouchers, podera fazer uso
 * destes, tendo um desconto.
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuCheckoutApps(AppStore& mieic);
/**
 * Funcao chamada no cesto de compras, que compara as apps do cesto de compras com as existentes.
 * Se entretanto uma app tiver desaparecido do vetor de apps (por exemplo, se um developer tiver apagado uma app,
 *  por exemplo), esta app sera tambem apagada do cesto de compras.
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 * @param cli Pointer para o cliente atual, a cujo cesto de compras se acede
 */
void apagaAppsNaoExistentes(AppStore& mieic,Cliente* cli);
/**
 * Menu que faz display dos tipos de ordenacao possiveis para as apps. Escolhe-se depois o tipo de
 * ordenacao e o menu chama o menuVisitaStoreOrdenada(...) e faz display do vetor das apps todas,
 * da maneira escolhida
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 * @param state Identifica quem visita a store e o que pode ver: 0 se for um guest a visitar, 1 se for um developer e 2 se for um cliente
 */
void menuVisitaStore(AppStore& mieic, unsigned int& state);
/**
 * Menu que pega no vetor de apps da appstore e as exibe com o menu de scroll.
 * Dependendo de quem esta a visitar a store(state), a funcao tera diferentes comportamentos.
 * Se for state= 0 ou 1, ou seja, guest ou developer, estes poderao carregar enter para aceder
 * a informacao de uma app e ler comentarios. Se for state = 2, entao o cliente pode, se nao tiver
 * comprado a app, pode po-la no cesto de compras ou ler comentarios. Se o cliente tiver comprado, pode
 * fazer download, ler comentarios, submeter comentario/classificacao ou regressar.
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 * @param state Identifica quem visita a store e o que pode ver: 0 se for um guest a visitar, 1 se for um developer e 2 se for um cliente
 * @param apps_ordenadas Vetor de apps que vao ser exibidas/listadas
 * @param tipo_ordenacao Tipo de ordenacao - por preco, alfabetica ou por dev+preco ou dev+alfabetica
 */
void menuVisitaStoreOrdenada(AppStore& mieic, unsigned int& state, vector<App> apps_ordenadas, string tipo_ordenacao);
/**
 * Menu que lista os developers existentes, podendo-se escolher o developer e o tipo de listagem.
 * O menu chama depois o menuVisitaStoreOrdenada(...) e faz display do vetor das apps desse
 * developer, ordenadas da maneira escolhida
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 * @param state Identifica quem visita a store e o que pode ver: 0 se for um guest a visitar, 1 se for um developer e 2 se for um cliente
 */
void menuListaDeveloper(AppStore& mieic, unsigned int& state);
/**
 * Menu que faz listagem dos clientes existentes, podendo-se ver o nome, idade e sexo
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuListaCliente(AppStore& mieic);

/**
 * Menu que faz validacao das apps em espera na priority_queue
 * A validacao so e efetuada apos o admin inserir os seus dados
 *
 * @param mieic AppStore criada no main, passada por referencia para poder ser alterada
 */
void menuValidarApps(AppStore& mieic);

#endif /* MENU_H_ */
