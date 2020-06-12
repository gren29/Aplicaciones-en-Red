#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h> //printf, perror,fdopen
#include <string.h>
#include <netdb.h> //gethostbyname
#include <unistd.h>//close
#include <stdlib.h> //exit

int main(int argc, char* argv[]){
    char host[10] = "127.0.0.1";
    int pto;
    printf("\nEscribe el puerto:");
    scanf("%d",&pto);
    fflush(stdin);
    struct hostent *dst = gethostbyname(host);
    if(dst==NULL)perror("Direccion no valida");
    struct sockaddr_in sdir;
    bzero((char *)&sdir, sizeof(sdir));
    sdir.sin_family=AF_INET;
    sdir.sin_port=htons(pto);
    memcpy((char*)&sdir.sin_addr.s_addr,dst->h_addr,  dst->h_length);
    int cd = socket(AF_INET,SOCK_STREAM,0);
    FILE *f = fdopen(cd,"w+");
    if (connect(cd,(struct sockaddr *)&sdir,sizeof(sdir))<0)
    perror("error en funcion connect()\n");
    printf("\n Conexion establecida.. enviando datos..\n");

    int datoInt,n;
    float datoFloat;
    char datoChar[20];
    float datoDouble;
    printf("\nIngrese Int: ");
    scanf("%d",&datoInt);
    printf("\nIngrese Float: ");
    scanf("%f",&datoFloat);
    printf("\nIngrese mensaje: ");
    scanf("%s",datoChar);
    printf("\nIngrese Double: ");
    scanf("%f",&datoDouble);
    char *datoCharS=datoChar;
    //datoInt
    n = write(cd,&datoInt,sizeof(datoInt));
    if(n<0)perror("Error de escritura\n");
    else if(n==0) perror("Socket cerrado error de escritura\n");
    else fflush(f);
    printf("Se envio Int: %d\n",datoInt);
    //datoFloat
    char datos[10];
    sprintf(datos,"%f",datoFloat);
    n = write(cd,datos,strlen(datos));
    if(n<0) 
	perror("Error de escritura\n");
    else if(n==0) perror("Socket cerrado\n");
    else printf("Se envio Float: %.02f\n",datoFloat);
    fflush(f);
    //datoChar
    n = write(cd,datoCharS,strlen(datoCharS)+1);
    if(n<0)perror("Error de escritura\n");
    else if(n==0)perror("Socket cerrado error de escritura\n");
    else printf("Se envio Char: %s\n",datoCharS);
    fflush(f);
    //datoDouble
    char datos2[40];
    sprintf(datos2,"%lf",datoDouble);
    n = write(cd,datos2,strlen(datos2));
    if(n<0)perror("Error de escritura\n");
    else if(n==0) perror("Socket cerrado\n");
    else printf("Se envio Double: %.08f\n",datoDouble);
    fflush(f);
    close(cd);
    fclose(f);
    return 0;
}//main



