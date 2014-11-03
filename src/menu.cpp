#include <stdio.h>
#include "menu.h"
#include <tchar.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;

void cor(int n) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, n);
}

int teclas() {
	int tecla;
	tecla = getch();
	if (tecla != 0) {
		while (tecla != 13) //ENQUANTO DIFERENTE DE ENTER
		{
			tecla = getch();
			if (tecla == 72) //ACIMA
				return 1;
			if (tecla == 80) //ABAIXO
				return -1;
			if (tecla == 75) //ESQUERDA
				return -2;
			if (tecla == 77) //DIREITA
				return 2;
		}
		return 13;
	}
}

//FUNCAO RESPONSAVEL POR RESTRINGIR A VARIAVEL "opcao" APENAS ÁS OPÇÕES DO MENU
int RestringeOpcaoTeclas(int min, int max, int opcao) {
	if (opcao > min && opcao < ((max * -1) + 13))
		return opcao = (-1 * max); //reinicia a variavel na ultima opcao do menu
	else if (opcao < (max * -1) || opcao > (min + 13)) //Situação em que Sai fora da gama de opções possiveis (valor > que nº de opcoes possiveis)
		return opcao = min; //reinicia a variavel na 1a opção do menu
	else
		return opcao; //se não se verificam as restrições, entao devolve-se novamente a variavel intacta
}

int menuInicial(AppStore mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);  //TODO: criar funcao para imprimir data
	int opcao = 0;
	for (;;) {
		system("cls");
		cout << "  Welcome to MIEICPlay  " << endl << endl;

		if (opcao == 0) cor(112);
		cout << "  Visitar AppStore  " << endl; cor(7);
		if (opcao == -1) cor(112);
		cout << "  Login na AppStore  " << endl; cor(7);
		if (opcao == -2) cor(112);
		cout << "  Registar na AppStore  " << endl; cor(7);
		if (opcao == -3) cor(124);
		cout << "  SAIR  " << endl; cor(7);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 3, opcao); //MUDAR  de 3 para o numero total de opções-1 do menu.

		switch (opcao - 13) //sempre que se adicionar mais opções, adicionar mais um case (ex: case -4: return 0; break;)
		{
		case 0:
			cout << "Finge que esta aqui a AppStore, pliz";
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;

		case -1:         // 2a opcao
			cout << "Fazer login";
			menuLogin(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -2:        // 3a opcao
			cout << "Fazer registo";
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -3:        // ultima opcao
			return 0; // indica ao menu que o programa vai fechar
			break;
		}
	}
}

int menuLogin(AppStore mieic) {
	system("cls");
	time_t t = time(0);
		struct tm *now = localtime(&t);
		Date data_atual(tm);
	int opcao = 0;
	for (;;) {
		system("cls");
		cout << "  Faca Login: escolha o seu tipo de conta  " << endl << endl;

		if (opcao == 0) cor(112);
		cout << "  Cliente  " << endl; cor(7);
		if (opcao == -1) cor(112);
		cout << "  Developer " << endl; cor(7);
		if (opcao == -2) cor(124);
		cout << "  SAIR  " << endl; cor(7);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 2, opcao);

		switch (opcao - 13) //sempre que se adicionar mais opções, adicionar mais um case (ex: case -4: return 0; break;)
		{
		case 0:
			cout << "Esta a fazer login cliente";
			menuLoginCliente(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;

		case -1:         // 2a opcao
			cout << "Esta a fazer login developer";
			menuLoginDeveloper(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -2:        // 3a opcao
			menuInicial(mieic);
			system("pause");
			return 0; // indica ao menu que ainda vai continuar o programa
			break;

		}
	}
}

int menuRegistar(AppStore mieic) {
	system("cls");
	time_t t = time(0);
		struct tm *now = localtime(&t);
		Date data_atual(tm);
	int opcao = 0;
	for (;;) {
		system("cls");
		cout << "  Faca o registo: escolha o seu tipo de conta  " << endl << endl;

		if (opcao == 0) cor(112);
		cout << "  Cliente  " << endl; cor(7);
		if (opcao == -1) cor(112);
		cout << "  Developer " << endl; cor(7);
		if (opcao == -2) cor(124);
		cout << "  SAIR  " << endl; cor(7);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 2, opcao);

		switch (opcao - 13) //sempre que se adicionar mais opções, adicionar mais um case (ex: case -4: return 0; break;)
		{
		case 0:
			cout << "Esta a fazer registo cliente";
			menuRegistarCliente(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;

		case -1:         // 2a opcao
			cout << "Esta a fazer registo developer";
			menuRegistarDeveloper(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -2:        // 3a opcao
			menuInicial(mieic);
			system("pause");
			return 0; // indica ao menu que ainda vai continuar o programa
			break;

		}
	}
}

int menuLoginCliente(AppStore mieic){
	system("cls");
	time_t t = time(0);
		struct tm *now = localtime(&t);
		Date data_atual(tm);

	string nome;
	unsigned int idade;
	string sexo;
	int cartao_credito;
	cout << "  Insira os seus dados de cliente  " << endl << endl << endl;

	cout << "  Indique o seu nome: "; cin >> nome; cout << endl;
	cout << "  Indique a sua idade: "; cin >> idade; cout << endl;
	cout << "  Indique o seu sexo (M ou F): "; cin >> sexo; cout << endl;
	cout << "  Indique o seu no. cartao credito: "; cin >> cartao_credito; cout << endl;

}

int menuLoginDeveloper(AppStore mieic){
	system("cls");
	time_t t = time(0);
		struct tm *now = localtime(&t);
		Date data_atual(tm);
}

int menuRegistarCliente(AppStore mieic){
	system("cls");
	time_t t = time(0);
		struct tm *now = localtime(&t);
		Date data_atual(tm);
}


int menuRegistarDeveloper(AppStore mieic){
	system("cls");
	time_t t = time(0);
		struct tm *now = localtime(&t);
		Date data_atual(tm);
}






/*void main()
 {
 int opc=0;
 do
 {
 opc=menu();
 ProcessarOpcaoMenu(opc);
 } while (opc);
 }*/
