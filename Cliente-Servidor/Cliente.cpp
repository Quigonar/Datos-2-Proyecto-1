#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#define PORT 8080
   
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";  //Mensaje que se quiere enviar
    char buffer[1024] = {0};            //Variable que va a almacenar el mensaje recibido de [1024] bytes

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)  //Envia un error al fallar la creacion del socket
    {
        std::cout << "\n Socket creation error \n";
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)     //Envia un error al recibir un address erroneo
    {
        std::cout << "\nInvalid address/ Address not supported \n";
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)    //Envia un error al fallar la conexion con el servidor
    {
        std::cout << "\nConnection Failed \n";
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
    std::cout << "Hello message sent\n";    //Envia notificacion de que el mensaje fue enviado
    valread = read( sock , buffer, 1024);
    std::cout << buffer;                    //Despliega el mensaje recibido
    return 0;
}