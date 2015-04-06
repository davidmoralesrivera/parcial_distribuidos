#include "Servidor.h"

#include <stdlib.h>

int main(int arg , char** args){
	cout<<"#### SERVIDOR ####"<<endl;
	cout<<"Por favor seleccione el tipo de topologia, Estrella(1) o Anillo(2): ";
	int tipo;

	cin>>tipo;

	while(tipo != ESTRELLA && tipo != ANILLO){
		cout<<"Las opciones son Estrella(1) o Anillo(2)"<<endl;
		cin>>tipo;
	}

	Servidor *servidor = new Servidor();
	servidor->setPuerto(atoi(args[1]));
	servidor->setTipo(tipo);
	servidor->inicializarServidor();
	servidor->ejecutarServidor();


	while(1);
	return 0;
}