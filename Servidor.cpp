#include "Servidor.h"

int cont;


Servidor::Servidor(){
	
}


Servidor::Servidor(int puerto){
	this->puerto=puerto;
}
 
void Servidor::inicializarServidor(){
	descriptorSer= socket(AF_INET,SOCK_STREAM,0);
	servidorInfo.sin_family=AF_INET;
	servidorInfo.sin_addr.s_addr=htonl(INADDR_ANY);
	servidorInfo.sin_port=htons(puerto);
	idBind=bind(descriptorSer,(struct sockaddr *)&servidorInfo, sizeof(servidorInfo));
	
	listen(descriptorSer, maxClientes);
}

void Servidor::cerrarServidor(){
	exit(EXIT_SUCCESS);
}



void * recibirCliente(void * cli){
	InformacionCliente * cliente=(InformacionCliente *) cli;
	char mensajeDeCliente[128];
	while(cliente->getEstado()){

		int i=recv(cliente->getDescriptorCliente(),(void *)&mensajeDeCliente,128,0);
		sleep(1);
		if(i!=0){
			cout<<"Informacion del cliente con ip: "<<inet_ntoa(cliente->getInformacionCliente().sin_addr)<<endl;
			
			string mensajeCompleto(mensajeDeCliente);
			stringstream ss(mensajeCompleto);
		    string item;
		    int cont_aux = 0;
		    string result[3];
		    while (getline(ss, item, ',')) {
		        result[cont_aux++]=item;
		    }

		    ofstream myfile;
		    string nombre = "info_de_"+result[0]+".txt";
			myfile.open (nombre);
			myfile << "IP: " <<result[0]<<endl;
			myfile << "mensaje: " <<result[1]<<endl;
			myfile << "Fecha y hora: " <<result[2]<<endl;
			myfile.close();

		}else{
			cliente->setEstado(false);
			close(cliente->getDescriptorCliente());
		}

	}
}


void Servidor::aceptarClientes(){
	int descriptorCliente;
	cont=0;

	while(cont<maxClientes){
		struct sockaddr_in InformacionClienter;
		int tamano= sizeof(struct sockaddr_in);
		cout<<"Aceptando cliente"<<endl;
		descriptorCliente=accept(this->descriptorSer,(struct sockaddr *)&InformacionClienter,(socklen_t*) &tamano);
		
		//recibiendo clientes

		if(descriptorCliente!=-1){
			cout<< "Cliente Conectado"<<endl;
			clientesDescriptor.push_back(new InformacionCliente(descriptorCliente,InformacionClienter));
			pthread_t clientesHilos;
			
			pthread_create(&clientesHilos,NULL,&recibirCliente,(void *) clientesDescriptor[cont]);

			clientesDescriptor[cont]->setId(cont);
			cont++;
		}
	}
		

}

void * Servidor::comenzarServidor(void * servidor){
	Servidor * server=(Servidor *) servidor;
	server->aceptarClientes();
}

void Servidor::ejecutarServidor(){
	pthread_t hilo;
	pthread_create(&hilo,NULL,&comenzarServidor,(void *) this);
}

void Servidor::setDescriptorServidor(int descriptor){
	this->descriptorSer=descriptor;
}

void Servidor::setIdBin(int bind){
	this->idBind=bind;
}
void Servidor::setPuerto(int puerto){
	this->puerto=puerto;
}
void Servidor::setServidorInfo(struct sockaddr_in info){
	this->servidorInfo = info;
}

void Servidor::setTipo(int tipo){
	this->tipo=tipo;
}



int Servidor::getDescriptorServidor(){
	return this->descriptorSer;
}
int Servidor::getIdBin(){
	return this->idBind;
}
int Servidor::getPuerto(){
	return this->puerto;
}

int Servidor::getTipo(){
	return this->tipo;
}

struct sockaddr_in Servidor::getServidorInfo(){
	return this->servidorInfo;
}

vector<InformacionCliente *> Servidor::getClientes(){
	return this->clientesDescriptor;
}


