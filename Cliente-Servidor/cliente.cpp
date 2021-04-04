#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    char connectionType, mode, buffer[2000];
    size_t received;
    socket.connect(ip, 8080);
    cout << "Connected to server" << endl;

    RenderWindow window(VideoMode(800,600), "Servidor");

    socket.setBlocking(false);

    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || event.key.code == Keyboard::Escape)
                window.close();
        }
        Packet packet;
        

        window.display();
        window.clear();
    }

    //socket.send(text.c_str(), text.length() + 1);
    //socket.receive(buffer, sizeof(buffer), received);
    //cout << buffer << endl;
    
    system("pause");
    return 0;
}