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

extern Developer* dev_act;
extern Cliente* cli_act;

void cor(int n);
int teclas();
int RestringeOpcaoTeclas(int min, int max, int opcao);
int menuInicial(AppStore mieic);
int menuLogin(AppStore mieic);
int menuRegistar(AppStore mieic);
void menuLoginCliente(AppStore mieic);
void menuLoginDeveloper(AppStore mieic);
void menuRegistarCliente(AppStore mieic);
void menuRegistarDeveloperIndividual(AppStore mieic);
void menuRegistarDeveloperEmpresa(AppStore mieic);
void menuCliente(AppStore mieic);
void menuDeveloper(AppStore mieic);
void menuClienteTransacoes(AppStore mieic);
void menuDeveloperGerirApps(AppStore mieic);
void menuDeveloperModApp(AppStore mieic);

// ainda nao implementei a funcao de login nos menus de login

#endif /* MENU_H_ */
