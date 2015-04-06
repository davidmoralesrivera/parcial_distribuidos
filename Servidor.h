#include "InformacionCliente.h"

#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#define maxClientes 100
#define ESTRELLA 1
#define ANILLO 2

class Servidor{


	private:
		int tipo;
		int descriptorSer;
		int idBind;
		int puerto;
		struct sockaddr_in servidorInfo; 
		vector<InformacionCliente *> clientesDescriptor;

		bool state;
	public:
		
		
		Servidor(void);
		Servidor(int);

		void inicializarServidor(void);
		void aceptarClientes(void);
		void cerrarServidor(void);	
		static void * comenzarServidor(void *);
		void ejecutarServidor(void);


		void setDescriptorServidor(int);
		int getDescriptorServidor(void);
		
		void setPuerto(int);
		int getPuerto(void);

		void setTipo(int);
		int getTipo(void);
		
		void setIdBin(int);
		int getIdBin(void);
		struct sockaddr_in getServidorInfo(void);
		void setServidorInfo(struct sockaddr_in);
		
		vector<InformacionCliente *> getClientes(void);

}; 

#endif /* SERVIDOR_H_ */