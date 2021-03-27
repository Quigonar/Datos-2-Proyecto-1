#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <rapidjson/document.h>
#include "JsonHandler.cpp"

#define PORT 8080

using namespace std;

string createJsonStr(string type, string name, int value, int line)    //Se crea funcion para formatear un mensaje a formato json dados los parametros
{
    string jsonStr = "{\"type\": " + type + ", \"name\": " + name + ", \"size\": " + to_string(value) + ", \"line\": " + to_string(line) + "}";
    return jsonStr;
}
   
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;       //Mensaje que se quiere enviar
    char buffer[1024] = {0};            //Variable que va a almacenar el mensaje recibido de [1024] bytes
    string json = createJsonStr("int", "a", 500, 1);   //Ejemplo de uso para la funcion
    const char *jsonChar = json.c_str();    //Se convierte el string a const char* porque ocupa este formato para ser enviado
    

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)  //Envia un error al fallar la creacion del socket
    {
        cout << "\n Socket creation error \n";
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)     //Envia un error al usar un address erroneo
    {
        cout << "\nInvalid address/ Address not supported \n";
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)    //Envia un error al fallar la conexion con el servidor
    {
        cout << "\nConnection Failed \n";
        return -1;
    }
    write(sock, jsonChar, strlen(jsonChar));              
    cout << "Message sent: " << jsonChar << endl;                   //Envia notificacion del mensaje enviado
    valread = read( sock , buffer, 1024);
    cout << "Message received: " << buffer << endl;         //Despliega el mensaje recibido

    return 0;
}
