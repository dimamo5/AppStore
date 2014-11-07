/*
 * AppStore.cpp
 *
 *  Created on: 30/10/2014
 *      Author: Moura
 */

#include "AppStore.h"
#include <sstream>

AppStore::AppStore() {
	// TODO Auto-generated constructor stub

}

Date AppStore::DataAtual(){
	time_t t = time(0);
	struct tm *now = localtime(&t);
	Date data_atual(now);
	return data_atual;
}

bool AppStore::save_clientes(ofstream& file) {
	if (clientes.empty()) {
		return false;
	} else {
		file << clientes[0].getNext_id();
		for (unsigned int i = 0; i < clientes.size(); i++) {
			file << clientes[i].getId() << endl;
			file << clientes[i].getNome() << endl;
			file << clientes[i].getIdade() << endl;
			file << clientes[i].getSexo() << endl;
			file << clientes[i].getCartaoCredito() << endl;
			file << clientes[i].getSaldo() << endl;
			file << clientes[i].getVouchers();
			file << clientes[i].getHistorico().size() << endl;
			for (unsigned int m = 0; i < clientes[i].getHistorico().size();
					m++) {
				file << clientes[i].getHistorico()[m]->getId();
			}
		}
		return true;
	}
}

//bool AppStore::load_clientes(fstream& file) {
//	unsigned int next_id, idade, nr_vouchers, historico_size, id_vendas;
//	int saldo, cartao_credito, id;
//	string sexo, nome, temp;
//	vector<Vendas*> vendas_temp;
//	getline(file, temp);
//	stringstream(temp) >> next_id;
//	Cliente::setNextID(next_id);
//	while (!file.eof()) {
//		getline(file, temp);
//		stringstream(temp) >> id;
//		getline(file, temp);
//		nome = temp;
//		getline(file, temp);
//		stringstream(temp) >> idade;
//		getline(file, temp);
//		sexo = temp;
//		getline(file, temp);
//		stringstream(temp) >> cartao_credito;
//		getline(file, temp);
//		stringstream(temp) >> saldo;
//		getline(file, temp);
//		stringstream(temp) >> nr_vouchers;
//		getline(file, temp);
//		stringstream(temp) >> historico_size;
//		for (unsigned int i = 0; i < historico_size; i++) {
//			getline(file, temp);
//			stringstream(temp) >> id_vendas;
//			vendas_temp.push_back(find_vendas_id(id_vendas));
//		}
//		Cliente temp_cliente = Cliente(id, nome, idade, sexo, cartao_credito,
//				saldo, nr_vouchers);
//		temp_cliente.setHistorico(vendas_temp);
//		clientes.push_back(temp_cliente);
//		vendas_temp.clear();
//	}
//	return true;
//}

bool AppStore::save_dev(ofstream& file) {
	if (dev.empty()) {
		return false;
	} else {
		file << dev[0]->getNextId() << endl;
		for (unsigned int i = 0; i < dev.size(); i++) {
			file << dev[i]->getId() << endl;
			file << dev[i]->getNome() << endl;
			file << dev[i]->getSaldo() << endl;
			file << dev[i]->getIdPass() << endl;
			file << dev[i]->getExtra() << endl;
			file << dev[i]->getMorada() << endl;
			if (dev[i]->isEmpresa()) {
				file << "emp" << endl;
				file << dev[i]->getNIF() << endl;
			} else {
				file << "ind" << endl;
			}

		}
	}
	return true;
}

bool AppStore::save_app(ofstream& file) {
	if (apps.empty()) {
		return false;
	} else {
		file << apps[0].getNextId() << endl;
		for (unsigned int i = 0; i < apps.size(); i++) {
			file << apps[i].getId() << endl;
			file << apps[i].getNome() << endl;
			file << apps[i].getCategoria() << endl;
			file << apps[i].getDescricao() << endl;
			file << apps[i].getPreco() << endl;
			file << apps[i].getClassificacaoFinal() << endl;
			file << apps[i].getNumClassificacoes() << endl;
			file << apps[i].getComentarios().size() << endl;
			for (unsigned int m = 0; i < apps[i].getComentarios().size(); m++) {
				file << apps[i].getComentarios()[m].getIdClient();
				file << apps[i].getComentarios()[m].getDescricao();
				file << apps[i].getComentarios()[m].getClassificacao();
			}
			file << apps[i].getDev()->getId();

		}
	}
	return true;
}

bool AppStore::load_app(fstream& file) {
	unsigned int next_id, id, clas_final, num_clas, com_size, com_id_cliente,
			com_clas, dev_id;
	float preco;
	string categoria, descricao, com_descricao, temp, nome;
	vector<Comentario> com_temp;
	getline(file, temp);
	stringstream(temp) >> next_id;
	App::setNextId(next_id);
	while (!file.eof()) {
		getline(file, temp);
		stringstream(temp) >> id;
		getline(file, temp);
		nome = temp;
		getline(file, temp);
		categoria = temp;
		getline(file, temp);
		descricao = temp;
		getline(file, temp);
		stringstream(temp) >> preco;
		getline(file, temp);
		stringstream(temp) >> clas_final;
		getline(file, temp);
		stringstream(temp) >> num_clas;
		getline(file, temp);
		stringstream(temp) >> com_size;
		for (unsigned int i = 0; i < com_size; i++) {
			getline(file, temp);
			stringstream(temp) >> com_id_cliente;
			getline(file, temp);
			com_descricao = temp;
			getline(file, temp);
			stringstream(temp) >> com_clas;
			Comentario * com_temp_obj = new Comentario(com_descricao,
					com_id_cliente, com_clas);
			com_temp.push_back(*com_temp_obj);
		}
		getline(file, temp);
		stringstream(temp) >> dev_id;
		App* app_temp = new App(id, nome, categoria, descricao, preco,
				clas_final, num_clas);
		app_temp->setDev(find_dev_id(dev_id));
		app_temp->setComentarios(com_temp);
		apps.push_back(*app_temp);
	}
	return true;

}

Developer* AppStore::find_dev_id(unsigned int id) const {
	for (unsigned int i = 0; i < dev.size(); i++) {
		if (dev[i]->getId() == id) {
			return dev[i];
		}
	}
	return NULL;
}

Cliente* AppStore::find_cliente_id(unsigned int id) {

	for (unsigned int i = 0; i < clientes.size(); i++) {
		if (clientes[i].getId() == id) {
			return &clientes[i];
		}
	}
	return NULL;

}

bool AppStore::save_all() {
	ofstream file_developer, file_vendas, file_apps, file_clientes;

	file_developer.open("files/developer.txt");
	save_dev(file_developer);
	file_developer.close();

	file_apps.open("files/app.txt");
	save_app(file_apps);
	file_apps.close();

	file_vendas.open("files/vendas.txt");
	save_vendas(file_vendas);
	file_vendas.close();

	file_clientes.open("files/clientes.txt");
	save_clientes(file_clientes);
	file_clientes.close();

}

//bool AppStore::load_all() {
//	fstream file_developer, file_vendas, file_apps, file_clientes;
//
//	file_developer.open("files/developer.txt");
//	load_dev(file_developer);
//	file_developer.close();
//
//	file_apps.open("files/app.txt");
//	load_app(file_apps);
//	file_apps.close();
//
//	file_vendas.open("files/vendas.txt");
//	load_vendas(file_vendas);
//	file_vendas.close();
//
//	file_clientes.open("files/clientes.txt");
//	load_clientes(file_clientes);
//	file_clientes.close();
//
//	//developer->app->vendas->cliente
//}


//TODO: remover cenas que tenham o pointer da app e adicionar o bool e a cena do ID
bool AppStore::save_vendas(ofstream &file) {
	if (vendas.empty()) {
		return false;
	} else {
		file << vendas[0].getNextId() << endl;
		for (unsigned int i = 0; i < vendas.size(); i++) {
			file << vendas[i].getId() << endl;
			file << vendas[i].getPreco() << endl;
			file << vendas[i].getDataVenda().getYear() << endl; //TODO melhor escrita data
			file << vendas[i].getDataVenda().getMonth() << endl;
			file << vendas[i].getDataVenda().getDay() << endl;
			file << vendas[i].getDataVenda().getHour() << endl;
			file << vendas[i].getDataVenda().getMinute() << endl;
			file << vendas[i].isRetorno() << endl;
			file << vendas[i].getReclamacao() << endl;
			file << vendas[i].getApp()->getId() << endl;
			file << vendas[i].getAppVendidaNome() << endl;
		}
	}
	return true;
}

bool AppStore::load_vendas(fstream &file) {
	unsigned int next_id, id, ano, mes, dia, hora, minuto, id_app;
	float preco;
	bool retorno;
	string reclamacao, nome_app_vendida, temp;
	getline(file, temp);
	stringstream(temp) >> next_id;
	Vendas::setNextId(next_id);
	while (!file.eof()) {
		getline(file, temp);
		stringstream(temp) >> id;
		getline(file, temp);
		stringstream(temp) >> preco;
		getline(file, temp);
		stringstream(temp) >> ano;
		getline(file, temp);
		stringstream(temp) >> mes;
		getline(file, temp);
		stringstream(temp) >> dia;
		getline(file, temp);
		stringstream(temp) >> hora;
		getline(file, temp);
		stringstream(temp) >> minuto;
		Date *date_temp = new Date(ano, mes, dia, hora, minuto);
		getline(file, temp);
		stringstream(temp) >> retorno;
		getline(file, temp);
		reclamacao = temp;
		getline(file, temp);
		stringstream(temp) >> id_app;
		getline(file, temp);
		nome_app_vendida = temp;
		Vendas *venda_temp = new Vendas(id, preco, *date_temp, retorno,
				reclamacao, nome_app_vendida);
		venda_temp->setApp(find_app_id(id_app));
		vendas.push_back(*venda_temp);
	}
	return true;
}

App* AppStore::find_app_id(unsigned int id) {
	for (unsigned int i = 0; i < apps.size(); i++) {
		if (apps[i].getId() == id) {
			return &apps[i];
		}
	}
	return NULL;
}

Vendas* AppStore::find_vendas_id(unsigned int id) {
	for (unsigned int i = 0; i < vendas.size(); i++) {
		if (vendas[i].getId() == id) {
			return &vendas[i];
		}
	}
	return NULL;
}

vector<App> AppStore::getApps(Developer* dev_act) {
	vector<App> apps_do_developer;

	for (unsigned int i = 0; i < apps.size(); i++) { // percorre as apps da store

		// sempre que ha uma app cujo ID  do dev coincide, tendo em conta que todos teem IDs diferentes
		if (apps[i].getDev()->getId() == dev_act->getId()) {
			apps_do_developer.push_back(apps[i]);
		}
	}
	return apps_do_developer;
}

unsigned int AppStore::getNrApps(Developer* dev_act) {
	unsigned int counter = 0;

	for (unsigned int i = 0; i < apps.size(); i++) {
		if (apps[i].getDev()->getId() == dev_act->getId())
			counter++;
	}
	return counter;
}

bool AppStore::existeNomeDev(string nome) const {

	for (unsigned int i = 0; i < dev.size(); i++) {

		if (dev[i]->getNome() == nome) {
			return true;
		}
	}
	return false;
}

bool AppStore::existeNomeApp(string nome) const {

	for (unsigned int i = 0; i < apps.size(); i++) {
		if (apps[i].getNome() == nome) {
			return true;
		}
	}
	return false;
}

bool AppStore::existeNomeDevEmp(string nome_dev, string nome_oficial) const {
	for (unsigned int i = 0; i < dev.size(); i++) {

		if (dev[i]->getNome() == nome_dev
				|| dev[i]->getExtra() == nome_oficial) {
			return true;
		}
	}
	return false;
}

bool AppStore::verificaLoginCliente(unsigned int id, string pass) const {

	for (unsigned int i = 0; i < clientes.size(); i++) {
		if (clientes[i].getId() == id) {
			if (clientes[i].getIdPass() == pass) {
				return true; // combinacao id-pass correta
			} else {
				return false;  // combinacao id-pass errada
			}
		}
	}
	return false;
}

bool AppStore::verificaLoginDev(unsigned int id, string pass) const {

	for (unsigned int i = 0; i < dev.size(); i++) {
		if (dev[i]->getId() == id) {
			if (dev[i]->getIdPass() == pass) {
				return true; // combinacao id-pass correta
			} else {
				return false;  // id existe, mas pass esta errada
			}
		}
	}
	return false;  // nao encontrou nenhum id igual ao dado
}

bool AppStore::load_dev(fstream& file) {

	unsigned int next_id, id;
	float saldo;
	string nome, pass, extra, temp, type, nif, morada;
	getline(file, temp);
	stringstream(temp) >> next_id;
	Developer::setNextID(next_id);
	while (!file.eof()) {
		getline(file, temp);
		stringstream(temp) >> id;
		getline(file, temp);
		nome = temp;
		getline(file, temp);
		stringstream(temp) >> saldo;
		getline(file, temp);
		pass = temp;
		getline(file, temp);
		extra = temp;
		getline(file, temp);
		morada = temp;
		getline(file, temp);
		type = temp;
		if (type == "ind") {
			Developer * dev_temp = new Individual(id, nome, saldo, pass, morada,
					extra);
			dev.push_back(dev_temp);
		} else if (type == "emp") {
			getline(file, temp);
			nif = temp;
			Developer * dev_temp = new Empresa(id, nome, saldo, pass, morada,
					nif, extra);
			dev.push_back(dev_temp);
		}

	}
	return true;
}

bool appsComparaPreco(App app1, App app2) {
	return (app1.getPreco() < app2.getPreco());
}

bool appsComparaNome(App app1, App app2) {
	return (app1.getNome() < app2.getNome());
}

bool devsComparaNome(Developer* dev1, Developer* dev2) {
	return (dev1->getNome() < dev2->getNome());
}
