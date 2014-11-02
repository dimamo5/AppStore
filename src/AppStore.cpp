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

bool AppStore::save_clientes(ofstream& file) {
	for (unsigned int i = 0; i < clientes.size(); i++) {
		file << clientes[i].getId() << endl;
		file << clientes[i].getNome() << endl;
		file << clientes[i].getIdade() << endl;
		file << clientes[i].getSexo() << endl;
		file << clientes[i].getCartaoCredito() << endl;
		file << clientes[i].getSaldo() << endl;
		file << clientes[i].getHistorico().size() << endl;
		for (unsigned int m = 0; i < clientes[i].getHistorico().size(); m++) {
			file << clientes[i].getHistorico()[m]->getId();
		}
	}
	return true;
}

bool AppStore::load_clientes(fstream& file) {
	unsigned int next_id, idade;
	int saldo, cartao_credito, id;
	string sexo, nome, temp;
	getline(file, temp);
	stringstream(temp) >> next_id;
	while (!file.eof()) {
		getline(file, temp);
		stringstream(temp) >> id;
		getline(file, temp);
		nome = temp;
		getline(file, temp);
		stringstream(temp) >> idade;
		getline(file, temp);
		sexo = temp;
		getline(file, temp);
		stringstream(temp) >> cartao_credito;
		getline(file, temp);
		stringstream(temp) >> saldo;
		Cliente temp_cliente = Cliente(id, nome, idade, sexo, cartao_credito,
				saldo);
		clientes.push_back(temp_cliente);
	}
	return true;
}

bool AppStore::save_dev(ofstream& file) {
	if (dev.empty()) {
		return false;
	} else {
		file << dev[0]->getNextId() << endl;
		for (unsigned int i = 0; i < dev.size(); i++) {
			file << dev[i]->getId() << endl;
			file << dev[i]->get_nome() << endl;
			file << dev[i]->get_saldo() << endl;
			file << dev[i]->getIdPass() << endl;
			file << dev[i]->getExtra() << endl;
		}
		return true;
	}
}

bool AppStore::save_app(ofstream& file) {
	if (apps.empty()) {
		return false;
	} else {
		file << apps[0].getNextId() << endl;
		for (unsigned int i = 0; i < apps.size(); i++) {
			file << apps[i].get_id() << endl;
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
			return true;
		}
	}
}

bool AppStore::load_app(fstream& file) {
	unsigned int next_id, id, clas_final, num_clas, com_size, com_id_cliente,
			com_clas,dev_id;
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
			com_descricao=temp;
			getline(file, temp);
			stringstream(temp) >> com_clas;
			Comentario * com_temp_obj=new Comentario (com_descricao,com_id_cliente,com_clas);
			com_temp.push_back(*com_temp_obj);
		}
		getline(file, temp);
		stringstream(temp) >> dev_id;
		App* app_temp=new App(id,nome,categoria,descricao,preco,clas_final,num_clas);
		app_temp->setDev(find_dev_id(dev_id));
		app_temp->setComentarios(com_temp);
		apps.push_back(*app_temp);
	}
	return true;

}

Developer* AppStore::find_dev_id(unsigned int id) const {
	for(unsigned int i=0;i<dev.size();i++){
		if(dev[i]->getId()==id){
			return dev[i];
		}
	}
	return NULL;
}

bool AppStore::save_all() {

}

bool AppStore::load_all() {
	//developer->app->vendas->cliente
}

bool AppStore::save_vendas() {
}

bool AppStore::load_vendas() {
}

bool AppStore::load_dev(fstream& file) {
	unsigned int next_id, id;
	float saldo;
	string nome, pass, extra, temp, type;
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
		type = temp;
		if (type == "ind") {
			Developer * dev_temp = new Individual(id, nome, saldo, pass, extra);
			dev.push_back(dev_temp);
		} else if (type == "emp") {
			Developer * dev_temp = new Empresa(id, nome, saldo, pass, extra);
			dev.push_back(dev_temp);
		}

	}
	return true;
}
