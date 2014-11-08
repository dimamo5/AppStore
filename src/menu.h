/*
 * menu.h
 *
 *  Created on: 02/11/2014
 *      Author: Moura
 */

#ifndef MENU_H_
#define MENU_H_

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

const unsigned int MAX_PER_SCREEN = 6;


#include "AppStore.h"
#include "Cliente.h"
#include "App.h"


class Date;

extern Developer* dev_act;
extern Cliente* cli_act;

void gotoxy(int xpos, int ypos);
void porDataNoCanto(int xpos, int ypos);


vector<string> getAppNames(vector<App> apps);
vector<string> getAppComentarios(vector<Comentario>);
vector<string> getDevNames(vector<Developer*> devs);

template<typename T>
bool verificaPass(T* dev_or_cli);
bool verificaCartao(Cliente* cli);
void printMenuScroll(vector<string> options, int selected_option, const unsigned int max_per_screen);
void cor(int background, int foreground);
int teclas();
int RestringeOpcaoTeclas(int min, int max, int opcao);
void menuInicial(AppStore& mieic);
void menuLogin(AppStore& mieic);
void menuRegistar(AppStore& mieic);
void menuLoginCliente(AppStore& mieic);
void menuLoginDeveloper(AppStore& mieic);
void menuRegistarCliente(AppStore& mieic);
void menuRegistarDeveloperIndividual(AppStore& mieic);
void menuRegistarDeveloperEmpresa(AppStore& mieic);
void menuCliente(AppStore& mieic);
void menuDeveloper(AppStore& mieic);
void menuClienteTransacoes(AppStore& mieic);
void menuClienteDefinicoes(AppStore& mieic);
void menuDeveloperDefinicoes(AppStore& mieic);
void menuDeveloperGerirApps(AppStore& mieic);
void menuDeveloperModApp(AppStore& mieic);
void menuClienteAddCredito(AppStore& mieic);
void menuCestoCompras(AppStore& mieic);
void menuHistoricoVendas(AppStore& mieic);
void menuAlterarPassCli(AppStore& mieic);
void menuAlterarCartao(AppStore& mieic);
void menuApagarContaCli(AppStore& mieic);
void menuAlterarPassDev(AppStore& mieic);
void menuAlterarMorada(AppStore& mieic);
void menuAlterarNIF(AppStore& mieic);
void menuApagarContaDev(AppStore& mieic);
void menuVerDev(AppStore& mieic);
void menuVerCli(AppStore& mieic);
void menuCriarApp(AppStore& mieic);
void menuRemoverApp(AppStore& mieic);
void menuModificarApp(AppStore& mieic);
void menuTiraAppsCesto(AppStore& mieic);
void menuCheckoutApps(AppStore& mieic);
void apagaAppsNaoExistentes(AppStore& mieic,Cliente* cli);


// State will be needed to know who is visiting the store, what that person will see and where the "SAIR" button will lead the person
void menuVisitaStore(AppStore& mieic, unsigned int& state);
void menuVisitaStoreOrdenada(AppStore& mieic, unsigned int& state, vector<App> apps_ordenadas, string tipo_ordenacao);
void menuListaDeveloper(AppStore& mieic, unsigned int& state);

#endif /* MENU_H_ */
