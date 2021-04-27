#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "rapidjson/document.h"
#include <string>
#include <iostream>
#include "MemoryManager.cpp"
#include "Logger.cpp"
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
    string type = "RLV";
    string jsonStr = R"({"memory":")"+ memory + R"(","type":")" + type + R"(","value":")" + value + R"(","variable":")" + variable + R"(","ref":")" + ref + "\"}";
    return jsonStr;
}

string msgsender(string msg, string type){
    string jsonstr = R"({"type":")"+ type + R"(","msg":")" + msg + "\"}";
    return jsonstr;
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
    string log = "";
    Logger logger;
    MemoryManager mserver(10*10*10*10*10);

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

                    offset = mserver.getoffset();//Busca el ultimo offset disponible
                    int val = int_parse(value);

                    bool paso = mserver.addvariableint(val,variable);//Inserta la variable en la memoria

                    if(paso){//si se logro insertar le devuelve la info al cliente
                        string addr = mem_parse((void*)mserver.getmemoryoffsetint(offset));//parse mem to string
                        string xref = int_tostring(mserver.get_varref("int",variable));//parse refnum to string
                        json = jsonSender(addr,value,variable,xref);//crea el json a mandar
                        mserver.printmem();
                        log = msgsender(logger.get_infolog("variable: "+variable+ " was allocated successfully"),"msg");
                    }
                    else{
                        //retorna error para que salga en consola falta de memoria
                        json = msgsender(logger.get_errorlog("IDE is out of memory. Could not allocate variable"),"msg");
                    }
                }

                else{
                    //redefine el valor de esa variable
                    offset = mserver.change_intvar(variable, int_parse(value));
                    string addr = mem_parse((void*)mserver.getmemoryoffsetint(offset));
                    mserver.add_varref("int",variable);
                    string xref = int_tostring(mserver.get_varref("int",variable));
                    json = jsonSender(addr,value,variable,xref);
                    mserver.printmem();
                    log = msgsender(logger.get_infolog("variable: "+variable+ " was redefined successfully"),"msg");
                    //addreference
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
                        log = msgsender(logger.get_infolog("variable: "+variable+ " was allocated successfully"),"msg");
                    } else {
                        //retorna error para que salga en consola falta de memoria
                        json = msgsender(logger.get_errorlog("IDE is out of memory. Could not allocate variable"),"msg");
                    }
                }
                else{
                    //redefine el valor de esa variable
                    offset = mserver.change_longvar(variable, long_parse(value));
                    string addr = mem_parse((void*)mserver.getmemoryoffsetlong(offset));
                    string xref = int_tostring(mserver.get_varref("long",variable));
                    json = jsonSender(addr,value,variable,xref);
                    mserver.printmem();
                    log = msgsender(logger.get_infolog("variable: "+variable+ " was redefined successfully"),"msg");
                }
            }
            else if (type == "char")
            {
                value = value[1];
                if(!mserver.getlist("char")->findvar(variable)) {
                    offset = mserver.getoffset();
                    char val = char_parse(value);

                    bool paso = mserver.addvariablechar(val, variable);

                    if (paso) {
                        string addr = mem_parse((void *) mserver.getmemoryoffsetchar(offset));
                        string xref = int_tostring(mserver.get_varref("char", variable));
                        json = jsonSender(addr, value, variable, xref);
                        mserver.printmem();
                        log = msgsender(logger.get_infolog("variable: "+variable+ " was allocated successfully"),"msg");
                    } else {
                        //retorna error para que salga en consola falta de memoria
                        json = msgsender(logger.get_errorlog("IDE is out of memory. Could not allocate variable"),"msg");
                    }
                }
                else{
                    //redefine el valor de esa variable
                    offset = mserver.change_charvar(variable, char_parse(value));
                    string addr = mem_parse((void*)mserver.getmemoryoffsetchar(offset));
                    string xref = int_tostring(mserver.get_varref("char",variable));
                    json = jsonSender(addr,value,variable,xref);
                    mserver.printmem();
                    log = msgsender(logger.get_infolog("variable: "+variable+ " was redefined successfully"),"msg");
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
                        log = msgsender(logger.get_infolog("variable: "+variable+ " was allocated successfully"),"msg");
                    } else {
                        //retorna error para que salga en consola falta de memoria
                        json = msgsender(logger.get_errorlog("IDE is out of memory. Could not allocate variable"),"msg");
                    }
                }
                else{
                    //redefine el valor de esa variable
                    offset = mserver.change_floatvar(variable, float_parse(value));
                    string addr = mem_parse((void*)mserver.getmemoryoffsetfloat(offset));
                    string xref = int_tostring(mserver.get_varref("float",variable));
                    json = jsonSender(addr,value,variable,xref);
                    mserver.printmem();
                    log = msgsender(logger.get_infolog("variable: "+variable+ " was redefined successfully"),"msg");
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
                        log = msgsender(logger.get_infolog("variable: " + variable + " was allocated successfully"),
                                        "msg");
                    }
                    else {
                        //retorna error para que salga en consola falta de memoria
                        json = msgsender(logger.get_errorlog("IDE is out of memory. Could not allocate variable"),"msg");
                    }
                }
                else{
                    //redefine el valor de esa variable
                    offset = mserver.change_doublevar(variable, long_parse(value));
                    string addr = mem_parse((void*)mserver.getmemoryoffsetdouble(offset));
                    string xref = int_tostring(mserver.get_varref("float",variable));
                    json = jsonSender(addr,value,variable,xref);
                    mserver.printmem();
                    log = msgsender(logger.get_infolog("variable: "+variable+ " was redefined successfully"),"msg");
                }
            }
            else if (type == "struct")
            {
                //Sigue sintaxis de C
            }
            else if (type == "reference")
            {
                if(!mserver.getlist("ref")->findvar(variable)){
                    offset = mserver.getoffset();

                    bool paso = mserver.addvariableref(type,variable,value);

                    if (paso) {
                        string addr = mem_parse((void *) mserver.getmemoryoffsetint(offset));
                        string xref = int_tostring(mserver.get_varref("ref", variable));
                        json = jsonSender(addr, value, variable, xref);

                        mserver.printmem();
                        log = msgsender(logger.get_infolog("variable: " + variable + " was allocated successfully"), "msg");
                    }
                    else{
                        json = msgsender(logger.get_errorlog("IDE is out of memory. Could not allocate variable"),"msg");
                    }
                }
                else{
                    //redefine el valor de esa variable
                    offset = mserver.change_refvar(variable, value);
                    string addr = mem_parse((void*)mserver.getmemoryoffsetdouble(offset));
                    string xref = int_tostring(mserver.get_varref("ref",variable));
                    json = jsonSender(addr,value,variable,xref);
                    mserver.printmem();
                    log = msgsender(logger.get_infolog("variable: "+variable+ " was redefined successfully"),"msg");
                }
            }
            else if (type == "free"){
                mserver.free_memory();
                string type = "ignore";
                json = R"({"type":")" + type + R"(","msg":")" + "msg" + "\"}";
                mserver.printmem();
            }
            else if(type == "garbage"){
                //borrar los espacios de memoria que se consideran basura
                cout << "Entre a garbage collector: " << variable << endl;
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
                //Utilizar "variables" para que el garbage collector elimine las variables que se encuentran en el garbage collector
                //Para instanciar y sacar todas las variables de un vector usar:
                for (auto & i : variables)
                {
                    if(mserver.getlist("int")->findvar(i)){
                        mserver.deleteint(i);
                    }
                    else if(mserver.getlist("float")->findvar(i)){
                        mserver.deletefloat(i);
                    }
                    else if(mserver.getlist("double")->findvar(i)){
                        mserver.deletedouble(i);
                    }
                    else if(mserver.getlist("long")->findvar(i)){
                        mserver.deletelong(i);
                    }
                    else if(mserver.getlist("char")->findvar(i)){
                        mserver.deletechar(i);
                    }
                    string type = "ignore";
                    json = R"({"type":")" + type + R"(","msg":")" + "msg" + "\"}";
                    log = msgsender(logger.get_infolog("Garbage collector clean unused variables!"),"msg");
                    cout << i << endl;
                }
                cout<<"**************************************************"<<endl;
                mserver.printmem();
            }
            else if (type == "addRef"){
                //anadir una referencia a la variable que le llega, el value esta estaria vacio
                cout << "Entre a anadir una referencia: " << variable << endl;
                if (value == "int"){
                    mserver.add_varref("int",variable);
                    offset = mserver.getlist("int")->findoffset(variable);
                    int refnum = mserver.get_varref("int",variable);
                    string addr = mem_parse((void*)mserver.getmemoryoffsetint(offset));
                    string xref = int_tostring(refnum);
                    int* val = mserver.getmemoryoffsetint(offset);
                    json = jsonSender(addr, int_tostring(*val),variable,xref);
                    log = msgsender(logger.get_infolog("variable: "+variable+ " has been referenced"),"msg");
                }
                else if (value=="float"){
                    mserver.add_varref("float",variable);
                    offset = mserver.getlist("float")->findoffset(variable);
                    int refnum = mserver.get_varref("float",variable);
                    string addr = mem_parse((void*)mserver.getmemoryoffsetfloat(offset));
                    string xref = int_tostring(refnum);
                    float val = *mserver.getmemoryoffsetfloat(offset);
                    string valstr = to_string(val);
                    json = jsonSender(addr, valstr,variable,xref);
                    log = msgsender(logger.get_infolog("variable: "+variable+ " has been referenced"),"msg");
                }
                else if (value=="double"){
                    mserver.add_varref("double",variable);
                    offset = mserver.getlist("double")->findoffset(variable);
                    int refnum = mserver.get_varref("double",variable);
                    string addr = mem_parse((void*)mserver.getmemoryoffsetdouble(offset));
                    string xref = int_tostring(refnum);
                    double val = *mserver.getmemoryoffsetdouble(offset);
                    string valstr = to_string(val);
                    json = jsonSender(addr,valstr,variable,xref);
                    log = msgsender(logger.get_infolog("variable: "+variable+ " has been referenced"),"msg");
                }
                else if (value=="char"){
                    mserver.add_varref("char",variable);
                    offset = mserver.getlist("char")->findoffset(variable);
                    int refnum = mserver.get_varref("char",variable);
                    string addr = mem_parse((void*)mserver.getmemoryoffsetchar(offset));
                    string xref = int_tostring(refnum);
                    char val = *mserver.getmemoryoffsetchar(offset);
                    cout << val << endl;
                    string valstr(1, val);
                    cout << valstr << endl;
                    json = jsonSender(addr,valstr,variable,xref);
                    log = msgsender(logger.get_infolog("variable: "+variable+ " has been referenced"),"msg");
                }
                else if (value=="long"){
                    mserver.add_varref("long",variable);
                    offset = mserver.getlist("long")->findoffset(variable);
                    int refnum = mserver.get_varref("long",variable);
                    string addr = mem_parse((void*)mserver.getmemoryoffsetlong(offset));
                    string xref = int_tostring(refnum);
                    long long val = *mserver.getmemoryoffsetlong(offset);
                    string valstr = to_string(val);
                    json = jsonSender(addr,valstr,variable,xref);
                    log = msgsender(logger.get_infolog("variable: "+variable+ " has been referenced"),"msg");
                }
                else if(value=="ref"){
                    mserver.add_varref("ref",variable);
                    offset = mserver.getlist("ref")->findoffset(variable);
                    int refnum = mserver.get_varref("ref",variable);
                    string addr = mem_parse((void*)mserver.getmemoryoffsetlong(offset));
                    string xref = int_tostring(refnum);
                    json = jsonSender(addr,"empty",variable,xref);
                    log = msgsender(logger.get_infolog("variable: "+variable+ " has been referenced"),"msg");
                }
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
            json = "";

            if(log != ""){
                cout<<"log is being sent"<<endl;
                packetS << log;
                socket.send(packetS);
                log = "";
                packetS.clear();
            }
        }
    }
    
    return 0;
}