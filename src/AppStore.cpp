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
		stringstream ss;
		ss<<clientes[i].getNext_id()<<endl;
		ss<<clientes[i].getId()<<endl;
		ss<<clientes[i].getNome()<<endl;
		ss<<clientes[i].getIdade()<<endl;
		ss<<clientes[i].getSexo()<<endl;
		ss<<clientes[i].getCartaoCredito()<<endl;
		ss<<clientes[i].getSaldo()<<endl;
		file<<ss.str();
	}
	return true;
}

bool AppStore::load_clientes(ifstream& file) {
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
	}
}

