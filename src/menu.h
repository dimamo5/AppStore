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

void cor(int n);
int teclas();
int RestringeOpcaoTeclas(int min, int max, int opcao);
int menuInicial(AppStore mieic);
int menuLogin(AppStore mieic);
int menuRegistar(AppStore mieic);
int menuLoginCliente(AppStore mieic);
int menuLoginDeveloper(AppStore mieic);
int menuRegistarCliente(AppStore mieic);
int menuRegistarDeveloper(AppStore mieic);


#endif /* MENU_H_ */
