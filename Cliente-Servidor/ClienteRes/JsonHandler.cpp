/**
 * @file JsonHandler.cpp
 * @version 1.0
 * @title JsonHandler
 * @brief Manejo de las lineas y JSONs recibidos por el cliente
 */
#include <iostream>
#include <map>
#include "ClienteRes/ListaDobleEnlazada.cpp"
#include "ClienteRes/GUI.cpp"
#include "rapidjson/document.h"
#include "RLVList/RLVlist.cpp"

using namespace std;
using namespace rapidjson;
/**
 * @brief Clase JsonHandler que se encarga de manejar las lineas y JSONs recibidos por el cliente
 */
//Se crea la clase para manejar y verificar las lineas del codigo
class JsonHandler{
public:
    //Se definen los diferentes diccionarios necesarios
    map<string, int> ints;
    map<string, long> longs;
    map<string, float> floats;
    map<string, double> doubles;
    map<string, char> chars;
    map<string, string> referencesI;
    map<string, string> referencesL;
    map<string, string> referencesF;
    map<string, string> referencesD;
    map<string, string> referencesC;
    map<string, string> structs;
    string terminal, structName;
    int counter = 1;
    vector<string> variableScope, addRef;
    bool scopeActive, printValue, changeType, isStruct;
    RLVlist* rlv;

    /**
     * @brief Constructor de la clase JsonHandler
     * @param ptr puntero de la lista del RAM Live Viewer
     */
    JsonHandler(RLVlist* ptr){
        rlv = ptr;
    }
    /**
     * @brief valueVerifier devuelve un booleano para saber si el valor ingresado en el codigo es valido o no
     * @param type es el tipo de la variable que se quiere verificar
     * @param value es el valor de la variable que se quiere verificar
     * @param variable es la variable que se quiere verificar
     * @param addMap es un booleano para ver si se anade o no al diccionario
     * @return booleano verdadero si el valor esta valido falso en caso contrario
     */
    //Verificador de que el valor ingresado corresponda al tipo ingresado
    bool valueVerifier(const string& type, string value, const string& variable, bool addMap)
    {
        try
        {
            //Verifica que el int ingresado sea valido
            if (type == "int" && *(typeid(stoi(value)).name()) == 'i')
            {
                int num = stoi(value);
                if (addMap)
                    ints[variable] = num;
                return true;
            }
            //Verifica que el long ingresado sea valido
            else if (type == "long" && *(typeid(stol(value)).name()) == 'l')
            {
                long num = stol(value);
                if (addMap)
                    longs[variable] = num;
                return true;
            }
            //Verifica que el char ingresado sea valido
            else if (type == "char")
            {
                if (value.length() == 3)
                {
                    if (*(typeid(value[1]).name()) == 'c')
                    {
                        char c = value[1];
                        if (addMap)
                            chars[variable] = c;
                        return true;
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            //Verifica que el float ingresado sea valido
            else if (type == "float" && *(typeid(stof(value)).name()) == 'f')
            {
                float num = stof(value);
                if (addMap)
                    floats[variable] = num;
                return true;
            }
            //Verifica que el double ingresado sea valido
            else if (type == "double" && *(typeid(stod(value)).name()) == 'd')
            {
                double num = stod(value);
                if (addMap)
                    doubles[variable] = num;
                return true;
            }
            else if (type == "struct" && *(typeid(stoi(value)).name()) == 's')
            {
                cout << "Not implemented yet" << endl;
                return true;
            }
            //Verifica que el reference<int> ingresado sea valido
            else if (type == "reference<int>")
            {
                if (addMap)
                    referencesI[variable] = value;
                return true;
            }
            //Verifica que el reference<long> ingresado sea valido
            else if (type == "reference<long>")
            {
                if (addMap)
                    referencesL[variable] = value;
                return true;
            }
            //Verifica que el reference<float> ingresado sea valido
            else if (type == "reference<float>")
            {
                if (addMap)
                    referencesF[variable] = value;
                return true;
            }
            //Verifica que el reference<double> ingresado sea valido
            else if (type == "reference<double>")
            {
                if (addMap)
                    referencesD[variable] = value;
                return true;
            }
            //Verifica que el reference<char> ingresado sea valido
            else if (type == "reference<char>")
            {
                if (addMap)
                    referencesC[variable] = value;
                return true;
            }
        }
        //Si no logra la conversion entonces retorna falso y despliega el error en stdout
        catch (invalid_argument error)
        {
            terminal.append("Error! Variable is not defined or is invalid");
            return false;
        }
    }
    /**
     * @brief verificador de las lineas el cual tambien crea los errores en el stdout y los JSONs que se envian al servidor
     * @param node es el nodo de la primera linea
     * @return retorna el JSON que se enviara al servidor
     */
    //Descompositor de la linea que crea un string estilo JSON con las variables necesarias o el tipo de funcion que
    //el usuario decidio hacer
    string jsonSender(Node* node)
    {
        string type, value, variable, line, delimiter;
        int n;
        vector<string> lineSplit;
        vector<string>::iterator it;
        line = node->data;
        bool ignoreStep = false;
        bool addReference = false;
        string types[11] = {"int", "long", "char", "float", "double", "struct", "reference<int>", "reference<long>",
                           "reference<float>", "reference<double>", "reference<char>"};

        //Divisor de la linea por espacios y los anade a un vector lineSplit
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

        //Si la linea esta completamente vacia retorna continuar
        if (lineSplit.front().empty())
            return "continue";

        //Verifica si el tipo esta definido al principio y define el tipo de la variable
        for (n = 0; n < 11; n++)
        {
            if (lineSplit.front() == types[n])
            {
                type = types[n];
                it = lineSplit.begin();
                lineSplit.erase(it);
                break;
            }
        }
        //Verifica si lo que esta al principio es cout para imprimir y torna el booleano a true para imprimir el valor
        if (lineSplit.front() == "cout" && lineSplit.back().back() == ';') {
            it = lineSplit.begin();
            lineSplit.erase(it);
            lineSplit.front().erase(lineSplit.front().size() - 1);
            printValue = true;
        }

        //Si no verifica que la variable se encuentre en alguno de los diccionarios para que no cause error
        if (ints.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "int";
            ignoreStep = true;
            addReference = true;
        }
        else if (longs.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "long";
            ignoreStep = true;
            addReference = true;
        }
        else if (floats.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "float";
            ignoreStep = true;
            addReference = true;
        }
        else if (doubles.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "double";
            ignoreStep = true;
            addReference = true;
        }
        else if(chars.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "char";
            ignoreStep = true;
            addReference = true;
        }
        else if (referencesI.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "reference<int>";
            ignoreStep = true;
            addReference = true;
        }
        else if (referencesL.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "reference<long>";
            ignoreStep = true;
            addReference = true;
        }
        else if (referencesF.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "reference<float>";
            ignoreStep = true;
            addReference = true;
        }
        else if (referencesD.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "reference<double>";
            ignoreStep = true;
            addReference = true;
        }
        else if (referencesC.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "reference<char>";
            ignoreStep = true;
            addReference = true;
        }

        //Si se encuentra el inicio de un scope torna scopeActive a true para tomar en cuenta las variables que se crean en el
        else if(lineSplit.front() == "{" && lineSplit.size() == 1 && !scopeActive)
        {
            scopeActive = true;
            return "continue";
        }
        //Si se encuentra el final de un scope se envian las variables al server para el garbage collector
        else if(lineSplit.front() == "}" && lineSplit.size() == 1 && scopeActive && !isStruct)
        {
            string variables;
            for (auto & i : variableScope)
            {
                if (ints.count(i) > 0)
                    ints.erase(i);
                else if (longs.count(i) > 0)
                    longs.erase(i);
                else if (floats.count(i) > 0)
                    floats.erase(i);
                else if (doubles.count(i) > 0)
                    doubles.erase(i);
                else if (chars.count(i) > 0)
                    chars.erase(i);
                else if (referencesI.count(i) > 0)
                    referencesI.erase(i);
                else if (referencesL.count(i) > 0)
                    referencesL.erase(i);
                else if (referencesF.count(i) > 0)
                    referencesF.erase(i);
                else if (referencesD.count(i) > 0)
                    referencesD.erase(i);
                else if (referencesC.count(i) > 0)
                    referencesC.erase(i);

                variables.append(i + ",");
            }
            scopeActive = false;
            string Type = "garbage";
            string jsonStr = R"({"type":")" + Type + R"(","value":")" + "value" + R"(","variable":")"+ variables +"\"}";
            return jsonStr;
        }
        else if(lineSplit.front() == "}" && lineSplit.size() == 1 && !scopeActive && isStruct)
        {
            string variables = structs.at(structName);
            type = "struct";
            isStruct = false;
            string jsonStr = R"({"type":")" + type + R"(","value":")" + variables + R"(","variable":")"+ structName +"\"}";
            structName = "";
            counter = 1;
            return jsonStr;
        }
        //Si no seria el imprimir alguna variable y desplegarla en la terminal o stdout
        if (printValue)
        {
            //Si no existe la variable retorna error
            if (type.empty()) {
                terminal.append("Error! Variable doesn't exist\n");
                printValue = false;
                return "error";
            }
            //Busca en cual diccionario se encuentra la variable e imprime el valor
            if (ints.count(lineSplit.front()) > 0) {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "int" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(to_string(ints.at(lineSplit.front())) + "\n");
                printValue = false;
                return "print";
            }
            else if (longs.count(lineSplit.front()) > 0) {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "long" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(to_string(longs.at(lineSplit.front())) + "\n");
                printValue = false;
                return "print";
            }
            else if (floats.count(lineSplit.front()) > 0) {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "float" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(to_string(floats.at(lineSplit.front())) + "\n");
                printValue = false;
                return "print";
            }
            else if (doubles.count(lineSplit.front()) > 0) {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "double" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(to_string(doubles.at(lineSplit.front())) + "\n");
                printValue = false;
                return "print";
            }
            else if (chars.count(lineSplit.front()) > 0) {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "char" + R"(","variable":")"+ lineSplit.front() +"\"}");
                string Char;
                Char = (char)chars.at(lineSplit.front());
                terminal.append(Char + "\n");
                printValue = false;
                return "print";
            }
            else if (referencesI.count(lineSplit.front()) > 0 )
            {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(referencesI.at(lineSplit.front()) + "\n");
                return "print";
            }
            else if (referencesL.count(lineSplit.front()) > 0 )
            {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(referencesL.at(lineSplit.front()) + "\n");
                return "print";
            }
            else if (referencesF.count(lineSplit.front()) > 0 )
            {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(referencesF.at(lineSplit.front()) + "\n");
                return "print";
            }
            else if (referencesD.count(lineSplit.front()) > 0 )
            {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(referencesD.at(lineSplit.front()) + "\n");
                return "print";
            }
            else if (referencesC.count(lineSplit.front()) > 0 )
            {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(referencesC.at(lineSplit.front()) + "\n");
                return "print";
            }
        }

        //Y por ultimo devolver un error y desplegarlo en la terminal o stdout
        if (type.empty()) {
            terminal.append("Error! code syntaxis is wrong: forgot to declare type or forgot to add \";\"\n");
            return "error";
        }

        if (type == "struct")
            isStruct = true;

        //Luego revisa si solo se define la variable sin valor alguno por lo cual por default se le da valor de NULL o 0
        if (lineSplit.front().length() >= 2 && lineSplit.front().back() == ';' && !isStruct)
        {
            variable = lineSplit.front().erase(lineSplit.front().length() - 1);
            //Si la variable se define dentro de un scope se anade a un vector para tomarlo en cuenta luego
            if (scopeActive)
                variableScope.push_back(variable);
            //Si se redefine una variable daria error
            if (ints.count(variable) > 0 || longs.count(variable) > 0 || floats.count(variable) > 0 || doubles.count(variable) > 0 || chars.count(variable) ||
                referencesI.count(variable) > 0 || referencesL.count(variable) > 0 || referencesF.count(variable) > 0 || referencesD.count(variable) > 0 || referencesC.count(variable) > 0){
                terminal.append("Error! redefining same variable: " + variable + "\n");
                return "error";
            }
            //Anade la variable al diccionario correspondiente con su valor y retorna el JSON para el servidor
            else
            {
                value = "NULL";
                if (type == "int")
                    ints[variable] = 0;
                else if (type == "long")
                    longs[variable] = 0;
                else if (type == "float")
                    floats[variable] = 0;
                else if (type == "double")
                    doubles[variable] = 0;
                else if (type == "char")
                    chars[variable] = '\0';
                else if (type == "reference<int>") {
                    referencesI[variable] = "NULL";
                    type = "reference";
                }
                else if (type == "reference<long>"){
                    referencesL[variable] = "NULL";
                    type = "reference";
                }
                else if (type == "reference<float>"){
                    referencesF[variable] = "NULL";
                    type = "reference";
                }
                else if (type == "reference<double>"){
                    referencesD[variable] = "NULL";
                    type = "reference";
                }
                else if (type == "reference<char>"){
                    referencesC[variable] = "NULL";
                    type = "reference";
                }

                string jsonStr = R"({"type":")"+ type + R"(","value":")" + value + R"(","variable":")" + variable + "\"}";
                return jsonStr;
            }
        }
        else if (lineSplit.front().length() >= 2 && lineSplit.front().back() == ';' && isStruct && counter <= 2)
        {
            if (counter < 2)
                structs.at(structName) += type + "," + lineSplit.front().erase(lineSplit.front().length() - 1) + ",";
            else if (counter == 2)
                structs.at(structName) += type + "," + lineSplit.front().erase(lineSplit.front().length() - 1);
            cout << counter << endl;
            cout << structs.at(structName) << endl;
            counter++;
            return "continue";
        }
        if (isStruct && lineSplit.front().size() >= 2 && lineSplit.front().back() == '{')
        {
            variable = lineSplit.front().erase(lineSplit.front().length() - 1);
            structs[variable] = "";
            structName = variable;
            return "continue";
        }
        //Revisa si se encuentra alguna error de sintaxis
        else if (lineSplit.front() == '=') {
            terminal.append("Error! code syntaxis is wrong: forgot to declare variable or redefining variable\n");
            return "error";
        }
        else if (ints.count(lineSplit.front()) > 0 && !ignoreStep){
            terminal.append("Error! code syntaxis is wrong: forgot to declare variable or redefining variable\n");
            return "error";
        }
        else if (longs.count(lineSplit.front()) > 0 && !ignoreStep){
            terminal.append("Error! code syntaxis is wrong: forgot to declare variable or redefining variable\n");
            return "error";
        }
        else if (floats.count(lineSplit.front()) > 0 && !ignoreStep){
            terminal.append("Error! code syntaxis is wrong: forgot to declare variable or redefining variable\n");
            return "error";
        }
        else if (doubles.count(lineSplit.front()) > 0 && !ignoreStep){
            terminal.append("Error! code syntaxis is wrong: forgot to declare variable or redefining variable\n");
            return "error";
        }

        //Y si no se continua a encontrar el valor de la variable.
        else
        {
            //Si se encuentra fuera del scope y se quiere dar valor a variable ya definida
            if (ignoreStep && !scopeActive)
                variable = lineSplit.front();
            //Si se encuentra dentro del scope y se quiere dar valor a variable ya definida
            else if (ignoreStep && scopeActive) {
                //Si la variable fue definida dentro del scope
                if (count(variableScope.begin(), variableScope.end(), lineSplit.front()))
                    variable = lineSplit.front();
                //Si la variable no fue definida dentro del scope
                else
                    variable = lineSplit.front();
            }
            //Si se encuentra fuera del scope y es una variable nueva
            else if (!ignoreStep && !scopeActive)
                variable = lineSplit.front();
            //Si se encuentra dentro del scope y es una variable nueva
            else if (!ignoreStep && scopeActive){
                variable = lineSplit.front();
                variableScope.push_back(variable);
            }
            it = lineSplit.begin();
            lineSplit.erase(it);
        }

        //Si el sintaxis esta bien escrito se procede a poner el valor a la variable
        if (lineSplit.front() == '=' && !isStruct)
        {
            it = lineSplit.begin();
            lineSplit.erase(it);
            //Si a la variable no se le quiere hacer una operacion y si presenta el punto y coma atras
            if (lineSplit.front().back() == ';' && lineSplit.front().length() >= 2)
            {
                value = lineSplit.front().erase(lineSplit.front().length() - 1);

                //Verificar si la valor a asignar a la variable es una variable previamente definida y sacar su valor y sumar referencia
                if (ints.count(value) > 0) {
                    string Type = "addRef";
                    addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "int" + R"(","variable":")" + value + "\"}");
                    value = to_string(ints.at(value));
                }
                else if (longs.count(value) > 0) {
                    string Type = "addRef";
                    addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "long" + R"(","variable":")" + value + "\"}");
                    value = to_string(longs.at(value));
                }
                else if (floats.count(value) > 0) {
                    string Type = "addRef";
                    addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "float" + R"(","variable":")" + value + "\"}");
                    value = to_string(floats.at(value));
                }
                else if (doubles.count(value) > 0) {
                    string Type = "addRef";
                    addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "double" + R"(","variable":")" + value + "\"}");
                    value = to_string(doubles.at(value));
                }
                else if (chars.count(value) > 0) {
                    string Type = "addRef";
                    addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "char" + R"(","variable":")" + value + "\"}");
                    value = to_string(chars.at(value));
                }
                else if (referencesI.count(value) > 0){
                    string Type = "addRef";
                    addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")" + value + "\"}");
                    changeType = true;
                    value = referencesI.at(value);
                }
                else if (referencesL.count(value) > 0){
                    string Type = "addRef";
                    addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")" + value + "\"}");
                    changeType = true;
                    value = referencesL.at(value);
                }
                else if (referencesF.count(value) > 0){
                    string Type = "addRef";
                    addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")" + value + "\"}");
                    changeType = true;
                    value = referencesF.at(value);
                }
                else if (referencesD.count(value) > 0){
                    string Type = "addRef";
                    addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")" + value + "\"}");
                    changeType = true;
                    value = referencesD.at(value);
                }
                else if (referencesC.count(value) > 0){
                    string Type = "addRef";
                    addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")" + value + "\"}");
                    changeType = true;
                    value = referencesC.at(value);
                }
                //Verificar que el valor de la variable se valido
                bool validValue = valueVerifier(type, value, variable, true);
                cout << validValue << endl;
                //Retorna el JSON si es valido
                if (validValue)
                {
                    if (changeType)
                    {
                        type = "reference";
                        changeType = false;
                    }
                    string jsonStr = R"({"type":")"+ type + R"(","value":")" + value + R"(","variable":")" + variable + "\"}";
                    return jsonStr;
                }
            }
            //Si se quiere crear una referencia
            else if (lineSplit.size() == 2 && (type == "reference<int>" || type == "reference<long>" || type == "reference<float>"
                        || type == "reference<double>" || type == "reference<char>"))
            {
                //Si la referencia se crea con el getaddr de una variable
                if (lineSplit.front() == "getaddr" && lineSplit.back().back() == ';') {
                    //Verificar si hay que anadir referencia al puntero
                    if (addReference)
                    {
                        //Verificar que la variable a referenciar se encuentre en su respectivo diccionario
                        if (type == "reference<int>" &&
                            ints.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0) {
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "int" + R"(","variable":")" +
                                             lineSplit.back() + "\"}");
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")" +
                                                     variable + "\"}");
                            string mem = rlv->findmem(lineSplit.back());
                            bool validValue = valueVerifier(type, mem, variable, true);
                            type = "reference";
                            if (validValue) {
                                cout << "entra a reference sending" << endl;
                                string jsonStr = R"({"type":")" + type + R"(","value":")" + mem + R"(","variable":")" +
                                                 variable + "\"}";
                                return jsonStr;
                            }
                        } else if (type == "reference<long>" &&
                                   longs.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0) {
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "long" + R"(","variable":")" +
                                             lineSplit.back() + "\"}");
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")" +
                                                     variable + "\"}");
                            string mem = rlv->findmem(lineSplit.back());
                            bool validValue = valueVerifier(type, mem, variable, true);
                            type = "reference";
                            if (validValue) {
                                string jsonStr = R"({"type":")" + type + R"(","value":")" + mem + R"(","variable":")" +
                                                 variable + "\"}";
                                return jsonStr;
                            }
                        } else if (type == "reference<float>" &&
                                   floats.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0) {
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "float" + R"(","variable":")" +
                                             lineSplit.back() + "\"}");
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")" +
                                                variable + "\"}");
                            string mem = rlv->findmem(lineSplit.back());
                            bool validValue = valueVerifier(type, mem, variable, true);
                            type = "reference";
                            if (validValue) {
                                string jsonStr = R"({"type":")" + type + R"(","value":")" + mem + R"(","variable":")" +
                                                 variable + "\"}";
                                return jsonStr;
                            }
                        } else if (type == "reference<double>" &&
                                   doubles.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0) {
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "double" + R"(","variable":")" +
                                             lineSplit.back() + "\"}");
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")" +
                                             variable + "\"}");
                            string mem = rlv->findmem(lineSplit.back());
                            bool validValue = valueVerifier(type, mem, variable, true);
                            type = "reference";
                            if (validValue) {
                                string jsonStr = R"({"type":")" + type + R"(","value":")" + mem + R"(","variable":")" +
                                                 variable + "\"}";
                                return jsonStr;
                            }
                        } else if (type == "reference<char>" &&
                                   chars.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0) {
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "char" + R"(","variable":")" +
                                             lineSplit.back() + "\"}");
                            string mem = rlv->findmem(lineSplit.back());
                            bool validValue = valueVerifier(type, mem, variable, true);
                            type = "reference";
                            if (validValue) {
                                string jsonStr = R"({"type":")" + type + R"(","value":")" + mem + R"(","variable":")" +
                                                 variable + "\"}";
                                return jsonStr;
                            }
                        }
                    }
                    //Verificar si hay que anadir referencia al puntero
                    else if (!addReference)
                    {
                        //Verificar que la variable a referenciar se encuentre en su respectivo diccionario
                        if (type == "reference<int>" &&
                            ints.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0) {
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "int" + R"(","variable":")" +
                                             lineSplit.back() + "\"}");
                            string mem = rlv->findmem(lineSplit.back());
                            bool validValue = valueVerifier(type, mem, variable, true);
                            type = "reference";
                            if (validValue) {
                                cout << "entra a reference sending" << endl;
                                string jsonStr = R"({"type":")" + type + R"(","value":")" + mem + R"(","variable":")" +
                                                 variable + "\"}";
                                return jsonStr;
                            }
                        } else if (type == "reference<long>" &&
                                   longs.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0) {
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "long" + R"(","variable":")" +
                                             lineSplit.back() + "\"}");
                            string mem = rlv->findmem(lineSplit.back());
                            bool validValue = valueVerifier(type, mem, variable, true);
                            type = "reference";
                            if (validValue) {
                                string jsonStr = R"({"type":")" + type + R"(","value":")" + mem + R"(","variable":")" +
                                                 variable + "\"}";
                                return jsonStr;
                            }
                        } else if (type == "reference<float>" &&
                                   floats.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0) {
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "float" + R"(","variable":")" +
                                             lineSplit.back() + "\"}");
                            string mem = rlv->findmem(lineSplit.back());
                            bool validValue = valueVerifier(type, mem, variable, true);
                            type = "reference";
                            if (validValue) {
                                string jsonStr = R"({"type":")" + type + R"(","value":")" + mem + R"(","variable":")" +
                                                 variable + "\"}";
                                return jsonStr;
                            }
                        } else if (type == "reference<double>" &&
                                   doubles.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0) {
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "double" + R"(","variable":")" +
                                             lineSplit.back() + "\"}");
                            string mem = rlv->findmem(lineSplit.back());
                            bool validValue = valueVerifier(type, mem, variable, true);
                            type = "reference";
                            if (validValue) {
                                string jsonStr = R"({"type":")" + type + R"(","value":")" + mem + R"(","variable":")" +
                                                 variable + "\"}";
                                return jsonStr;
                            }
                        } else if (type == "reference<char>" &&
                                   chars.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0) {
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "char" + R"(","variable":")" +
                                             lineSplit.back() + "\"}");
                            string mem = rlv->findmem(lineSplit.back());
                            bool validValue = valueVerifier(type, mem, variable, true);
                            type = "reference";
                            if (validValue) {
                                string jsonStr = R"({"type":")" + type + R"(","value":")" + mem + R"(","variable":")" +
                                                 variable + "\"}";
                                return jsonStr;
                            }
                        }
                    }
                    //Si no la variable no existe
                    else
                    {
                        terminal.append("Error! trying to access invalid variable's memory address\n");
                        return "error";
                    }
                }
                //Si no existe un error sintactico
                else
                {
                    terminal.append("Error! forgot to add \";\" or syntaxis error\n");
                    return "error";
                }
            }
            //Si se quiere crear una variable diferente de referencia
            else if (lineSplit.size() == 2 && (type == "int" || type == "long" || type == "float" || type == "double"
                    || type == "char"))
            {
                //Si la variable se usa getvalue para dar valor
                if (lineSplit.front() == "getvalue" && lineSplit.back().back() == ';')
                {
                    //Verificar si hay que anadir referencia a la variable
                    if (addReference)
                    {
                        //Verifica si el puntero existe en su diccionario correspondiente
                        if (type == "int" && referencesI.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                        {
                            string val = rlv->findvalue(referencesI.at(lineSplit.back()));
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.back() +"\"}");
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "int" + R"(","variable":")"+ variable +"\"}");
                            bool validValue = valueVerifier(type, val, variable, true);
                            if (validValue)
                            {
                                string jsonStr = R"({"type":")"+ type + R"(","value":")" + val + R"(","variable":")" + variable + "\"}";
                                return jsonStr;
                            }
                        }
                        else if (type == "long" && referencesL.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                        {
                            string val = rlv->findvalue(referencesL.at(lineSplit.back()));
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.back() +"\"}");
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "long" + R"(","variable":")"+ variable +"\"}");
                            bool validValue = valueVerifier(type, val, variable, true);
                            if (validValue)
                            {
                                string jsonStr = R"({"type":")"+ type + R"(","value":")" + val + R"(","variable":")" + variable + "\"}";
                                return jsonStr;
                            }
                        }
                        else if (type == "float" && referencesF.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                        {
                            string val = rlv->findvalue(referencesF.at(lineSplit.back()));
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.back() +"\"}");
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "float" + R"(","variable":")"+ variable +"\"}");
                            bool validValue = valueVerifier(type, val, variable, true);
                            if (validValue)
                            {
                                string jsonStr = R"({"type":")"+ type + R"(","value":")" + val + R"(","variable":")" + variable + "\"}";
                                return jsonStr;
                            }
                        }
                        else if (type == "double" && referencesD.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                        {
                            string val = rlv->findvalue(referencesD.at(lineSplit.back()));
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.back() +"\"}");
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "double" + R"(","variable":")"+ variable +"\"}");
                            bool validValue = valueVerifier(type, val, variable, true);
                            if (validValue)
                            {
                                string jsonStr = R"({"type":")"+ type + R"(","value":")" + val + R"(","variable":")" + variable + "\"}";
                                return jsonStr;
                            }
                        }
                        else if (type == "char" && referencesC.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                        {
                            string val = rlv->findvalue(referencesC.at(lineSplit.back()));
                            string valChar = "'" + val + "'";
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.back() +"\"}");
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "char" + R"(","variable":")"+ variable +"\"}");
                            bool validValue = valueVerifier(type, valChar, variable, true);
                            cout << validValue << endl;
                            if (validValue)
                            {
                                string jsonStr = R"({"type":")"+ type + R"(","value":")" + valChar + R"(","variable":")" + variable + "\"}";
                                return jsonStr;
                            }
                        }
                    }
                    //Verificar si se tiene que anadir una referencia a la variable
                    else if (!addReference)
                    {
                        //Verificar si el puntero existe en su diccionario correspondiente
                        if (type == "int" && referencesI.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                        {
                            string val = rlv->findvalue(referencesI.at(lineSplit.back()));
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.back() +"\"}");
                            bool validValue = valueVerifier(type, val, variable, true);
                            if (validValue)
                            {
                                string jsonStr = R"({"type":")"+ type + R"(","value":")" + val + R"(","variable":")" + variable + "\"}";
                                return jsonStr;
                            }
                        }
                        else if (type == "long" && referencesL.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                        {
                            string val = rlv->findvalue(referencesL.at(lineSplit.back()));
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.back() +"\"}");
                            bool validValue = valueVerifier(type, val, variable, true);
                            if (validValue)
                            {
                                string jsonStr = R"({"type":")"+ type + R"(","value":")" + val + R"(","variable":")" + variable + "\"}";
                                return jsonStr;
                            }
                        }
                        else if (type == "float" && referencesF.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                        {
                            string val = rlv->findvalue(referencesF.at(lineSplit.back()));
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.back() +"\"}");
                            bool validValue = valueVerifier(type, val, variable, true);
                            if (validValue)
                            {
                                string jsonStr = R"({"type":")"+ type + R"(","value":")" + val + R"(","variable":")" + variable + "\"}";
                                return jsonStr;
                            }
                        }
                        else if (type == "double" && referencesD.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                        {
                            string val = rlv->findvalue(referencesD.at(lineSplit.back()));
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.back() +"\"}");
                            bool validValue = valueVerifier(type, val, variable, true);
                            if (validValue)
                            {
                                string jsonStr = R"({"type":")"+ type + R"(","value":")" + val + R"(","variable":")" + variable + "\"}";
                                return jsonStr;
                            }
                        }
                        else if (type == "char" && referencesC.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                        {
                            string val = rlv->findvalue(referencesC.at(lineSplit.back()));
                            string valChar = "'" + val + "'";
                            string Type = "addRef";
                            addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "ref" + R"(","variable":")"+ lineSplit.back() +"\"}");
                            bool validValue = valueVerifier(type, valChar, variable, true);
                            cout << validValue << endl;
                            if (validValue)
                            {
                                string jsonStr = R"({"type":")"+ type + R"(","value":")" + valChar + R"(","variable":")" + variable + "\"}";
                                return jsonStr;
                            }
                        }
                    }
                    //Si no se intenta accesar una puntero que no existe
                    else
                    {
                        terminal.append("Error! trying to access invalid memory address\n");
                        return "error";
                    }
                }
            }
            //Verifica si se habla de una operacion
            else if (lineSplit.size() >= 3)
            {
                //Si hay una operacion
                if (lineSplit.at(1) == "+" || lineSplit.at(1) == "-" || lineSplit.at(1) == "*" || lineSplit.at(1) == "/")
                {
                    string val;
                    string split2 = lineSplit.at(2).erase(lineSplit.at(2).size() - 1);
                    //Verifica si la operacion contiene algun tipo de variable previamente definida
                    if (ints.count(lineSplit.at(0)) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "int" + R"(","variable":")"+ lineSplit.front() +"\"}");
                        val = to_string(ints.at(lineSplit.at(0)));
                        lineSplit.at(0) = val;
                    }
                    if (ints.count(split2) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "int" + R"(","variable":")"+ split2 +"\"}");
                        val = to_string(ints.at(lineSplit.at(2)));
                        lineSplit.at(2) = val;
                    }
                    if (longs.count(lineSplit.at(0)) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "long" + R"(","variable":")"+ lineSplit.front() +"\"}");
                        val = to_string(longs.at(lineSplit.at(0)));
                        lineSplit.at(0) = val;
                    }
                    if (longs.count(split2) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "long" + R"(","variable":")"+ split2 +"\"}");
                        val = to_string(longs.at(lineSplit.at(2)));
                        lineSplit.at(2) = val;
                    }
                    if (floats.count(lineSplit.at(0)) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "float" + R"(","variable":")"+ lineSplit.front() +"\"}");

                        val = to_string(floats.at(lineSplit.at(0)));
                        lineSplit.at(0) = val;
                    }
                    if (floats.count(split2) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "float" + R"(","variable":")"+ split2 +"\"}");
                        val = to_string(floats.at(lineSplit.at(2)));
                        lineSplit.at(2) = val;
                    }
                    if (doubles.count(lineSplit.at(0)) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "double" + R"(","variable":")"+ lineSplit.front() +"\"}");
                        val = to_string(doubles.at(lineSplit.at(0)));
                        lineSplit.at(0) = val;
                    }
                    if (doubles.count(split2) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "double" + R"(","variable":")"+ split2 +"\"}");
                        val = to_string(doubles.at(lineSplit.at(2)));
                        lineSplit.at(2) = val;
                    }

                    //Se realiza la operacion
                    if (valueVerifier(type, lineSplit.at(0), variable, false)
                        && valueVerifier(type, lineSplit.at(2), variable, false))
                    {
                        int i1, i2;
                        long l1, l2;
                        float f1, f2;
                        double d1 , d2;

                        if (type == "int")
                        {
                            i1 = stoi(lineSplit.at(0));
                            i2 = stoi(lineSplit.at(2));

                            if (lineSplit.at(1) == "+")
                                value = to_string(i1 + i2);
                            else if (lineSplit.at(1) == "-")
                                value = to_string(i1 - i2);
                            else if (lineSplit.at(1) == "*")
                                value = to_string(i1 * i2);
                            else if (lineSplit.at(1) == "/")
                                value = to_string(i1 / i2);
                            ints[variable] = stoi(value);

                        } else if (type == "long")
                        {
                            l1 = stol(lineSplit.at(0));
                            l2 = stol(lineSplit.at(2));

                            if (lineSplit.at(1) == "+")
                                value = to_string(l1 + l2);
                            else if (lineSplit.at(1) == "-")
                                value = to_string(l1 - l2);
                            else if (lineSplit.at(1) == "*")
                                value = to_string(l1 * l2);
                            else if (lineSplit.at(1) == "/")
                                value = to_string(l1 / l2);
                            longs[variable] = stol(value);
                        } else if (type == "float")
                        {
                            f1 = stof(lineSplit.at(0));
                            f2 = stof(lineSplit.at(2));

                            if (lineSplit.at(1) == "+")
                                value = to_string(f1 + f2);
                            else if (lineSplit.at(1) == "-")
                                value = to_string(f1 - f2);
                            else if (lineSplit.at(1) == "*")
                                value = to_string(f1 * f2);
                            else if (lineSplit.at(1) == "/")
                                value = to_string(f1 / f2);
                            floats[variable] = stof(value);
                        } else if (type == "double")
                        {
                            d1 = stod(lineSplit.at(0));
                            d2 = stod(lineSplit.at(2));

                            if (lineSplit.at(1) == "+")
                                value = to_string(d1 + d2);
                            else if (lineSplit.at(1) == "-")
                                value = to_string(d1 - d2);
                            else if (lineSplit.at(1) == "*")
                                value = to_string(d1 * d2);
                            else if (lineSplit.at(1) == "/")
                                value = to_string(d1 / d2);
                            doubles[variable] = stod(value);
                        }
                        string jsonStr = R"({"type":")"+ type + R"(","value":")" + value + R"(","variable":")" + variable + "\"}";
                        return jsonStr;
                    }

                }
            }
            //Si no hay problema de sintaxis en el codigo
            else {
                terminal.append("Error! code syntaxis is wrong: forgot to add \";\" or invalid operation written\n");
                return "error";
            }
        }
        //Si no hay problema de sintaxis en el codigo
        else
            terminal.append("Error! code syntaxis is wrong: forgot to add value to the variable or defining inside struct or defining more that 2 variables inside struct\n");
        return "error";
    }
    /**
     * @brief getTerminal retorna el string del stdout
     * @return el string del stdout
     */
    //Se define funcion que devuelve el string de la terminal para desplegarlo en la pantalla
    string getTerminal() const
    {
        return terminal;
    }
    /**
     * @brief getAddRef retorna el vector de las referencia que se necesitan anadir
     * @return el vector de las referencias
     */
    vector<string> getAddRef() const
    {
        return addRef;
    }
    /**
     * @brief jsonReceiver recibe un packet y formatea lo de adentro para poder ser utilizado como un JSON
     * @param packet es el packet que recibe el cliente
     * @return retorna un JSON que puede ser accesado por la variables
     */
    //Se define funcion que devuelve el json que puede ser accedido como un JSON
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
};