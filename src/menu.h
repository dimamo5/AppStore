/*
 * menu.h
 *
 *  Created on: 02/11/2014
 *      Author: Moura
 */

#ifndef MENU_H_
#define MENU_H_

void cor(int n);
int teclas();
int RestringeOpcaoTeclas(int min, int max, int opcao);
int menuInicial();
int menuLogin();
int menuLoginCliente();
int menuLoginDeveloper();
int menuRegistarCliente();
int menuRegistarDeveloper();


#endif /* MENU_H_ */
