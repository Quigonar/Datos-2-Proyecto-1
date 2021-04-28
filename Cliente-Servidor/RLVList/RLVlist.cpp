/**
 * @file RLVlist.cpp
 * @version 1.0
 * @title RlVlist
 * @brief Manejo del Ram Live View
 */
#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include "RLVnode.cpp"


using namespace std;

/**
 * @brief Clase RLVlist se encarga del manejo de datos del Ram Live View
 */
class RLVlist{

public:
    //atributos
    RLVnode* start;//inicio de la lista
    int size;//tamaño de la lista
    RLVnode* tail;//ultimo elemento de la lista

    /**
     * @brief Constructor de clase RLVlist
     */
    RLVlist(){
        start = NULL;
        int size = 0;
        tail = NULL;
    }

    //Append element to list
    /**
     * @brief append agrega nueva variable al RLV
     * @param mem espacio de memoria
     * @param value valor de la variable
     * @param name nombre de la variable
     * @param ref cantidad de referencias de la variable
     */
    void append(string mem, string value, string name, string ref) {

        if (start == NULL)//lista nula
        {
            start = new RLVnode(mem,value,name,ref);
            tail = start;
            size++;
        }
        else
        {
            if (find(name)){//revis asi ya existe en la lista
                if(value !="empty"){//revisa si es puntero
                    change_val(name,value);//cambia el espacio de memoria
                }
                change_ref(name,ref);//cambia la referencias
            }
            else{
                RLVnode* newNode = new RLVnode(mem,value,name,ref);//crea un nuevo nodo
                tail->set_next(newNode);//lo añade a la lista
                tail = newNode;
                size++;//incrementa tamaño
            }

        }
    }
    /**
     * @brief find busca si la variable existe en la lista
     * @param name nombre de la variable
     * @return booleano si existe o no la variable
     */
    bool find(string name) {
        if (start == NULL)//lista nula
        {
            return false;
        }
        else if (start == tail)//lista de un 1 elemento
        {
            if (start->get_name() == name)//revisar si head se busca
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (start->get_name() == name)//revisar si head se busca
            {
                return true;
            }
            else
            {
                RLVnode* tmp = start->get_next();
                while (tmp != NULL)//Buscar en la lista
                {
                    if (tmp->get_name() == name)//revisar elemento
                    {
                        return true;
                    }

                    tmp = tmp->get_next();//siguiente elemento
                }
                return false;
            }
        }
    }

    /**
     * @brief change_val busca el elemento y cambia el valor
     * @param name nombre de la variable
     * @param value valor por cambiar
     */
    void change_val(string name,string value) {
        if (start == NULL)//lista nula
        {
            //
        }
        else if (start == tail)//1 elemento en la lista
        {
            if (start->get_name() == name)
            {
                start->set_value(value);//se cambia elemento
            }
        }
        else
        {
            if (start->get_name() == name)//primer elemento
            {
                start->set_value(value);
            }
            else
            {
                RLVnode* tmp = start->get_next();
                while (tmp != NULL)//se busca en la lista
                {
                    if (tmp->get_name() == name)
                    {
                        tmp->set_value(value);//se cambia valor
                    }

                    tmp = tmp->get_next();//siguiente elemento
                }
            }
        }
    }

    /**
     * @brief findmem busca el espacio de memoria de la variable
     * @param name nombre de la variable
     * @return string con el espacio de memoria
     */
    string findmem(string name) {
        if (start == NULL)//lista vacia
        {
            return "NULL";
        }
        else if (start == tail)//1 elemento
        {
            if (start->get_name() == name)
            {
                return start->get_mem();//se retorna mem
            }
            else
            {
                return "NULL";
            }
        }
        else
        {
            if (start->get_name() == name)//primer elemento
            {
                return start->get_mem();//se retorna mem
            }
            else
            {
                RLVnode* tmp = start->get_next();
                while (tmp != NULL)//se busca en la lista
                {
                    if (tmp->get_name() == name)
                    {
                        return tmp->get_mem();//se retorna mem
                    }

                    tmp = tmp->get_next();//siguiente elemento
                }
                return "NULL";
            }
        }
    }

    /**
     * @brief findvalue busca el valor de la variable con el espacio de memoria
     * @param mem espacio de memoria
     * @return el valor en string del espacio de memoria
     */
    string findvalue(string mem) {
        if (start == NULL)//lista vacia
        {
            return "NULL";
        }
        else if (start == tail)//1 elemento en lista
        {
            if (start->get_mem() == mem)//head
            {
                return start->get_value();//retorna valor
            }
            else
            {
                return "NULL";
            }
        }
        else
        {
            if (start->get_mem() == mem)//primer elemento
            {
                return start->get_value();//retorna valor
            }
            else
            {
                RLVnode* tmp = start->get_next();
                while (tmp != NULL)//buscar en la lista
                {
                    if (tmp->get_mem() == mem)
                    {
                        return tmp->get_value();//retorna valor
                    }
                    tmp = tmp->get_next();//siguiente elemento
                }
                return "NULL";
            }
        }
    }

    /**
     * @brief change_ref cambia la cantidad de referencias del elemento
     * @param name nombre de la variable
     * @param ref cantidad de referencias
     */
    void change_ref(string name,string ref) {
        if (start == NULL)//lista nula
        {
            //
        }
        else if (start == tail)//1 elemento en lista
        {
            if (start->get_name() == name)//primer elemento
            {
                start->set_ref(ref);//cambia ref
            }
        }
        else
        {
            if (start->get_name() == name)//primer elemento
            {
                start->set_ref(ref);//cambia ref
            }
            else
            {
                RLVnode* tmp = start->get_next();
                while (tmp != NULL)//revisar lista
                {
                    if (tmp->get_name() == name)//revisar elemento
                    {
                        tmp->set_ref(ref);//cambia ref
                    }

                    tmp = tmp->get_next();//siguiente elemento
                }
            }
        }
    }

    /**
     * @brief get_memory organiza todos los espacios de memoria para el RLV
     * @return string con todos los espacios de memoria
     */
    string get_memory(){
        if(start == NULL){//lista vacia
            return "";
        }
        else{
            string memory = start->get_mem() + "\n\n";//primer elementi
            RLVnode* tmp = start->get_next();
            while (tmp != NULL)//recorre lista
            {
                memory += tmp->get_mem() + "\n\n";//agrega al total
                tmp = tmp->get_next();//siguiente elemento
            }
            return memory;
        }
    }

    /**
     * @brief get_value organiza todos los valores  para el RLV
     * @return string con todos los valores
     */
    string get_value(){
        if(start == NULL){//lista nula
            return "";
        }
        else{
            string value = start->get_value() + "\n\n";//primer elemento
            RLVnode* tmp = start->get_next();
            while (tmp != NULL)//recorrer lista
            {
                value += tmp->get_value() + "\n\n";//agregar al el total
                tmp = tmp->get_next();//siguiente elemento
            }
            return value;
        }
    }

    /**
     * @brief get_name organiza todos los nombres  para el RLV
     * @return string con todos los nombres
     */
    string get_name(){
        if(start == NULL){//lista nula
            return "";
        }
        else{
            string name = start->get_name() + "\n\n";//primer elemento
            RLVnode* tmp = start->get_next();
            while (tmp != NULL)//recorre lista
            {
                name += tmp->get_name() + "\n\n";//agrega al total
                tmp = tmp->get_next();//siguiente elemento
            }
            return name;
        }
    }

    /**
     * @brief get_ref organiza todos los ref  para el RLV
     * @return string con todos los ref
     */
    string get_ref(){
        if(start == NULL){//lista nula
            return "";
        }
        else{
            string ref = start->get_ref() + "\n\n";//primer elemento
            RLVnode* tmp = start->get_next();
            while (tmp != NULL)//recorrer lista
            {
                ref += tmp->get_ref() + "\n\n";//agregar al total
                tmp = tmp->get_next();//siguiente elemento
            }
            return ref;
        }
    }

    /**
     * @void RLVupdate borra el elemento que se le indique de RLV
     * @param aname nombre de la variable
     */
    void RLVupdate(string aname,bool stc = false){


        if (start == NULL){//lista nula
            //
        }else {
            if (start == tail){//1 elemento en lista
                if (start->get_name() == aname) {//head
                    //inicializar lista
                    free(start);
                    start = NULL;
                    tail = NULL;
                    size--;
                }
            }
            else{
                if (start->get_name() == aname) {//head
                    //inicializar lista
                    free(start);
                    start = start->get_next();
                    size--;
                }
                else{

                    RLVnode* tmp = start;
                    while (tmp->get_next() != NULL)//recorrer lista
                    {
                        if (tmp->get_next()->get_name() == aname)//lo encuentra
                        {

                            RLVnode* tmpnext = tmp->get_next();
                            if (tmpnext == tail){// si el el tail de la lista
                                tail = tmp;
                                tail->set_next(NULL);
                                size--;
                                break;
                            }
                            else{
                                tmp->set_next(tmpnext->get_next());//saltar elemento
                                size--;
                                break;
                            }
                        }
                        tmp = tmp->get_next();//siguiente elemento
                    }
                }
            }
        }

        if (stc == false){
            RLVupdate(" ",true);
        }
        else{
            //
        }
    }
    /**
     * @brief clear inicializa toda la lista y borra todos los elementos
     */
    void clear(){
        start = NULL;
        tail = NULL;
        size = 0;
    }
};