/*
 * AppStore.h
 *
 *  Created on: 30/10/2014
 *      Author: Moura
 */

#ifndef APPSTORE_H_
#define APPSTORE_H_

#include "Developer.h"
#include "Vendas.h"
#include "Cliente.h"
#include "App.h"
#include "Date.h"
#include "BST.h"
#include <string>
#include <fstream>
#include <ctime>
#include <tr1/unordered_set>
#include <queue>
#include <conio.h>
#include <windows.h>
#include "BST.h"

extern Developer* dev_act;
extern Cliente* cli_act;

using namespace std;

/**
 * Funcao usada no Sort para comparar o preco de Apps
 * @param app1 1 app para comparar
 * @param app2 2 app para comparar
 * @return True no caso do preco de 1<2 e False no caso contrario
 */
bool appsComparaPreco(App app1, App app2);
/**
 * Funcao usada no Sort para comparar o nome de Apps
 * @param app1 1 app para comparar
 * @param app2 2 app para comparar
 * @return True no caso do nome de 1<2 e False no caso contrario
 */
bool appsComparaNome(App app1, App app2);
/**
 * Funcao usada no Sort para comparar o nome de Dev
 * @param dev1 1 dev para comparar
 * @param dev2 2 dev para comparar
 * @return True no caso do nome de 1<2 e False no caso contrario
 */
bool devsComparaNome(Developer* dev1, Developer* dev2);

/**
 * @class AppStore
 * @brief Classe Principal do projecto que contem toda a informacao sofre a AppStore
 */

/**
 * Struct Comparacao para Apps
 */
struct ComparaAppValidar {
	bool operator()(App app1, App app2) {
		if (app1.getDataSubmissao() < app2.getDataSubmissao()) {
			return true;
		} else if (app1.getDataSubmissao() == app2.getDataSubmissao()) {
			if (app1.getPreco() > app2.getPreco()) {
				return true;
			} else if (app1.getPreco() == app2.getPreco()) {
				if (app1.getNome() < app2.getNome()) {
					return true;
				}
			}
		}
		return false;
	}
};

/*
 * Struct para funcao Equal da Hashtable
 */
struct EqualApp {
	bool operator()(const App &app1, const App &app2) const {
		return (app1.getNome() == app2.getNome());
	}
};
/*`
 * Struct para funcao Hash da Hashtable
 */
struct HashApp {
	int operator()(const App &app1) const {
		string s1 = app1.getNome();
		int v = 0;
		for (unsigned int i = 0; i < s1.size(); i++)
			v = 37 * v + s1[i];
		return v;
	}
};

class AppStore {
public:
	/**
	 * Construtor Default AppStore
	 */
	AppStore();
	vector<App> apps;/**< Vector com todas as Apps activas na Store */
	vector<Cliente> clientes; /**< Vector com todos os Clientes activos na Store */
	vector<Developer *> dev; /**< Vector com todos os Developers activos na Store */
	vector<Vendas *> vendas; /**< Vector com todos os Vendas activos na Store */
	Date data_atual; /**< Data Actual */
	bool has_put_password;

	BST<App> arv_apps; /**< Arvore com todas as Apps activas na Store */

	priority_queue<App, vector<App>, ComparaAppValidar> apps_a_validar; /**< Priority queue */
	tr1::unordered_set<App, HashApp, EqualApp> apps_apagadas; /**< Hashtable das apps apagadas */

	/**
	 * Obter Data da Maquina em que o processo esta a ser executado
	 * @return Data Actual
	 */
	Date DataAtual();

	/**
	 *	Encontra um Developer por Id
	 * @param id Id do Developer desejado
	 * @return Pointer Developer
	 */
	Developer* find_dev_id(unsigned int id) const;
	/**
	 * Encontra um Cliente por Id
	 * @param id Id do Cliente desejado
	 * @return Pointer Cliente
	 */
	Cliente* find_cliente_id(unsigned int id);
	/**
	 * Encontra um App por Id
	 * @param id Id do App desejado
	 * @return Pointer App
	 */
	App* find_app_id(unsigned int id);
	/**
	 * Encontra uma Venda por Id
	 * @param id Id do Vendas desejado
	 * @return Pointer Vendas
	 */
	Vendas* find_vendas_id(unsigned int id);
	/**
	 * Todas as Apps pertencentes a um Developer, que estejam dentro da store
	 * @param dev_act Pointer Developer
	 * @return Vector Apps
	 */
	vector<App> getApps(Developer* dev_act);
	/**
	 * Todas as Apps pertencentes a um Developer, que
	 * @param dev_act Pointer Developer
	 * @return Vector Apps
	 */
	vector<App> getAppsForaStore(Developer * dev_act);

	vector<App> getAppsNaoValidadas(Developer* dev_act);

	/**
	 *
	 * @return
	 */
	tr1::unordered_set<App, HashApp, EqualApp> getHashTable();
	/**
	 * Numero de Apps de um Developer
	 * @param dev_act Pointer Developer
	 * @return Int Nr. Apps
	 */
	unsigned int getNrApps(Developer* dev_act);
	/**
	 * Testa se existe determinado Developer
	 * @param nome Nome do Developer
	 * @return True se existe / False se nao existe
	 */
	bool existeNomeDev(string nome) const;
	/**
	 * Testa se existe determinada App
	 * @param nome Nome da App
	 * @return True se existe / False se nao existe
	 */
	bool existeNomeApp(string nome) const;
	/**
	 *
	 * @param nome
	 * @return
	 */
	bool existeNomeAppAnywhere(string nome) const;
	/**
	 * Testa se existe determinada Empresa Developer
	 * @param nome_dev Nome Developer
	 * @param nome_oficial Nome Oficial Empresa
	 * @return True se existe / False se nao existe
	 */
	bool existeNomeDevEmp(string nome_dev, string nome_oficial) const;
	/**
	 * Valida o Login do Cliente
	 * @param id Id Cliente
	 * @param pass Pass Cliente
	 * @return True-Sucesso / False-Insucesso
	 */
	bool verificaLoginCliente(unsigned int id, string pass) const;
	// true - "faz login"  false - "combinacao errada" Alternativamente poderia ter feito -1 -> "cliente nao existe" 0 -> "login OK" 1 -> "password errada"
	/**
	 * Valida o Login do Developer
	 * @param id Id Developer
	 * @param pass Pass Developer
	 * @return True-Sucesso / False-Insucesso
	 */
	bool verificaLoginDev(unsigned int id, string pass) const;

	/**
	 * Faz save de todas a informacao da AppStore
	 * @return True-Sucesso / False-Insucesso
	 */
	bool save_all();
	/**
	 * Faz load de todas a informacao da AppStore
	 * @return True-Sucesso / False-Insucesso
	 */
	bool load_all();
	/**
	 * Faz save de todas as Apps da AppStore
	 * @param file ficheiro para onde é gravada a informacao
	 * @return True-Sucesso / False-Insucesso
	 */
	bool save_app(ofstream &file);
	/**
	 * Faz load de todas as Apps da AppStore
	 * @param file ficheiro de onde é carregada a informacao
	 * @return True-Sucesso / False-Insucesso
	 */
	bool load_app(fstream &file);
	/**
	 * Faz save de todas as Vendas da AppStore
	 * @param file ficheiro para onde é gravada a informacao
	 * @return True-Sucesso / False-Insucesso
	 */
	bool save_vendas(ofstream &file);
	/**
	 * Faz load de todas as Vendas da AppStore
	 * @param file ficheiro de onde é carregada a informacao
	 * @return True-Sucesso / False-Insucesso
	 */
	bool load_vendas(fstream &file);
	/**
	 * Faz save de todos os Clientes da AppStore
	 * @param file ficheiro para onde é gravada a informacao
	 * @return True-Sucesso / False-Insucesso
	 */
	bool save_clientes(ofstream &file);
	/**
	 * Faz load de todos os Clientes da AppStore
	 * @param file ficheiro de onde é carregada a informacao
	 * @return True-Sucesso / False-Insucesso
	 */
	bool load_clientes(fstream &file);
	/**
	 * Faz save de todos os Developers da AppStore
	 * @param file ficheiro para onde é gravada a informacao
	 * @return True-Sucesso / False-Insucesso
	 */
	bool save_dev(ofstream &file);
	/**
	 * Faz load de todos os Developers da AppStore
	 * @param file ficheiro de onde é carregada a informacao
	 * @return True-Sucesso / False-Insucesso
	 */
	bool load_dev(fstream &file);

	void validarApp();

	void save_one_app(ofstream& file, App a);

	bool removeAppValidar(unsigned int id);
	/**
	 * Obtem vector de apps ja validadas
	 * @return apps prontas para serem vendidas
	 */
	vector<App> appsDisponiveis() const;
	/**
	 * Passa todas as apps do vetor apps para arvore arv_apps
	 */
	void create_tree();
	/**
	 * Imprime as top 10 apps presentes na arvore
	 */
	void top10();
	/**
	 * Faz update da posi��o de uma app que foi alterada
	 * @param appa app a alterar
	 */
	void updateAppInTree(App & appa);

};

/**
 * @class File_Exp
 * @brief Classe para ajudar no tratamento de excepcoes relacionada com os ficheiros
 */
class File_Exp {
private:
	unsigned int id_erro;
	string descricao_erro;
public:
	/**
	 * Construtor para Excepcao do Ficheiro
	 * @param id Id Erro
	 * @param descricao DEscricao Erro
	 */
	File_Exp(unsigned int id, string descricao);
	/**
	 * Getter Descricao Erro
	 * @return String Descricao
	 */
	string getDescricaoErro() const;
	/**
	 * Setter Descricao Erro
	 * @param descricaoErro Nova Descricao do Erro
	 */
	void setDescricaoErro(string descricaoErro);
	/**
	 * Getter do Id Erro
	 * @return Int Id Erro
	 */
	unsigned int getIdErro() const;
	/**
	 * Getter Id Erro
	 * @param idErro Novo Id para o Erro
	 */
	void setIdErro(unsigned int idErro);
};

#endif /* APPSTORE_H_ */

