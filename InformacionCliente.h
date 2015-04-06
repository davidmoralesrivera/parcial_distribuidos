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
#include <string>
#include <fstream>



#ifndef INFROMACIONCLIENTE_H_
#define INFROMACIONCLIENTE_H_


using namespace std;

class InformacionCliente{

	private:
		int descriptorCliente;
		struct sockaddr_in informacionCliente; 
		bool estado;
		int id;
	public:
		
		InformacionCliente(int ,struct sockaddr_in);

		int getId(void);
		void setId(int);

		int getDescriptorCliente(void);
		struct sockaddr_in getInformacionCliente();

		bool getEstado(void);
		void setEstado(bool);


};

#endif /* INFROMACIONCLIENTE_H_ */