#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];
	// INICIALITZACIONS
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");
	// Fem el bind al port
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// escucharemos en el port 9050
	serv_adr.sin_port = htons(9050);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	//La cola de peticiones pendientes no podr? ser superior a 4
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");
	int i;
	//peticiones infinitas
	for(;;){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexi?n\n");
		//sock_conn es el socket que usaremos para este cliente
		char *p = strtok(peticion, "/");
		int codigo =  atoi (p);
		char nombre[20];
		p = strtok( NULL, "/");		
		int grados = atoi (p);
		printf ("Codigo: %d, Nombre: %s\n", codigo, grados);
		//Bucle de atención al cliente
		int terminar=0;
		while (terminar=0)
		{
			if (codigo ==1)
			{//Pasar de Celsius a Farenheit
				int farenheit = (grados*9/5) +32;
			sprintf (respuesta,"%d",farenheit);
			}
			else if (codigo ==2)
			{
				int celsius = (grados-32) *5/9;
				sprintf (respuesta,"%d",celsius);		
            
			}
			terminar = 1;
		}
		printf("Respuesta; %s\n", respuesta);			
		// Enviamos la respuesta
		write (sock_conn,respuesta, strlen(respuesta));
	}	     			
	// Se acabo el servicio para este cliente

close(sock_conn); 
		
}

