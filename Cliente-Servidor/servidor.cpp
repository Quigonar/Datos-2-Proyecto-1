#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "rapidjson/document.h"
#include <string>
#include <iostream>
#include "MemoryManager.cpp"
#include <sstream>

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

string jsonSender(string memory, string value, string variable,string ref)
{
    string jsonStr = "{\"memory\":"+ memory + ",\"value\":" + value + ",\"variable\":" + variable + ",\"ref\":" + ref+ "}";
    return jsonStr;
}

int int_parse(string s){
    stringstream ss(s);
    int tmp = 0;
    ss>>tmp;
    return tmp;
}
long long long_parse(string s){
    stringstream ss(s);
    long long tmp = 0;
    ss>>tmp;
    return tmp;
}

char char_parse(string s){
    stringstream ss(s);
    char tmp = '0';
    ss>>tmp;
    return tmp;
}

float float_parse(string s){
    stringstream ss(s);
    float tmp = 0.0;
    ss>>tmp;
    return tmp;
}

double double_parse(string s){
    stringstream ss(s);
    double tmp = 0.0;
    ss>>tmp;
    return tmp;
}

string int_tostring(int num){
    ostringstream o;
    o << num;
    string snum = o.str();
    return snum;
}


string mem_parse(void* ptr){
    ostringstream o;
    o<<ptr;
    string addr = o.str();
    return addr;
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
    MemoryManager mserver(10*10*10*10*10);

    while (!done)
    {
        Event event;
        if (event.key.code == Keyboard::Escape)
            done = true;
        
        socket.receive(packetR);

        if (packetR.getData() == NULL)
            //cout << "No message received yet" << endl;
            done = false;

        else
        {
            petition = jsonReceiver(packetR);
            string value = petition["value"].GetString();
            string type = petition["type"].GetString();
            string variable = petition["variable"].GetString();

            int offset;

            if (type == "int")
            {
                //revisar si variable ya existe.
                if(!mserver.getlist("int")->findvar(variable)){
                    offset = mserver.getoffset();
                    int val = int_parse(value);

                    bool paso = mserver.addvariableint(val,variable);

                    if(paso){
                        string addr = mem_parse((void*)mserver.getmemoryoffsetint(offset));
                        string xref = int_tostring(mserver.get_varref("int",variable));
                        json = jsonSender(addr,value,variable,xref);
                        mserver.printmem();
                    }
                    else{
                        //retorna error para que salga en consola falta de memoria
                    }
                }
                else{
                    //redefine el valor de esa variable
                }

            }
            else if (type == "long")
            {
                //revisar si variable ya existe.
                if(!mserver.getlist("long")->findvar(variable)) {
                    offset = mserver.getoffset();
                    long long val = long_parse(value);

                    bool paso = mserver.addvariablelong(val, variable);

                    if (paso) {
                        string addr = mem_parse((void *) mserver.getmemoryoffsetlong(offset));
                        string xref = int_tostring(mserver.get_varref("long", variable));
                        json = jsonSender(addr, value, variable, xref);
                        mserver.printmem();
                    } else {
                        //retorna error para que salga en consola falta de memoria
                    }
                }
                else{
                    //redefine el valor de esa variable
                }
            }
            else if (type == "char")
            {
                if(!mserver.getlist("char")->findvar(variable)) {
                    offset = mserver.getoffset();
                    char val = char_parse(value);

                    bool paso = mserver.addvariablechar(val, variable);

                    if (paso) {
                        string addr = mem_parse((void *) mserver.getmemoryoffsetchar(offset));
                        string xref = int_tostring(mserver.get_varref("char", variable));
                        json = jsonSender(addr, value, variable, xref);
                        mserver.printmem();
                    } else {
                        //retorna error para que salga en consola falta de memoria
                    }
                }
                else{
                    //redefine el valor de esa variable
                }
            }
            else if (type == "float")
            {
                if(!mserver.getlist("float")->findvar(variable)) {
                    offset = mserver.getoffset();
                    float val = float_parse(value);

                    bool paso = mserver.addvariablefloat(val, variable);

                    if (paso) {
                        string addr = mem_parse((void *) mserver.getmemoryoffsetfloat(offset));
                        string xref = int_tostring(mserver.get_varref("float", variable));
                        json = jsonSender(addr, value, variable, xref);
                        mserver.printmem();
                    } else {
                        //retorna error para que salga en consola falta de memoria
                    }
                }
                else{
                    //redefine el valor de esa variable
                }
            }
            else if (type == "double")
            {
                if(!mserver.getlist("double")->findvar(variable)) {
                    offset = mserver.getoffset();
                    double val = double_parse(value);

                    bool paso = mserver.addvariabledouble(val, variable);

                    if (paso) {
                        string addr = mem_parse((void *) mserver.getmemoryoffsetdouble(offset));
                        string xref = int_tostring(mserver.get_varref("double", variable));
                        json = jsonSender(addr, value, variable, xref);
                        mserver.printmem();
                    } else {
                        //retorna error para que salga en consola falta de memoria
                    }
                }
                else{
                    //redefine el valor de esa variable
                }
            }
            else if (type == "struct")
            {
                //Sigue sintaxis de C
            }
            else if (type == "reference")
            {
                //Hace offset de 4 bytes
            }
            /*
            int a = 10;
            ostringstream o;
            int* ptr = &a;
            o << ptr;
            string addr = o.str();
            json = jsonSender(addr, value, variable);
             */
            packetS << json;
            socket.send(packetS);
            packetS.clear();
            packetR.clear();
        }
    }
    
    return 0;
}