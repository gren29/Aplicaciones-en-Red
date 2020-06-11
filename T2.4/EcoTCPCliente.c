//Cliente EcoTCPCliente.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "MensajeError.h"
#define TAMBUFER 2000

int main(int argc, char** argv) {
        if (argc < 3|| argc >4)
              mensajeFinalError(
            "Uso: EcoTCPCliente <Dirección del servidor> <Palabra de eco> [<Puerto>]");
        char *servIP = argv[1];
        char *cadenaEco = argv[2];
        //Argumento opcional, se agrega por defecto
        in_port_t puerto = (argc == 4) ? atoi(argv[3]) : 7;
        //Crea el socket del cliente TCP
        int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(s < 0){
                mensajeFinalError("Error de apertura del conector");
        }
        //Creamos la dirección del servidor de entrada
        struct sockaddr_in dirServ;
        memset(&dirServ,0,sizeof(dirServ));
        dirServ.sin_family = AF_INET;
        int valRet = inet_pton(AF_INET,servIP,&dirServ.sin_addr.s_addr);
        if(valRet == 0)
                mensajeFinalError(
		"Dirección del servidor erronea");
        else if(valRet < 0)
                mensajeFinalError("Error en el inet_pton()");
        dirServ.sin_port = htons(puerto);
        //Establecemos la comunicación con el servidor de eco
        if(connect(s, (struct sockaddr*) &dirServ,sizeof(dirServ))<0)
                mensajeFinalError("Error en la conexión");
        size_t longCadenaEco = strlen(cadenaEco);
        //Envia el mensaje al servidor
        ssize_t numBytes = send(s,cadenaEco,longCadenaEco, 0);
        if(numBytes< 0)
                mensajeFinalError("Fallo el envio");
        else if(numBytes != longCadenaEco)
                mensajeFinalError("Número de bytes enviados erroneo");
        //Recibimos de vuelta la cadena desde el servidor
        unsigned int totalBytesRec = 0;
        while(totalBytesRec < longCadenaEco){
   		char bufer[TAMBUFER];
                memset(bufer,0,TAMBUFER);
                numBytes = recv(s,bufer,TAMBUFER, 0);

                 if(numBytes<0)
                        mensajeFinalError("Recepción fallida");
                else if(numBytes==0)
                        mensajeFinalError(
                              "Conexión cerrada prematuramente");
                totalBytesRec += numBytes;
                printf("Recibido: %s\n",bufer);
        }
        close(s);
        return 0;
}
