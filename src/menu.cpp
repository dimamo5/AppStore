#include <stdio.h>
#include "menu.h"
#include <tchar.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;

void cor(int n)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, n);
}

int teclas()
{
	int tecla;
	tecla = getch();
	if(tecla!=0)
	{
		while(tecla!=13)//ENQUANTO DIFERENTE DE ENTER
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
	}
}

//FUNCAO RESPONSAVEL POR RESTRINGIR A VARIAVEL "opcao" APENAS ÁS OPÇÕES DO MENU
int RestringeOpcaoTeclas(int min, int max, int opcao)
{
	if(opcao>min && opcao <((max*-1)+13))
		return opcao=(-1*max); //reinicia a variavel na ultima opcao do menu
	else if(opcao<(max*-1) || opcao>(min+13)) //Situação em que Sai fora da gama de opções possiveis (valor > que nº de opcoes possiveis)
		return opcao=min; //reinicia a variavel na 1a opção do menu
	else
		return opcao; //se não se verificam as restrições, entao devolve-se novamente a variavel intacta
}


int menu()
{
	system("cls");
	int opcao=0;
	for(;;)
	{
		system("cls");
		cout<< "  INTRODUZIR NOVA VIATURA  "<<endl<<endl;

		if(opcao==0) cor(112);
		cout<< "  Ligeiro"<<endl; cor(7);
		if(opcao==-1) cor(112);
		cout<< "  Motocilo"<<endl; cor(7);
		if(opcao==-2) cor(112);
		cout<< "  Pesado"<<endl; cor(7);
		if(opcao==-3) cor(124);
		cout<< "  SAIR"<<endl; cor(7);

		opcao+=teclas();
		opcao = RestringeOpcaoTeclas(0,3,opcao);//MUDAR  de 3 para o numero total de opções do menu.

		switch(opcao-13)//sempre que se adicionar mais opções, adicionar mais um case (ex: case -4: return 0; break;)
		{
			case 0: return 1; break;
			case -1: return 2; break;
			case -2: return 3; break;
			case -3: return 0; break;
		}
	}
}


void ProcessarOpcaoMenu(int op) //a função tem de conhecer quem é a lista de viaturas
{
	switch (op)
	 {
		case 1:
			cout<<"OPCAO 1";
			system("pause");
			break;
		case 2:
			cout<<"OPCAO 2";
			system("pause");
			break;
		case 3:
			cout<<"OPCAO 3";
			system("pause");
			break;
		case 4:
			cout<<"OPCAO 4";
			system("pause");
			break;
	}
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
