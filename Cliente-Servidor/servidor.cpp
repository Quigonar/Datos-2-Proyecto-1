/**
 * @file servidor.cpp
 * @version 1.0
 * @title servidor
 * @brief Servidor donde se maneja el intercambio de mensajes y la memoria con el cliente
 */

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

/**
 * @brief jsonReviever se encarga de desempaquetar el mensaje JSON del cliente
 * @param packet paquete que envio el cliente
 * @return un documento donde se pueden extraer las variables
 */
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
/**
 * @brief jsonSender se encarga de formatear los mensajes de servidor-> cliente
 * @param memory espacio de memoria alocada
 * @param value valor de la variable
 * @param variable nombre de la variable
 * @param ref cantiad de referencias
 * @return un string en formato JSON listo para enviar
 */
string jsonSender(string memory, string value, string variable,string ref)
{
    string type = "RLV";
    string jsonStr = R"({"memory":")"+ memory + R"(","type":")" + type + R"(","value":")" + value + R"(","variable":")" + variable + R"(","ref":")" + ref + "\"}";
    return jsonStr;
}
/**
 * @brief msgsender se encarga de formatear los mensajes de info o de log servidor->cliente
 * @param msg mensaje a enviar
 * @param type tipo de mensaje
 * @return un string en formato JSON listo para enviar
 */
string msgsender(string msg, string type){
    string jsonstr = R"({"type":")"+ type + R"(","msg":")" + msg + "\"}";
    return jsonstr;
}
/**
 * @brief int_parse cambia string a int
 * @param s string a cambiar
 * @return int parseado
 */
int int_parse(string s){
    stringstream ss(s);
    int tmp = 0;
    ss>>tmp;
    return tmp;
}
/**
 * @brief long_parse cambia string a long
 * @param s string a cambiar
 * @return long parseado
 */
long long long_parse(string s){
    stringstream ss(s);
    long long tmp = 0;
    ss>>tmp;
    return tmp;
}
/**
 * @brief char_parse cambia string a char
 * @param s string a cambiar
 * @return char parseado
 */
char char_parse(string s){
    stringstream ss(s);
    char tmp = '0';
    ss>>tmp;
    return tmp;
}
/**
 * @brief float_parse cambia string a float
 * @param s string a cambiar
 * @return float parseado
 */
float float_parse(string s){
    stringstream ss(s);
    float tmp = 0.0;
    ss>>tmp;
    return tmp;
}
/**
 * @brief double_parse cambia string a double
 * @param s string a cambiar
 * @return double parseado
 */
double double_parse(string s){
    stringstream ss(s);
    double tmp = 0.0;
    ss>>tmp;
    return tmp;
}

/**
 * @brief int_tostring cambia un int a un string
 * @param num numero a cambiar
 * @return string del int num
 */
string int_tostring(int num){
    ostringstream o;
    o << num;
    string snum = o.str();
    return snum;
}

/**
 * @brief mem_parse cambia un espacio de memoria a string
 * @param ptr puntero a cambiar
 * @return string con el espacio de memoria
 */
string mem_parse(void* ptr){
    ostringstream o;
    o<<ptr;
    string addr = o.str();
    return addr;
}

/**
 * @brief main es la funcion donde corre el servido se y se hace el manejo de mensajes y memoria con el cliente
 * @return 1
 */
int main()
{
    IpAddress ip = IpAddress::getLocalAddress();//ipaddres del socket
    TcpSocket socket;//socket a conectar
    char connectionType, mode;//varles de conexion
    bool done = false;
    Packet packetR, packetS;//packets para recibir y mandar JSON
    size_t received;
    Document petition;//petition del packetR
    string json;//json que se manda
    string log = "";//log msg que se manda
    Logger logger;//instancia de clase Logger
    MemoryManager mserver(10*10*10*10*10*10);//instancia de memory manager con 1 MB

    TcpListener listener;//listener del server
    listener.listen(8080);//asigarle el puerto 8080
    listener.accept(socket);//recibe la conexion del socket de cliente
    mode = 'r';


    while (!done)
    {
        Event event;// revisar eventos en la pantalla
        if (event.key.code == Keyboard::Escape)//cerrar el server
            done = true;

        socket.receive(packetR);

        if (packetR.getData() == NULL)//si no recibe nada el servidor no actua
            //cout << "No message received yet" << endl;
            done = false;

        else
        {
            petition = jsonReceiver(packetR);//desempaqueta el JSON
            //separa el json en variables
            string value = petition["value"].GetString();
            string type = petition["type"].GetString();
            string variable = petition["variable"].GetString();

            int offset;

            if (type == "int")//revisa se le envio menssaje para creacion de int
            {
                if(!mserver.getlist("int")->findvar(variable)){//revisar si variable ya existe.

                    offset = mserver.getoffset();//Busca el ultimo offset disponible
                    int val = int_parse(value);//parsear valor a int

                    bool paso = mserver.addvariableint(val,variable);//Inserta la variable en la memoria

                    if(paso){//si se logro insertar le devuelve la info al cliente
                        string addr = mem_parse((void*)mserver.getmemoryoffsetint(offset));//parse mem to string
                        string xref = int_tostring(mserver.get_varref("int",variable));//parse refnum to string
                        json = jsonSender(addr,value,variable,xref);//crea el json a mandar
                        mserver.printmem();
                        //envia mensaje log que se genero la variable
                        log = msgsender(logger.get_infolog("variable: "+variable+ " was allocated successfully"),"msg");
                    }
                    else{
                        //retorna error para que salga en consola falta de memoria
                        json = msgsender(logger.get_errorlog("IDE is out of memory. Could not allocate variable"),"msg");
                    }
                }

                else{
                    //redefine el valor de esa variable
                    offset = mserver.change_intvar(variable, int_parse(value));//offset de la variable y cambio de valor
                    string addr = mem_parse((void*)mserver.getmemoryoffsetint(offset));//address de la variable
                    mserver.add_varref("int",variable);//agrega referencia
                    string xref = int_tostring(mserver.get_varref("int",variable));
                    json = jsonSender(addr,value,variable,xref);
                    mserver.printmem();
                    log = msgsender(logger.get_infolog("variable: "+variable+ " was redefined successfully"),"msg");
                }

            }
            else if (type == "long")//revisa se le envio menssaje para creacion de long
            {
                //revisar si variable ya existe.
                if(!mserver.getlist("long")->findvar(variable)) {
                    offset = mserver.getoffset();//offset disponible
                    long long val = long_parse(value);//parse el valor a long

                    bool paso = mserver.addvariablelong(val, variable);//inserta la variable a memoria

                    if (paso) {
                        string addr = mem_parse((void *) mserver.getmemoryoffsetlong(offset));//address de la variable
                        string xref = int_tostring(mserver.get_varref("long", variable));// cantidad de referencias
                        json = jsonSender(addr, value, variable, xref);//creacion del json a enviar
                        mserver.printmem();
                        //genera log
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
                cout<<value<<endl;
                if(!mserver.getlist("char")->findvar(variable)) {//revisa si ya existe
                    offset = mserver.getoffset();//offset nuevo
                    char val = char_parse(value);//parse value a char

                    bool paso = mserver.addvariablechar(val, variable);//se inserta variable a memoria

                    if (paso) {//si se genero bien
                        string addr = mem_parse((void *) mserver.getmemoryoffsetchar(offset));//addrss de la variable
                        string xref = int_tostring(mserver.get_varref("char", variable));//cantidad de ref
                        json = jsonSender(addr, value, variable, xref);//generacion del json
                        mserver.printmem();
                        //genera log
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
            else if (type == "float")//revisa se le envio menssaje para creacion de float
            {
                if(!mserver.getlist("float")->findvar(variable)) {//revisar si ya existe
                    offset = mserver.getoffset();//offset de la variable
                    float val = float_parse(value);//parse value a float

                    bool paso = mserver.addvariablefloat(val, variable);//insertar valor en memoria

                    if (paso) {//si se logra crear bien
                        string addr = mem_parse((void *) mserver.getmemoryoffsetfloat(offset));//addr de la variable
                        string xref = int_tostring(mserver.get_varref("float", variable));//cantidad de ref
                        json = jsonSender(addr, value, variable, xref);//generacion del json
                        mserver.printmem();
                        //se genera log
                        log = msgsender(logger.get_infolog("variable: "+variable+ " was allocated successfully"),"msg");
                    } else {
                        //retorna error para que salga en consola falta de memoria
                        json = msgsender(logger.get_errorlog("IDE is out of memory. Could not allocate variable"),"msg");
                    }
                }
                else{
                    //redefine el valor de esa variable
                    offset = mserver.change_floatvar(variable, float_parse(value));//se cambia valor
                    string addr = mem_parse((void*)mserver.getmemoryoffsetfloat(offset));
                    string xref = int_tostring(mserver.get_varref("float",variable));
                    json = jsonSender(addr,value,variable,xref);
                    mserver.printmem();
                    log = msgsender(logger.get_infolog("variable: "+variable+ " was redefined successfully"),"msg");
                }
            }
            else if (type == "double")//revisa se le envio menssaje para creacion de double
            {
                if(!mserver.getlist("double")->findvar(variable)) {//revisar si ya existe
                    offset = mserver.getoffset();//offset de la variable
                    double val = double_parse(value);//parse value a double

                    bool paso = mserver.addvariabledouble(val, variable);//insertar variable en memoria

                    if (paso) {//si se inserta bien
                        string addr = mem_parse((void *) mserver.getmemoryoffsetdouble(offset));//addr de la variable
                        string xref = int_tostring(mserver.get_varref("double", variable));//cantidad de ref
                        json = jsonSender(addr, value, variable, xref);//genera el json
                        mserver.printmem();
                        //genera el log
                        log = msgsender(logger.get_infolog("variable: " + variable + " was allocated successfully"),"msg");
                    }
                    else {
                        //retorna error para que salga en consola falta de memoria
                        json = msgsender(logger.get_errorlog("IDE is out of memory. Could not allocate variable"),"msg");
                    }
                }
                else{
                    //redefine el valor de esa variable
                    offset = mserver.change_doublevar(variable, long_parse(value));//redefine el valor
                    string addr = mem_parse((void*)mserver.getmemoryoffsetdouble(offset));
                    string xref = int_tostring(mserver.get_varref("float",variable));
                    json = jsonSender(addr,value,variable,xref);
                    mserver.printmem();
                    log = msgsender(logger.get_infolog("variable: "+variable+ " was redefined successfully"),"msg");
                }
            }
            else if (type == "struct")//revisa se le envio menssaje para creacion de un struct
            {
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

                string type1 = variables.at(0);
                string name1 = variables.at(1);
                string type2 = variables.at(2);
                string name2 = variables.at(3);

                string addr1;
                string addr2;
                string xref1;
                string xref2;

                string value1;
                string value2;
                int offset1;

                if(type1 == "int"){
                    bool paso = mserver.addvariableint(0,name1);
                    int aoffset = mserver.getlist("int")->findoffset(name1);
                    offset1 = aoffset;
                    addr1 = mem_parse((void*)mserver.getmemoryoffsetint(aoffset));
                    xref1 = int_tostring(mserver.get_varref("int",name1));
                    value1 = to_string(*mserver.getmemoryoffsetint(aoffset));
                }
                else if(type1 == "float"){
                    bool paso = mserver.addvariablefloat(0.0,name1);
                    int aoffset = mserver.getlist("float")->findoffset(name1);
                    offset1 = aoffset;
                    addr1 = mem_parse((void*)mserver.getmemoryoffsetfloat(aoffset));
                    xref1 = int_tostring(mserver.get_varref("float",name1));
                    value1 = to_string(*mserver.getmemoryoffsetfloat(aoffset));
                }
                else if(type1 =="double"){
                    bool paso = mserver.addvariabledouble(0.0,name1);
                    int aoffset = mserver.getlist("double")->findoffset(name1);
                    offset1 = aoffset;
                    addr1 = mem_parse((void*)mserver.getmemoryoffsetdouble(aoffset));
                    xref1 = int_tostring(mserver.get_varref("double",name1));
                    value1 = to_string(*mserver.getmemoryoffsetdouble(aoffset));
                }
                else if(type1 =="long"){
                    bool paso = mserver.addvariablelong(0,name1);
                    int aoffset = mserver.getlist("long")->findoffset(name1);
                    offset1 = aoffset;
                    addr1 = mem_parse((void*)mserver.getmemoryoffsetlong(aoffset));
                    xref1 = int_tostring(mserver.get_varref("long",name1));
                    value1 = to_string(*mserver.getmemoryoffsetlong(aoffset));
                }
                else if(type1 =="char"){
                    bool paso = mserver.addvariablechar('0',name1);
                    int aoffset = mserver.getlist("char")->findoffset(name1);
                    offset1 = aoffset;
                    addr1 = mem_parse((void*)mserver.getmemoryoffsetchar(aoffset));
                    xref1 = int_tostring(mserver.get_varref("char",name1));
                    value1 = to_string(*mserver.getmemoryoffsetchar(aoffset));
                }

                if(type2 == "int"){
                    bool paso = mserver.addvariableint(0,name2);
                    int aoffset = mserver.getlist("int")->findoffset(name2);
                    offset1 = aoffset;
                    addr2 = mem_parse((void*)mserver.getmemoryoffsetint(aoffset));
                    xref2 = int_tostring(mserver.get_varref("int",name2));
                    value2 = to_string(*mserver.getmemoryoffsetint(aoffset));
                }
                else if(type2 == "float"){
                    bool paso = mserver.addvariablefloat(0.0,name2);
                    int aoffset = mserver.getlist("float")->findoffset(name2);
                    offset1 = aoffset;
                    addr2 = mem_parse((void*)mserver.getmemoryoffsetfloat(aoffset));
                    xref2 = int_tostring(mserver.get_varref("float",name2));
                    value2 = to_string(*mserver.getmemoryoffsetfloat(aoffset));
                }
                else if(type2 =="double"){
                    bool paso = mserver.addvariabledouble(0.0,name2);
                    int aoffset = mserver.getlist("double")->findoffset(name2);
                    offset1 = aoffset;
                    addr2 = mem_parse((void*)mserver.getmemoryoffsetdouble(aoffset));
                    xref2 = int_tostring(mserver.get_varref("double",name2));
                    value2 = to_string(*mserver.getmemoryoffsetdouble(aoffset));
                }
                else if(type2 =="long"){
                    bool paso = mserver.addvariablelong(0,name2);
                    int aoffset = mserver.getlist("long")->findoffset(name2);
                    offset1 = aoffset;
                    addr2 = mem_parse((void*)mserver.getmemoryoffsetlong(aoffset));
                    xref2 = int_tostring(mserver.get_varref("long",name1));
                    value2 = to_string(*mserver.getmemoryoffsetlong(aoffset));
                }
                else if(type2 =="char"){
                    bool paso = mserver.addvariablechar('0',name2);
                    int aoffset = mserver.getlist("char")->findoffset(name2);
                    offset1 = aoffset;
                    addr2 = mem_parse((void*)mserver.getmemoryoffsetchar(aoffset));
                    xref2 = int_tostring(mserver.get_varref("char",name1));
                    value2 = to_string(*mserver.getmemoryoffsetchar(aoffset));
                }

                mserver.addvariablestruct(variable,offset1,type1);
                json = jsonSender(addr1,value1,variable,xref1);
                log = jsonSender(addr2,value2," ", " ");

            }
            else if (type == "reference")//revisa se le envio menssaje para creacion de un referencetype
            {
                if(!mserver.getlist("ref")->findvar(variable)){//revisar si existe
                    offset = mserver.getoffset();//offset del puntero

                    bool paso = mserver.addvariableref(type,variable,value);//se genera le puntero en memoria

                    if (paso) {//se genera bien
                        string addr = mem_parse((void *) mserver.getmemoryoffsetint(offset));//addr del puntero
                        string xref = int_tostring(mserver.get_varref("ref", variable));//cantidad de referencias
                        json = jsonSender(addr, value, variable, xref);//generacion del json
                        mserver.printmem();
                        //genera el log
                        log = msgsender(logger.get_infolog("variable: " + variable + " was allocated successfully"), "msg");
                    }
                    else{
                        //no se pudo generar la variable error
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
            else if (type == "free"){//revisa se le envio menssaje para borrar la memoria
                mserver.free_memory();//vacia la memoria
                string type = "ignore";
                json = R"({"type":")" + type + R"(","msg":")" + "msg" + "\"}";//genera el json para avisar al cliente
                mserver.printmem();
            }
            else if(type == "garbage"){//revisa se le envio menssaje para activar el garbage collector
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
                    if(mserver.getlist("int")->findvar(i)){//si el valor es int
                        mserver.deleteint(i);
                    }
                    else if(mserver.getlist("float")->findvar(i)){//si el valor es float
                        mserver.deletefloat(i);
                    }
                    else if(mserver.getlist("double")->findvar(i)){//si el valor es double
                        mserver.deletedouble(i);
                    }
                    else if(mserver.getlist("long")->findvar(i)){//si el valor es long
                        mserver.deletelong(i);
                    }
                    else if(mserver.getlist("char")->findvar(i)){//si el valor es char
                        mserver.deletechar(i);
                    }
                    string type = "ignore";
                    json = R"({"type":")" + type + R"(","msg":")" + "msg" + "\"}";//genera json
                    //genera log
                    log = msgsender(logger.get_infolog("Garbage collector clean unused variables!"),"msg");
                }
                cout<<"**************************************************"<<endl;
                mserver.printmem();
                cout<<"**************************************************"<<endl;
            }
            else if (type == "addRef"){//revisa se le envio menssaje para añadir referencia a variable
                //anadir una referencia a la variable que le llega, el value esta estaria vacio
                cout << "Entre a anadir una referencia: " << variable << endl;
                if (value == "int"){//si es un int
                    mserver.add_varref("int",variable);//se añade referencia
                    offset = mserver.getlist("int")->findoffset(variable);//offset de la variable
                    int refnum = mserver.get_varref("int",variable);//cantidad de referencias
                    string addr = mem_parse((void*)mserver.getmemoryoffsetint(offset));//addr de la variable
                    string xref = int_tostring(refnum);//cantidad de ref en int
                    int* val = mserver.getmemoryoffsetint(offset);//valor de la variable
                    json = jsonSender(addr, int_tostring(*val),variable,xref);//genera json
                    //genera log
                    log = msgsender(logger.get_infolog("variable: "+variable+ " has been referenced"),"msg");
                }
                else if (value=="float"){//si es float
                    mserver.add_varref("float",variable);// agrega referencia
                    offset = mserver.getlist("float")->findoffset(variable);//offset de variable
                    int refnum = mserver.get_varref("float",variable);//cantidad de ref
                    string addr = mem_parse((void*)mserver.getmemoryoffsetfloat(offset));//addr de varaiable
                    string xref = int_tostring(refnum);//cantidad de ref en string
                    float val = *mserver.getmemoryoffsetfloat(offset);//valor de variable
                    string valstr = to_string(val);//parse valor a string
                    json = jsonSender(addr, valstr,variable,xref);//genera json
                    //genera log
                    log = msgsender(logger.get_infolog("variable: "+variable+ " has been referenced"),"msg");
                }
                else if (value=="double"){//si es double
                    mserver.add_varref("double",variable);
                    offset = mserver.getlist("double")->findoffset(variable);
                    int refnum = mserver.get_varref("double",variable);
                    string addr = mem_parse((void*)mserver.getmemoryoffsetdouble(offset));
                    string xref = int_tostring(refnum);
                    double val = *mserver.getmemoryoffsetdouble(offset);
                    string valstr = to_string(val);
                    json = jsonSender(addr,valstr,variable,xref);//genera json
                    //genera log
                    log = msgsender(logger.get_infolog("variable: "+variable+ " has been referenced"),"msg");
                }
                else if (value=="char"){//si es char
                    mserver.add_varref("char",variable);
                    offset = mserver.getlist("char")->findoffset(variable);
                    int refnum = mserver.get_varref("char",variable);
                    string addr = mem_parse((void*)mserver.getmemoryoffsetchar(offset));
                    string xref = int_tostring(refnum);
                    char val = *mserver.getmemoryoffsetchar(offset);
                    string valstr(1, val);
                    cout<<valstr<<endl;
                    json = jsonSender(addr,valstr,variable,xref);//genera json
                    //genera log
                    log = msgsender(logger.get_infolog("variable: "+variable+ " has been referenced"),"msg");
                }
                else if (value=="long"){//si es long
                    mserver.add_varref("long",variable);
                    offset = mserver.getlist("long")->findoffset(variable);
                    int refnum = mserver.get_varref("long",variable);
                    string addr = mem_parse((void*)mserver.getmemoryoffsetlong(offset));
                    string xref = int_tostring(refnum);
                    long long val = *mserver.getmemoryoffsetlong(offset);
                    string valstr = to_string(val);
                    json = jsonSender(addr,valstr,variable,xref);//genera json
                    //genera log
                    log = msgsender(logger.get_infolog("variable: "+variable+ " has been referenced"),"msg");
                }
                else if(value=="ref"){//si es un puntero
                    mserver.add_varref("ref",variable);
                    offset = mserver.getlist("ref")->findoffset(variable);
                    int refnum = mserver.get_varref("ref",variable);
                    string addr = mem_parse((void*)mserver.getmemoryoffsetlong(offset));
                    string xref = int_tostring(refnum);
                    json = jsonSender(addr,"empty",variable,xref);//genera json
                    //genera log
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
            packetS << json;//empaqueta el json
            socket.send(packetS);//manda el json a cliente
            packetS.clear();//vacia los packets
            packetR.clear();
            json = "";//vacia el log

            if(log != ""){// si se genero un log de error
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