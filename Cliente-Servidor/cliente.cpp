#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "ClienteRes/ListaDobleEnlazada.cpp"
#include "ClienteRes/GUI.cpp"
#include "ClienteRes/JsonHandler.cpp"

using namespace sf;
using namespace std;
using namespace rapidjson;

int main(int argc, char *argv[])
{
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    char connectionType, mode;
    size_t received;
    Document RLV;
    Packet packetS, packetR;
    string json, terminal;
    bool highlightLine = false;
    JsonHandler jsonHandler;

    Node* head = nullptr;

    Font font;
    GUI gui;

    if (!font.loadFromFile("arial.ttf"))
        cout << "Couldn't load font" << endl;

    Text code, lineNumber, terminalT;
    string codeInput;
    code.setFont(font);
    code.setCharacterSize(15);
    code.setFillColor(Color::White);
    code.setPosition(50, 30);

    int lineCounter = 1;
    string lineStr = "<1>\n";
    lineNumber.setFont(font);
    lineNumber.setCharacterSize(15);
    lineNumber.setFillColor(Color::White);
    lineNumber.setPosition(5, 30);

    terminalT.setFont(font);
    terminalT.setCharacterSize(15);
    terminalT.setFillColor(Color::White);
    terminalT.setPosition(5, 540);

    socket.connect(ip, 8080);

    RenderWindow window(VideoMode(1500,1050), "C! IDE");

    socket.setBlocking(false);
    mode = 's';
    window.setKeyRepeatEnabled(true);

    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            int analyzeLines = gui.update(Vector2f(event.mouseButton.x,event.mouseButton.y));

            if (analyzeLines == 1)
            {
                clearDLList(&head);
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
                gui.lineUpdater("nothing");
                json = jsonHandler.jsonSender(head);
                terminal = jsonHandler.getTerminal();
                code.setPosition(50,30);
                lineNumber.setPosition(5,30);
                if (json == "error")
                {
                    highlightLine = false;
                }
                else if (json == "print")
                {
                    cout << "Requested to print in stdout";
                }
                else if (json != "error" && json != "print" && !json.empty())
                {
                    packetS << json;
                    if (socket.send(packetS))
                        cout << "I will now receive a message" << endl;
                    packetS.clear();
                    cout << json << endl;
                    highlightLine = true;
                }
            }
            else if (analyzeLines == 2)
            {
                highlightLine = false;
                jsonHandler.terminal.clear();
                terminal.clear();
                analyzeLines = 0;
                clearDLList(&head);
                jsonHandler.ints.clear();
                jsonHandler.longs.clear();
                jsonHandler.floats.clear();
                jsonHandler.doubles.clear();
                jsonHandler.chars.clear();
            }
            if (Keyboard::isKeyPressed(Keyboard::Down) && highlightLine)
            {
                Node* temp;
                temp = head;
                head = head->next;
                head->prev = temp;
                bool moveCode = gui.lineUpdater("down");
                if (moveCode)
                {
                    code.setPosition(code.getPosition().x, code.getPosition().y - 17);
                    lineNumber.setPosition(lineNumber.getPosition().x, lineNumber.getPosition().y - 17);
                }
                json = jsonHandler.jsonSender(head);
                terminal = jsonHandler.getTerminal();
                if (json == "error")
                {
                    highlightLine = false;
                }
                else if (json == "print")
                {
                    cout << "Requested to print in stdout";
                }
                else if (json != "error" && json != "print" && !json.empty())
                {
                    packetS << json;
                    if (socket.send(packetS))
                        cout << "I will now receive a message" << endl;
                    packetS.clear();
                    cout << json << endl;
                    highlightLine = true;
                }
            }

            switch(event.type)
            {
                case Event::Closed:
                    //printList(head);
                    window.close();
                    break;

                case Event::MouseWheelMoved:
                    if (event.mouseWheel.delta >= 0 )
                    {
                        if (!highlightLine && gui.codeBool)
                        {
                            if (code.getPosition().y <= 29 && lineNumber.getPosition().y <= 29)
                            {
                                code.setPosition(code.getPosition().x, code.getPosition().y + 5);
                                lineNumber.setPosition(lineNumber.getPosition().x, lineNumber.getPosition().y + 5);
                            }
                        }
                        else if (gui.stdoutBool)
                        {
                            if (terminalT.getPosition().y <= 539)
                                terminalT.setPosition(terminalT.getPosition().x, terminalT.getPosition().y + 5);
                        }
                        else if (gui.appLogBool)
                        {
                            cout << "applog is selected" << endl;
                        }
                    }
                    else if (event.mouseWheel.delta <= 0)
                    {
                        if (!highlightLine && gui.codeBool)
                        {
                            if (code.getPosition().y + code.getGlobalBounds().height >= 150) {
                                code.setPosition(code.getPosition().x, code.getPosition().y - 5);
                                lineNumber.setPosition(lineNumber.getPosition().x, lineNumber.getPosition().y - 5);
                            }
                        }
                        else if (gui.stdoutBool)
                        {
                            if (terminalT.getPosition().y + terminalT.getGlobalBounds().height >= 600)
                                terminalT.setPosition(terminalT.getPosition().x, terminalT.getPosition().y - 5);
                        }
                        else if (gui.appLogBool)
                        {
                            cout << "applog is selected" << endl;
                        }
                    }
                    break;
                    
                case Event::TextEntered:
                    if (gui.codeBool)
                    {
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
                    }
                
                system("clear");
                break;
            }
        }
        socket.receive(packetR);
        if (packetR.getData() != NULL)
        {
            RLV = jsonHandler.jsonReceiver(packetR);
            packetR.clear();
        }
        terminalT.setString(terminal);
        lineNumber.setString(lineStr);
        if (gui.codeBool)
            code.setString(codeInput + "_");
        else
            code.setString(codeInput);
        window.clear();
        gui.Render(&window, code, lineNumber, font, terminalT);
        window.display();
    }
    
    return 0;
}