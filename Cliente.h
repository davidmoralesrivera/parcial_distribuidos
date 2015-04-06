#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <cstdio>
#include <stdlib.h>
#include <pthread.h>
#include <sstream>
#include <vector>
#include <net/if.h>
#include <ifaddrs.h>
#include <errno.h>


#ifndef CLIENTE_H_
#define CLIENTE_H_
#define ESTRELLA 1
#define ANILLO 2

using namespace std;

class Cliente{

	private:
		int tipo;
		int descriptorCliente;
		struct sockaddr_in servidorInfo;
		int puertoServidor;
		string ipServidor;
		bool estado;

	public:
		Cliente(void);
		Cliente(int, string);

		void conectarServidor(void);
		void conectarAnillo(void);
		static void * escucharServidor(void*);
		static void * escribirServidor(void*);
		static void * escucharNodoAnterior(void*);
		static void * aceptarClientes(void*);
		
		int getDescriptor(void);
		void setDescriptor(int);

		int getTipo(void);
		void setTipo(int);

		bool getEstado(void);
		void setEstado(bool);
};


#endif /* CLIENTE_H_ */
