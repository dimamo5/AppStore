#include <iostream>
#include "menu.h"
#include "Developer.h"
#include "App.h"
#include "Vendas.h"
#include "Cliente.h"
#include "AppStore.h"
using namespace std;

Developer* dev_act = NULL;
Cliente* cli_act = NULL;

int main() {

	int opc=0;
		do
		{
			opc=menuInicial();
		} while (opc); // so acaba o programa quando opc == 0


	return 1;
}
