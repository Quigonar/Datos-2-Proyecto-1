#include <iostream>
#include <map>
#include "ClienteRes/ListaDobleEnlazada.cpp"

using namespace std;

class JsonHandler{
public:
    map<string, int> ints;
    map<string, long> longs;
    map<string, float> floats;
    map<string, double> doubles;
    map<string, char> chars;

    bool valueVerifier(string type, string value, string variable, bool addMap)
    {
        if (type == "int" && *(typeid(stoi(value)).name()) == 'i')
        {
            if (addMap)
                ints[variable] = stoi(value);
            return true;
        }
        else if (type == "long" && *(typeid(stol(value)).name()) == 'l')
        {
            if (addMap)
                longs[variable] = stol(value);
            return true;
        }
        else if (type == "char")
        {
            if (value.length() == 3)
            {
                if (*(typeid(value[1]).name()) == 'c')
                {
                    if (addMap)
                        chars[variable] = value[1];
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
            if (addMap)
                floats[variable] = stof(value);
            return true;
        }
        else if (type == "double" && *(typeid(stod(value)).name()) == 'd')
        {
            if (addMap)
                doubles[variable] = stod(value);
            return true;
        }

            /*else if (type == "struct" && *(typeid(stoi(value)).name()) == 's')
            {
                cout << "Not implemented yet" << endl;
                return true;
            }
            else if (type == "reference" && *(typeid(stoi(value)).name()) == 'r')
            {
                cout << "Not implemented yet" << endl;
                return true;
            }*/
        else
        {
            cout << "Value wasn't valid" << endl;
            return false;
        }
    }

    string jsonSender(Node* node)
    {
        string type, value, variable, line, delimiter;
        int n;
        vector<string> lineSplit;
        vector<string>::iterator it;
        line = node->data;
        bool ignoreStep = false;
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
            if (lineSplit.front() == types[n])
            {
                type = types[n];
                it = lineSplit.begin();
                lineSplit.erase(it);
                break;
            }
        }
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
        else if (type.empty())
        {
            cout << "Error: code syntaxis is wrong, forgot to declare type" << endl;
            return "Failed to create json";
        }

        if (lineSplit.front().length() >= 2 && lineSplit.front().back() == ';')
        {
            variable = lineSplit.front().erase(lineSplit.front().length() - 1);
            if (ints.count(variable) > 0)
            {
                cout << "Error redefining same variable: " << variable << endl;
                return "Failed to create json";
            }
            else if (longs.count(variable) > 0)
            {
                cout << "Error redefining same variable: " << variable << endl;
                return "Failed to create json";
            }
            else if (floats.count(variable) > 0)
            {
                cout << "Error redefining same variable: " << variable << endl;
                return "Failed to create json";
            }
            else if (doubles.count(variable) > 0)
            {
                cout << "Error redefining same variable: " << variable << endl;
                return "Failed to create json";
            }
            else
                value = "NULL";
                if (type == "int")
                    ints[variable] = NULL;
                else if (type == "long")
                    longs[variable] = NULL;
                else if (type == "float")
                    floats[variable] = NULL;
                else if (type == "double")
                    doubles[variable] = NULL;
                else if (type == "char")
                    chars[variable] = NULL;

                string jsonStr = "{\"type\":"+ type + ",\"value\":" + value + ",\"variable\":" + variable + "}";
                return jsonStr;
        }
        else if (lineSplit.front() == '=')
        {
            cout << "Error: code syntaxis is wrong, forgot to declare variable" << endl;
        }
        else if (ints.count(lineSplit.front()) > 0 && !ignoreStep)
        {
            cout << "Error redefining same variable: " << variable << endl;
            ignoreStep = false;
            return "Failed to create json";
        }
        else if (longs.count(lineSplit.front()) > 0 && !ignoreStep)
        {
            cout << "Error redefining same variable: " << variable << endl;
            ignoreStep = false;
            return "Failed to create json";
        }
        else if (floats.count(lineSplit.front()) > 0 && !ignoreStep)
        {
            cout << "Error redefining same variable: " << variable << endl;
            ignoreStep = false;
            return "Failed to create json";
        }
        else if (doubles.count(lineSplit.front()) > 0 && !ignoreStep)
        {
            cout << "Error redefining same variable: " << variable << endl;
            ignoreStep = false;
            return "Failed to create json";
        }
        else
        {
            variable = lineSplit.front();
            it = lineSplit.begin();
            lineSplit.erase(it);
        }

        if (lineSplit.front() == '=')
        {
            it = lineSplit.begin();
            lineSplit.erase(it);
            if (lineSplit.front().back() == ';' && lineSplit.front().length() >= 2)
            {
                value = lineSplit.front().erase(lineSplit.front().length() - 1);
                bool validValue = valueVerifier(type, value, variable, true);
                if (validValue)
                {
                    string jsonStr = "{\"type\":" + type + ",\"value\":" + value + ",\"variable\":" + variable + "}";
                    return jsonStr;
                }
            }
            else if (lineSplit.at(1) == "+" || lineSplit.at(1) == "-" || lineSplit.at(1) == "*" || lineSplit.at(1) == "/")
            {
                string val;
                string split2 = lineSplit.at(2).erase(lineSplit.at(2).size() - 1);
                if (ints.count(lineSplit.at(0)) > 0)
                {
                    val = to_string(ints.at(lineSplit.at(0)));
                    lineSplit.at(0) = val;
                }
                if (ints.count(split2) > 0)
                {
                    val = to_string(ints.at(lineSplit.at(2)));
                    lineSplit.at(2) = val;
                }
                if (longs.count(lineSplit.at(0)) > 0)
                {
                    val = to_string(longs.at(lineSplit.at(0)));
                    lineSplit.at(0) = val;
                }
                if (longs.count(split2) > 0)
                {
                    val = to_string(longs.at(lineSplit.at(2)));
                    lineSplit.at(2) = val;
                }
                if (floats.count(lineSplit.at(0)) > 0)
                {
                    val = to_string(floats.at(lineSplit.at(0)));
                    lineSplit.at(0) = val;
                }
                if (floats.count(split2) > 0)
                {
                    val = to_string(floats.at(lineSplit.at(2)));
                    lineSplit.at(2) = val;
                }
                if (doubles.count(lineSplit.at(0)) > 0)
                {
                    val = to_string(doubles.at(lineSplit.at(0)));
                    lineSplit.at(0) = val;
                }
                if (doubles.count(split2) > 0)
                {
                    val = to_string(doubles.at(lineSplit.at(2)));
                    lineSplit.at(2) = val;
                }

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
                        {
                            value = to_string(i1 + i2);
                        }
                        else if (lineSplit.at(1) == "-")
                        {
                            value = to_string(i1 - i2);
                        }
                        else if (lineSplit.at(1) == "*")
                        {
                            value = to_string(i1 * i2);
                        }
                        else if (lineSplit.at(1) == "/")
                        {
                            value = to_string(i1 / i2);
                        }
                        ints[variable] = stoi(value);

                    } else if (type == "long")
                    {
                        l1 = stol(lineSplit.at(0));
                        l2 = stol(lineSplit.at(2));

                        if (lineSplit.at(1) == "+")
                        {
                            value = to_string(l1 + l2);
                        }
                        else if (lineSplit.at(1) == "-")
                        {
                            value = to_string(l1 - l2);
                        }
                        else if (lineSplit.at(1) == "*")
                        {
                            value = to_string(l1 * l2);
                        }
                        else if (lineSplit.at(1) == "/")
                        {
                            value = to_string(l1 / l2);
                        }
                        longs[variable] = stol(value);
                    } else if (type == "float")
                    {
                        f1 = stof(lineSplit.at(0));
                        f2 = stof(lineSplit.at(2));

                        if (lineSplit.at(1) == "+")
                        {
                            value = to_string(f1 + f2);
                        }
                        else if (lineSplit.at(1) == "-")
                        {
                            value = to_string(f1 - f2);
                        }
                        else if (lineSplit.at(1) == "*")
                        {
                            value = to_string(f1 * f2);
                        }
                        else if (lineSplit.at(1) == "/")
                        {
                            value = to_string(f1 / f2);
                        }
                        floats[variable] = stof(value);
                    } else if (type == "double")
                    {
                        d1 = stod(lineSplit.at(0));
                        d2 = stod(lineSplit.at(2));

                        if (lineSplit.at(1) == "+")
                        {
                            value = to_string(d1 + d2);
                        }
                        else if (lineSplit.at(1) == "-")
                        {
                            value = to_string(d1 - d2);
                        }
                        else if (lineSplit.at(1) == "*")
                        {
                            value = to_string(d1 * d2);
                        }
                        else if (lineSplit.at(1) == "/")
                        {
                            value = to_string(d1 / d2);
                        }
                        doubles[variable] = stod(value);
                    }
                string jsonStr = "{\"type\":" + type + ",\"value\":" + value + ",\"variable\":" + variable + "}";
                return jsonStr;
                }

            }
            else
            {
                cout << "Error: code syntaxis is wrong, forgot to add \";\" or invalid operation" << endl;
            }
        }
        else
        {
            cout << "Error: code syntaxis is wrong, forgot to add value to the variable" << endl;
        }
        return "Couldn't create the json";
    }
};