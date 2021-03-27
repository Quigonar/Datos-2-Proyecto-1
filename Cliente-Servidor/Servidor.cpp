#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

#define PORT 8080

using namespace std;

string createJsonStr(string memory, int value, string name, int line)  //Se crea funcion para formatear un mensaje a formato json dados los parametros
{
    string jsonStr = "{\"type\": " + memory + ", \"value\": " + to_string(value) + ", \"name\": " + name + ", \"line\": " + to_string(line) + "}";
    return jsonStr;
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};                //Variable que va a almacenar el mensaje recibido de [1024] bytes
    string json = createJsonStr("0x00", 500, "a", 1);      //Ejemplo de uso para la funcion
    const char *jsonChar = json.c_str();                //Se convierte el string a const char* porque ocupa este formato para ser enviado
       
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)     //Da error al fallar la creacion del socket
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) //Da error al fallar la conexion del socket al puerto
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) //Da error al fallar la conexion del socket con el address
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)   //Da error al no poder escuchar en el socket
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) //Da error al fallar el aceptar al cliente
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read( new_socket , buffer, 1024);
    cout << "Message received: " << buffer << endl;         //Despliega el mensaje recibido
    send(new_socket , jsonChar , strlen(jsonChar) , 0 );
    cout << "Message sent: " << jsonChar;                   //Envia notificacion de que el mensaje se envio
    return 0;
}