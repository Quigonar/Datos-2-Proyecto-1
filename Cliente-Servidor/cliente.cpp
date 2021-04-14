#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include "rapidjson/document.h"
#include "ClienteRes/ListaDobleEnlazada.cpp"
#include "ClienteRes/GUI.cpp"

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

/*string jsonSender(string type, string value, string variable, string line)
{
    string jsonStr = "{\"type\":"+ type + ",\"value\":" + value + ",\"variable\":" + variable + ",\"line\":" + line + "}";
    return jsonStr;
}*/

string jsonSender(Node* node)
{
    string type, value, variable, line, delimiter;
    int n;
    vector<string> lineSplit;
    vector<string>::iterator it;
    line = node->data;
    string types[7] = {"int", "long", "char", "float", "double", "struct", "reference"};

    delimiter = " ";
    auto start = 0U;
    auto end = line.find(delimiter);
    while (end != string::npos)
    {
        lineSplit.push_back(line.substr(start, end - start));
        start = end + delimiter.length();
        end = line.find(delimiter, start);
    }
    lineSplit.push_back(line.substr(start, end));

    for (n = 0; n < 7; n++)
    {
        if (lineSplit.front().compare(types[n]) == 0)
        {
            type = types[n];
            it = lineSplit.begin();
            lineSplit.erase(it);
        }
        else
        {
            cout << "Error code syntaxis is wrong" << endl;
            break;
        }
    }

    for (auto i = lineSplit.begin(); i != lineSplit.end(); i++)
        cout << *i << ", ";

    string jsonStr = "{\"type\":"+ type + ",\"value\":" + value + ",\"variable\":" + variable + "}";
    return jsonStr;
}

int main()
{
    //IpAddress ip = IpAddress::getLocalAddress();
    //TcpSocket socket;
    char connectionType, mode;
    //size_t received;
    //Document RLV;
    //Packet packetS, packetR;
    string json;
    //Text playerText;

    Node* head = nullptr;

    Font font;
    GUI gui;

    if (!font.loadFromFile("arial.ttf"))
        cout << "Couldn't load font" << endl;

    Text code;
    string codeInput;
    code.setFont(font);
    code.setCharacterSize(15);
    code.setFillColor(Color::White);
    code.setPosition(50, 30);

    Text lineNumber;
    int lineCounter = 1;
    string lineStr = "<1>\n";
    lineNumber.setFont(font);
    lineNumber.setCharacterSize(15);
    lineNumber.setFillColor(Color::White);
    lineNumber.setPosition(5, 30);

    //socket.connect(ip, 8080);

    RenderWindow window(VideoMode(1400,800), "C! IDE");

    //socket.setBlocking(false);
    mode = 's';
    window.setKeyRepeatEnabled(true);

    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case Event::Closed:
                    //printList(head);
                    cout << json << endl;
                    window.close();
                    break;

                case Event::MouseWheelMoved:
                    if (event.mouseWheel.delta >= 0)
                    {
                        if (code.getPosition().y <= 33 && lineNumber.getPosition().y <= 33)
                        {
                            code.setPosition(code.getPosition().x, code.getPosition().y + 7);
                            lineNumber.setPosition(lineNumber.getPosition().x, lineNumber.getPosition().y + 7);
                        }
                    }
                    else
                    {
                        if (code.getPosition().y + code.getGlobalBounds().height >= 200)
                        {
                            code.setPosition(code.getPosition().x, code.getPosition().y - 5);
                            lineNumber.setPosition(lineNumber.getPosition().x, lineNumber.getPosition().y - 5);
                        }
                    }
                    break;
                    
                case Event::TextEntered:
                    if(event.text.unicode == 8)
                    {
                        if (codeInput.back() == '\n')
                        {
                            codeInput = codeInput.substr(0, codeInput.length() - 1);
                            if (lineCounter >= 10)
                            {
                                lineStr = lineStr.substr(0, lineStr.length() - 5);
                                lineCounter --;
                            }
                            else
                            {
                                lineStr = lineStr.substr(0, lineStr.length() - 4);
                                lineCounter --;
                            }

                        }
                        else
                            codeInput = codeInput.substr(0, codeInput.length() - 1);


                    }
                    else if(event.text.unicode == 13)
                    {
                        lineCounter ++;
                        codeInput = codeInput.append("\n");
                        lineStr = lineStr.append("<" + to_string(lineCounter) + ">\n");
                    }
                    else
                    {
                        codeInput += (char)event.text.unicode;
                    }
                
                system("clear");
                break;
            }
        }

        bool analyzeLines = gui.update(Vector2f(event.mouseButton.x,event.mouseButton.y));

        if (analyzeLines)
        {
            string delimiter = "\n";
            auto start = 0U;
            auto end = codeInput.find(delimiter);
            while (end != string::npos)
            {
                insert_end(&head, codeInput.substr(start, end - start));
                start = end + delimiter.length();
                end = codeInput.find(delimiter, start);
            }
            insert_end(&head, codeInput.substr(start, end));
            json = jsonSender(head);
        }

        /*
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
            if (!packetR.getData() == NULL)
            {
                cout << packetR.getData() << endl;
                RLV = jsonReceiver(packetR);
                mode = 's';
            }
        }*/

        lineNumber.setString(lineStr);
        code.setString(codeInput + "_");
        window.clear();
        gui.Render(&window, code, lineNumber);
        window.display();
    }
    
    return 0;
}