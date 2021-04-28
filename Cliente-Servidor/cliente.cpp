/**
 * @file cliente.cpp
 * @version 1.0
 * @title cliente
 * @brief Manejo de todo el IDE del usuario
 */
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "ClienteRes/ListaDobleEnlazada.cpp"
#include "ClienteRes/GUI.cpp"
#include "ClienteRes/JsonHandler.cpp"
#include "RLVList/RLVlist.cpp"

using namespace sf;
using namespace std;
using namespace rapidjson;
/**
 * @brief main es el main del IDE o cliente
 */
int main(int argc, char *argv[])
{
    //Se definen la variables necesarias para la comunicacion por sockets
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    char connectionType, mode;
    size_t received;
    Document RLV;
    Packet packetS, packetR;
    vector<string> addRef;
    string json, terminal, appLog, RLVStrA, RLVStrVal, RLVStrVar, RLVStrRef, lastAppLog;
    bool highlightLine = false;
    RLVlist rlvlist;
    JsonHandler jsonHandler(&rlvlist);


    //Se define la cabeza para crear la lista enlazada
    Node* head = nullptr;

    //Se crean las variables graficas
    Font font;
    GUI gui;

    //Si no logra cargar el font del archivo
    if (!font.loadFromFile("arial.ttf"))
        cout << "Couldn't load font" << endl;

    //Creacion de todos los textos que se pueden desplegar en el IDE
    Text code, lineNumber, terminalT, appLogT, RLVAddr, RLVValue, RLVVariable, RLVReference;
    //Codigo
    string codeInput;
    code.setFont(font);
    code.setCharacterSize(15);
    code.setFillColor(Color::White);
    code.setPosition(50, 30);

    //Linea del codigo
    int lineCounter = 1;
    string lineStr = "<1>\n";
    lineNumber.setFont(font);
    lineNumber.setCharacterSize(15);
    lineNumber.setFillColor(Color::White);
    lineNumber.setPosition(5, 30);

    //STDOUT
    terminalT.setFont(font);
    terminalT.setCharacterSize(15);
    terminalT.setFillColor(Color::White);
    terminalT.setPosition(5, 540);

    //Application Log
    appLogT.setFont(font);
    appLogT.setCharacterSize(15);
    appLogT.setFillColor(Color::White);
    appLogT.setPosition(5, 770);

    //RAM Live View address
    RLVAddr.setFont(font);
    RLVAddr.setCharacterSize(20);
    RLVAddr.setFillColor(Color::Black);
    RLVAddr.setPosition(975, 50);

    //RAM Live View value
    RLVValue.setFont(font);
    RLVValue.setCharacterSize(20);
    RLVValue.setFillColor(Color::Black);
    RLVValue.setPosition(1190, 50);

    //RAM Live View variable
    RLVVariable.setFont(font);
    RLVVariable.setCharacterSize(20);
    RLVVariable.setFillColor(Color::Black);
    RLVVariable.setPosition(1390, 50);

    //RAM Live View reference
    RLVReference.setFont(font);
    RLVReference.setCharacterSize(20);
    RLVReference.setFillColor(Color::Black);
    RLVReference.setPosition(1515, 50);

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
                //Se divide las lineas del codigo y se insertan en nodos
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
                //Si el JsonHandler devuelve un error el programa
                if (json == "error")
                {
                    highlightLine = false;
                }
                //Si el JsonHandler devuelve un print o continue continua el programa con stdout actualizado
                else if (json == "print" || json == "continue")
                {
                    highlightLine = true;
                }
                //Si el json esta bien formateado entonces se envia
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
                jsonHandler.addRef.clear();
                jsonHandler.referencesI.clear();
                jsonHandler.referencesL.clear();
                jsonHandler.referencesF.clear();
                jsonHandler.referencesD.clear();
                jsonHandler.referencesC.clear();
                jsonHandler.structName.clear();
                jsonHandler.isStruct = false;
                jsonHandler.structs.clear();
                jsonHandler.counter = 1;
                RLVStrA.clear();
                RLVStrVal.clear();
                RLVStrVar.clear();
                RLVStrRef.clear();
                rlvlist.clear();
                string type = "free";
                json = R"({"type":")"+ type + R"(","value":")" + "value" + R"(","variable":")"+"variable"+"\"}";
                packetS << json;
                if (socket.send(packetS))
                    cout << "I will now receive a message" << endl;
                packetS.clear();
                cout << json << endl;
                appLog = "";
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
                addRef = jsonHandler.getAddRef();

                //Si el JsonHandler devuelve un error el programa
                if (json == "error")
                {
                    highlightLine = false;
                }
                //Si el JsonHandler devuelve un print o continue continua el programa con stdout actualizado
                else if (json == "print" || json == "continue")
                {
                    highlightLine = true;
                }
                //Si el json esta bien formateado entonces se envia
                else if (json != "error" && json != "print" && !json.empty())
                {
                    packetS << json;
                    if (socket.send(packetS))
                        cout << "I will now receive a message" << endl;
                    packetS.clear();
                    cout << json << endl;
                    highlightLine = true;

                    Packet tmp;
                    tmp << json;
                    Document check = jsonHandler.jsonReceiver(tmp);
                    string variable = check["variable"].GetString();
                    string type = check["type"].GetString();
                    //Revisa si el json es para que el garbage collector funcione o no
                    if ( type == "garbage"){
                        vector<string> variables;
                        string delimiter = ",";
                        auto start = 0U;
                        auto end = variable.find(delimiter);
                        while (end != string::npos)
                        {
                            variables.push_back(variable.substr(start, end - start));
                            start = end + delimiter.length();
                            end = variable.find(delimiter, start);
                        }
                        variables.push_back(variable.substr(start, end));
                        cout<< rlvlist.get_name() <<endl;
                        for (auto & i : variables) {
                            rlvlist.RLVupdate(i);
                        }
                        RLVStrA = rlvlist.get_memory();
                        RLVStrVal = rlvlist.get_value();
                        RLVStrVar = rlvlist.get_name();
                        RLVStrRef = rlvlist.get_ref();
                    }
                }
                //Si se da el caso de anadir una referencia se lo envia al servidor para que aumente la referencia
                if (!addRef.empty())
                {
                    for (auto & i : addRef)
                    {
                        packetS << i;
                        if (socket.send(packetS))
                            cout << "I will now receive a message" << endl;
                        packetS.clear();
                        cout << i << endl;
                        highlightLine = true;
                    }
                    addRef.clear();
                    jsonHandler.addRef.clear();
                }
            }
            switch(event.type)
            {
                //Si se cierra la pantalla se termina el programa
                case Event::Closed:
                    socket.disconnect();
                    window.close();
                    break;

                    //Funcionalidad para hacer scroll de las diferentes partes de la interfaz grafica
                case Event::MouseWheelMoved:
                    if (event.mouseWheel.delta >= 0 )
                    {
                        //Si se esta analizando el codigo no sirve la funcion de scroll
                        if (!highlightLine && gui.codeBool)
                        {
                            //Si la posicion del texto es menor al tope de la pantalla no sirve
                            if (code.getPosition().y <= 29 && lineNumber.getPosition().y <= 29)
                            {
                                code.setPosition(code.getPosition().x, code.getPosition().y + 5);
                                lineNumber.setPosition(lineNumber.getPosition().x, lineNumber.getPosition().y + 5);
                            }
                        }
                    }
                    else if (event.mouseWheel.delta <= 0)
                    {
                        //Si se esta analizando el codigo no sirve la funcion de scroll
                        if (!highlightLine && gui.codeBool)
                        {
                            //Si la posicion del texto es mayor a la mitad de la pantalla no sirve
                            if (code.getPosition().y + code.getGlobalBounds().height >= 150) {
                                code.setPosition(code.getPosition().x, code.getPosition().y - 5);
                                lineNumber.setPosition(lineNumber.getPosition().x, lineNumber.getPosition().y - 5);
                            }
                        }
                    }
                    break;

                    //Funcionalidad para guardar codigo y desplegarlo en la pantalla
                case Event::TextEntered:
                    //Si no se esta analizando el codigo y se tiene seleccionado la pantalla del code
                    if (gui.codeBool && !highlightLine)
                    {
                        //Casos especiales de borrar o space
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
                        //Si no nada mas agarra el char y lo anade al string
                        else
                        {
                            codeInput += (char)event.text.unicode;
                        }
                    }
                
                system("clear");
                break;
            }
        }
        //Si el applog se llena se eliminan las lineas pasadas y se pone la ultima linea como primera
        if (appLogT.getPosition().y + appLogT.getGlobalBounds().height >= 1000)
            appLog = lastAppLog + "\n";

        //El socket esta constantemente recibiendo los mensajes
        socket.receive(packetR);


        //Si el mensaje recibido no se encuentra vacio
        if (packetR.getData() != NULL)
        {
            Document petition = jsonHandler.jsonReceiver(packetR);
            string type = petition["type"].GetString();

            //Si el tipo de mensaje es para updatear el RAM Live Viewer
            if (type == "RLV"){
                RLV = jsonHandler.jsonReceiver(packetR);
                string memory = RLV["memory"].GetString();

                string value = RLV["value"].GetString();

                string variable = RLV["variable"].GetString();

                string ref = RLV["ref"].GetString();

                rlvlist.append(memory,value,variable,ref);
                RLVStrA = rlvlist.get_memory();
                RLVStrVal = rlvlist.get_value();
                RLVStrVar = rlvlist.get_name();
                RLVStrRef = rlvlist.get_ref();
                packetR.clear();
            }
            //Si el tipo de mensaje es para updatear el Application Log
            if (type == "msg"){
                string log = petition["msg"].GetString();
                lastAppLog = log;
                appLog += log + "\n";
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