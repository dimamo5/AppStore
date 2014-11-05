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
void menuVisitaStore(AppStore& mieic);
void menuVisitaAlfabetica(AppStore& mieic);
void menuVisitaPreco(AppStore& mieic);
void menuVisitaDeveloper(AppStore& mieic);


#endif /* MENU_H_ */
