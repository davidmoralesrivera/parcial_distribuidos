#include "Cliente.h"
#include "InformacionCliente.h"


Cliente::Cliente(){
	
}

Cliente::Cliente(int puerto, string ip){
	this->puertoServidor=puerto;
	this->ipServidor=ip;
	this->estado=true;
}

void * Cliente::escucharServidor(void * cli){
	Cliente* cliente=(Cliente *) cli;
	char mensajeDeServidor[60];

	while(1){
		recv(cliente->getDescriptor(),(void *)&mensajeDeServidor ,60,0);
		cout<<mensajeDeServidor<<endl;
	}
}


const std::string tiempoActual() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

void * Cliente::escribirServidor(void * cli){
	Cliente* cliente=(Cliente *) cli;

	int conectado=1;
	while(conectado){

		char msg[128];

		struct ifaddrs *myaddrs, *ifa;
	    void *in_addr;
	    char buf[64];

	    getifaddrs(&myaddrs);
	    
	    for (ifa = myaddrs; ifa != NULL; ifa = ifa->ifa_next)
	    {
	        if (ifa->ifa_addr == NULL)
	            continue;
	        if (!(ifa->ifa_flags & IFF_UP))
	            continue;

	        switch (ifa->ifa_addr->sa_family)
	        {
	            case AF_INET:
	            {
	                struct sockaddr_in *s4 = (struct sockaddr_in *)ifa->ifa_addr;
	                in_addr = &s4->sin_addr;
	                break;
	            }

	            default:
	                continue;
	        }

	        inet_ntop(ifa->ifa_addr->sa_family, in_addr, buf, sizeof(buf));
	        
	    }


		sprintf(msg,"%s,conectado en topologia estrella,%s",buf,tiempoActual().c_str());

		int i=send(cliente->getDescriptor(),(void *)msg,sizeof(msg),0);
		sleep(1);

		if(i==-1){
			conectado=0;
			cout<<"se desconecto del servidor"<<endl;
			close(cliente->getDescriptor());
			exit(EXIT_SUCCESS);
		}
	}	
}

void Cliente::conectarServidor(){

	int contador = 1;
	while(contador < 30){

		descriptorCliente= socket(AF_INET,SOCK_STREAM,0);

		servidorInfo.sin_family=AF_INET;

		inet_pton(AF_INET,ipServidor.c_str(),&servidorInfo.sin_addr);

		servidorInfo.sin_port=htons(puertoServidor);

		int conn=connect(descriptorCliente,(struct sockaddr *)&servidorInfo,sizeof(servidorInfo));
		if(conn!=-1){

			pthread_t hiloEscucha;
			pthread_create(&hiloEscucha,NULL,escucharServidor,(void *)this);

			pthread_t hiloEscribe;
			pthread_create(&hiloEscribe,NULL,escribirServidor,(void *)this);

			cout<<"Conectado!"<<endl;
			while(1);
		}else{

			cout<<"No se pudo conectar con el servidor, intento "<<contador++<<" de 30."<<endl;
			sleep(1);
		}
	}
}


void * Cliente::escucharNodoAnterior(void * cli){

	InformacionCliente * cliente=(InformacionCliente *) cli;
	char mensajeDeServidor[128];

	while(1){
		recv(cliente->getDescriptorCliente(),(void *)&mensajeDeServidor ,128,0);
		cout<<mensajeDeServidor<<endl;
	}
}

void * Cliente::aceptarClientes(void * c){
	int t = *((int*)(&c));
	int descriptorCliente;

	struct sockaddr_in InformacionClienter;
	int tamano= sizeof(struct sockaddr_in);
	cout<<"Aceptando cliente"<<endl;
	descriptorCliente=accept(t,(struct sockaddr *)&InformacionClienter,(socklen_t*) &tamano);
	
	//recibiendo clientes

	if(descriptorCliente!=-1){
		cout<< "Cliente Conectado"<<endl;
		InformacionCliente *aux = new InformacionCliente(descriptorCliente,InformacionClienter);
		
		pthread_t clientesHilos;
		
		pthread_create(&clientesHilos,NULL,&escucharNodoAnterior,(void *) aux);
	}
		

}

void Cliente::conectarAnillo(){
	struct sockaddr_in servidorInfo;
	int descriptorSer= socket(AF_INET,SOCK_STREAM,0);
	servidorInfo.sin_family=AF_INET;
	servidorInfo.sin_addr.s_addr=htonl(INADDR_ANY);
	servidorInfo.sin_port=htons(9080);
	int idBind=bind(descriptorSer,(struct sockaddr *)&servidorInfo, sizeof(servidorInfo));
	
	listen(descriptorSer, 2);



	pthread_t hiloEscucha;
	pthread_create(&hiloEscucha,NULL,&aceptarClientes,(void *)descriptorSer);


	int contador = 1;
	while(contador < 30){

		descriptorCliente= socket(AF_INET,SOCK_STREAM,0);

		servidorInfo.sin_family=AF_INET;

		inet_pton(AF_INET,ipServidor.c_str(),&servidorInfo.sin_addr);

		servidorInfo.sin_port=htons(puertoServidor);

		int conn=connect(descriptorCliente,(struct sockaddr *)&servidorInfo,sizeof(servidorInfo));
		if(conn!=-1){
			pthread_t hiloEscribe;
			pthread_create(&hiloEscribe,NULL,escribirServidor,(void *)this);

			cout<<"Conectado!"<<endl;
			while(1);
		}else{

			cout<<"No se pudo conectar con el siguiente nodo en el anillo, intento "<<contador++<<" de 30."<<endl;
			sleep(1);
		}
	}
}

int Cliente::getDescriptor(){
	return this->descriptorCliente;
}

void Cliente::setDescriptor(int descriptor){
	 this->descriptorCliente=descriptor;
}

int Cliente::getTipo(){
	return this->tipo;
}

void Cliente::setTipo(int tipo){
	 this->tipo=tipo;
}


bool Cliente::getEstado(){
	return this->estado;
}

void Cliente::setEstado(bool estado){
	 this->estado=estado;
}

