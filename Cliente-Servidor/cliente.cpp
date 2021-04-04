#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
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
    string text = "Connected to: Client";

    socket.connect(ip, 8080);
    socket.send(text.c_str(), text.length() + 1);
    socket.receive(buffer, sizeof(buffer), received);
    cout << buffer << endl;
    
    system("pause");
    return 0;
}