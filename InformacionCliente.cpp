#include "InformacionCliente.h"

using namespace std;

InformacionCliente::InformacionCliente(int desc , struct sockaddr_in infor){
	this->descriptorCliente=desc;
	this->informacionCliente = infor;
	this->estado=true;
}

int InformacionCliente::getId(){
	return this->id;
}

void InformacionCliente::setId(int id){
 	this->id=id;
}


int InformacionCliente::getDescriptorCliente(void){
	return this->descriptorCliente;
}
struct sockaddr_in InformacionCliente::getInformacionCliente(){
	return this->informacionCliente;
}

bool InformacionCliente::getEstado(){
	return this->estado;
}

void InformacionCliente::setEstado(bool estado){
	this->estado=estado;
}