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

void gotoxy(int xpos, int ypos)  // just take this function as it is.
		{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos;
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void porDataNoCanto(Date data, int xpos, int ypos) {
	gotoxy(xpos, ypos);
	cout << data.imprimeData();
	gotoxy(0, 0);
}

vector<string> getAppNames(vector<App> apps) {
	vector<string> app_names;
	for (unsigned int i = 0; i < apps.size(); i++) {
		app_names.push_back(apps[i].getNome());
	}
	return app_names;
}

// pega em vector de Comentarios e retorn vetor de strings com classificacao-descricao
vector<string> getAppComentarios(vector<Comentario> comentarios_app) {
	string temp_str = "";
	vector<string> temp_comentarios;
	stringstream ss;
	stringstream ss2;
	string classificacao;
	string id_cliente;
	for (unsigned int i = 0; i < comentarios_app.size(); i++) {
		ss << comentarios_app[i].getClassificacao();
		ss >> classificacao; // transforma classificacao em string
		ss.clear();
		ss << comentarios_app[i].getIdClient();
		ss >> id_cliente;
		ss.clear();
		temp_str = "Cliente " + id_cliente + " - " + classificacao + "* - "
				+ comentarios_app[i].getDescricao();
		temp_comentarios.push_back(temp_str);
	}
	return temp_comentarios;
}

vector<string> getDevNames(vector<Developer*> devs) {
	vector<string> dev_names;
	for (unsigned int i = 0; i < devs.size(); i++) {
		dev_names.push_back(devs[i]->getNome());
	}
	return dev_names;
}

template<typename T>
bool verificaPass(T* dev_or_cli) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(now);
	int opcao = 0;
	string password;
	bool inputFail = false;

	cout << "  Verificacao por Password  " << endl << endl << endl << endl;

	do {
		system("cls");
		cout << "  Verificacao por Password  " << endl << endl << endl << endl;
		cout << "  Insira a password da sua conta: ";
		cin >> password;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	if (password == dev_or_cli->getIdPass()) {
		return true;
	} else {
		return false;
	}
}

bool verificaCartao(Cliente* cli) {

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

	dev_act = NULL; // da reset aos indicadores de login atual, ou seja, faz logout
	cli_act = NULL;
	unsigned int state = 0; //state 0 is guest
	int opcao = 0;
	for (;;) {
		system("cls");
		porDataNoCanto(mieic.DataAtual(), 1, 23);
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
	Date data_atual(now);
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
	Date data_atual(now);
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
	Date data_atual(now);

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
	Date data_atual(now);

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
	Date data_atual(now);

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
	Date data_atual(now);

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

	char key;

	while (1) {
		system("cls");
		cout << "  Insira os seus dados para registo de developer  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome pessoal: " << nome_pessoal << endl;
		cout << "  Indique o seu nome de developer: " << nome_dev << endl;
		cout << "  Indique a sua morada: " << morada;

		fflush(stdin);

		key = _getch();

		if (key == 13) {
			if (morada != "") {
				break;
			}
		} else if (key == 8) {
			// Backspace detected, delete last input character from string
			if (morada.length() > 0)
				morada = morada.substr(0, morada.length() - 1);
		} else {
			if (key == 0 || key == 224) {
				// An arrow or function key was pressed, run _getch again to remove the second return value from buffer
				_getch();
			} else if (key >= 32 && key <= 126) // It's a valid ASCII caracter
				morada += (char) key;
		}
	}

	do {
		system("cls");
		cout << "  Insira os seus dados para registo de developer  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome pessoal: " << nome_pessoal << endl;
		cout << "  Indique o seu nome de developer: " << nome_dev << endl;
		cout << "  Indique a sua morada: " << morada << endl;
		cout << "  Introduza agora a password que pretende: ";

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
	cout << "  Introduza agora a password que pretende: " << password; //TODO: por astericos na pass
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
	Date data_atual(now);

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
		nomeRepetido = mieic.existeNomeDevEmp(nome_dev, nome_oficial);

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
			cout
					<< "  Registo invalido! Um developer com esse nome de developer ou pertencente a empresa ja existe. "
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

	unsigned int state = 2; //state 2 is the client
	int opcao = 0;

	for (;;) {
		system("cls");
		porDataNoCanto(mieic.DataAtual(), 1, 23);
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

	unsigned int state = 1; // state = 1 is developer
	int opcao = 0;

	for (;;) {
		system("cls");
		porDataNoCanto(mieic.DataAtual(), 1, 23);
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
	Date data_atual(now);
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
			menuClienteAddCredito(mieic);
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
	Date data_atual(now);
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
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(now);
	int opcao = 0;

	for (;;) {
		system("cls");
		cout << "  Gestao de Apps  " << endl << endl;

		if (opcao == 0)
			cor(WHITE, BLACK);
		cout << "  Adicionar App  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -1)
			cor(WHITE, BLACK);
		cout << "  Remover App " << endl;
		cor(BLACK, WHITE);
		if (opcao == -2)
			cor(WHITE, BLACK);
		cout << "  Modificar App  " << endl;
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
			menuCriarApp(mieic);
			system("pause");
			break;
		case -1:          // 1a opcao
			menuRemoverApp(mieic);
			system("pause");
			break;
		case -2:          // 2a opcao
			menuModificarApp(mieic);
			system("pause");
			break;
		case -3:          // 4a opcao
			menuDeveloper(mieic);          //
			system("pause");
			break;
		}
	}

}

void menuDeveloperDefinicoes(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(now);
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

void menuClienteAddCredito(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(now);
	int opcao = 0;

	int cartao_credito;
	float saldo_a_adicionar;
	string password_nova;
	bool inputFail = false;

	cout << "  Adicionar Credito  " << endl << endl << endl << endl;

	do {
		system("cls");
		cout << "  Adicionar Credito  " << endl << endl << endl << endl;
		cout << "  Insira o Nr. do seu Cartao de Credito: ";
		cin >> cartao_credito;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	do {
		system("cls");
		cout << "  Adicionar Credito  " << endl << endl << endl << endl;
		cout << "  Insira o Nr. do seu Cartao de Credito: " << cartao_credito
				<< endl;
		cout << "  Insira o credito a adicionar: ";
		cin >> saldo_a_adicionar;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	system("cls");
	cout << "  Adicionar Credito  " << endl << endl << endl << endl;
	cout << "  Insira o Nr. do seu Cartao de Credito: " << cartao_credito
			<< endl;
	cout << "  Insira o credito a adicionar: " << saldo_a_adicionar << endl
			<< endl;
	cout
			<< "  Prima (Enter) para validar ou (Esc) para regressar sem registar  "
			<< endl << endl;
	int tecla;
	tecla = getch();
	if (tecla != 0) {
		while (tecla != 13 && tecla != 27) { // enquanto nao prime enter para continuar
			tecla = getch();
		}
	}
	if (tecla == 13) {
		if (cli_act->getCartaoCredito() == cartao_credito) {

			// modifica o saldo para ser o que ja tinha + o saldo a adicionar
			cli_act->setSaldo(cli_act->getSaldo() + saldo_a_adicionar);

			system("cls");
			cout << "  Adicionar Credito  " << endl << endl << endl;
			cout << "  Sucesso! Credito adicionado.  " << endl;
			cout << "  O seu saldo e agora de " << cli_act->getSaldo()
					<< " euros." << endl << endl;
			cout << "  Prima (Enter) para continuar " << endl;

			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13) { // enquanto nao prime enter para continuar
					tecla = getch();
				}
			}
			menuClienteTransacoes(mieic);
		} else
			system("cls");
		cout << "  Adicionar Credito " << endl << endl << endl;
		cout << "  Tentativa falhada! Errou o Nr. do seu Cartao de Credito.  "
				<< endl << endl;
		cout
				<< "  Prima (Enter) para tentar de novo ou (Escape) para regressar "
				<< endl;

		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) { // enquanto nao prime enter para continuar
				tecla = getch();
			}
		}
		if (tecla == 13) {
			menuClienteAddCredito(mieic);
		} else if (tecla == 27) {
			menuClienteTransacoes(mieic);
		}

	} else if (tecla == 27) {
		menuClienteTransacoes(mieic);
	}
}

void menuCestoCompras(AppStore& mieic) {
	system("cls");

	int opcao = 0;

	for (;;) {
		system("cls");
		porDataNoCanto(mieic.DataAtual(), 1, 23);
		cout << "  Cesto de Compras  " << endl << endl;

		if (opcao == 0)
			cor(WHITE, BLACK);
		cout << "  Ver cesto/Checkout cesto  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -1)
			cor(WHITE, BLACK);
		cout << "  Remover apps do cesto  " << endl;
		cor(BLACK, WHITE);
		if (opcao == -2)
			cor(WHITE, LIGHT_RED);
		cout << "  SAIR  " << endl;
		cor(BLACK, WHITE);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 2, opcao);

		switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
		{
		case 0:
			menuCheckoutApps(mieic);
			system("pause");
			break;
		case -1:          // 1a opcao
			menuTiraAppsCesto(mieic);
			system("pause");
			break;
		case -2:          // 5a opcao
			menuCliente(mieic);
			system("pause");
			break;

		}
	}
}

void menuHistoricoVendas(AppStore& mieic) {

}

void menuAlterarPassCli(AppStore& mieic) {
	system("cls");

	string password_nova;
	bool passCerta = false;
	bool inputFail = false;

	passCerta = verificaPass(cli_act);

	if (passCerta) {
		do {
			system("cls");
			cout << "  Alterar Password  " << endl << endl << endl << endl;
			cout << "  Insira a nova password para a sua conta: ";
			cin >> password_nova;

			inputFail = cin.fail();
			cin.clear();  // da clear a flag do fail
			cin.ignore(1000, '\n');
		} while (inputFail == true);

		system("cls");
		cout << "  Alterar Password  " << endl << endl << endl << endl;
		cout << "  Insira a nova password para a sua conta: " << password_nova
				<< endl << endl;
		cout
				<< "  Prima (Enter) para confirmar ou (Esc) para regressar sem alterar "
				<< endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) {
				tecla = getch();
			}
		}
		if (tecla == 13) {

			cli_act->setIdPass(password_nova);

			system("cls");
			cout << "  Alterar Password  " << endl << endl << endl << endl;
			cout << "  Sucesso! Password alterada.  " << endl << endl;
			cout << "  Prima (Enter) para continuar " << endl << endl;

			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13) {
					tecla = getch();
				}
			}
			menuClienteDefinicoes(mieic);
		}
		if (tecla == 27)
			menuClienteDefinicoes(mieic);

	} else if (!passCerta) {
		system("cls");
		cout << "  Alterar Password " << endl << endl << endl << endl;
		cout << "  Password errada.  " << endl << endl;
		cout
				<< "  Prima (Enter) para tentar novamente ou (Esc) para regressar  "
				<< endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) { // enquanto nao prime enter para continuar
				tecla = getch();
			}
		}
		if (tecla == 13)
			menuAlterarPassCli(mieic);
		if (tecla == 27)
			menuClienteDefinicoes(mieic);

	}

}

void menuAlterarCartao(AppStore& mieic) {
	system("cls");

	int cartao_credito;
	bool passCerta = false;
	bool inputFail = false;

	passCerta = verificaPass(cli_act);

	if (passCerta) {
		do {
			system("cls");
			cout << "  Alterar Cartao Credito  " << endl << endl << endl
					<< endl;
			cout
					<< "  Insira o Nr. do novo de Cartao de Credito para a sua conta: ";
			cin >> cartao_credito;

			inputFail = cin.fail();
			cin.clear();  // da clear a flag do fail
			cin.ignore(1000, '\n');
		} while (inputFail == true);

		system("cls");
		cout << "  Alterar Cartao Credito  " << endl << endl << endl << endl;
		cout << "  Insira o Nr. do novo de Cartao de Credito para a sua conta: "
				<< cartao_credito << endl << endl;
		cout
				<< "  Prima (Enter) para confirmar ou (Esc) para regressar sem alterar "
				<< endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) {
				tecla = getch();
			}
		}
		if (tecla == 13) {

			cli_act->setCartao(cartao_credito);

			system("cls");
			cout << "  Alterar Cartao  " << endl << endl << endl << endl;
			cout << "  Sucesso! Cartao Credito alterado.  " << endl << endl;
			cout << "  Prima (Enter) para continuar " << endl << endl;

			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13) {
					tecla = getch();
				}
			}
			menuClienteDefinicoes(mieic);
		}
		if (tecla == 27)
			menuClienteDefinicoes(mieic);

	} else if (!passCerta) {
		system("cls");
		cout << "  Alterar Cartao Credito " << endl << endl << endl << endl;
		cout << "  Password errada.  " << endl << endl;
		cout
				<< "  Prima (Enter) para tentar novamente ou (Esc) para regressar  "
				<< endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) { // enquanto nao prime enter para continuar
				tecla = getch();
			}
		}
		if (tecla == 13)
			menuAlterarCartao(mieic);
		if (tecla == 27)
			menuClienteDefinicoes(mieic);

	}
}

void menuApagarContaCli(AppStore& mieic) {
	system("cls");

	string NIF_novo;
	bool passCerta = false;
	bool inputFail = false;
	int opcao = 0;
	passCerta = verificaPass(cli_act);

	if (passCerta) {

		for (;;) {
			system("cls");
			cout << "  Apagar Conta  " << endl << endl << endl;
			cout << "  Tem a certeza que pretende apagar a sua conta?" << endl
					<< endl << endl;

			if (opcao == 0)
				cor(WHITE, LIGHT_RED);
			cout << "  SIM  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -1)
				cor(WHITE, BLACK);
			cout << "  NAO " << endl;
			cor(BLACK, WHITE);

			opcao += teclas();
			opcao = RestringeOpcaoTeclas(0, 1, opcao);

			switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
			{
			case 0: // SIM - apaga-se o cliente (vendas nao se apagam, tem de ficar registadas a mesma)

				//apaga o cliente
				for (unsigned int i = 0; i < mieic.clientes.size(); i++) {
					if (mieic.clientes[i].getId() == cli_act->getId()) {
						mieic.clientes.erase(mieic.clientes.begin() + i);
						break;
					}
				}

				system("cls");
				cout << "  Apagar Conta  " << endl << endl << endl << endl;
				cout << "  Sucesso. A sua conta foi apagada.  " << endl << endl;
				cout
						<< "  Prima (Enter) para ser redirigido para o Menu Inicial  "
						<< endl;
				int tecla;
				tecla = getch();
				if (tecla != 0) {
					while (tecla != 13) {
						tecla = getch();
					}
				}

				cli_act = NULL;
				menuInicial(mieic);
				break;

			case -1:
				// NAO
				menuClienteDefinicoes(mieic);
				system("pause");
				break;
			}
		}

	} else if (!passCerta) {
		system("cls");
		cout << "  Apagar Conta  " << endl << endl << endl << endl;
		cout << "  Password errada.  " << endl << endl;
		cout
				<< "  Prima (Enter) para tentar novamente ou (Esc) para regressar  "
				<< endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) {
				tecla = getch();
			}
		}
		if (tecla == 13)
			menuApagarContaCli(mieic);
		if (tecla == 27)
			menuClienteDefinicoes(mieic);

	}
}

void menuAlterarPassDev(AppStore& mieic) {
	system("cls");

	string password_nova;
	bool passCerta = false;
	bool inputFail = false;

	passCerta = verificaPass(dev_act);

	if (passCerta) {
		do {
			system("cls");
			cout << "  Alterar Password  " << endl << endl << endl << endl;
			cout << "  Insira a nova password para a sua conta: ";
			cin >> password_nova;

			inputFail = cin.fail();
			cin.clear();  // da clear a flag do fail
			cin.ignore(1000, '\n');
		} while (inputFail == true);

		system("cls");
		cout << "  Alterar Password  " << endl << endl << endl << endl;
		cout << "  Insira a nova password para a sua conta: " << password_nova
				<< endl << endl;
		cout
				<< "  Prima (Enter) para confirmar ou (Esc) para regressar sem alterar "
				<< endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) {
				tecla = getch();
			}
		}
		if (tecla == 13) {

			dev_act->setIdPass(password_nova);

			system("cls");
			cout << "  Alterar Password  " << endl << endl << endl << endl;
			cout << "  Sucesso! Password alterada.  " << endl << endl;
			cout << "  Prima (Enter) para continuar " << endl << endl;

			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13) {
					tecla = getch();
				}
			}
			menuDeveloperDefinicoes(mieic);
		}
		if (tecla == 27)
			menuDeveloperDefinicoes(mieic);

	} else if (!passCerta) {
		system("cls");
		cout << "  Alterar Password " << endl << endl << endl << endl;
		cout << "  Password errada.  " << endl << endl;
		cout
				<< "  Prima (Enter) para tentar novamente ou (Esc) para regressar  "
				<< endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) { // enquanto nao prime enter para continuar
				tecla = getch();
			}
		}
		if (tecla == 13)
			menuAlterarPassDev(mieic);
		if (tecla == 27)
			menuDeveloperDefinicoes(mieic);

	}

}

void menuAlterarMorada(AppStore& mieic) {
	system("cls");

	string morada_nova;
	bool passCerta = false;
	bool inputFail = false;

	passCerta = verificaPass(dev_act);

	if (passCerta) {

		char key;

		while (1) {
			system("cls");
			cout << "  Alterar Morada  " << endl << endl << endl << endl;
			cout << "  Insira a nova morada para a sua conta: " << morada_nova;

			fflush(stdin);

			key = _getch();

			if (key == 13) {
				if (morada_nova != "") {
					break;
				}
			} else if (key == 8) {
				// Backspace detected, delete last input character from string
				if (morada_nova.length() > 0)
					morada_nova = morada_nova.substr(0,
							morada_nova.length() - 1);
			} else {
				if (key == 0 || key == 224) {
					// An arrow or function key was pressed, run _getch again to remove the second return value from buffer
					_getch();
				} else if (key >= 32 && key <= 126) // It's a valid ASCII caracter
					morada_nova += (char) key;
			}
		}

		system("cls");
		cout << "  Alterar Morada  " << endl << endl << endl << endl;
		cout << "  Insira a nova morada para a sua conta: " << morada_nova
				<< endl << endl;
		cout
				<< "  Prima (Enter) para confirmar ou (Esc) para regressar sem alterar "
				<< endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) {
				tecla = getch();
			}
		}
		if (tecla == 13) {

			dev_act->setMorada(morada_nova);

			system("cls");
			cout << "  Alterar Morada  " << endl << endl << endl << endl;
			cout << "  Sucesso! Morada alterado.  " << endl << endl;
			cout << "  Prima (Enter) para continuar " << endl << endl;

			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13) {
					tecla = getch();
				}
			}
			menuDeveloperDefinicoes(mieic);
		}
		if (tecla == 27)
			menuDeveloperDefinicoes(mieic);

	} else if (!passCerta) {
		system("cls");
		cout << "  Alterar Morada  " << endl << endl << endl << endl;
		cout << "  Password errada.  " << endl << endl;
		cout
				<< "  Prima (Enter) para tentar novamente ou (Esc) para regressar  "
				<< endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) { // enquanto nao prime enter para continuar
				tecla = getch();
			}
		}
		if (tecla == 13)
			menuAlterarMorada(mieic);
		if (tecla == 27)
			menuDeveloperDefinicoes(mieic);

	}

}

void menuAlterarNIF(AppStore& mieic) {
	system("cls");

	string NIF_novo;
	bool passCerta = false;
	bool inputFail = false;

	passCerta = verificaPass(dev_act);

	if (passCerta) {
		do {
			system("cls");
			cout << "  Alterar NIF  " << endl << endl << endl << endl;
			cout << "  Insira o novo NIF para a sua conta: ";
			cin >> NIF_novo;

			inputFail = cin.fail();
			for (unsigned int i = 0; i < NIF_novo.size(); i++) { //verifica se NIF so tem numeros
				if (!isdigit(NIF_novo[i])) {
					inputFail = true;
				}
			}
			cin.clear();  // da clear a flag do fail
			cin.ignore(1000, '\n');
		} while (inputFail == true);

		system("cls");
		cout << "  Alterar NIF  " << endl << endl << endl << endl;
		cout << "  Insira o novo NIF para a sua conta: " << NIF_novo << endl
				<< endl;
		cout
				<< "  Prima (Enter) para confirmar ou (Esc) para regressar sem alterar "
				<< endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) {
				tecla = getch();
			}
		}
		if (tecla == 13) {

			dev_act->setNIF(NIF_novo);

			system("cls");
			cout << "  Alterar NIF  " << endl << endl << endl << endl;
			cout << "  Sucesso! NIF alterado.  " << endl << endl;
			cout << "  Prima (Enter) para continuar " << endl << endl;

			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13) {
					tecla = getch();
				}
			}
			menuDeveloperDefinicoes(mieic);
		}
		if (tecla == 27)
			menuDeveloperDefinicoes(mieic);

	} else if (!passCerta) {
		system("cls");
		cout << "  Alterar NIF  " << endl << endl << endl << endl;
		cout << "  Password errada.  " << endl << endl;
		cout
				<< "  Prima (Enter) para tentar novamente ou (Esc) para regressar  "
				<< endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) { // enquanto nao prime enter para continuar
				tecla = getch();
			}
		}
		if (tecla == 13)
			menuAlterarNIF(mieic);
		if (tecla == 27)
			menuDeveloperDefinicoes(mieic);

	}

}

void menuApagarContaDev(AppStore& mieic) {
	system("cls");

	string NIF_novo;
	bool passCerta = false;
	bool inputFail = false;
	int opcao = 0;
	vector<int> ids_apps_apagadas;
	passCerta = verificaPass(dev_act);

	if (passCerta) {

		for (;;) {
			system("cls");
			cout << "  Apagar Conta  " << endl << endl << endl;
			cout << "  Tem a certeza que pretende apagar a sua conta?" << endl
					<< endl << endl;

			if (opcao == 0)
				cor(WHITE, LIGHT_RED);
			cout << "  SIM  " << endl;
			cor(BLACK, WHITE);
			if (opcao == -1)
				cor(WHITE, BLACK);
			cout << "  NAO " << endl;
			cor(BLACK, WHITE);

			opcao += teclas();
			opcao = RestringeOpcaoTeclas(0, 1, opcao);

			switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
			{
			case 0: // SIM - em 1o apagam-se as apps do Dev e as vendas ficam com o historico do nome

				//apaga o dev
				for (unsigned int i = 0; i < mieic.dev.size(); i++) {
					if (mieic.dev[i] == dev_act) {
						mieic.dev.erase(mieic.dev.begin() + i);
						break;
					}
				}

				//apaga apps que eram deste dev

				for (unsigned int j = 0; j < mieic.apps.size(); j++) {
//					cout<<"mieic.apps - " << mieic.apps[j].getNome() << endl;
					if (mieic.apps[j].getDev() == dev_act) {
						ids_apps_apagadas.push_back(mieic.apps[j].getId());
//						cout << "A app " << mieic.apps[j].getNome() << " foi apagada." << endl;
						mieic.apps.erase(mieic.apps.begin() + j);
						j--;
					}
				}

				// para cada venda, analisa se o ID da app na venda pertence as que foram apagadas
				for (unsigned int k = 0; k < mieic.vendas.size(); k++) {
					for (unsigned int l = 0; l < ids_apps_apagadas.size(); l++)
						if (mieic.vendas[k].getAppVendidaId()
								== ids_apps_apagadas[l]) { // encontrou uma venda cuja app tinha sido apagada
							mieic.vendas[k].setAppApagada(true);
							break; //cada venda so tem 1 app - ao fim de descobrir que foi apagada ja nao precisa analisar mais para essa venda
						}
				}

				system("cls");
				cout << "  Apagar Conta  " << endl << endl << endl << endl;
				cout << "  Sucesso. A sua conta foi apagada.  " << endl << endl;
				cout
						<< "  Prima (Enter) para ser redirigido para o Menu Inicial  "
						<< endl;
				int tecla;
				tecla = getch();
				if (tecla != 0) {
					while (tecla != 13) {
						tecla = getch();
					}
				}
//				delete dev_act;
				dev_act = NULL;
				menuInicial(mieic);
				break;

			case -1:
				// NAO
				menuDeveloperDefinicoes(mieic);
				system("pause");
				break;
			}
		}

	} else if (!passCerta) {
		system("cls");
		cout << "  Apagar Conta  " << endl << endl << endl << endl;
		cout << "  Password errada.  " << endl << endl;
		cout
				<< "  Prima (Enter) para tentar novamente ou (Esc) para regressar  "
				<< endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) {
				tecla = getch();
			}
		}
		if (tecla == 13)
			menuApagarContaDev(mieic);
		if (tecla == 27)
			menuDeveloperDefinicoes(mieic);

	}

}

void menuVisitaStore(AppStore& mieic, unsigned int& state) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(now);

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
				menuCliente(mieic);
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
	Date data_atual(now);
	int opcao_app = 0;

	//	vector<string> menu_options = getAppNames(apps_ordenadas);
	vector<string> menu_options;
	string preco;

	for (unsigned int i = 0; i < apps_ordenadas.size(); i++) {
		stringstream ss;
		ss << apps_ordenadas[i].getPreco();
		ss >> preco;
		ss.clear();
		string temp_str = " Preco: " + preco + "   Nome: "
				+ apps_ordenadas[i].getNome();
		menu_options.push_back(temp_str);
	}


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

	if (state == 0 || state == 1) {

		cout << "  Visita Store - Apps Ordenadas por " << tipo_ordenacao << endl
				<< endl;
		cout << "  Prima (Enter) para selecionar ou (Esc) para regressar  "
				<< endl << endl;
		printMenuScroll(menu_options, opcao_app, MAX_PER_SCREEN);

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) //ENQUANTO DIFERENTE DE ENTER E ESCAPE
			{
				tecla = getch();
				if (tecla == 72) //ACIMA
						{
					opcao_app--;
					if (opcao_app < 0)
						opcao_app = menu_options.size() - 1; // se subir mais que o inicio, passa para o fim
					system("cls");
					cout << "  Visita Store - Apps Ordenadas por "
							<< tipo_ordenacao << endl << endl;
					cout
							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao_app, MAX_PER_SCREEN);
				}
				if (tecla == 80) //ABAIXO
						{
					opcao_app++;
					if (opcao_app > (menu_options.size() - 1))
						opcao_app = 0; // se passar o fim, volta ao inicio
					system("cls");
					cout << "  Visita Store - Apps Ordenadas por "
							<< tipo_ordenacao << endl << endl;
					cout
							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao_app, MAX_PER_SCREEN);
				}
			}
		}

		if (tecla == 13) { // visita a App - imprime as especificacoes desta e da opcao de ler comentarios
			int opcao_menu = 0;
			int opcao_comentario = 0; // por default o scroll ira comecar no 1o comentario
			vector<Comentario> menu_comentarios =
					apps_ordenadas[opcao_app].getComentarios();
			vector<string> lista_comentarios = getAppComentarios(
					menu_comentarios);
			for (;;) {
				system("cls");
				cout << "  Especificacoes da App  " << endl << endl << endl;
				cout << apps_ordenadas[opcao_app].imprime() << endl << endl
						<< endl;

				if (opcao_menu == 0)
					cor(WHITE, BLACK);
				cout << "  Ler Comentarios " << endl;
				cor(BLACK, WHITE);
				if (opcao_menu == -1)
					cor(WHITE, LIGHT_RED);
				cout << "  SAIR  " << endl;
				cor(BLACK, WHITE);

				opcao_menu += teclas();
				opcao_menu = RestringeOpcaoTeclas(0, 1, opcao_menu);

				switch (opcao_menu - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
				{
				case 0:          // 1a opcao

					// no caso de nao haver comentarios
					if (menu_comentarios.empty()) {
						cout << endl << endl << "Nao ha comentarios a mostrar."
								<< endl;
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

					//mas, se houver comentarios, entao vai exibi-los enquanto nao se carrega ESC

					system("cls");
					cout << "  Comentarios da App " << endl << endl;
					cout << "  Prima (Esc) para regressar a lista de Apps "
							<< endl << endl;
					printMenuScroll(lista_comentarios, opcao_comentario,
							MAX_PER_SCREEN);

					int tecla;
					tecla = getch();
					if (tecla != 0) {
						while (tecla != 27) //ENQUANTO DIFERENTE DE ESCAPE
						{
							tecla = getch();
							if (tecla == 72) //ACIMA
									{
								opcao_comentario--;
								if (opcao_comentario < 0)
									opcao_comentario = lista_comentarios.size()
											- 1; // se subir mais que o inicio, passa para o fim
								system("cls");
								cout << "  Comentarios da App  " << endl
										<< endl;
								cout
										<< "  Prima (Esc) para regressar a lista de Apps "
										<< endl << endl;
								printMenuScroll(lista_comentarios,
										opcao_comentario, MAX_PER_SCREEN);
							}
							if (tecla == 80) //ABAIXO
									{
								opcao_comentario++;
								if (opcao_comentario
										> (lista_comentarios.size() - 1))
									opcao_comentario = 0; // se passar o fim, volta ao inicio
								system("cls");
								cout << "  Comentarios da App  " << endl
										<< endl;
								cout
										<< "  Prima (Esc) para regressar a lista de Apps "
										<< endl << endl;
								printMenuScroll(lista_comentarios,
										opcao_comentario, MAX_PER_SCREEN);
							}
						}
					} // ao sair do ciclo e porque o user carregou escape

					menuVisitaStoreOrdenada(mieic, state, apps_ordenadas,
							tipo_ordenacao);

					break;

				case -1:          // 2a opcao
					menuVisitaStoreOrdenada(mieic, state, apps_ordenadas,
							tipo_ordenacao);
					break;
				}
			}
		}

		if (tecla == 27) { // volta da lista de apps para o menu anterior
			if (tipo_ordenacao == "Developer e Nome"
					|| tipo_ordenacao == "Developer e Preco") {
				menuListaDeveloper(mieic, state);
			} else {
				menuVisitaStore(mieic, state);
			}
		}
	}
	if (state == 2) {

		cout << "  Visita Store - Apps Ordenadas por " << tipo_ordenacao << endl
				<< endl;
		cout << "  Prima (Enter) para selecionar ou (Esc) para regressar  "
				<< endl << endl;
		printMenuScroll(menu_options, opcao_app, MAX_PER_SCREEN);

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) //ENQUANTO DIFERENTE DE ENTER E ESCAPE
			{
				tecla = getch();
				if (tecla == 72) //ACIMA
						{
					opcao_app--;
					if (opcao_app < 0)
						opcao_app = menu_options.size() - 1; // se subir mais que o inicio, passa para o fim
					system("cls");
					cout << "  Visita Store - Apps Ordenadas por "
							<< tipo_ordenacao << endl << endl;
					cout
							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao_app, MAX_PER_SCREEN);
				}
				if (tecla == 80) //ABAIXO
						{
					opcao_app++;
					if (opcao_app > (menu_options.size() - 1))
						opcao_app = 0; // se passar o fim, volta ao inicio
					system("cls");
					cout << "  Visita Store - Apps Ordenadas por "
							<< tipo_ordenacao << endl << endl;
					cout
							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao_app, MAX_PER_SCREEN);
				}
			}
		}

		if (tecla == 13) { // visita a App - imprime as especificacoes desta e da opcao de ler comentarios
			int opcao_menu = 0;
			int opcao_comentario = 0; // por default o scroll ira comecar no 1o comentario
			vector<Comentario> menu_comentarios =
					apps_ordenadas[opcao_app].getComentarios();
			vector<string> lista_comentarios = getAppComentarios(
					menu_comentarios);

			bool comprado = cli_act->jaComprou(apps_ordenadas[opcao_app]);

			if (comprado) {

				for (;;) {
					system("cls");
					cout << "  Especificacoes da App  " << endl << endl << endl;
					cout << apps_ordenadas[opcao_app].imprime() << endl << endl
							<< endl;

					if (opcao_menu == 0)
						cor(WHITE, BLACK);
					cout << "  Ler Comentarios " << endl;
					cor(BLACK, WHITE);
					if (opcao_menu == -1)
						cor(WHITE, BLACK);
					cout << "  Submeter comentario/classificacao " << endl;
					cor(BLACK, WHITE);
					if (opcao_menu == -2)
						cor(WHITE, BLACK);
					cout << "  Fazer Download  " << endl;
					cor(BLACK, WHITE);
					if (opcao_menu == -3)
						cor(WHITE, LIGHT_RED);
					cout << "  SAIR  " << endl;
					cor(BLACK, WHITE);

					opcao_menu += teclas();
					opcao_menu = RestringeOpcaoTeclas(0, 3, opcao_menu);

					string comentario_str;
					bool inputFail = false;
					float progress = 0.0;
					int i = 0;
					switch (opcao_menu - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
					{
					case 0:          // 1a opcao

						// no caso de nao haver comentarios
						if (menu_comentarios.empty()) {
							cout << endl << endl
									<< "Nao ha comentarios a mostrar." << endl;
							int tecla;
							tecla = getch();
							if (tecla != 0) {
								while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
									tecla = getch();
								}

							}
							menuVisitaStoreOrdenada(mieic, state,
									apps_ordenadas, tipo_ordenacao);

						}

						//mas, se houver comentarios, entao vai exibi-los enquanto nao se carrega ESC

						system("cls");
						cout << "  Comentarios da App " << endl << endl;
						cout << "  Prima (Esc) para regressar a lista de Apps "
								<< endl << endl;
						printMenuScroll(lista_comentarios, opcao_comentario,
								MAX_PER_SCREEN);

						int tecla;
						tecla = getch();
						if (tecla != 0) {
							while (tecla != 27) //ENQUANTO DIFERENTE DE ESCAPE
							{
								tecla = getch();
								if (tecla == 72) //ACIMA
										{
									opcao_comentario--;
									if (opcao_comentario < 0)
										opcao_comentario =
												lista_comentarios.size() - 1; // se subir mais que o inicio, passa para o fim
									system("cls");
									cout << "  Comentarios da App  " << endl
											<< endl;
									cout
											<< "  Prima (Esc) para regressar a lista de Apps "
											<< endl << endl;
									printMenuScroll(lista_comentarios,
											opcao_comentario, MAX_PER_SCREEN);
								}
								if (tecla == 80) //ABAIXO
										{
									opcao_comentario++;
									if (opcao_comentario
											> (lista_comentarios.size() - 1))
										opcao_comentario = 0; // se passar o fim, volta ao inicio
									system("cls");
									cout << "  Comentarios da App  " << endl
											<< endl;
									cout
											<< "  Prima (Esc) para regressar a lista de Apps "
											<< endl << endl;
									printMenuScroll(lista_comentarios,
											opcao_comentario, MAX_PER_SCREEN);
								}
							}
						} // ao sair do ciclo e porque o user carregou escape

						menuVisitaStoreOrdenada(mieic, state, apps_ordenadas,
								tipo_ordenacao);

						break;

					case -1:          // 2a opcao

						unsigned int classificacao;
						char key;

						while (1) {
							system("cls");
							cout
									<< "  Escreva o seu comentario e classificacao para a App   "
									<< endl << endl << endl;
							cout << "  Comentario: " << comentario_str;

							fflush(stdin);

							key = _getch();

							if (key == 13) {
								if (comentario_str != "") {
									break;
								}
							} else if (key == 8) {
								// Backspace detected, delete last input character from string
								if (comentario_str.length() > 0)
									comentario_str = comentario_str.substr(0,
											comentario_str.length() - 1);
							} else {
								if (key == 0 || key == 224) {
									// An arrow or function key was pressed, run _getch again to remove the second return value from buffer
									_getch();
								} else if (key >= 32 && key <= 126) // It's a valid ASCII caracter
									comentario_str += (char) key;
							}
						}

						do {

							system("cls");
							cout
									<< "  Escreva o seu comentario e classificacao para a App   "
									<< endl << endl << endl;
							cout << "  Comentario: " << comentario_str << endl;
							cout << "  Classificacao: ";

							cin >> classificacao;

							inputFail = cin.fail();
							if (classificacao < 1 || classificacao > 5)
								inputFail = true;
							cin.clear();  // da clear a flag do fail
							cin.ignore(1000, '\n');
						} while (inputFail == true);

						system("cls");
						cout
								<< "  Escreva o seu comentario e classificacao para a App   "
								<< endl << endl << endl;
						cout << "  Comentario: " << comentario_str << endl;
						cout << "  Classificacao: " << classificacao;
						cout << endl << endl << endl;
						cout
								<< "  Prima (Enter) para validar ou (Esc) para regressar a lista de apps"
								<< endl << endl;

						cin.clear();

						tecla = getch();
						if (tecla != 0) {
							while (tecla != 13 && tecla != 27) {
								tecla = getch();
							}
						}
						if (tecla == 13) {

							Comentario comment(comentario_str, cli_act->getId(),
									classificacao);

							// a partir do id da app vai-se descobrir o indice da app no vetor
							// do mieic.apps para poder adicionar o comentario diretamente
							// nesse vetor
							unsigned int id_da_app =
									apps_ordenadas[opcao_app].getId();

							for (unsigned int j = 0; j < mieic.apps.size();
									j++) {
								if (id_da_app == mieic.apps[j].getId()) {
									mieic.apps[j].addComentario(comment);
									break;
								}
							}
							// esta linha serve para o comentario atualizar imediatamente sem
							// necessitar de sair da store
							apps_ordenadas[opcao_app].addComentario(comment);

							system("cls");
							cout
									<< "  Escreva o seu comentario e classificacao para a App   "
									<< endl << endl << endl;
							cout
									<< "  Sucesso. Comentario adicionado a lista de comentarios da App. "
									<< endl << endl;
							cout
									<< "  Prime (Enter) para regressar a lista de apps ";

							tecla = getch();
							if (tecla != 0) {
								while (tecla != 13) {
									tecla = getch();
								}
							}
							menuVisitaStoreOrdenada(mieic, state,
									apps_ordenadas, tipo_ordenacao);
						}
						if (tecla == 27) {
							menuVisitaStoreOrdenada(mieic, state,
									apps_ordenadas, tipo_ordenacao);
						}

						break;
					case -2:
						system("cls");
						cout << "  Download " << endl << endl << endl;

						while (progress <= 1.01) {
							int barWidth = 70;

							cout << "[";
							int pos = barWidth * progress;
							for (int i = 0; i < barWidth; ++i) {
								if (i < pos)
									cout << "=";
								else if (i == pos)
									cout << ">";
								else
									cout << " ";
							}
							cout << "] " << int(progress * 100.0) << " %\r";
							cout.flush();

							progress += 0.01; // for demonstration only
							Sleep(50);
						}
						cout << endl;

						while (i < 100) {
							ungetch(13);
							i++;
						}

						cout
								<< "  Download efetuado! Prima (Enter) para regressar.";

						fflush(stdin);
						cin.ignore(10000, '\n');

						tecla = getch();
						if (tecla != 0) {
							while (tecla != 13) {
								tecla = getch();
							}
						}
						menuVisitaStoreOrdenada(mieic, state, apps_ordenadas,
								tipo_ordenacao);

						break;
					case -3:
						menuVisitaStoreOrdenada(mieic, state, apps_ordenadas,
								tipo_ordenacao);
						break;
					}
				}
			}
			if (!comprado) {

				for (;;) {
					system("cls");
					system("cls");
					cout << "  Especificacoes da App  " << endl << endl << endl;
					cout << apps_ordenadas[opcao_app].imprime() << endl << endl
							<< endl;

					if (opcao_menu == 0)
						cor(WHITE, BLACK);
					cout << "  Ler Comentarios  " << endl;
					cor(BLACK, WHITE);
					if (opcao_menu == -1)
						cor(WHITE, BLACK);
					cout << "  Por no Cesto de Compras " << endl;
					cor(BLACK, WHITE);
					if (opcao_menu == -2)
						cor(WHITE, LIGHT_RED);
					cout << "  SAIR  " << endl;
					cor(BLACK, WHITE);

					opcao_menu += teclas();
					opcao_menu = RestringeOpcaoTeclas(0, 2, opcao_menu);

					bool ja_existe_no_cesto = false;
					vector<int> cesto_temp = cli_act->getCesto();
					switch (opcao_menu - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
					{
					case 0:
						// no caso de nao haver comentarios
						if (menu_comentarios.empty()) {
							cout << endl << endl
									<< "Nao ha comentarios a mostrar." << endl;
							int tecla;
							tecla = getch();
							if (tecla != 0) {
								while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
									tecla = getch();
								}

							}
							menuVisitaStoreOrdenada(mieic, state,
									apps_ordenadas, tipo_ordenacao);

						}

						//mas, se houver comentarios, entao vai exibi-los enquanto nao se carrega ESC

						system("cls");
						cout << "  Comentarios da App " << endl << endl;
						cout << "  Prima (Esc) para regressar a lista de Apps "
								<< endl << endl;
						printMenuScroll(lista_comentarios, opcao_comentario,
								MAX_PER_SCREEN);

						int tecla;
						tecla = getch();
						if (tecla != 0) {
							while (tecla != 27) //ENQUANTO DIFERENTE DE ESCAPE
							{
								tecla = getch();
								if (tecla == 72) //ACIMA
										{
									opcao_comentario--;
									if (opcao_comentario < 0)
										opcao_comentario =
												lista_comentarios.size() - 1; // se subir mais que o inicio, passa para o fim
									system("cls");
									cout << "  Comentarios da App  " << endl
											<< endl;
									cout
											<< "  Prima (Esc) para regressar a lista de Apps "
											<< endl << endl;
									printMenuScroll(lista_comentarios,
											opcao_comentario, MAX_PER_SCREEN);
								}
								if (tecla == 80) //ABAIXO
										{
									opcao_comentario++;
									if (opcao_comentario
											> (lista_comentarios.size() - 1))
										opcao_comentario = 0; // se passar o fim, volta ao inicio
									system("cls");
									cout << "  Comentarios da App  " << endl
											<< endl;
									cout
											<< "  Prima (Esc) para regressar a lista de Apps "
											<< endl << endl;
									printMenuScroll(lista_comentarios,
											opcao_comentario, MAX_PER_SCREEN);
								}
							}
						} // ao sair do ciclo e porque o user carregou escape

						menuVisitaStoreOrdenada(mieic, state, apps_ordenadas,
								tipo_ordenacao);

						break;
					case -1:

						// percorre o cesto e verifica se a app ja la esta
						for (unsigned int l = 0; l < cesto_temp.size(); l++) {
							if (cesto_temp[l]
									== apps_ordenadas[opcao_app].getId()) {
								ja_existe_no_cesto = true;
								break;
							}
							ja_existe_no_cesto = false;
						}

						if (!ja_existe_no_cesto) {
							// adiciona ao cesto do cliente atual a app que estava a ver
							cli_act->adicionaAppCesto(
									apps_ordenadas[opcao_app].getId());

							system("cls");
							cout << "  Cesto de Compras " << endl << endl
									<< endl;
							cout
									<< "  App adicionada ao cesto! Prima (Enter) para regressar."
									<< endl;

							tecla = getch();
							if (tecla != 0) {
								while (tecla != 13) {
									tecla = getch();
								}
							}
							menuVisitaStoreOrdenada(mieic, state,
									apps_ordenadas, tipo_ordenacao);
						} else if (ja_existe_no_cesto) {
							system("cls");
							cout << "  Cesto de Compras " << endl << endl
									<< endl;
							cout
									<< "  App ja pertencia ao cesto. Prima (Enter) para regressar."
									<< endl;

							tecla = getch();
							if (tecla != 0) {
								while (tecla != 13) {
									tecla = getch();
								}
							}
							menuVisitaStoreOrdenada(mieic, state,
									apps_ordenadas, tipo_ordenacao);
						}
						break;
					case -2:
						menuVisitaStoreOrdenada(mieic, state, apps_ordenadas,
								tipo_ordenacao);
						break;

					}
				}

			}
		}
		if (tecla == 27) { // volta da lista de apps para o menu anterior
			if (tipo_ordenacao == "Developer e Nome"
					|| tipo_ordenacao == "Developer e Preco") {
				menuListaDeveloper(mieic, state);
			} else {
				menuVisitaStore(mieic, state);
			}
		}
	}
}

void menuListaDeveloper(AppStore& mieic, unsigned int& state) {

	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(now);
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

	if (state == 0 || state == 1 || state == 2) { // lista de devs e menus anteriores e posteriores vao ser iguais para state 0 e 1
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
					apps_do_dev_por_nome = mieic.getApps(devs_ordenados[opcao]);
					sort(apps_do_dev_por_nome.begin(),
							apps_do_dev_por_nome.end(), appsComparaNome);
					menuVisitaStoreOrdenada(mieic, state, apps_do_dev_por_nome,
							"Developer e Nome");
					system("pause");
					break;

				case -1:          // 2a opcao
					apps_do_dev_por_preco = mieic.getApps(
							devs_ordenados[opcao]);
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

}

void menuVerDev(AppStore& mieic) {
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(now);

	if (dev_act->isEmpresa()) {
		system("cls");
		cout << "  Atributos da Empresa  " << endl << endl;
		cout << "  Prima (Esc) para regressar " << endl << endl << endl;

		cout << "  ID de Login: " << dev_act->getId() << endl;
		cout << "  Saldo: " << dev_act->getSaldo() << endl;
		cout << "  Nr. de Aplicacoes na Store: " << mieic.getNrApps(dev_act)
				<< endl;
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
		cout << "  Nr. de Aplicacoes na Store: " << mieic.getNrApps(dev_act)
				<< endl;
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
	Date data_atual(now);

	cout << "  Atributos de Cliente"
			"  " << endl << endl;
	cout << "  Prima (Esc) para regressar " << endl << endl << endl;

	cout << "  ID de Login: " << cli_act->getId() << endl;
	cout << "  Saldo: " << cli_act->getSaldo() << " euros" << endl;
	cout << "  Nome: " << cli_act->getNome() << endl;
	cout << "  Idade: " << cli_act->getIdade() << endl;
	cout << "  Sexo: " << cli_act->getSexo() << endl;
	cout << "  Nr. Cartao de Credito: " << "*********" << endl;
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

void menuCriarApp(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(now);

	bool nomeRepetido = false;
	bool inputFail;
	string nome_app, categoria, descricao;
	double preco;

	do {
		system("cls");
		cout << "  Criar Apps - Insira os dados da App que pretende criar  "
				<< endl << endl << endl;
		cout << "  Indique o seu nome da App: ";
		fflush(stdin);
		getline(cin, nome_app);
	} while (nome_app == "");

	do {
		system("cls");
		cout << "  Criar Apps - Insira os dados da App que pretende criar  "
				<< endl << endl << endl;
		cout << "  Indique o seu nome da App: " << nome_app << endl;
		cout << "  Indique a categoria em que se insere: ";

		fflush(stdin);
		getline(cin, categoria);
	} while (categoria == "");

	do {
		system("cls");
		cout << "  Criar Apps - Insira os dados da App que pretende criar  "
				<< endl << endl << endl;
		cout << "  Indique o seu nome da App: " << nome_app << endl;
		cout << "  Indique a categoria em que se insere: " << categoria << endl;
		cout << "  Faca uma pequena descricao da App: ";
		fflush(stdin);
		getline(cin, descricao);
	} while (descricao == "");

	do {
		system("cls");
		cout << "  Criar Apps - Insira os dados da App que pretende criar  "
				<< endl << endl << endl;
		cout << "  Indique o seu nome da App: " << nome_app << endl;
		cout << "  Indique a categoria em que se insere: " << categoria << endl;
		cout << "  Faca uma pequena descricao da App: " << descricao << endl;
		cout << "  Indique o preco da App:  ";

		cin >> preco;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	system("cls");
	cout << "  Criar Apps - Insira os dados da App que pretende criar  " << endl
			<< endl << endl;
	cout << "  Indique o seu nome da App: " << nome_app << endl;
	cout << "  Indique a categoria em que se insere: " << categoria << endl;
	cout << "  Faca uma pequena descricao da App: " << descricao << endl;
	cout << "  Indique o preco da App:  " << preco;
	cout << endl << endl << endl;
	cout
			<< "  Prima (Enter) para validar a criacao ou (Esc) para regressar sem criar a App  "
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
		nomeRepetido = mieic.existeNomeApp(nome_app);

		if (!nomeRepetido) { // se nome nao for repetido, sucesso!

			App app_temp(nome_app, categoria, descricao, preco);
			app_temp.setDev(dev_act);
			mieic.apps.push_back(app_temp);

			cout << "  Sucesso! App criada. " << endl << endl;
			cout << "  Prima (Enter) para continuar  " << endl;
			tecla = getch();
			if (tecla != 0) {
				while (tecla != 13) { // enquanto nao prime enter para continuar
					tecla = getch();
				}
				menuDeveloperGerirApps(mieic);
			}
		} else if (nomeRepetido) { // se o nome for repetido, retry ou regressa
			cout << "  App invalida! Uma App com esse nome ja existe. " << endl
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
				menuCriarApp(mieic);
			else if (tecla == 27)
				menuDeveloperGerirApps(mieic);
		}

	} else if (tecla == 27) {  // se o user premir (Esc)
		menuDeveloperGerirApps(mieic);
	}
}

void menuRemoverApp(AppStore& mieic) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(now);
	int opcao = 0;
	bool passCerta = false; // default para false

// vai buscar apps do dev e ordena-as por nome
	vector<App> apps_ordenadas = mieic.getApps(dev_act);
	sort(apps_ordenadas.begin(), apps_ordenadas.end(), appsComparaNome);

//Vai criar a lista de opcoes com o nome das Apps do developer atual
	vector<string> menu_options = getAppNames(apps_ordenadas);

	if (apps_ordenadas.empty()) {
		system("cls");
		cout << "  Remover Apps " << endl << endl;
		cout << "  Prima (Esc) para regressar  " << endl << endl;

		cout << endl << endl << endl << "  Nao ha Apps para mostrar  " << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
				tecla = getch();
			}

		}
		menuDeveloperGerirApps(mieic);
	} else {

		cout << "  Remover Apps " << endl << endl;
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
						opcao = menu_options.size() - 1; // se subir mais que o inicio, passa para o fim
					system("cls");
					cout << "  Remover Apps " << endl << endl;
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
					cout << "  Remover Apps " << endl << endl;
					cout
							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
				}
			}
		}
		if (tecla == 13) {

			passCerta = verificaPass(dev_act);

			if (passCerta) {
				system("cls");
				cout << "  Remover Apps " << endl << endl << endl << endl;
				cout << "  Sucesso! App removida.  " << endl << endl;
				cout << "  Prima (Enter) para continuar " << endl << endl;

				//pesquisa nas vendas se alguma estava associada a esta App
				//se alguma estivesse, poe app_apagada como true
				for (unsigned int k = 0; k < mieic.vendas.size(); k++) {
					if (mieic.vendas[k].getAppVendidaId()
							== mieic.apps[opcao].getId()) { // encontrou uma venda a qual esta app pertencia
						mieic.vendas[k].setAppApagada(true);
						break;
					}
				}

				unsigned int id_app_a_remover = apps_ordenadas[opcao].getId();

				// Pesquisa no vetor das apps da appstore qual vai remover.
				for (unsigned int j = 0; j < mieic.apps.size(); j++) {
					if (id_app_a_remover == mieic.apps[j].getId()) {
						mieic.apps.erase(mieic.apps.begin() + j); // Usa o indice encontrado para a remover
						break;
					}
				}

				tecla = getch();
				if (tecla != 0) {
					while (tecla != 13) { // enquanto nao prime enter para continuar
						tecla = getch();
					}
				}
				menuRemoverApp(mieic);

			} else if (!passCerta) {
				system("cls");
				cout << "  Remover Apps " << endl << endl;
				cout << "  Password errada.  " << endl;

				tecla = getch();
				if (tecla != 0) {
					while (tecla != 13) { // enquanto nao prime enter para continuar
						tecla = getch();
					}
				}
				menuRemoverApp(mieic);

			}
		}
		if (tecla == 27) {
			menuDeveloperGerirApps(mieic);
		}

	}

}

void menuModificarApp(AppStore& mieic) {

	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(now);
	int opcao = 0;
	string nome_novo, categoria_nova, descricao_nova;
	double preco_novo;
	bool passCerta = false; // default para false

// vai buscar apps do dev e ordena-as por nome
	vector<App> apps_ordenadas = mieic.getApps(dev_act);
	sort(apps_ordenadas.begin(), apps_ordenadas.end(), appsComparaNome);

//Vai criar a lista de opcoes com o nome das Apps do developer atual
	vector<string> menu_options = getAppNames(apps_ordenadas);

	if (apps_ordenadas.empty()) {
		system("cls");
		cout << "  Modificar Apps " << endl << endl;
		cout << "  Prima (Esc) para regressar  " << endl << endl;

		cout << endl << endl << endl << "  Nao ha Apps para mostrar  " << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
				tecla = getch();
			}

		}
		menuDeveloperGerirApps(mieic);
	} else {

		cout << "  Modificar Apps " << endl << endl;
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
						opcao = menu_options.size() - 1; // se subir mais que o inicio, passa para o fim
					system("cls");
					cout << "  Modificar Apps " << endl << endl;
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
					cout << "  Modificar Apps " << endl << endl;
					cout
							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
				}
			}
		}
		//neste ponto ja tem a app selecionada
		if (tecla == 13) {

			passCerta = verificaPass(dev_act);
			if (passCerta) {
				system("cls");

				time_t t = time(0);
				struct tm *now = localtime(&t);
				Date data_atual(now);
				int opcao2 = 0;
				bool inputFail = false;

				for (;;) {
					system("cls");
					cout
							<< "  Escolha o atributo que pretende modificar na App  "
							<< endl << endl;

					if (opcao2 == 0)
						cor(WHITE, BLACK);
					cout << "  Modificar Nome  " << endl;
					cor(BLACK, WHITE);
					if (opcao2 == -1)
						cor(WHITE, BLACK);
					cout << "  Modificar Categoria " << endl;
					cor(BLACK, WHITE);
					if (opcao2 == -2)
						cor(WHITE, BLACK);
					cout << "  Modificar Descricao  " << endl;
					cor(BLACK, WHITE);
					if (opcao2 == -3)
						cor(WHITE, BLACK);
					cout << "  Modificar Preco  " << endl;
					cor(BLACK, WHITE);
					if (opcao2 == -4)
						cor(WHITE, LIGHT_RED);
					cout << "  SAIR  " << endl;
					cor(BLACK, WHITE);

					opcao2 += teclas();
					opcao2 = RestringeOpcaoTeclas(0, 4, opcao2);
					int tecla2;

					switch (opcao2 - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
					{
					case 0:          // 1a opcao
						do {
							system("cls");
							cout << "  Modificar nome da App  " << endl << endl
									<< endl;
							cout << "  Escolha um novo nome para a App: ";
							fflush(stdin);
							getline(cin, nome_novo);
						} while (nome_novo == "");

						system("cls");
						cout << "  Modificar nome da App  " << endl << endl
								<< endl;
						cout << "  Escolha um novo nome para a App: "
								<< nome_novo << endl << endl << endl;
						cout
								<< "  Prima (Enter) para validar ou (Esc) para regressar sem modificar  "
								<< endl << endl;

						tecla2 = getch();
						if (tecla2 != 0) {
							while (tecla2 != 13 && tecla2 != 27) {
								tecla2 = getch();
							}
						}
						if (tecla2 == 13) { // se o user premir (Enter), valida mudanca

							mieic.apps[opcao].setNome(nome_novo);

							cout << "  Sucesso! O nome da App foi modificado "
									<< endl << endl;
							cout << "  Prima enter para continuar  " << endl;
							tecla2 = getch();
							if (tecla2 != 0) {
								while (tecla2 != 13) { // enquanto nao prime enter para continuar
									tecla2 = getch();
								}
								menuModificarApp(mieic);
							}

						} else if (tecla2 == 27) { // se o user premir (Esc)
							menuModificarApp(mieic);
						}
						break;
					case -1:          // 1a opcao
						do {
							system("cls");
							cout << "  Modificar categoria da App  " << endl
									<< endl << endl;
							cout << "  Escolha uma nova categoria para a App: ";
							fflush(stdin);
							getline(cin, categoria_nova);
						} while (categoria_nova == "");

						system("cls");
						cout << "  Modificar categoria da App  " << endl << endl
								<< endl;
						cout << "  Escolha uma nova categoria para a App: "
								<< categoria_nova << endl << endl << endl;
						cout
								<< "  Prima (Enter) para validar ou (Esc) para regressar sem modificar  "
								<< endl << endl;
						tecla2 = getch();
						if (tecla2 != 0) {
							while (tecla2 != 13 && tecla2 != 27) {
								tecla2 = getch();
							}
						}
						if (tecla2 == 13) { // se o user premir (Enter), valida mudanca

							mieic.apps[opcao].setCategoria(categoria_nova);

							cout
									<< "  Sucesso! A categoria da App foi modificada "
									<< endl << endl;
							cout << "  Prima enter para continuar  " << endl;
							tecla2 = getch();
							if (tecla2 != 0) {
								while (tecla2 != 13) { // enquanto nao prime enter para continuar
									tecla2 = getch();
								}
								menuModificarApp(mieic);
							}

						} else if (tecla2 == 27) { // se o user premir (Esc)
							menuModificarApp(mieic);
						}
						break;
					case -2:          // 2a opcao
						do {
							system("cls");
							cout << "  Modificar descricao da App  " << endl
									<< endl << endl;
							cout << "  Escolha uma descricao nova para a App: ";
							fflush(stdin);
							getline(cin, descricao_nova);
						} while (descricao_nova == "");

						system("cls");
						cout << "  Modificar descricao da App  " << endl << endl
								<< endl;
						cout << "  Escolha uma nova descricao para a App: "
								<< descricao_nova << endl << endl << endl;
						cout
								<< "  Prima (Enter) para validar ou (Esc) para regressar sem modificar  "
								<< endl << endl;

						tecla2 = getch();
						if (tecla2 != 0) {
							while (tecla2 != 13 && tecla2 != 27) {
								tecla2 = getch();
							}
						}
						if (tecla2 == 13) { // se o user premir (Enter), valida mudanca

							mieic.apps[opcao].setDescricao(descricao_nova);

							cout
									<< "  Sucesso! A descricao da App foi modificada "
									<< endl << endl;
							cout << "  Prima enter para continuar  " << endl;
							tecla2 = getch();
							if (tecla2 != 0) {
								while (tecla2 != 13) { // enquanto nao prime enter para continuar
									tecla2 = getch();
								}
								menuModificarApp(mieic);
							}

						} else if (tecla2 == 27) { // se o user premir (Esc)
							menuModificarApp(mieic);
						}
						break;
					case -3:          // 4a opcao
						do {
							system("cls");
							cout << "  Modificar preco da App  " << endl << endl
									<< endl;
							cout << "  Escolha um novo preco para a App: ";
							cin >> preco_novo;

							inputFail = cin.fail();
							cin.clear();  // da clear a flag do fail
							cin.ignore(1000, '\n');
						} while (inputFail == true);

						system("cls");
						cout << "  Modificar preco da App  " << endl << endl
								<< endl;
						cout << "  Escolha um novo preco para a App: "
								<< nome_novo << endl << endl << endl;
						cout
								<< "  Prima (Enter) para validar ou (Esc) para regressar sem modificar  "
								<< endl << endl;

						tecla2 = getch();
						if (tecla2 != 0) {
							while (tecla2 != 13 && tecla2 != 27) {
								tecla2 = getch();
							}
						}
						if (tecla2 == 13) { // se o user premir (Enter), valida mudanca

							mieic.apps[opcao].setPreco(preco_novo);

							cout << "  Sucesso! O preco da App foi modificado "
									<< endl << endl;
							cout << "  Prima enter para continuar  " << endl;
							tecla2 = getch();
							if (tecla2 != 0) {
								while (tecla2 != 13) { // enquanto nao prime enter para continuar
									tecla2 = getch();
								}
								menuModificarApp(mieic);
							}

						} else if (tecla2 == 27) { // se o user premir (Esc)
							menuModificarApp(mieic);
						}
						break;
					case -4:          // 5a opcao
						menuModificarApp(mieic);          //
						system("pause");
						break;
					}
				}
			} else if (!passCerta) {
				system("cls");
				cout << "  Modificar Apps " << endl << endl;
				cout << "  Prima (Enter) para continuar " << endl << endl;
				cout << "  Password errada. Tente novamente.  " << endl;

				tecla = getch();
				if (tecla != 0) {
					while (tecla != 13) { // enquanto nao prime enter para continuar
						tecla = getch();
					}
				}
				menuModificarApp(mieic);

			}
		}
		if (tecla == 27) {
			menuDeveloperGerirApps(mieic);
		}

	}
}

void menuCheckoutApps(AppStore& mieic) {
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(now);

	int opcao_cesto = 0;

	apagaAppsNaoExistentes(mieic, cli_act);
	vector<int> ids_apps_cesto = cli_act->getCesto();
	vector<string> menu_options;
	double preco_total = 0;
	double saldo_disponivel = cli_act->getSaldo();
	// Cria vector com nomes de apps.
	for (unsigned int k = 0; k < ids_apps_cesto.size(); k++) {
		for (unsigned int p = 0; p < mieic.apps.size(); p++) {
			if (ids_apps_cesto[k] == mieic.apps[p].getId()) {
				stringstream ss;
				string preco;
				ss << mieic.apps[p].getPreco();
				ss >> preco;
				preco_total += mieic.apps[p].getPreco(); //  vai somando ao preço total das apps
				string temp_str = " Preco: " + preco + "   Nome: "
						+ mieic.apps[p].getNome();
				menu_options.push_back(temp_str);
				break;
			}
		}
	}

	if (cli_act->getCesto().size() == 0) {
		system("cls");
		cout << "  Apps do Cesto " << endl << endl;
		cout << "  Prima (Esc) para regressar  " << endl << endl;
		cout << "  Nao ha apps no cesto.";

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 27) {
				tecla = getch();
			}
		}
		menuCestoCompras(mieic);
	}

	system("cls");
	cout << "  Apps do Cesto - Ver e Checkout " << endl << endl;
	cout
			<< "  Prima (Enter) para  fazer checkout das apps ou (Esc) para regressar  "
			<< endl << endl;
	printMenuScroll(menu_options, opcao_cesto, MAX_PER_SCREEN);
	cout << endl << endl;
	cor(WHITE, BLACK);
	cout << "  Custo Total: " << preco_total << "  Custo Total c/ Voucher: "
			<< preco_total * 0.95 << "   Saldo Disponivel: " << saldo_disponivel
			<< " " << endl;
	cor(BLACK, WHITE);
	porDataNoCanto(mieic.DataAtual(), 1, 23);

	int tecla;
	tecla = getch();
	if (tecla != 0) {
		while (tecla != 27 && tecla != 13) //ENQUANTO DIFERENTE DE ENTER E ESCAPE
		{
			tecla = getch();
			if (tecla == 72) //ACIMA
					{
				opcao_cesto--;
				if (opcao_cesto < 0)
					opcao_cesto = menu_options.size() - 1; // se subir mais que o inicio, passa para o fim
				system("cls");
				cout << "  Apps do Cesto - Ver e Checkout " << endl << endl;
				cout
						<< "  Prima (Enter) para  fazer checkout das apps ou (Esc) para regressar  "
						<< endl << endl;
				printMenuScroll(menu_options, opcao_cesto, MAX_PER_SCREEN);
				cout << endl << endl;
				cor(WHITE, BLACK);
				cout << "  Custo Total: " << preco_total
						<< "  Custo Total c/ Voucher: " << preco_total * 0.95
						<< "   Saldo Disponivel: " << saldo_disponivel << " "
						<< endl;
				cor(BLACK, WHITE);
				porDataNoCanto(mieic.DataAtual(), 1, 23);
			}
			if (tecla == 80) //ABAIXO
					{
				opcao_cesto++;
				if (opcao_cesto > (menu_options.size() - 1))
					opcao_cesto = 0; // se passar o fim, volta ao inicio
				system("cls");
				cout << "  Apps do Cesto - Ver e Checkout " << endl << endl;
				cout
						<< "  Prima (Enter) para  fazer checkout das apps ou (Esc) para regressar  "
						<< endl << endl;
				printMenuScroll(menu_options, opcao_cesto, MAX_PER_SCREEN);
				cout << endl << endl;
				cor(WHITE, BLACK);
				cout << "  Custo Total: " << preco_total
						<< "  Custo Total c/ Voucher: " << preco_total * 0.95
						<< "   Saldo Disponivel: " << saldo_disponivel << " "
						<< endl;
				cor(BLACK, WHITE);
				porDataNoCanto(mieic.DataAtual(), 1, 23);
			}
		}
	}
	if (tecla == 13) {
		if (cli_act->getVouchers() > 0) { // Se tiver vouchers, a store pergunta se quer usar
			int opcao = 0;
			for (;;) {
				system("cls");
				porDataNoCanto(mieic.DataAtual(), 1, 23);
				cout << "  Apps do Cesto - Ver e Checkout " << endl << endl;
				cout
						<< "  Tem Vouchers de desconto disponiveis. Pretende usar um Voucher?"
						<< endl << endl << endl;

				if (opcao == 0)
					cor(WHITE, BLACK);
				cout << "  Sim  " << endl;
				cor(BLACK, WHITE); // apos imprimir com a cor anterior, da reset à cor para o normal
				if (opcao == -1)
					cor(WHITE, BLACK);
				cout << "  Nao " << endl;
				cor(BLACK, WHITE);
				if (opcao == -2)
					cor(WHITE, LIGHT_RED);
				cout << "  SAIR  " << endl;
				cor(BLACK, WHITE);

				opcao += teclas();
				opcao = RestringeOpcaoTeclas(0, 2, opcao); //MUDAR  de 3 para o numero total de opções-1 do menu.

				switch (opcao - 13) //sempre que se adicionar mais opções, adicionar mais um case (ex: case -4: return 0; break;)
				{
				case 0:
					if (preco_total * 0.95 > saldo_disponivel) { // Compra nao efetuada
						system("cls");
						cout << "  Apps do Cesto - Ver e Checkout " << endl
								<< endl << endl;
						cout
								<< "  Compra nao efetuada. Saldo disponivel insuficiente."
								<< endl << endl;
						cout << "  Prima (Esc) para regressar  " << endl;
						int tecla;
						tecla = getch();
						if (tecla != 0) {
							while (tecla != 27) {
								tecla = getch();
							}
						}
						menuCheckoutApps(mieic);
					} else if (preco_total * 0.95 <= saldo_disponivel) {
						// Retira o preço a pagar ao saldo do cliente
						cli_act->setSaldo(
								cli_act->getSaldo() - preco_total * 0.95);
						cli_act->addVoucher();
						cli_act->emptyCesto();

						// Para cada app, vai ao developer e da-lhe a sua parte do dinheiro
						for (unsigned int k = 0; k < ids_apps_cesto.size();
								k++) {
							for (unsigned int p = 0; p < mieic.apps.size();
									p++) {
								if (ids_apps_cesto[k]
										== mieic.apps[p].getId()) {
									mieic.apps[p].getDev()->addSaldo(
											mieic.apps[p].getPreco() * 0.8);
									Vendas venda_temp(
											mieic.apps[p].getPreco() * 0.95,
											data_atual,
											mieic.apps[p].getNome());
									venda_temp.setAppVendidaId(
											mieic.apps[p].getId());
									mieic.vendas.push_back(venda_temp);
									cli_act->adicionarVenda(
											&mieic.vendas[mieic.vendas.size()
													- 1]);
									break;
								}
							}
						}
						system("cls");
						cout << "  Apps do Cesto - Ver e Checkout " << endl
								<< endl << endl;
						cout
								<< "  Compra efetuada! Recebeu um Voucher de desconto para a proxima compra."
								<< endl;
						cout << "  Tem saldo restante de "
								<< cli_act->getSaldo() << " euros." << endl
								<< endl;
						cout << "  Prima (Enter) para continuar  " << endl;
						int tecla;
						tecla = getch();
						if (tecla != 0) {
							while (tecla != 13) {
								tecla = getch();
							}
						}
						menuCheckoutApps(mieic);
					}
					system("pause");

					break;
				case -1:
					if (preco_total > saldo_disponivel) { // Compra nao efetuada
						system("cls");
						cout << "  Apps do Cesto - Ver e Checkout " << endl
								<< endl << endl;
						cout
								<< "  Compra nao efetuada. Saldo disponivel insuficiente."
								<< endl << endl;
						cout << "  Prima (Esc) para regressar  " << endl;
						int tecla;
						tecla = getch();
						if (tecla != 0) {
							while (tecla != 27) {
								tecla = getch();
							}
						}
						menuCheckoutApps(mieic);
					} else if (preco_total <= saldo_disponivel) {
						cli_act->setSaldo(cli_act->getSaldo() - preco_total);
						cli_act->addVoucher();
						cli_act->emptyCesto();

						// Para cada app, vai ao developer e da-lhe a sua parte do dinheiro
						for (unsigned int k = 0; k < ids_apps_cesto.size();
								k++) {
							for (unsigned int p = 0; p < mieic.apps.size();
									p++) {
								if (ids_apps_cesto[k]
										== mieic.apps[p].getId()) {
									mieic.apps[p].getDev()->addSaldo(
											mieic.apps[p].getPreco() * 0.8);
									Vendas venda_temp(mieic.apps[p].getPreco(),
											data_atual,
											mieic.apps[p].getNome());
									venda_temp.setAppVendidaId(
											mieic.apps[p].getId());
									mieic.vendas.push_back(venda_temp);
									cli_act->adicionarVenda(
											&mieic.vendas[mieic.vendas.size()
													- 1]);
									break;
								}
							}
						}
						system("cls");
						cout << "  Apps do Cesto - Ver e Checkout " << endl
								<< endl << endl;
						cout
								<< "  Compra efetuada! Recebeu um Voucher de desconto para a proxima compra."
								<< endl;
						cout << "  Tem saldo restante de "
								<< cli_act->getSaldo() << " euros." << endl
								<< endl;
						cout << "  Prima (Enter) para continuar  " << endl;
						int tecla;
						tecla = getch();
						if (tecla != 0) {
							while (tecla != 13) {
								tecla = getch();
							}
						}
						menuCheckoutApps(mieic);

					}

					system("pause");
					break;
				case -2:
					return;
					//menuCheckoutApps(mieic);
					break;
				}
			}

		} else if (cli_act->getVouchers() == 0) { // NO CASO DE NAO TER VOUCHERS == CASO NAO USAR
			if (preco_total > saldo_disponivel) {
				system("cls");
				cout << "  Apps do Cesto - Ver e Checkout " << endl << endl
						<< endl;
				cout << "  Compra nao efetuada. Saldo disponivel insuficiente."
						<< endl << endl;
				cout << "  Prima (Esc) para regressar  " << endl;
				int tecla;
				tecla = getch();
				if (tecla != 0) {
					while (tecla != 27) {
						tecla = getch();
					}
				}
				menuCheckoutApps(mieic);
			} else if (preco_total <= saldo_disponivel) {
				cli_act->setSaldo(cli_act->getSaldo() - preco_total);
				cli_act->addVoucher();
				cli_act->emptyCesto();

				// Para cada app, vai ao developer e da-lhe a sua parte do dinheiro
				for (unsigned int k = 0; k < ids_apps_cesto.size(); k++) {
					for (unsigned int p = 0; p < mieic.apps.size(); p++) {
						if (ids_apps_cesto[k] == mieic.apps[p].getId()) {
							mieic.apps[p].getDev()->addSaldo(
									mieic.apps[p].getPreco() * 0.8);
							Vendas venda_temp(mieic.apps[p].getPreco(),
									data_atual, mieic.apps[p].getNome());
							venda_temp.setAppVendidaId(mieic.apps[p].getId());
							mieic.vendas.push_back(venda_temp);
							cli_act->adicionarVenda(
									&mieic.vendas[mieic.vendas.size() - 1]);
							break;
						}
					}
				}
				system("cls");
				cout << "  Apps do Cesto - Ver e Checkout " << endl << endl
						<< endl;
				cout
						<< "  Compra efetuada! Recebeu um Voucher de desconto para a proxima compra."
						<< endl;
				cout << "  Tem saldo restante de " << cli_act->getSaldo()
						<< " euros." << endl << endl;
				cout << "  Prima (Enter) para continuar  " << endl;
				int tecla;
				tecla = getch();
				if (tecla != 0) {
					while (tecla != 13) {
						tecla = getch();
					}
				}
				menuCheckoutApps(mieic);

			}

		}
	}
	if (tecla == 27) {
		menuCestoCompras(mieic);
	}
}

void menuTiraAppsCesto(AppStore& mieic) {

	int opcao_cesto = 0;

	apagaAppsNaoExistentes(mieic, cli_act);
//
//	// vao ser apagadas do cesto as apps que ja que nao existirem
//	for (unsigned int i = 0; i < cli_act->getCesto().size(); i++) {
//		existe_app = false;   // reset ao existe app - verifica proxima
//		for (unsigned int j = 0; j < mieic.apps.size(); j++) {
//			if (cli_act->getCesto()[i] == mieic.apps[j].getId()) {
//				existe_app = true;
//				break; // Se for igual e porque existe -> passa a verificar o proximo item do cesto
//			}
//
//		}
//		if (!existe_app) {
//			cli_act->eliminaAppCesto(i);
//			i--;
//		}
//	}
// Neste ponto ja apagou do cesto as apps que ja nao existiam
	vector<int> ids_apps_cesto = cli_act->getCesto();
	vector<string> menu_options;

// Cria vector com nomes de apps.
	for (unsigned int k = 0; k < ids_apps_cesto.size(); k++) {
		for (unsigned int p = 0; p < mieic.apps.size(); p++) {
			if (ids_apps_cesto[k] == mieic.apps[p].getId()) {
				stringstream ss;
				string preco;
				ss << mieic.apps[p].getPreco();
				ss >> preco;
				string temp_str = " Preco: " + preco + "   Nome: "
						+ mieic.apps[p].getNome();
				menu_options.push_back(temp_str);
			}
		}
	}

	if (cli_act->getCesto().size() == 0) {
		system("cls");
		cout << "  Remover Apps do Cesto " << endl << endl;
		cout << "  Prima (Esc) para regressar  " << endl << endl;
		cout << "  Nao ha apps no cesto.";

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 27) {
				tecla = getch();
			}
		}
		menuCestoCompras(mieic);
	}

	system("cls");
	cout << " Remover Apps do Cesto " << endl << endl;
	cout
			<< "  Prima (Enter) para selecionar uma app para apagar ou (Esc) para regressar  "
			<< endl << endl;
	printMenuScroll(menu_options, opcao_cesto, MAX_PER_SCREEN);

	int tecla;
	tecla = getch();
	if (tecla != 0) {
		while (tecla != 13 && tecla != 27) //ENQUANTO DIFERENTE DE ENTER E ESCAPE
		{
			tecla = getch();
			if (tecla == 72) //ACIMA
					{
				opcao_cesto--;
				if (opcao_cesto < 0)
					opcao_cesto = menu_options.size() - 1; // se subir mais que o inicio, passa para o fim
				system("cls");
				cout << " Remover Apps do Cesto " << endl << endl;
				cout
						<< "  Prima (Enter) para selecionar uma app para apagar ou (Esc) para regressar  "
						<< endl << endl;
				printMenuScroll(menu_options, opcao_cesto, MAX_PER_SCREEN);
			}
			if (tecla == 80) //ABAIXO
					{
				opcao_cesto++;
				if (opcao_cesto > (menu_options.size() - 1))
					opcao_cesto = 0; // se passar o fim, volta ao inicio
				system("cls");
				cout << " Remover Apps do Cesto " << endl << endl;
				cout
						<< "  Prima (Enter) para selecionar uma app para apagar ou (Esc) para regressar  "
						<< endl << endl;
				printMenuScroll(menu_options, opcao_cesto, MAX_PER_SCREEN);
			}
		}
	}
	if (tecla == 13) {
		//contando que menu_options tem o mesmo nr. de items que o cesto
		//uma vez que se apagaram do cesto apps que desapareceram e menu_options foi criado a partir do cesto
		cli_act->eliminaAppCesto(opcao_cesto);
		menuTiraAppsCesto(mieic);
	}
	if (tecla == 27) {
		menuCestoCompras(mieic);
	}

}

void apagaAppsNaoExistentes(AppStore& mieic, Cliente* cli) {

	bool existe_app = false;

// vao ser apagadas do cesto as apps que ja que nao existirem
	for (unsigned int i = 0; i < cli->getCesto().size(); i++) {
		existe_app = false;   // reset ao existe app - verifica proxima
		for (unsigned int j = 0; j < mieic.apps.size(); j++) {
			if (cli->getCesto()[i] == mieic.apps[j].getId()) {
				existe_app = true;
				break; // Se for igual e porque existe -> passa a verificar o proximo item do cesto
			}

		}
		if (!existe_app) {
			cli->eliminaAppCesto(i);
			i--;
		}
	}
}
