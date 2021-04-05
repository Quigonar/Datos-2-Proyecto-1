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

string jsonSender(string type, string value, string variable, string line)
{
    string jsonStr = "{\"type\":"+ type + ",\"value\":" + value + ",\"variable\":" + variable + ",\"line\":" + line + "}";
    return jsonStr;
}

int main()
{
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    char connectionType, mode;
    size_t received;
    Document RLV;
    Packet packetS, packetR;
    string json;

    socket.connect(ip, 8080);

    RenderWindow window(VideoMode(1000,800), "C! IDE");

    socket.setBlocking(false);
    mode = 's';

    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || event.key.code == Keyboard::Escape)
                window.close();
        }

        json = jsonSender("int", "20", "a", "1");
        packetS << json;
        
        if (mode == 's')
        {
            if (socket.send(packetS))
            {
                cout << "I will now receive a message" << endl;
                mode = 'r';
            }
            else
                cout << "Message hasn't been sent" << endl;
        }
        else if (mode == 'r')
        {
            socket.receive(packetR);
            if (packetR.getData() == NULL)
                cout << "No message received yet" << endl;
                
            else
            {
                cout << packetR.getData() << endl;
                RLV = jsonReceiver(packetR);
                mode = 's';
            }
        }

        window.display();
        window.clear();
    }
    
    return 0;
}