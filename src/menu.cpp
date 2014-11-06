#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "menu.h"

using namespace std;

vector<App> getApps(Developer* dev, AppStore mieic) {
	vector<App> apps_do_developer;
	vector<App> apps_da_store = mieic.apps;

	for (unsigned int i = 0; i < apps_da_store.size(); i++) { // percorre as apps da store

		// sempre que ha uma app cujo dev coincide, tendo em conta que todos teem nomes diferentes
		if (dev->getNome() == apps_da_store[i].getDev()->getNome()) {
			apps_do_developer.push_back(apps_da_store[i]);
		}
	}
	return apps_do_developer;
}

vector<string> getAppNames(vector<App> apps) {
	vector<string> app_names;
	for (unsigned int i = 0; i < apps.size(); i++) {
		app_names.push_back(apps[i].getNome());
	}
	return app_names;
}

vector<string> getDevNames(vector<Developer*> devs) {
	vector<string> dev_names;
	for (unsigned int i = 0; i < devs.size(); i++) {
		dev_names.push_back(devs[i]->getNome());
	}
	return dev_names;
}

void printMenuScroll(vector<string> options, int selected_option,
		const unsigned int max_per_screen) {
	int min = selected_option - (max_per_screen / 2);
	unsigned int max = selected_option + ((max_per_screen + 1) / 2);

	if (max < max_per_screen)
		max = max_per_screen;

	if (max > options.size())
		max = options.size();

	unsigned int range = max - min;

	if (range < max_per_screen)
		min = options.size() - max_per_screen;

	if (min < 0)
		min = 0;

	string temp;

	for (unsigned int i = min; i < max; i++) {
		if (i == selected_option) {
			cor(WHITE, BLACK);
			temp = "  " + options[i];
			cout << temp;
			cout << endl << endl;
			cor(BLACK, WHITE);  // reset a cor
		} else {
			temp = "  " + options[i];
			cout << temp;
			cout << endl << endl;
		}

	}
}

// First 4 bits are background, last 4 bits are foreground
void cor(int background, int foreground) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, foreground + 16 * background);
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
				return 2;
			if (tecla == 77) //DIREITA
				return -2;
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

int menuInicial(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);
	dev_act = NULL; // da reset aos indicadores de login atual, ou seja, faz logout
	cli_act = NULL;
	unsigned int state = 0; //state 0 is guest
	int opcao = 0;
	for (;;) {
		system("cls");
		cout << "  Bem-vindo a AppStore MIEICPlay  " << endl << endl;

		if (opcao == 0)
			cor(WHITE, BLACK);
		cout << "  Visitar AppStore  " << endl;
		cor(BLACK, WHITE); // apos imprimir com a cor anterior, da reset à cor para o normal
		if (opcao == -1)
			cor(WHITE, BLACK);
		cout << "  Login na AppStore  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -2)
			cor(WHITE, BLACK);
		cout << "  Registar na AppStore  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -3)
			cor(WHITE, LIGHT_RED);
		cout << "  SAIR  " << endl;
		cor(BLACK, WHITE);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 3, opcao); //MUDAR  de 3 para o numero total de opções-1 do menu.

		switch (opcao - 13) //sempre que se adicionar mais opções, adicionar mais um case (ex: case -4: return 0; break;)
		{
		case 0:
			menuVisitaStore(mieic, state);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -1: // 2a opcao
			menuLogin(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -2: // 3a opcao
			menuRegistar(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -3: // ultima opcao
			// E NECESSARIO CHAMAR OS SAVES DE FICHEIROS AQUI!!!!!!!!
			exit(0);
			return 0;			// indica ao menu que o programa vai fechar
			break;
		}
	}
}
int menuLogin(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);
	int opcao = 0;
	for (;;) {
		system("cls");
		cout << "  Faca Login: escolha o seu tipo de conta  " << endl << endl;

		if (opcao == 0)
			cor(WHITE, BLACK);
		cout << "  Cliente  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -1)
			cor(WHITE, BLACK);
		cout << "  Developer " << endl;
		cor(BLACK, WHITE);
		if (opcao == -2)
			cor(WHITE, LIGHT_RED);
		cout << "  SAIR  " << endl;
		cor(BLACK, WHITE);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 2, opcao);

		switch (opcao - 13) //sempre que se adicionar mais opções, adicionar mais um case (ex: case -4: return 0; break;)
		{
		case 0:
			menuLoginCliente(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;

		case -1: // 2a opcao
			menuLoginDeveloper(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -2: // 3a opcao
			menuInicial(mieic);
			system("pause");
			return 0; // indica ao menu que ainda vai continuar o programa
			break;

		}
	}
}
int menuRegistar(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);
	int opcao = 0;
	for (;;) {
		system("cls");
		cout << "  Faca o registo: escolha o seu tipo de conta  " << endl
				<< endl;

		if (opcao == 0)
			cor(WHITE, BLACK);
		cout << "  Cliente  " << endl;
		cor(BLACK, WHITE);

		if (opcao == -1)
			cor(WHITE, BLACK);
		cout << "  Developer Individual  " << endl;
		cor(BLACK, WHITE);

		if (opcao == -2)
			cor(WHITE, BLACK);
		cout << "  Developer Empresa  " << endl;
		cor(BLACK, WHITE);

		if (opcao == -3)
			cor(WHITE, LIGHT_RED);
		cout << "  SAIR  " << endl;
		cor(BLACK, WHITE);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 3, opcao);

		switch (opcao - 13) //sempre que se adicionar mais opções, adicionar mais um case (ex: case -4: return 0; break;)
		{
		case 0:
			menuRegistarCliente(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;

		case -1: // 2a opcao
			menuRegistarDeveloperIndividual(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -2: // 2a opcao
			menuRegistarDeveloperEmpresa(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -3: // 3a opcao
			menuInicial(mieic);
			system("pause");
			return 0; // indica ao menu que ainda vai continuar o programa
			break;

		}
	}
}
void menuLoginCliente(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);

	bool loginCliente = false; // valor default = false
	bool inputFail;
	unsigned int id;
	string password;

	do {
		system("cls");
		cout << "  Insira os seus dados para login de cliente  " << endl << endl
				<< endl;
		cout << "  Introduza o seu ID de login:  ";
		cin >> id;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	do {
		system("cls");
		cout << "  Insira os seus dados para login de cliente  " << endl << endl
				<< endl;
		cout << "  Introduza o seu ID de login:  " << id << endl;
		cout << "  Introduza agora a sua password:  ";

		cin >> password;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	system("cls");
	cout << "  Insira os seus dados para login de cliente  " << endl << endl
			<< endl;
	cout << "  Introduza o seu ID de login:  " << id << endl;
	cout << "  Introduza agora a sua password:  " << password << endl << endl
			<< endl;

	cout
			<< "  Prima (Enter) para validar ou (Esc) para regressar sem tentar efetuar login  "
			<< endl << endl;

	cin.clear();

	int tecla;
	tecla = getch();
	if (tecla != 0) {
		while (tecla != 13 && tecla != 27) {
			tecla = getch();
		}
	}
	if (tecla == 13) { // se o user premir (Enter) tenta fazer login

		// verifica se existe a combinacao id/pass na appstore do mieic
		loginCliente = mieic.verificaLoginCliente(id, password);

		if (loginCliente) { // da ecra de login e prime enter para continuar
			cout << "  Sucesso! Login efetuado! " << endl << endl;
			cout << "  Prima (Enter) para continuar  " << endl;

			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13) { // enquanto nao prime enter para continuar
					tecla = getch();
				}

				// usa o ID de login para devolver um pointer para o cliente atual
				// cli_act e a variavel global do cliente currently logged in
				cli_act = mieic.find_cliente_id(id);
				menuCliente(mieic);			// continua para o menu de Cliente
			}
		} else if (!loginCliente) {
			cout << "  Acesso negado! Combinacao ID/Password errada " << endl
					<< endl;
			cout
					<< "  Prima (Enter) para tentar novamente ou (Esc) para regressar  "
					<< endl;

			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13 && tecla != 27) { // enquanto nao prime enter para continuar
					tecla = getch();
				}
			}
			if (tecla == 13)
				menuLoginCliente(mieic); // retry o login
			else if (tecla == 27)
				menuInicial(mieic); // desistir do login
		}

	} else if (tecla == 27) {  // se o user premir (Esc) logo, sai para tras
		menuInicial(mieic);
	}

}
void menuLoginDeveloper(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);

	bool loginDeveloper; // valor default = false
	bool inputFail;
	unsigned int id;
	string password;

	do {
		system("cls");
		cout << "  Insira os seus dados para login de developer  " << endl
				<< endl << endl;
		cout << "  Introduza o seu ID de login:  ";
		cin >> id;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	do {
		system("cls");
		cout << "  Insira os seus dados para login de developer  " << endl
				<< endl << endl;
		cout << "  Introduza o seu ID de login:  " << id << endl;
		cout << "  Introduza agora a sua password:  ";

		cin >> password;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	system("cls");
	cout << "  Insira os seus dados para login de developer  " << endl << endl
			<< endl;
	cout << "  Introduza o seu ID de login:  " << id << endl;
	cout << "  Introduza agora a sua password:  " << password << endl << endl
			<< endl;

	cout
			<< "  Prima (Enter) para validar ou (Esc) para regressar sem tentar efetuar login  "
			<< endl << endl;

	cin.clear();

	int tecla;
	tecla = getch();
	if (tecla != 0) {
		while (tecla != 13 && tecla != 27) {
			tecla = getch();
		}
	}
	if (tecla == 13) { // se o user premir (Enter) tenta fazer login

		// verifica se existe a combinacao id/pass na appstore do mieic
		loginDeveloper = mieic.verificaLoginDev(id, password);

		if (loginDeveloper) { // da ecra de login e prime enter para continuar
			cout << "  Sucesso! Login efetuado! " << endl << endl;
			cout << "  Prima (Enter) para continuar  " << endl;

			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13) { // enquanto nao prime enter para continuar
					tecla = getch();
				}
				// usa o ID de login para devolver um pointer para o cliente atual
				// cli_act e a variavel global do cliente currently logged in
				dev_act = mieic.find_dev_id(id);
				menuDeveloper(mieic);				// segue para o menu de Dev
			}
		} else if (!loginDeveloper) {
			cout << "  Acesso negado! Combinacao ID/Password errada " << endl
					<< endl;
			cout
					<< "  Prima (Enter) para tentar novamente ou (Esc) para regressar  "
					<< endl;

			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13 && tecla != 27) { // enquanto nao prime enter para continuar
					tecla = getch();
				}
			}
			if (tecla == 13)
				menuLoginDeveloper(mieic); // retry o login
			else if (tecla == 27)
				menuInicial(mieic); // desistir do login
		}

	} else if (tecla == 27) {  // se o user premir (Esc) logo, sai para tras
		menuInicial(mieic);
	}

}
void menuRegistarCliente(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);

	// imprimeData(data_atual); fazer funcao para imprimir data

	bool inputFail;
	string nome, sexo, password;
	unsigned int idade;
	int cartao_credito;

	cout << "  Insira os seus dados para registo de cliente  " << endl << endl
			<< endl;

	cout << "  Indique o seu nome: ";
	fflush(stdin);
	cin >> nome;
	cout << endl;

	do {
		system("cls");
		cout << "  Insira os seus dados para registo de cliente  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome: " << nome << endl;
		cout << "  Indique a sua idade: ";
		cin >> idade;
		inputFail = cin.fail(); // guarda a flag do fail
		cin.clear(); // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	do {
		system("cls");
		cout << "  Insira os seus dados para registo de cliente  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome: " << nome << endl;
		cout << "  Indique a sua idade: " << idade << endl;
		cout << "  Indique o seu sexo (M ou F): ";
		cin >> sexo;

		inputFail = cin.fail();
		if (sexo == "M" || sexo == "F") { // se o user nao puser uma destas opcoes, falha
			inputFail = false;
		} else
			inputFail = true;
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	do {
		system("cls");
		cout << "  Insira os seus dados para registo de cliente  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome: " << nome << endl;
		cout << "  Indique a sua idade: " << idade << endl;
		cout << "  Indique o seu sexo (M ou F): " << sexo << endl;
		cout << "  Indique o seu no. cartao credito: ";
		cin >> cartao_credito;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);
	do {
		system("cls");
		cout << "  Insira os seus dados para registo de cliente  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome: " << nome << endl;
		cout << "  Indique a sua idade: " << idade << endl;
		cout << "  Indique o seu sexo (M ou F): " << sexo << endl;
		cout << "  Indique o seu no. cartao credito: " << cartao_credito << endl
				<< endl;
		cout << "  Introduza agora a password que pretende:  ";

		cin >> password;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	system("cls");
	cout << "  Insira os seus dados para registo de cliente  " << endl << endl
			<< endl;
	cout << "  Indique o seu nome: " << nome << endl;
	cout << "  Indique a sua idade: " << idade << endl;
	cout << "  Indique o seu sexo (M ou F): " << sexo << endl;
	cout << "  Indique o seu no. cartao credito: " << cartao_credito << endl
			<< endl;
	cout << "  Introduza agora a password que pretende:  " << password << endl
			<< endl << endl;

	cout
			<< "  Prima (Enter) para validar ou (Esc) para regressar sem registar  "
			<< endl << endl;

	cin.clear();

	int tecla;
	tecla = getch();
	if (tecla != 0) {
		while (tecla != 13 && tecla != 27) {
			tecla = getch();
		}
	}
	if (tecla == 13) { // se o user premir (Enter)
		Cliente cli_temp(nome, idade, sexo, cartao_credito, password);
		mieic.clientes.push_back(cli_temp);

		cout << "  Sucesso! O seu ID de login e " << cli_temp.getId() << endl
				<< endl;
		cout << "  Prima enter para continuar  " << endl;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13) { // enquanto nao prime enter para continuar
				tecla = getch();
			}
			menuInicial(mieic);
		}

	} else if (tecla == 27) {  // se o user premir (Esc)
		menuRegistar(mieic);
	}

}
void menuRegistarDeveloperIndividual(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);

	// imprimeData(data_atual); fazer funcao para imprimir data

	bool nomeRepetido = false;
	bool inputFail;
	string nome_dev, password, morada;
	string nome_pessoal;

	do {
		system("cls");
		cout << "  Insira os seus dados para registo de developer  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome pessoal: ";
		fflush(stdin);
		getline(cin, nome_pessoal);
	} while (nome_pessoal == "");

	do {
		system("cls");
		cout << "  Insira os seus dados para registo de developer  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome pessoal: " << nome_pessoal << endl;
		cout << "  Indique o seu nome de developer: ";

		fflush(stdin);
		getline(cin, nome_dev);
	} while (nome_dev == "");

	do {
		system("cls");
		cout << "  Insira os seus dados para registo de developer  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome pessoal: " << nome_pessoal << endl;
		cout << "  Indique o seu nome de developer: " << nome_dev << endl;
		cout << "  Indique a sua morada: ";
		fflush(stdin);
		getline(cin, morada);
	} while (morada == "");

	do {
		system("cls");
		cout << "  Insira os seus dados para registo de developer  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome pessoal: " << nome_pessoal << endl;
		cout << "  Indique o seu nome de developer: " << nome_dev << endl;
		cout << "  Indique a sua morada: " << morada << endl;
		cout << "  Introduza agora a password que pretende:  ";

		cin >> password;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	system("cls");
	cout << "  Insira os seus dados para registo de developer  " << endl << endl
			<< endl;
	cout << "  Indique o seu nome pessoal: " << nome_pessoal << endl;
	cout << "  Indique o seu nome de developer: " << nome_dev << endl;
	cout << "  Indique a sua morada: " << morada << endl;
	cout << "  Introduza agora a password que pretende:  " << password; //TODO: por astericos na pass
	cout << endl << endl << endl;
	cout
			<< "  Prima (Enter) para validar ou (Esc) para regressar sem registar  "
			<< endl << endl;

	cin.clear();

	int tecla;
	tecla = getch();
	if (tecla != 0) {
		while (tecla != 13 && tecla != 27) {
			tecla = getch();
		}
	}
	if (tecla == 13) { // se o user premir (Enter)

		// verifica se na appstore mieic ja ha algum developer com este nome de dev
		nomeRepetido = mieic.existeNomeDev(nome_dev);

		if (!nomeRepetido) { // se nome nao for repetido, sucesso!

			Developer* individ_temp = new Individual(nome_dev, password, morada,
					nome_pessoal);
			mieic.dev.push_back(individ_temp);

			cout << "  Sucesso! O seu ID de login e " << individ_temp->getId()
					<< endl << endl;
			cout << "  Prima (Enter) para continuar  " << endl;
			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13) { // enquanto nao prime enter para continuar
					tecla = getch();
				}
				menuInicial(mieic);
			}
		} else if (nomeRepetido) { // se o nome for repetido, retry ou regressa
			cout
					<< "  Registo invalido! Um developer com esse nome de developer ja existe. "
					<< endl << endl;
			cout
					<< "  Prima (Enter) para tentar novamente ou (Esc) para regressar  "
					<< endl;

			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13 && tecla != 27) { // enquanto nao prime enter para continuar
					tecla = getch();
				}
			}
			if (tecla == 13)
				menuRegistarDeveloperIndividual(mieic);
			else if (tecla == 27)
				menuRegistar(mieic);
		}

	} else if (tecla == 27) {  // se o user premir (Esc)
		menuRegistar(mieic);
	}

}
void menuRegistarDeveloperEmpresa(AppStore& mieic) {

	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);

	// imprimeData(data_atual); fazer funcao para imprimir data

	bool nomeRepetido = false;
	bool inputFail;
	string nome_dev, password, morada;
	string NIF, nome_oficial;

	do {
		system("cls");
		cout << "  Insira os dados para registo da empresa  " << endl << endl
				<< endl;
		cout << "  Indique o nome oficial da empresa: ";
		fflush(stdin);
		getline(cin, nome_oficial);

	} while (nome_oficial == "");

	do {
		system("cls");
		cout << "  Insira os dados para registo da empresa  " << endl << endl
				<< endl;
		cout << "  Indique o nome oficial da empresa: " << nome_oficial << endl;
		cout << "  Indique o nome de developer da empresa: ";
		fflush(stdin);
		getline(cin, nome_dev);

	} while (nome_dev == "");

	do {
		system("cls");
		cout << "  Insira os dados para registo da empresa  " << endl << endl
				<< endl;
		cout << "  Indique o nome oficial da empresa: " << nome_oficial << endl;
		cout << "  Indique o nome de developer da empresa: " << nome_dev
				<< endl;
		cout << "  Indique o NIF da empresa: ";
		cin >> NIF;

		inputFail = cin.fail();

		for (unsigned int i = 0; i < NIF.size(); i++) { //verifica se NIF so tem numeros
			if (!isdigit(NIF[i])) {
				inputFail = true;
			}
		}

		cin.clear();
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	do {
		system("cls");
		cout << "  Insira os dados para registo da empresa  " << endl << endl
				<< endl;
		cout << "  Indique o nome oficial da empresa: " << nome_oficial << endl;
		cout << "  Indique o nome de developer da empresa: " << nome_dev
				<< endl;
		cout << "  Indique o NIF da empresa: " << NIF << endl;
		cout << "  Indique a morada da empresa  ";

		fflush(stdin);
		getline(cin, morada);

	} while (morada == "");

	do {
		system("cls");
		cout << "  Insira os dados para registo da empresa  " << endl << endl
				<< endl;
		cout << "  Indique o nome oficial da empresa: " << nome_oficial << endl;
		cout << "  Indique o nome de developer da empresa: " << nome_dev
				<< endl;
		cout << "  Indique o NIF da empresa: " << NIF << endl;
		cout << "  Indique a morada da empresa  " << morada << endl;
		cout << "  Introduza agora a password que pretende:  ";

		cin >> password;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	system("cls");
	cout << "  Insira os dados para registo da empresa  " << endl << endl
			<< endl;
	cout << "  Indique o nome oficial da empresa: " << nome_oficial << endl;
	cout << "  Indique o nome de developer da empresa: " << nome_dev << endl;
	cout << "  Indique o NIF da empresa: " << NIF << endl;
	cout << "  Indique a morada da empresa  " << morada << endl;
	cout << "  Introduza agora a password que pretende:  " << password; //TODO: por astericos na pass
	cout << endl << endl << endl;
	cout
			<< "  Prima (Enter) para validar ou (Esc) para regressar sem registar  "
			<< endl << endl;

	cin.clear();

	int tecla;
	tecla = getch();
	if (tecla != 0) {
		while (tecla != 13 && tecla != 27) {
			tecla = getch();
		}
	}
	if (tecla == 13) { // se o user premir (Enter)

		// se alguma das 2 condicoes for verdadeira, significa que o nome e repetido
		nomeRepetido = (mieic.existeNomeDev(nome_dev)
				|| mieic.existeNomeDev(nome_oficial));

		if (!nomeRepetido) { // se nome nao for repetido, sucesso!

			Developer* empresa_temp = new Empresa(nome_dev, password, NIF,
					morada, nome_oficial);
			mieic.dev.push_back(empresa_temp);

			cout << "  Sucesso! O seu ID de login e " << empresa_temp->getId()
					<< endl << endl;
			cout << "  Prima (Enter) para continuar  " << endl;
			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13) { // enquanto nao prime enter para continuar
					tecla = getch();
				}
				menuInicial(mieic);
			}
		} else if (nomeRepetido) { // se o nome for repetido, retry ou regressa
			cout << "  Registo invalido! Um developer com esse nome ja existe. "
					<< endl << endl;
			cout
					<< "  Prima (Enter) para tentar novamente ou (Esc) para regressar  "
					<< endl;

			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13 && tecla != 27) { // enquanto nao prime enter para continuar
					tecla = getch();
				}
			}
			if (tecla == 13)
				menuRegistarDeveloperEmpresa(mieic);
			else if (tecla == 27)
				menuRegistar(mieic);
		}

	} else if (tecla == 27) {  // se o user premir (Esc)
		menuRegistar(mieic);
	}

}
void menuCliente(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);
	unsigned int state = 2; //state 2 is the client
	int opcao = 0;

	for (;;) {
		system("cls");
		cout << "  Menu Cliente  " << endl << endl;

		if (opcao == 0)
			cor(WHITE, BLACK);
		cout << "  Entrar na AppStore  " << endl; // fazer listagem por apps compradas
		cor(BLACK, WHITE);
		if (opcao == -1)
			cor(WHITE, BLACK);
		cout << "  Transacoes e Credito " << endl;
		cor(BLACK, WHITE);
		if (opcao == -2)
			cor(WHITE, BLACK);
		cout << "  Definicoes da Conta  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -3)
			cor(WHITE, BLACK);
		cout << "  Visualisar Atributos de Cliente  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -4)
			cor(WHITE, LIGHT_RED);
		cout << "  LOGOUT  " << endl;
		cor(BLACK, WHITE);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 4, opcao);

		switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
		{
		case 0:          // 1a opcao
			menuVisitaStore(mieic, state); // TODO: implementar a listagem de apps
			system("pause");
			break;

		case -1:          // 2a opcao
			menuClienteTransacoes(mieic);
			system("pause");
			break;
		case -2:          // 3a opcao
			menuClienteDefinicoes(mieic);
			system("pause");
			break;
		case -3:          // 4a opcao
			menuVerCli(mieic); // TODO: implementar a listagem atributos do cliente
			system("pause");
			break;
		case -4:          // 5a opcao
			menuInicial(mieic);
			system("pause");
			break;

		}
	}
}
void menuDeveloper(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);
	unsigned int state = 1; // state = 1 is developer
	int opcao = 0;

	for (;;) {
		system("cls");
		cout << "  Menu Developer  " << endl << endl;

		if (opcao == 0)
			cor(WHITE, BLACK);
		cout << "  Visitar AppStore  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -1)
			cor(WHITE, BLACK);
		cout << "  Gerir Apps " << endl;
		cor(BLACK, WHITE);
		if (opcao == -2)
			cor(WHITE, BLACK);
		cout << "  Definicoes da Conta  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -3)
			cor(WHITE, BLACK);
		cout << "  Visualisar Atributos de Developer  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -4)
			cor(WHITE, LIGHT_RED);
		cout << "  LOGOUT  " << endl;
		cor(BLACK, WHITE);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 4, opcao);

		switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
		{
		case 0:          // 1a opcao
			menuVisitaStore(mieic, state);
			system("pause");
			break;

		case -1:          // 2a opcao
			menuDeveloperGerirApps(mieic);
			system("pause");
			break;
		case -2:          // 3a opcao
			menuDeveloperDefinicoes(mieic);
			system("pause");
			break;
		case -3:          // 4a opcao
			menuVerDev(mieic); // TODO: implementar a listagem atributos do developer
			system("pause");
			break;
		case -4:          // 5a opcao
			menuInicial(mieic);
			system("pause");
			break;

		}
	}
}

void menuClienteTransacoes(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);
	int opcao = 0;

	for (;;) {
		system("cls");
		cout << "  Transacoes e Credito do Cliente  " << endl << endl;

		if (opcao == 0)
			cor(WHITE, BLACK);
		cout << "  Adicionar Credito  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -1)
			cor(WHITE, BLACK);
		cout << "  Cesto de Compras " << endl;
		cor(BLACK, WHITE);
		if (opcao == -2)
			cor(WHITE, BLACK);
		cout << "  Historico de Vendas  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -3)
			cor(WHITE, LIGHT_RED);
		cout << "  SAIR  " << endl;
		cor(BLACK, WHITE);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 3, opcao);

		switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
		{
		case 0:          // 1a opcao
			menuClienteCredito(mieic);
			system("pause");
			break;

		case -1:          // 2a opcao
			menuCestoCompras(mieic);
			system("pause");
			break;
		case -2:          // 3a opcao
			menuHistoricoVendas(mieic);
			system("pause");
			break;
		case -3:          // 4a opcao
			menuCliente(mieic);
			system("pause");
			break;

		}
	}
}

void menuClienteDefinicoes(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);
	int opcao = 0;

	for (;;) {
		system("cls");
		cout << "  Definicoes de Cliente  " << endl << endl;

		if (opcao == 0)
			cor(WHITE, BLACK);
		cout << "  Alterar Password  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -1)
			cor(WHITE, BLACK);
		cout << "  Alterar Nr. de Cartao de Credito " << endl;
		cor(BLACK, WHITE);
		if (opcao == -2)
			cor(WHITE, BLACK);
		cout << "  Apagar Conta  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -3)
			cor(WHITE, LIGHT_RED);
		cout << "  SAIR  " << endl;
		cor(BLACK, WHITE);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 3, opcao);

		switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
		{
		case 0:          // 1a opcao
			menuAlterarPassCli(mieic);
			system("pause");
			break;

		case -1:          // 2a opcao
			menuAlterarCartao(mieic);
			system("pause");
			break;
		case -2:          // 3a opcao
			menuApagarContaCli(mieic);
			system("pause");
			break;
		case -3:          // 4a opcao
			menuCliente(mieic);          //
			system("pause");
			break;
		}
	}
}

void menuDeveloperGerirApps(AppStore& mieic) {

}

void menuDeveloperDefinicoes(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);
	int opcao = 0;

	if (dev_act->isEmpresa()) {
		for (;;) {
			system("cls");
			cout << "  Definicoes de Developer Empresarial " << endl << endl;

			if (opcao == 0)
				cor(WHITE, BLACK);
			cout << "  Alterar Password  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -1)
				cor(WHITE, BLACK);
			cout << "  Alterar Morada " << endl;
			cor(BLACK, WHITE);
			if (opcao == -2)
				cor(WHITE, BLACK);
			cout << "  Alterar NIF  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -3)
				cor(WHITE, BLACK);
			cout << "  Apagar Conta  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -4)
				cor(WHITE, LIGHT_RED);
			cout << "  SAIR  " << endl;
			cor(BLACK, WHITE);

			opcao += teclas();
			opcao = RestringeOpcaoTeclas(0, 4, opcao);

			switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
			{
			case 0:          // 1a opcao
				menuAlterarPassDev(mieic);
				system("pause");
				break;
			case 1:          // 1a opcao
				menuAlterarMorada(mieic);
				system("pause");
				break;
			case -2:          // 2a opcao
				menuAlterarNIF(mieic);
				system("pause");
				break;
			case -3:          // 3a opcao
				menuApagarContaDev(mieic);
				system("pause");
				break;
			case -4:          // 4a opcao
				menuDeveloper(mieic);          //
				system("pause");
				break;
			}
		}
	} else if (!dev_act->isEmpresa()) {
		for (;;) {
			system("cls");
			cout << "  Definicoes de Developer Individual  " << endl << endl;

			if (opcao == 0)
				cor(WHITE, BLACK);
			cout << "  Alterar Password  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -1)
				cor(WHITE, BLACK);
			cout << "  Alterar Morada " << endl;
			cor(BLACK, WHITE);
			if (opcao == -2)
				cor(WHITE, BLACK);
			cout << "  Apagar Conta  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -3)
				cor(WHITE, LIGHT_RED);
			cout << "  SAIR  " << endl;
			cor(BLACK, WHITE);

			opcao += teclas();
			opcao = RestringeOpcaoTeclas(0, 3, opcao);

			switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
			{
			case 0:          // 1a opcao
				menuAlterarPassDev(mieic);
				system("pause");
				break;

			case -1:          // 2a opcao
				menuAlterarMorada(mieic);
				system("pause");
				break;
			case -2:          // 3a opcao
				menuApagarContaDev(mieic);
				system("pause");
				break;
			case -3:          // 4a opcao
				menuDeveloper(mieic);          //
				system("pause");
				break;
			}
		}
	}
}

void menuClienteCredito(AppStore& mieic) {

}

void menuCestoCompras(AppStore& mieic) {

}

void menuHistoricoVendas(AppStore& mieic) {

}

void menuAlterarPassCli(AppStore& mieic) {

}

void menuAlterarCartao(AppStore& mieic) {

}

void menuApagarContaCli(AppStore& mieic) {

}

void menuAlterarPassDev(AppStore& mieic) {

}

void menuAlterarMorada(AppStore& mieic) {

}

void menuAlterarNIF(AppStore& mieic) {

}

void menuAlterarNomePessoal(AppStore& mieic) {

}

void menuApagarContaDev(AppStore& mieic) {

}

void menuVisitaStore(AppStore& mieic, unsigned int& state) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);

	vector<App> apps_por_nome;
	vector<App> apps_por_preco;
	vector<Developer*> devs_por_nome;

	if (state == 0) {

		int opcao = 0;
		for (;;) {
			system("cls");
			cout << "  AppStore MIEICPlay  - Esta a entrar com state " << state
					<< endl << endl;

			cout << "  Escolha como quer listar as apps:  " << endl << endl;

			if (opcao == 0)
				cor(WHITE, BLACK);
			cout << "  Por Ordem Alfabetica  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -1)
				cor(WHITE, BLACK);
			cout << "  Por Preco " << endl;
			cor(BLACK, WHITE);
			if (opcao == -2)
				cor(WHITE, BLACK);
			cout << "  Por developer  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -3)
				cor(WHITE, LIGHT_RED);
			cout << "  SAIR  " << endl;
			cor(BLACK, WHITE);

			opcao += teclas();
			opcao = RestringeOpcaoTeclas(0, 3, opcao);

			switch (opcao - 13) {
			case 0:          // 1a opcao
				apps_por_nome = mieic.apps;
				sort(apps_por_nome.begin(), apps_por_nome.end(),
						appsComparaNome);
				menuVisitaStoreOrdenada(mieic, state, apps_por_nome,
						"Ordem Alfabetica");
				system("pause");
				break;

			case -1:          // 2a opcao
				apps_por_preco = mieic.apps;
				sort(apps_por_preco.begin(), apps_por_preco.end(),
						appsComparaPreco);
				menuVisitaStoreOrdenada(mieic, state, apps_por_preco, "Preco");
				system("pause");
				break;
			case -2:          // 3a opcao
				menuListaDeveloper(mieic, state); //-> esta funcao vai chamar a menuVisitaStoreOrdenada, apos a escolha de um dev
				system("pause");
				break;
			case -3:          // 4a opcao
				menuInicial(mieic);
				system("pause");
				break;
			}
		}
	}

	if (state == 1) { // a diferenca do guest para o dev e o que acontece ao escolher a opcao "SAIR"

		int opcao = 0;
		for (;;) {
			system("cls");
			cout << "  AppStore MIEICPlay  - Esta a entrar com state " << state
					<< endl << endl;

			cout << "  Escolha como quer listar as apps:  " << endl << endl;

			if (opcao == 0)
				cor(WHITE, BLACK);
			cout << "  Por Ordem Alfabetica  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -1)
				cor(WHITE, BLACK);
			cout << "  Por Preco " << endl;
			cor(BLACK, WHITE);
			if (opcao == -2)
				cor(WHITE, BLACK);
			cout << "  Por developer  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -3)
				cor(WHITE, LIGHT_RED);
			cout << "  SAIR  " << endl;
			cor(BLACK, WHITE);

			opcao += teclas();
			opcao = RestringeOpcaoTeclas(0, 3, opcao);

			switch (opcao - 13) {
			case 0:          // 1a opcao
				apps_por_nome = mieic.apps;
				sort(apps_por_nome.begin(), apps_por_nome.end(),
						appsComparaNome);
				menuVisitaStoreOrdenada(mieic, state, apps_por_nome,
						"Ordem Alfabetica");
				system("pause");
				break;

			case -1:          // 2a opcao
				apps_por_preco = mieic.apps;
				sort(apps_por_preco.begin(), apps_por_preco.end(),
						appsComparaPreco);
				menuVisitaStoreOrdenada(mieic, state, apps_por_preco, "Preco");
				system("pause");
				break;
			case -2:          // 3a opcao
				menuListaDeveloper(mieic, state); //-> esta funcao vai chamar a menuVisitaStoreOrdenada, apos a escolha de um dev
				system("pause");
				break;
			case -3:          // 4a opcao
				menuDeveloper(mieic);
				system("pause");
				break;
			}
		}
	}

	if (state == 2) {

		int opcao = 0;
		for (;;) {
			system("cls");
			cout << "  AppStore MIEICPlay  - Esta a entrar com state " << state
					<< endl << endl;

			cout << "  Escolha como quer listar as apps:  " << endl << endl;

			if (opcao == 0)
				cor(WHITE, BLACK);
			cout << "  Por Ordem Alfabetica  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -1)
				cor(WHITE, BLACK);
			cout << "  Por Preco " << endl;
			cor(BLACK, WHITE);
			if (opcao == -2)
				cor(WHITE, BLACK);
			cout << "  Por developer  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -3)
				cor(WHITE, LIGHT_RED);
			cout << "  SAIR  " << endl;
			cor(BLACK, WHITE);

			opcao += teclas();
			opcao = RestringeOpcaoTeclas(0, 3, opcao);

			switch (opcao - 13) {
			case 0:          // 1a opcao
				apps_por_nome = mieic.apps;
				sort(apps_por_nome.begin(), apps_por_nome.end(),
						appsComparaNome);
				menuVisitaStoreOrdenada(mieic, state, apps_por_nome,
						"Ordem Alfabetica");
				system("pause");
				break;

			case -1:          // 2a opcao
				apps_por_preco = mieic.apps;
				sort(apps_por_preco.begin(), apps_por_preco.end(),
						appsComparaPreco);
				menuVisitaStoreOrdenada(mieic, state, apps_por_preco, "Preco");
				system("pause");
				break;
			case -2:          // 3a opcao
				menuListaDeveloper(mieic, state); //-> esta funcao vai chamar a menuVisitaStoreOrdenada, apos a escolha de um dev
				system("pause");
				break;
			case -3:          // 4a opcao
				menuInicial(mieic);
				system("pause");
				break;
			}
		}
	}
}

void menuVisitaStoreOrdenada(AppStore& mieic, unsigned int& state,
		vector<App> apps_ordenadas, string tipo_ordenacao) {

	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);

	vector<string> menu_options = getAppNames(apps_ordenadas);
	int opcao = 0;

	cout << "  Visita Store - Apps Ordenadas por " << tipo_ordenacao << endl
			<< endl;
	cout << "  Prima (Enter) para selecionar ou (Esc) para regressar  " << endl
			<< endl;

	if (apps_ordenadas.empty()) {
		system("cls");
		cout << "  Visita Store - Apps Ordenadas por " << tipo_ordenacao << endl
				<< endl;
		cout << "  Prima (Esc) para regressar  " << endl << endl;

		cout << endl << endl << endl << "  Nao ha Apps para mostrar  " << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
				tecla = getch();
			}

		}
		if (tipo_ordenacao == "Developer e Nome"
				|| tipo_ordenacao == "Developer e Preco") {
			menuListaDeveloper(mieic, state);
		} else {

			menuVisitaStore(mieic, state);
		}

	}

	if (state == 0) {

		printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) //ENQUANTO DIFERENTE DE ENTER E ESCAPE
			{
				tecla = getch();
				if (tecla == 72) //ACIMA
						{
					opcao--;
					if (opcao < 0)
						opcao = menu_options.size() - 1; // se subir mais que o inicio, passa para o fim
					system("cls");
					cout << "  Visita Store - Apps Ordenadas por "
							<< tipo_ordenacao << endl << endl;
					cout
							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
				}
				if (tecla == 80) //ABAIXO
						{
					opcao++;
					if (opcao > (menu_options.size() - 1))
						opcao = 0; // se passar o fim, volta ao inicio
					system("cls");
					cout << "  Visita Store - Apps Ordenadas por "
							<< tipo_ordenacao << endl << endl;
					cout
							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
				}
			}
		}
		if (tecla == 13) {
			system("cls");
			cout << "  Especificacoes da App  " << endl << endl;
			cout << "  Prima (Esc) para regressar  " << endl << endl << endl;
			cout << apps_ordenadas[opcao].imprime() << endl;
			int tecla;
			tecla = getch();
			if (tecla != 0) {
				while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
					tecla = getch();
				}
			}
			menuVisitaStoreOrdenada(mieic, state, apps_ordenadas,
					tipo_ordenacao);
		}

		if (tecla == 27) {
			if (tipo_ordenacao == "Developer e Nome"
					|| tipo_ordenacao == "Developer e Preco") {
				menuListaDeveloper(mieic, state);
			} else {
				menuVisitaStore(mieic, state);
			}
		}
	}
	if (state == 1) {

		printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) //ENQUANTO DIFERENTE DE ENTER E ESCAPE
			{
				tecla = getch();
				if (tecla == 72) //ACIMA
						{
					opcao--;
					if (opcao < 0)
						opcao = menu_options.size() - 1; // se subir mais que o inicio, passa para o fim
					system("cls");
					cout << "  Visita Store - Apps Ordenadas por "
							<< tipo_ordenacao << endl << endl;
					cout
							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
				}
				if (tecla == 80) //ABAIXO
						{
					opcao++;
					if (opcao > (menu_options.size() - 1))
						opcao = 0; // se passar o fim, volta ao inicio
					system("cls");
					cout << "  Visita Store - Apps Ordenadas por "
							<< tipo_ordenacao << endl << endl;
					cout
							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
				}
			}
		}
		if (tecla == 13) {
			system("cls");
			cout << "  Especificacoes da App  " << endl << endl;
			cout << "  Prima (Esc) para regressar  " << endl << endl << endl;
			cout << apps_ordenadas[opcao].imprime() << endl;
			int tecla;
			tecla = getch();
			if (tecla != 0) {
				while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
					tecla = getch();
				}
			}
			menuVisitaStoreOrdenada(mieic, state, apps_ordenadas,
					tipo_ordenacao);
		}

		if (tecla == 27) {
			if (tipo_ordenacao == "Developer e Nome"
					|| tipo_ordenacao == "Developer e Preco") {
				menuListaDeveloper(mieic, state);
			} else {
				menuVisitaStore(mieic, state);
			}
		}
	}
	if (state == 2) {

	}

}

void menuListaDeveloper(AppStore& mieic, unsigned int& state) {

	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);
	int opcao = 0;
	int opcao2 = 0;
	vector<Developer*> devs_ordenados = mieic.dev;
	sort(devs_ordenados.begin(), devs_ordenados.end(), devsComparaNome); // cria lista de devs ordenados

	vector<App> apps_do_dev_por_nome;
	vector<App> apps_do_dev_por_preco;

	if (devs_ordenados.empty()) {
		system("cls");
		cout << "  Visita Store - Devs Ordenados por Nome" << endl << endl;
		cout << "  Prima (Esc) para regressar  " << endl << endl;

		cout << endl << endl << endl << "  Nao ha Devs para mostrar  " << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
				tecla = getch();
			}
		}
		menuVisitaStore(mieic, state); // ao carregar escape, regressa a escolha de criterios da store
	}

	if (state == 0 || state == 1) { // lista de devs e menus anteriores e posteriores vao ser iguais para state 0 e 1
		vector<string> menu_options = getDevNames(devs_ordenados);

		cout << "  Visita Store - Devs Ordenados por Nome" << endl << endl;
		cout << "  Prima (Enter) para selecionar ou (Esc) para regressar  "
				<< endl << endl;
		printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) //ENQUANTO DIFERENTE DE ENTER E ESCAPE
			{
				tecla = getch();
				if (tecla == 72) //ACIMA
						{
					opcao--;
					if (opcao < 0)
						opcao = 0;
					system("cls");
					cout << "  Visita Store - Devs Ordenados por Nome" << endl
							<< endl;
					cout
							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
				}
				if (tecla == 80) //ABAIXO
						{
					opcao++;
					if (opcao > (menu_options.size() - 1))
						opcao = menu_options.size() - 1;
					system("cls");
					cout << "  Visita Store - Devs Ordenados por Nome" << endl
							<< endl;
					cout
							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
				}
			}
		}
		if (tecla == 13) { // aqui tem um dev selecionado. opcao = indice
			for (;;) {
				system("cls");
				cout << "  Escolha como quer listar as apps:  " << endl << endl;

				if (opcao2 == 0)
					cor(WHITE, BLACK);
				cout << "  Por Ordem Alfabetica  " << endl;
				cor(BLACK, WHITE);
				if (opcao2 == -1)
					cor(WHITE, BLACK);
				cout << "  Por Preco " << endl;
				cor(BLACK, WHITE);

				opcao2 += teclas();
				opcao2 = RestringeOpcaoTeclas(0, 1, opcao2);

				switch (opcao2 - 13) {
				case 0:          // 1a opcao
					apps_do_dev_por_nome = getApps(devs_ordenados[opcao],
							mieic);
					sort(apps_do_dev_por_nome.begin(),
							apps_do_dev_por_nome.end(), appsComparaNome);
					menuVisitaStoreOrdenada(mieic, state, apps_do_dev_por_nome,
							"Developer e Nome");
					system("pause");
					break;

				case -1:          // 2a opcao
					apps_do_dev_por_preco = getApps(devs_ordenados[opcao],
							mieic);
					sort(apps_do_dev_por_preco.begin(),
							apps_do_dev_por_preco.end(), appsComparaPreco);
					menuVisitaStoreOrdenada(mieic, state, apps_do_dev_por_preco,
							"Developer e Preco");
					system("pause");
					break;
				}
			}
		}
		if (tecla == 27)
			menuVisitaStore(mieic, state); // se na listagem de devs carrega esc, volta para o menu inic.

	}

	if (state == 2) {

	}

}

void menuVerDev(AppStore& mieic) {
time_t t = time(0);
struct tm *now = localtime(&t);
Date data_atual(tm);

if (dev_act->isEmpresa()) {
	system("cls");
	cout << "  Atributos da Empresa  " << endl << endl;
	cout << "  Prima (Esc) para regressar " << endl << endl << endl;

	cout << "  ID de Login: " << dev_act->getId() << endl;
	cout << "  Saldo: " << dev_act->getSaldo() << endl;
	cout << "  Nome Oficial: " << dev_act->getExtra() << endl;
	cout << "  Nome de Developer: " << dev_act->getNome() << endl;
	cout << "  NIF: " << dev_act->getNIF() << endl;
	cout << "  Morada: " << dev_act->getMorada() << endl;

	int tecla;
	tecla = getch();
	if (tecla != 0) {
		while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
			tecla = getch();
		}
	}
	menuDeveloper(mieic);

} else if (!dev_act->isEmpresa()) {
	system("cls");
	cout << "  Atributos do developer Individual  " << endl << endl;
	cout << "  Prima (Esc) para regressar " << endl << endl << endl;

	cout << "  ID de Login: " << dev_act->getId() << endl;
	cout << "  Saldo: " << dev_act->getSaldo() << endl;
	cout << "  Nome Pessoal: " << dev_act->getExtra() << endl;
	cout << "  Nome de Developer: " << dev_act->getNome() << endl;
	cout << "  Morada: " << dev_act->getMorada() << endl;

	int tecla;
	tecla = getch();
	if (tecla != 0) {
		while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
			tecla = getch();
		}
	}
	menuDeveloper(mieic);
}
}

void menuVerCli(AppStore& mieic) {
system("cls");
time_t t = time(0);
struct tm *now = localtime(&t);
Date data_atual(tm);

cout << "  Atributos de Cliente"
		"  " << endl << endl;
cout << "  Prima (Esc) para regressar " << endl << endl << endl;

cout << "  ID de Login: " << cli_act->getId() << endl;
cout << "  Saldo: " << cli_act->getSaldo() << endl;
cout << "  Nome: " << cli_act->getNome() << endl;
cout << "  Idade: " << cli_act->getIdade() << endl;
cout << "  Sexo: " << cli_act->getSexo() << endl;
cout << "  Nr. Cartao de Credito: " << cli_act->getCartaoCredito() << endl;
cout << "  Nr. de Vouchers disponiveis: " << cli_act->getVouchers() << endl;

int tecla;
tecla = getch();
if (tecla != 0) {
	while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
		tecla = getch();
	}
}
menuCliente(mieic);
}

