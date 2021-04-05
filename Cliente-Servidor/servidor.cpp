#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "rapidjson/document.h"
#include <string>
#include <iostream>

using namespace sf;
using namespace std;
using namespace rapidjson;
Document jsonReceiver(Packet packet)
{
    string pet;
    Document petD;

    packet >> pet;
    cout << pet << endl;
    const char* petChar = pet.c_str();
    petD.Parse(petChar);

    return petD;
}

string jsonSender(string memory, string value, string variable, string line)
{
    string jsonStr = "{\"memory\":"+ memory + ",\"value\":" + value + ",\"variable\":" + variable + ",\"line\":" + line + "}";
    return jsonStr;
}

int main()
{
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    char connectionType, mode;
    bool done = false;
    Packet packetR, packetS;
    size_t received;
    Document petition;
    string json;

    TcpListener listener;
    listener.listen(8080);
    listener.accept(socket);
    mode = 'r';
    
    while (!done)
    {
        Event event;
        if (event.key.code == Keyboard::Escape)
            done = true;
        
        socket.receive(packetR);

        if (packetR.getData() == NULL)
            cout << "No message received yet" << endl;

        else
        {
            petition = jsonReceiver(packetR);
            Value& type = petition["type"];
            Value& value = petition["value"];
            Value& variable = petition["variable"];
            Value& line = petition["line"];

            if (type.GetString() == "int")
            {
                //Hace offset de 4 bytes
            }
            else if (type.GetString() == "long")
            {
                //Hace offset de 8 bytes
            }
            else if (type.GetString() == "char")
            {
                //Hace offset de 1 byte
            }
            else if (type.GetString() == "float")
            {
                //Hace offset de 4 bytes
            }
            else if (type.GetString() == "double")
            {
                //Hace offset de 8 bytes
            }
            else if (type.GetString() == "struct")
            {
                //Sigue sintaxis de C
            }
            else if (type.GetString() == "reference")
            {
                //Hace offset de 4 bytes
            }

            json = jsonSender("0x000", value.GetString(), variable.GetString(), line.GetString());
            packetS << json;
            socket.send(packetS);
        }
    }
    
    return 0;
}