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
    //Se definen la variables necesarias para la comunicacion por sockets
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    char connectionType, mode;
    size_t received;
    Document RLV;
    Packet packetS, packetR;
    string json, terminal, appLog, RLVStrA, RLVStrVal, RLVStrVar, RLVStrRef;
    bool highlightLine = false;
    JsonHandler jsonHandler;

    //Se define la cabeza para crear la lista enlazada
    Node* head = nullptr;

    //Se crean las variables graficas
    Font font;
    GUI gui;

    if (!font.loadFromFile("arial.ttf"))
        cout << "Couldn't load font" << endl;

    Text code, lineNumber, terminalT, appLogT, RLVAddr, RLVValue, RLVVariable, RLVReference;
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

    appLogT.setFont(font);
    appLogT.setCharacterSize(15);
    appLogT.setFillColor(Color::White);
    appLogT.setPosition(5, 770);

    RLVAddr.setFont(font);
    RLVAddr.setCharacterSize(20);
    RLVAddr.setFillColor(Color::Black);
    RLVAddr.setPosition(975, 50);

    RLVValue.setFont(font);
    RLVValue.setCharacterSize(20);
    RLVValue.setFillColor(Color::Black);
    RLVValue.setPosition(1190, 50);

    RLVVariable.setFont(font);
    RLVVariable.setCharacterSize(20);
    RLVVariable.setFillColor(Color::Black);
    RLVVariable.setPosition(1305, 50);

    RLVReference.setFont(font);
    RLVReference.setCharacterSize(20);
    RLVReference.setFillColor(Color::Black);
    RLVReference.setPosition(1412, 50);

    //Se conecta el cliente al socket
    socket.connect(ip, 8080);

    //Se crea la pantalla grafica
    RenderWindow window(VideoMode(1500,1050), "C! IDE");

    //Se ponen condiciones para el socket y pantalla
    socket.setBlocking(false);
    mode = 's';
    window.setKeyRepeatEnabled(true);

    //Se define el while loop principal
    while(window.isOpen())
    {
        //Se revisa por eventos que suceden en la pantalla
        Event event;
        while (window.pollEvent(event))
        {
            //Se revisa por click en los botones
            int analyzeLines = gui.update(Vector2f(event.mouseButton.x,event.mouseButton.y));

            //Si se presiona el boton de run se anaden las lineas a nodos de lista enlazada para enviar al handler
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
                    cout << "Requested to print in stdout" << endl;
                    highlightLine = true;
                }
                else if (json == "continue")
                {
                    cout << "Requested to continue" << endl;
                    highlightLine = true;
                }
                else if (json != "error" && json != "print" && json != "continue" && !json.empty())
                {
                    packetS << json;
                    if (socket.send(packetS))
                        cout << "I will now receive a message" << endl;
                    packetS.clear();
                    cout << json << endl;
                    highlightLine = true;
                }
            }
            //Si se presiona el boton de stop el programa detiene el corrido del codigo y limpia la terminal y variables creadas
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
                RLVStrA.clear();
                RLVStrVal.clear();
                RLVStrVar.clear();
                RLVStrRef.clear();
            }
            //Al presionar el boton de abajo en las flechas cuando se corre el codigo la linea siendo analizada baja
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
                    cout << "Requested to print in stdout" << endl;
                }
                else if (json == "continue")
                {
                    cout << "Requested to continue" << endl;
                    highlightLine = true;
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
                //Si se cierra la pantalla se termina el programa
                case Event::Closed:
                    //printList(head);
                    window.close();
                    break;

                    //Funcionalidad para hacer scroll de las diferentes partes de la interfaz grafica
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

                    //Funcionalidad para guardar codigo y desplegarlo en la pantalla
                case Event::TextEntered:
                    if (gui.codeBool && !highlightLine)
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

        //El socket esta constantemente recibiendo los mensajes
        socket.receive(packetR);


        //Si el mensaje recibido no se encuentra vacio
        if (packetR.getData() != NULL)
        {
            Document petition = jsonHandler.jsonReceiver(packetR);
            string type = petition["type"].GetString();

            if (type == "RLV"){

                RLV = jsonHandler.jsonReceiver(packetR);
                string memory = RLV["memory"].GetString();
                RLVStrA += memory + "\n\n";
                string value = RLV["value"].GetString();
                RLVStrVal += value + "\n\n";
                string variable = RLV["variable"].GetString();
                RLVStrVar += variable + "\n\n";
                string ref = RLV["ref"].GetString();
                RLVStrRef += ref + "\n\n";
                packetR.clear();
            }
            if (type == "msg"){
                //app log
            }
        }

        //Se pone el texto anadido a la pantalla
        appLogT.setString("APP LOG: \n" + appLog);
        terminalT.setString("STDOUT: \n" + terminal);
        lineNumber.setString(lineStr);
        RLVAddr.setString("Memory Addr\n\n" + RLVStrA);
        RLVValue.setString("Value\n\n" + RLVStrVal);
        RLVVariable.setString("Variable\n\n" + RLVStrVar);
        RLVReference.setString("Reference\n\n" + RLVStrRef);

        //Si se selecciona la parte del codigo se despliega un caracter para reconocer donde se encuentra
        if (gui.codeBool)
            code.setString(codeInput + "_");
        else
            code.setString(codeInput);

        //Se limpia la pantalla para evitar memory overflow y se vuelve a imprimir en la pantalla la interfaz
        window.clear();
        gui.Render(&window, code, lineNumber, font, terminalT, appLogT, RLVAddr, RLVValue, RLVVariable, RLVReference);
        window.display();
    }
    
    return 0;
}