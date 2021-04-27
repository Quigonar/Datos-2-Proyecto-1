#include <iostream>
#include <map>
#include "ClienteRes/ListaDobleEnlazada.cpp"
#include "ClienteRes/GUI.cpp"
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

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
    string terminal;
    vector<string> variableScope, addRef;
    bool scopeActive, printValue;

    //Verificador de que el valor ingresado corresponda al tipo ingresado
    bool valueVerifier(const string& type, string value, const string& variable, bool addMap)
    {
        try
        {
            if (type == "int" && *(typeid(stoi(value)).name()) == 'i')
            {
                int num = stoi(value);
                if (addMap)
                    ints[variable] = num;
                return true;
            }
            else if (type == "long" && *(typeid(stol(value)).name()) == 'l')
            {
                long num = stol(value);
                if (addMap)
                    longs[variable] = num;
                return true;
            }
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
            else if (type == "float" && *(typeid(stof(value)).name()) == 'f')
            {
                float num = stof(value);
                if (addMap)
                    floats[variable] = num;
                return true;
            }
            else if (type == "double" && *(typeid(stod(value)).name()) == 'd')
            {
                double num = stod(value);
                if (addMap)
                    doubles[variable] = stod(value);
                return true;
            }
            /*
            else if (type == "struct" && *(typeid(stoi(value)).name()) == 's')
            {
                cout << "Not implemented yet" << endl;
                return true;
            }
            else if (type == "reference" && *(typeid(stoi(value)).name()) == 'r')
            {
                cout << "Not implemented yet" << endl;
                return true;
            }*/
            }
        catch (invalid_argument error)
        {
            cout << "Entre al catch" << endl;
            terminal.append("Error! Variable is not defined");
            return false;
        }
    }

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
        string types[11] = {"int", "long", "char", "float", "double", "struct", "reference<int>", "reference<long>",
                           "reference<float>", "reference<double>", "reference<char>"};

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
        if (lineSplit.front() == "cout" && lineSplit.back().back() == ';') {
            it = lineSplit.begin();
            lineSplit.erase(it);
            lineSplit.front().erase(lineSplit.front().size() - 1);
            printValue = true;
        }
        //Si no verifica que la variable se encuentre en alguno de los diccionarios
        if (ints.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "int";
            ignoreStep = true;
        }
        else if (longs.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "long";
            ignoreStep = true;
        }
        else if (floats.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "float";
            ignoreStep = true;
        }
        else if (doubles.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "double";
            ignoreStep = true;
        }
        else if(chars.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "char";
            ignoreStep = true;
        }
        else if (referencesI.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "reference<int>";
            ignoreStep = true;
        }
        else if (referencesL.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "reference<long>";
            ignoreStep = true;
        }
        else if (referencesF.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "reference<float>";
            ignoreStep = true;
        }
        else if (referencesD.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "reference<double>";
            ignoreStep = true;
        }
        else if (referencesC.count(lineSplit.front()) > 0 && type.empty())
        {
            type = "reference<char>";
            ignoreStep = true;
        }
        else if(lineSplit.front() == "{" && lineSplit.size() == 1 && !scopeActive)
        {
            cout << "Entered scope" << endl;
            scopeActive = true;
            return "continue";
        }
        else if(lineSplit.front() == "}" && lineSplit.size() == 1 && scopeActive)
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

                variables.append(i + ",");
            }
            cout << "Finished scope" << endl;
            scopeActive = false;
            string Type = "garbage";
            string jsonStr = R"({"type":")" + Type + R"(","value":")" + "value" + R"(","variable":")"+ variables +"\"}";
            return jsonStr;
        }
        //Si no seria el imprimir alguna variable y desplegarla en la terminal o stdout
        if (printValue)
        {
            if (type.empty()) {
                terminal.append("Error! Variable doesn't exist\n");
                printValue = false;
                return "error";
            }
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
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "char" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(referencesI.at(lineSplit.front()) + "\n");
                return "print";
            }
            else if (referencesL.count(lineSplit.front()) > 0 )
            {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "char" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(referencesL.at(lineSplit.front()) + "\n");
                return "print";
            }
            else if (referencesF.count(lineSplit.front()) > 0 )
            {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "char" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(referencesF.at(lineSplit.front()) + "\n");
                return "print";
            }
            else if (referencesD.count(lineSplit.front()) > 0 )
            {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "char" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(referencesD.at(lineSplit.front()) + "\n");
                return "print";
            }
            else if (referencesC.count(lineSplit.front()) > 0 )
            {
                string Type = "addRef";
                addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "char" + R"(","variable":")"+ lineSplit.front() +"\"}");
                terminal.append(referencesC.at(lineSplit.front()) + "\n");
                return "print";
            }
        }
        //Y por ultimo devolver un error y desplegarlo en la terminal o stdout
        if (type.empty()) {
            terminal.append("Error! code syntaxis is wrong: forgot to declare type or forgot to add \";\"\n");
            return "error";
        }

        //Luego revisa si solo se define la variable sin valor alguno por lo cual por default se le da valor de NULL o 0
        if (lineSplit.front().length() >= 2 && lineSplit.front().back() == ';')
        {
            variable = lineSplit.front().erase(lineSplit.front().length() - 1);
            if (scopeActive)
                variableScope.push_back(variable);
            if (ints.count(variable) > 0 || longs.count(variable) > 0 || floats.count(variable) > 0 || doubles.count(variable) > 0){
                terminal.append("Error! redefining same variable: " + variable + "\n");
                return "error";
            }
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

                string jsonStr = R"({"type":")"+ type + R"(","value":")" + value + R"(","variable":")" + variable + "\"}";
                return jsonStr;
            }
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
            //If its "a" and out of scope
            if (ignoreStep && !scopeActive)
                variable = lineSplit.front();
            //If its "a" and in scope
            else if (ignoreStep && scopeActive) {
                //If variable was defined in scope
                if (count(variableScope.begin(), variableScope.end(), lineSplit.front()))
                    variable = lineSplit.front();
                //Else if variable wasn't define in scope
                else
                    variable = lineSplit.front();
            }
            else if (!ignoreStep && !scopeActive)
                variable = lineSplit.front();
            else if (!ignoreStep && scopeActive){
                variable = lineSplit.front();
                variableScope.push_back(variable);
            }
            it = lineSplit.begin();
            lineSplit.erase(it);
        }

        //Si el sintaxis esta bien escrito se procede a poner el valor a la variable
        if (lineSplit.front() == '=')
        {
            it = lineSplit.begin();
            lineSplit.erase(it);
            if (lineSplit.front().back() == ';' && lineSplit.front().length() >= 2)
            {
                value = lineSplit.front().erase(lineSplit.front().length() - 1);

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

                if (ints.count(variable) > 0 || longs.count(variable) > 0 || floats.count(variable) > 0 || doubles.count(variable) > 0) {
                    terminal.append("Error! redefining same variable: " + variable + "\n");
                    return "error";
                }
                bool validValue = valueVerifier(type, value, variable, true);
                if (validValue)
                {
                    string jsonStr = R"({"type":")"+ type + R"(","value":")" + value + R"(","variable":")" + variable + "\"}";
                    return jsonStr;
                }
            }
            //Si se encuentra algun tipo de operacion para realizarlo
            else if (lineSplit.size() == 2 && (type == "reference<int>" || type == "reference<long>" || type == "reference<float>"
                        || type == "reference<double>" || type == "reference<char>"))
            {
                if (lineSplit.front() == "getaddr" && lineSplit.back().back() == ';')
                {
                    if (type == "reference<int>" && ints.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "int" + R"(","variable":")"+ lineSplit.back() +"\"}");
                        cout << "entered reference<int>" << endl;
                        return "continue";
                    }
                    else if (type == "reference<long>" && longs.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "int" + R"(","variable":")"+ lineSplit.back() +"\"}");
                        cout << "entered reference<long>" << endl;
                        return "continue";
                    }
                    else if (type == "reference<float>" && floats.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "int" + R"(","variable":")"+ lineSplit.back() +"\"}");
                        cout << "entered reference<float>" << endl;
                        return "continue";
                    }
                    else if (type == "reference<double>" && doubles.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "int" + R"(","variable":")"+ lineSplit.back() +"\"}");
                        cout << "entered reference<double>" << endl;
                        return "continue";
                    }
                    else if (type == "reference<char>" && chars.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                    {
                        string Type = "addRef";
                        addRef.push_back(R"({"type":")" + Type + R"(","value":")" + "int" + R"(","variable":")"+ lineSplit.back() +"\"}");
                        cout << "entered reference<char>" << endl;
                        return "continue";
                    }
                    else
                    {
                        terminal.append("Error! trying to access invalid variable's memory address\n");
                        return "error";
                    }
                }
                else
                {
                    terminal.append("Error! forgot to add \";\" or syntaxis error\n");
                    return "error";
                }
            }
            else if (lineSplit.size() == 2 && (type == "int" || type == "long" || type == "float" || type == "double"
                    || type == "char"))
            {
                if (lineSplit.front() == "getvalue" && lineSplit.back().back() == ';')
                {
                    if (type == "int" && referencesI.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                    {
                        cout << "entered int for reference" << endl;
                    }
                    else if (type == "long" && referencesL.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                    {
                        cout << "entered long for reference" << endl;
                    }
                    else if (type == "float" && referencesF.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                    {
                        cout << "entered float for reference" << endl;
                    }
                    else if (type == "double" && referencesD.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                    {
                        cout << "entered double for reference" << endl;
                    }
                    else if (type == "char" && referencesC.count(lineSplit.back().erase(lineSplit.back().size() - 1)) > 0)
                    {
                        cout << "entered char for reference" << endl;
                    }
                    else
                    {
                        terminal.append("Error! trying to access invalid memory address\n");
                        return "error";
                    }
                }
            }
            else if (lineSplit.size() >= 3)
            {
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
            terminal.append("Error! code syntaxis is wrong: forgot to add value to the variable\n");
        return "error";
    }

    //Se define funcion que devuelve el string de la terminal para desplegarlo en la pantalla
    string getTerminal() const
    {
        return terminal;
    }

    vector<string> getAddRef() const
    {
        return addRef;
    }

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