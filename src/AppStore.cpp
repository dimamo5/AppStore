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
	for(unsigned int i=0;i<clientes.size();i++){
		file<<clientes[i].getId()<<endl;
		file<<clientes[i].getNome()<<endl;
		file<<clientes[i].getIdade()<<endl;
		file<<clientes[i].getSexo()<<endl;
		file<<clientes[i].getCartaoCredito()<<endl;
		file<<clientes[i].getSaldo()<<endl;
		file<<clientes[i].getHistorico().size()<<endl;
		for(unsigned int m =0;i<clientes[i].getHistorico().size();m++){
			file<<clientes[i].getHistorico()[m]->getId();
		}
	}
	return true;
}

bool AppStore::load_clientes(fstream& file) {
	unsigned int next_id,idade;
	int saldo,cartao_credito,id;
	string sexo,nome,temp;
	getline(file,temp);
	stringstream(temp)>>next_id;
	while(!file.eof()){
		getline(file,temp);
		stringstream(temp)>>id;
		getline(file,temp);
		nome=temp;
		getline(file,temp);
		stringstream(temp)>>idade;
		getline(file,temp);
		sexo=temp;
		getline(file,temp);
		stringstream(temp)>>cartao_credito;
		getline(file,temp);
		stringstream(temp)>>saldo;
		Cliente temp_cliente =Cliente(id,nome,idade,sexo,cartao_credito,saldo);
		clientes.push_back(temp_cliente);
	}
	return true;
}

bool AppStore::save_dev(ofstream& file) {
	if(dev.empty()){
		return false;
	}
	else{
		file<<dev[0]->getNextId()<<endl;
		for(unsigned int i=0;i<dev.size();i++){
			file<<dev[i]->getId()<<endl;
			file<<dev[i]->get_nome()<<endl;
			file<<dev[i]->get_saldo()<<endl;
			file<<dev[i]->getIdPass()<<endl;
			file<<dev[i]->getExtra()<<endl;

			}
			return true;
		}
	}


/*bool AppStore::load_dev(fstream& file) {
}*/
