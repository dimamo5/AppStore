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
int menu();
void ProcessarOpcaoMenu(int op);


#endif /* MENU_H_ */
