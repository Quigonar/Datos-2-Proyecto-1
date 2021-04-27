/**
 * @file Node.cpp
 * @version 1.0
 * @title Node
 * @brief Nodo de lista de memoria virtual
 */
#include <iostream>
#include <cmath>
using namespace std;

//Node list
/**
 * @brief Clase Node se encarga de guardar la informacion de cada variable
 */
class Node {
public:
    //Atributes
    string name;// nombre de la variable
    string refname;// nombre del puntero
    string type;//tipo de variable
    int refnum;//cantidad de referencias
    int offset;//offset de la variable
    Node* next;//puntero al siguiente elemento
    string mem;//memoria a la cual apunta


    //Constructor with argument
    /**
     * @brief Constructor de la clase Node
     * @param adata offset de la variable
     * @param atype tipo de variable
     * @param aname nombre de la variable
     */
    Node(int adata,string atype, string aname) {
        offset = adata;
        type = atype;
        name = aname;
        next = NULL;
        refnum = 0;

    }

    //pointer setter
    /**
     * @brief set_next cambia el valor del puntero
     * @param ptr el puntero al siguiente elemento
     */
    void set_next(Node* ptr) {
        next = ptr;
    }

    /**
     * @brief add_refnum agrega 1 a la cantidad de referencias
     */
    void add_refnum() {
        refnum++;
    }
    /**
     * @brief set_mem cambia el valor al que apunta el puntero
     * @param amem espacio de memoria al que quiere que apunte
     */
    void set_mem(string amem){
        mem = amem;
    }
    /**
     * @brief set_refname retorna el nombre de la referencia
     * @param arefname
     */
    void set_refname(string arefname){
        refname = arefname;
    }


    //pointer getter
    /**
     * @brief get_next retorna el puntero al siguiente elemento
     * @return puntero al siguiente elemento
     */
    Node* get_next() {
        return next;
    }

    /**
     * @brief get_varoffset retorna el valor del offset de la variable
     * @return offset de la variable
     */
    int get_varoffset() {
        return offset;
    }

    /**
     * @brief get_refnum retorna la cantidad de referencias
     * @return cantidad de referencias
     */
    int get_refnum(){
        return refnum;
    }
    /**
     * @brief get_offset retorna el offset de la variable
     * @return offset
     */
    int get_offset(){
        return offset;
    }
    /**
     * @brief get_name retorna el nombre de la variable
     * @return name de la variable
     */
    string get_name() {
        return name;
    }

    /**
     * @brief get_mem retorna espacio de memoria al que apunta
     * @return mem espacio de memoria en string
     */
    string get_mem(){
        return mem;
    }
    /**
     * @brief get_refname retorna el nombre del puntero
     * @return nombre del puntero
     */
    string get_refname(){
        return refname;
    }
};



