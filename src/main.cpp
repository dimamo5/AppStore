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

AppStore MEIC_Play;

	int opc=0;
		do
		{
			opc=menuInicial(MEIC_Play);
		} while (opc); // so acaba o programa quando opc == 0


	return 1;
}
