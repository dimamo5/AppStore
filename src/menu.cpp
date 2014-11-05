#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "menu.h"

using namespace std;

vector<string> getAppNames(vector<App> apps) {
	vector<string> app_names;
	for (unsigned int i = 0; i < apps.size(); i++) {
		app_names.push_back(apps[i].getNome());
	}
	return app_names;
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
		if (i == selected_option)
			temp = "  -> " + options[i];
		else
			temp = "     " + options[i];

		cout << temp;
		cout << endl << endl;
	}
}

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
			cor(112);
		cout << "  Visitar AppStore  " << endl;
		cor(7);
		if (opcao == -1)
			cor(112);
		cout << "  Login na AppStore  " << endl;
		cor(7);
		if (opcao == -2)
			cor(112);
		cout << "  Registar na AppStore  " << endl;
		cor(7);
		if (opcao == -3)
			cor(124);
		cout << "  SAIR  " << endl;
		cor(7);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 3, opcao); //MUDAR  de 3 para o numero total de opções-1 do menu.

		switch (opcao - 13) //sempre que se adicionar mais opções, adicionar mais um case (ex: case -4: return 0; break;)
		{
		case 0:
			// COMO LISTAR APPS ALFABETICAMENTE, POR PRECO E POR DEV:
			// na lista de apps vai ser precisa uma funcao que imprime todas por ordem.
			// Para ficarem ordenadas alfabeticamente, e necessario o operador < , que vai
			// comparar so as strings dos nomes das apps. Depois pode-se criar um vetor cópia
			// (ou usar original) das apps e usar o sort nesse vetor e imprimir.
			// Cria-se uma funcao entao que imprime e que vai ter uma variavel "opcao" que
			// varia quando andamos com as setas. Ao carregar enter retorna essa opcao
			// (que vai ser o indice no vetor, da app selecionada).
			// ps: a funcao podera receber como argumento o tal vetor copiado e sorted
			// depois e so usar esse indice retornado para imprimir no ecra as infos dessa app
			// e aceder ao que for preciso dela. No caso de ordenacao de app por developer
			// vai ser preciso criar um vetor de apps desse  developer a partir do vetor
			// de todas as apps existentes (a qual se podera fazer sort alfabetico depois).
			// Isto e feito listando os developers e usando
			// o metodo acima para ter o indice do developer pretendido. Ou seja, navega-se
			// pelos developers e vai haver uma funcao que retorna a opcao/indice quando
			// se carrega no enter. Depois usa-se esse developer para pesquisar as apps dele
			// e ir adicionando-as a um vetor temporario (ao qual se podera fazer sort).
			// ps: alternativamente à lista de apps alfabeticamente e por dev, poder-se-a
			// tambem listar por preco. Basta mudar as apps para estarem sorted por preco
			// o que significa que se tem de fazer um operador que compare precos

			menuVisitaStore(mieic, state);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;

		case -1:         // 2a opcao
			menuLogin(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -2:        // 3a opcao
			menuRegistar(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -3:        // ultima opcao
			// E NECESSARIO CHAMAR OS SAVES DE FICHEIROS AQUI!!!!!!!!
			exit(0);
			return 0; // indica ao menu que o programa vai fechar
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
			cor(112);
		cout << "  Cliente  " << endl;
		cor(7);
		if (opcao == -1)
			cor(112);
		cout << "  Developer " << endl;
		cor(7);
		if (opcao == -2)
			cor(124);
		cout << "  SAIR  " << endl;
		cor(7);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 2, opcao);

		switch (opcao - 13) //sempre que se adicionar mais opções, adicionar mais um case (ex: case -4: return 0; break;)
		{
		case 0:
			menuLoginCliente(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;

		case -1:         // 2a opcao
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
			cor(112);
		cout << "  Cliente  " << endl;
		cor(7);

		if (opcao == -1)
			cor(112);
		cout << "  Developer Individual  " << endl;
		cor(7);

		if (opcao == -2)
			cor(112);
		cout << "  Developer Empresa  " << endl;
		cor(7);

		if (opcao == -3)
			cor(124);
		cout << "  SAIR  " << endl;
		cor(7);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 3, opcao);

		switch (opcao - 13) //sempre que se adicionar mais opções, adicionar mais um case (ex: case -4: return 0; break;)
		{
		case 0:
			menuRegistarCliente(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;

		case -1:         // 2a opcao
			menuRegistarDeveloperIndividual(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -2:         // 2a opcao
			menuRegistarDeveloperEmpresa(mieic);
			system("pause");
			return 1; // indica ao menu que ainda vai continuar o programa
			break;
		case -3:        // 3a opcao
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
				menuCliente(mieic); // continua para o menu de Cliente
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
				menuInicial(mieic);  // desistir do login
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
				menuDeveloper(mieic); // segue para o menu de Dev
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
		cin.clear();  // da clear a flag do fail
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
	string nome, morada, password;

	do {
		system("cls");
		cout << "  Insira os seus dados para registo de developer  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome: ";
		fflush(stdin);
		getline(cin, nome);
	} while (nome == "");

	do {
		system("cls");
		cout << "  Insira os seus dados para registo de developer  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome: " << nome << endl;
		cout << "  Indique a sua morada: ";
		fflush(stdin);
		getline(cin, morada);
	} while (morada == "");

	do {
		system("cls");
		cout << "  Insira os seus dados para registo de developer  " << endl
				<< endl << endl;
		cout << "  Indique o seu nome: " << nome << endl;
		cout << "  Indique a sua morada: " << morada << endl << endl;
		cout << "  Introduza agora a password que pretende:  ";

		cin >> password;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	system("cls");
	cout << "  Insira os seus dados para registo de developer  " << endl << endl
			<< endl;
	cout << "  Indique o seu nome: " << nome << endl;
	cout << "  Indique a sua morada: " << morada << endl << endl;
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

		// verifica se na appstore mieic ja ha algum developer com este nome
		nomeRepetido = mieic.existeNomeDev(nome);

		if (!nomeRepetido) { // se nome nao for repetido, sucesso!

			Developer* individ_temp = new Individual(nome, password, morada);
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
	string nome, password;
	string NIF;

	do {
		system("cls");
		cout << "  Insira os dados para registo da empresa  " << endl << endl
				<< endl;
		cout << "  Indique o nome da empresa: ";
		fflush(stdin);
		getline(cin, nome);

	} while (nome == "");

	do {
		system("cls");
		cout << "  Insira os dados para registo da empresa  " << endl << endl
				<< endl;
		cout << "  Indique o nome da empresa: " << nome << endl;
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
		cout << "  Indique o nome da empresa: " << nome << endl;
		cout << "  Indique o NIF da empresa: " << NIF << endl << endl;
		cout << "  Introduza agora a password que pretende:  ";

		cin >> password;

		inputFail = cin.fail();
		cin.clear();  // da clear a flag do fail
		cin.ignore(1000, '\n');
	} while (inputFail == true);

	system("cls");
	cout << "  Insira os dados para registo da empresa  " << endl << endl
			<< endl;
	cout << "  Indique o nome da empresa: " << nome << endl;
	cout << "  Indique o NIF da empresa: " << NIF << endl << endl;
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

		// verifica se na appstore mieic ja ha algum developer com este nome
		nomeRepetido = mieic.existeNomeDev(nome);

		if (!nomeRepetido) { // se nome nao for repetido, sucesso!

			Developer* empresa_temp = new Empresa(nome, password, NIF);
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
			cor(112);
		cout << "  Entrar na AppStore  " << endl; // fazer listagem por apps compradas
		cor(7);
		if (opcao == -1)
			cor(112);
		cout << "  Transacoes e Credito " << endl;
		cor(7);
		if (opcao == -2)
			cor(112);
		cout << "  Definicoes da Conta  " << endl;
		cor(7);
		if (opcao == -3)
			cor(112);
		cout << "  Visualisar Atributos de Cliente  " << endl;
		cor(7);
		if (opcao == -4)
			cor(124);
		cout << "  LOGOUT  " << endl;
		cor(7);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 4, opcao);

		switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
		{
		case 0:          // 1a opcao
			menuVisitaStore(mieic, state); // TODO: implementar a listagem de apps
			system("pause");
			break;

		case -1:         // 2a opcao
			menuClienteTransacoes(mieic);
			system("pause");
			break;
		case -2:        // 3a opcao
			menuClienteDefinicoes(mieic);
			system("pause");
			break;
		case -3:        // 4a opcao
			menuInicial(mieic); // TODO: implementar a listagem atributos do cliente
			system("pause");
			break;
		case -4:        // 5a opcao
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
			cor(112);
		cout << "  Visitar AppStore  " << endl;
		cor(7);
		if (opcao == -1)
			cor(112);
		cout << "  Gerir Apps " << endl;
		cor(7);
		if (opcao == -2)
			cor(112);
		cout << "  Definicoes da Conta  " << endl;
		cor(7);
		if (opcao == -3)
			cor(112);
		cout << "  Visualisar Atributos de Developer  " << endl;
		cor(7);
		if (opcao == -4)
			cor(124);
		cout << "  LOGOUT  " << endl;
		cor(7);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 4, opcao);

		switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
		{
		case 0:          // 1a opcao
			menuVisitaStore(mieic, state);
			system("pause");
			break;

		case -1:         // 2a opcao
			menuDeveloperGerirApps(mieic);
			system("pause");
			break;
		case -2:        // 3a opcao
			menuDeveloperDefinicoes(mieic);
			system("pause");
			break;
		case -3:        // 4a opcao
			menuInicial(mieic); // TODO: implementar a listagem atributos do developer
			system("pause");
			break;
		case -4:        // 5a opcao
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
			cor(112);
		cout << "  Adicionar Credito  " << endl;
		cor(7);
		if (opcao == -1)
			cor(112);
		cout << "  Cesto de Compras " << endl;
		cor(7);
		if (opcao == -2)
			cor(112);
		cout << "  Historico de Vendas  " << endl;
		cor(7);
		if (opcao == -3)
			cor(124);
		cout << "  SAIR  " << endl;
		cor(7);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 3, opcao);

		switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
		{
		case 0:          // 1a opcao
			menuClienteCredito(mieic);
			system("pause");
			break;

		case -1:         // 2a opcao
			menuCestoCompras(mieic);
			system("pause");
			break;
		case -2:        // 3a opcao
			menuHistoricoVendas(mieic);
			system("pause");
			break;
		case -3:        // 4a opcao
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
			cor(112);
		cout << "  Alterar Password  " << endl;
		cor(7);
		if (opcao == -1)
			cor(112);
		cout << "  Alterar Nr. de Cartao de Credito " << endl;
		cor(7);
		if (opcao == -2)
			cor(112);
		cout << "  Apagar Conta  " << endl;
		cor(7);
		if (opcao == -3)
			cor(124);
		cout << "  SAIR  " << endl;
		cor(7);

		opcao += teclas();
		opcao = RestringeOpcaoTeclas(0, 3, opcao);

		switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
		{
		case 0:          // 1a opcao
			menuAlterarPass(mieic);
			system("pause");
			break;

		case -1:         // 2a opcao
			menuAlterarCartao(mieic);
			system("pause");
			break;
		case -2:        // 3a opcao
			menuApagarConta(mieic);
			system("pause");
			break;
		case -3:        // 4a opcao
			menuCliente(mieic); //
			system("pause");
			break;
		}
	}
}

void menuDeveloperGerirApps(AppStore& mieic) {

}

void menuDeveloperDefinicoes(AppStore& mieic) {

}

void menuClienteCredito(AppStore& mieic) {

}

void menuCestoCompras(AppStore& mieic) {

}

void menuHistoricoVendas(AppStore& mieic) {

}

void menuAlterarPass(AppStore& mieic) {

}

void menuAlterarCartao(AppStore& mieic) {

}

void menuApagarConta(AppStore& mieic) {

}

//TODO: fazer os subvetores e organizar vetores apps para por no argumento da StoreOrdenada
//state 0 is when a guest is visiting the store.
//state 1 is when a developer is visiting the store
//state 2 is when a client is visiting the store
void menuVisitaStore(AppStore& mieic, unsigned int& state) {
	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);

	if (state == 0) {

		int opcao = 0;
		for (;;) {
			system("cls");
			cout << "  AppStore MIEICPlay  - Esta a entrar com state " << state
					<< endl << endl;

			cout << "  Escolha como quer listar as apps  " << endl << endl;

			if (opcao == 0)
				cor(112);
			cout << "  Por Ordem Alfabetica  " << endl;
			cor(7);
			if (opcao == -1)
				cor(112);
			cout << "  Por Preco " << endl;
			cor(7);
			if (opcao == -2)
				cor(112);
			cout << "  Por developer  " << endl;
			cor(7);
			if (opcao == -3)
				cor(124);
			cout << "  SAIR  " << endl;
			cor(7);

			opcao += teclas();
			opcao = RestringeOpcaoTeclas(0, 3, opcao);

			switch (opcao - 13) {
			case 0:          // 1a opcao
				menuVisitaStoreOrdenada(mieic, state, mieic.apps, "Ordem Alfabetica");
				system("pause");
				break;

			case -1:         // 2a opcao
				menuVisitaStoreOrdenada(mieic, state, mieic.apps, "Preco");
				system("pause");
				break;
			case -2:        // 3a opcao
				//menuListaDeveloper(mieic,state); -> esta funcao vai chamar a menuVisitaStoreOrdenada, apos a escolha de um dev
				system("pause");
				break;
			case -3:        // 4a opcao
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
			cout << "  AppStore MIEICPlay  " << endl << endl;

			cout << "  Escolha como quer listar as apps  " << endl << endl;

			if (opcao == 0)
				cor(112);
			cout << "  Por Ordem Alfabetica  " << endl;
			cor(7);
			if (opcao == -1)
				cor(112);
			cout << "  Por Preco " << endl;
			cor(7);
			if (opcao == -2)
				cor(112);
			cout << "  Por developer  " << endl;
			cor(7);
			if (opcao == -3)
				cor(124);
			cout << "  SAIR  " << endl;
			cor(7);

			opcao += teclas();
			opcao = RestringeOpcaoTeclas(0, 3, opcao);

			switch (opcao - 13) //quando se prime enter adiciona 13. Logo so entra no switch quando e um caso de opcao - 13
			{
			case 0:          // 1a opcao
				//menuVisitaStoreOrdenada(mieic, state, apps)
				system("pause");
				break;

			case -1:         // 2a opcao
				//menuVisitaStoreOrdenada(mieic, state, apps)
				system("pause");
				break;
			case -2:        // 3a opcao
				//menuListaDeveloper(mieic); -> esta funcao vai chamar a menuVisitaStoreOrdenada, apos a escolha de um dev
				system("pause");
				break;
			case -3:        // 4a opcao
				menuDeveloper(mieic); // TODO: implementar a listagem atributos do cliente
				system("pause");
				break;
			}
		}
	}

	if (state == 2) {

		int opcao = 0;
		for (;;) {
			system("cls");
			cout << "  AppStore MIEICPlay  " << endl << endl;

			cout << "  Escolha como quer listar as apps  " << endl << endl;

			if (opcao == 0)
				cor(112);
			cout << "  Por Ordem Alfabetica  " << endl;
			cor(7);
			if (opcao == -1)
				cor(112);
			cout << "  Por Preco " << endl;
			cor(7);
			if (opcao == -2)
				cor(112);
			cout << "  Por developer  " << endl;
			cor(7);
			if (opcao == -3)
				cor(124);
			cout << "  SAIR  " << endl;
			cor(7);

			opcao += teclas();
			opcao = RestringeOpcaoTeclas(0, 3, opcao);

			switch (opcao - 13) {
			case 0:          // 1a opcao
				//menuVisitaStoreOrdenada(mieic, state, apps)
				system("pause");
				break;

			case -1:         // 2a opcao
				//menuVisitaStoreOrdenada(mieic, state, apps)
				system("pause");
				break;
			case -2:        // 3a opcao
				//menuListaDeveloper(mieic); -> esta funcao vai chamar a menuVisitaStoreOrdenada, apos a escolha de um dev
				system("pause");
				break;
			case -3:        // 4a opcao
				menuCliente(mieic);
				system("pause");
				break;
			}
		}
	}
}

void menuVisitaStoreOrdenada(AppStore& mieic, unsigned int& state,
		vector<App> apps_ordenadas, string tipo) {

	system("cls");
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(tm);
	int opcao = 0;
	cout << "  Visita Store - Apps Ordenadas por " << tipo <<  endl;

	if (state == 0) {
		vector<string> menu_options = getAppNames(apps_ordenadas);
		printMenuScroll(menu_options, opcao, 4);

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13) //ENQUANTO DIFERENTE DE ENTER
			{
				tecla = getch();
				if (tecla == 72) //ACIMA
						{
					opcao--;
					if(opcao < 0)
						opcao = 0;
					system("cls");
					printMenuScroll(menu_options, opcao, 4);
				}
				if (tecla == 80) //ABAIXO
						{
					opcao++;
					if (opcao > (menu_options.size()-1))
						opcao = menu_options.size()-1;
					system("cls");
					printMenuScroll(menu_options, opcao, 4);
				}
			}
		}
		menuInicial(mieic);

	}
	if (state == 1) {

	}
	if (state == 2) {

	}

}
void menuListaDeveloper(AppStore& mieic, unsigned int& state) {

}
