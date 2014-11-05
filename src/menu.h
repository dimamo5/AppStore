/*
 * menu.h
 *
 *  Created on: 02/11/2014
 *      Author: Moura
 */

#ifndef MENU_H_
#define MENU_H_

#include "AppStore.h"
#include "Cliente.h"
#include "App.h"

const unsigned int MAX_PER_SCREEN = 6;

extern Developer* dev_act;
extern Cliente* cli_act;

vector<App> getApps(Developer* dev, AppStore mieic);
vector<string> getAppNames(vector<App> apps);
vector<string> getDevNames(vector<Developer*> devs);

void printMenuScroll(vector<string> options, int selected_option, const unsigned int max_per_screen);
void cor(int n);
int teclas();
int RestringeOpcaoTeclas(int min, int max, int opcao);
int menuInicial(AppStore& mieic);
int menuLogin(AppStore& mieic);
int menuRegistar(AppStore& mieic);
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
void menuClienteCredito(AppStore& mieic);
void menuCestoCompras(AppStore& mieic);
void menuHistoricoVendas(AppStore& mieic);
void menuAlterarPass(AppStore& mieic);
void menuAlterarCartao(AppStore& mieic);
void menuApagarConta(AppStore& mieic);

// State will be needed to know who is visiting the store, what that person will see and where the "SAIR" button will lead the person
void menuVisitaStore(AppStore& mieic, unsigned int& state);
void menuVisitaStoreOrdenada(AppStore& mieic, unsigned int& state, vector<App> apps_ordenadas, string tipo_ordenacao);
void menuListaDeveloper(AppStore& mieic, unsigned int& state);

#endif /* MENU_H_ */
