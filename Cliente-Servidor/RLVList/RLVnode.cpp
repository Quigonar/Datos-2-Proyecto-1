/**
 * @file RLVnode.cpp
 * @version 1.0
 * @title RlVnode
 * @brief Nodo de la lista RLVlist
 */
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

/**
 * @brief Clase RLVnode se encarga de guardar los valores de las variables para el RLV
 */
class RLVnode{

public:
    string info [4] = {};//array [mem,value,name,ref]
    RLVnode* next;//puntero next

    /**
     * constructor de la clase RLVnode
     * @param mem espacio de memoria
     * @param value valor de variable
     * @param name nombre de variable
     * @param ref cantidad de referencias
     */
    RLVnode(string mem,string value, string name, string ref){
        info[0] = mem;
        info[1] = value;
        info[2] = name;
        info[3] = ref;
        next = NULL;
    }

    /**
     * @brief get_next retorna el punter next
     * @return puntero al siguiente elemento
     */
    RLVnode* get_next(){
        return next;
    }

    /**
     * @brief get_mem retorna memoria de la variable
     * @return string de memoria
     */
    string get_mem(){
        return info[0];
    }

    /**
     * @brief get_value retorna el valor de la variable
     * @return string del valor
     */
    string get_value(){
        return info[1];
    }
    /**
     * @brief get_name retorna el nombre de la variable
     * @return string del nombre
     */
    string get_name(){
        return info[2];
    }

    /**
     * @brief get_ref retorna la cantidad de referencias
     * @return string cantidad de referencias
     */
    string get_ref(){
        return info[3];
    }

    /**
     * @brief set_next cambia el valor del puntero next
     * @param node el valor que se quiere cambiar
     */
    void set_next(RLVnode* node){
        next = node;
    }
    /**
     * @brief set_value cambia el valor del value de la variable
     * @param value calor al que se quiere cambiar
     */
    void set_value(string value){
        info[1] = value;
    }

    /**
     * @brief set_ref cambia el valor de la cantidad de referencias
     * @param ref cantidad de referencias en string
     */
    void set_ref(string ref){
        info[3] = ref;
    }
};

