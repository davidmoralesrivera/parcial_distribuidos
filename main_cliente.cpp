#include "Cliente.h"

#include <stdlib.h>
int main(int argc, char ** argv){

	cout<<"#### CLIENTE ####"<<endl;
	cout<<"Por favor seleccione el tipo de topologia, Estrella(1) o Anillo(2): ";
	int tipo;

	cin>>tipo;

	while(tipo != ESTRELLA && tipo != ANILLO){
		cout<<"Las opciones son Estrella(1) o Anillo(2)"<<endl;
		cin>>tipo;
	}

	Cliente *cliente = new Cliente(atoi(argv[1]),argv[2]);
	cliente->setTipo(tipo);

	if (tipo == ESTRELLA){
		cliente->conectarServidor();

	}else if(tipo == ANILLO){
		cliente->conectarAnillo();
	}
	return 0;
}
