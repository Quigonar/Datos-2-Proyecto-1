#include "rapidjson/document.h"
#include <iostream>

using namespace rapidjson;
using namespace std;

//Idea de que cuando un mensaje sea recibido se llame a esta clase pasandole el mensaje para que
//retorne un json y se pueda accesar a la informacion del json, ver documentacion en: rapidjson.org/md_doc_tutorial.html
//y para instalar libreria usar comandos en terminal de linux: 
//sudo apt-get update -y | sudo apt-get install -y rapidjson-dev
//Si se logra encontrar otra manera sencilla se puede cambiar.
Document createJson(char* json)
{
    Document document;
    document.Parse(json);
    return document;
}