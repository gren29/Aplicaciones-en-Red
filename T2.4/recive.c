#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h> 
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h> 
#include <unistd.h>
#include <arpa/inet.h>

int main(int agrc, char* argv[]){
   struct sockaddr_in sdir,cdir;
   bzero((char *)&sdir, sizeof(sdir));
    //printf("\n1PREServicio iniciado..");
    int pto = 3035;
   sdir.sin_family=AF_INET;
   sdir.sin_port=htons(pto); 
   sdir.sin_addr.s_addr=htonl(INADDR_ANY); 
   socklen_t ctam = sizeof(cdir);
   int sd,cd,v=1,op;
    //printf("\nPREServicio iniciado..");
    if((sd=socket(AF_INET,SOCK_STREAM,0))<0)
    perror("Error en la funcion socket()\n");
    op=setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&v,sizeof(v));
    if(op<0) perror("Error en la opcion de socket\n");
    if(bind(sd,(struct sockaddr *)&sdir,sizeof(sdir))<0){
        close(sd);
        perror("El puerto ya esta en uso\n");
    }
    printf("\nServicio iniciado...");
    printf("\n  Puerto: %d",pto);
    listen(sd,5);
    for(;;){
        if((cd=accept(sd,(struct sockaddr *)&cdir,&ctam))<0){
            perror("Error en funcion accept()\n");
            continue;
        }//if
        printf("\n  Cliente conectado desde -> %s:%d\n"
                    "Recibiendo datos...\n", 
        inet_ntoa(cdir.sin_addr),ntohs(cdir.sin_port));
        int n,datoInt;
        float datoFloat;
        char datoChar[50];
        double datoDouble;
        bzero(datoChar,sizeof(datoChar));
        //datoInt
        n = read(cd,&datoInt, sizeof(datoInt));
        printf("Dato Int: %d\n",datoInt);
        //datoFloat
        char datos[20];
        n= read(cd,datos, sizeof(datos));
        datoFloat= atof(datos);
        printf("Dato Float: %.02f\n",datoFloat);
        //datoChar
        n= read(cd,datoChar, sizeof(datoChar));
        printf("Dato Char: %s\n",datoChar);
        //datoDouble
        char datos2[40];
        n= read(cd,datos2, sizeof(datos2));
        printf("%s N: %d\n",datos2,n);
        datoDouble= atof(datos2);
        printf("Dato Double: %.08f\n",datoDouble);
        close(cd);
        }//for
    }//main



