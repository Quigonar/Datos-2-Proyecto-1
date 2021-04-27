/**
 * @file LinkedList.cpp
 * @version 1.0
 * @title LinkedList
 * @brief Manejo de la memoria virtual del servidor
 */
#include <iostream>
#include <cmath>
#include "Node.cpp"
using namespace std;


/**
 * @brief Clase LinkedList se encarga de guardar la informacion necesaria para el manejo de la memoria virtual
 */
class LinkedList {

public:
    //Atributes
    /**
     * @brief Node* start es el inicio de la lista
     */
    Node* start;
    /**
     * @brief int size es el tamaño de la lista
     */
    int size;
    /**
     * @brief Node* tail es el ultimo elemento de la lista
     */
    Node* tail;

    //Constructor
    /**
     * @brief Constructor de la clase LinkedList
     */
    LinkedList() {
        start = NULL;
        tail = NULL;
        size = 0;
    }

    //Append element to list
    /**
     * @brief append se encarga de agregar nuevos nodos al final de la lista
     * @param data offset de la variable que se agrego
     * @param type tipo de variable que se agrego
     * @param name nombre de la variable
     * @param mem cuando es un puntero es el espacio de memoria al que apunta
     * @param refname es el nombre de la variable a la cual apunta
     */
    void append(int data,string type,string name,string mem = "", string refname = "") {

        if (start == NULL)//revisa si la lista esta vacia
        {
            start = new Node(data,type, name);//crea el nuevo nodo
            //importa solo si es un puntero
            start->set_mem(mem);//le agrega la memoria
            start->set_refname(refname);//le nombre de la variable que apunta

            tail = start;//se define como el inicio y el final
            size++;//incrementa el tamaño de la lista
        }
        else
        {
            Node* newNode = new Node(data, type, name);//se genera un nuevo nodo
            tail->set_next(newNode);//se agrega al final de la lista
            tail = newNode;//se pone como el ultimo nodo
            //solo aplica si es un puntero
            tail->set_mem(mem);
            tail->set_refname(refname);

            size++;//incrementa el tamaño de la lista
        }
    }

    /**
     * @brief find busca si la variable existe en la lista
     * @param aoffset el offset de la variable que se busca
     * @return un booleano si existe o no la variable en la lista
     */
    bool find(int aoffset) {
        if (start == NULL)//lista nula
        {
            return false;
        }
        else if (start == tail)//solo tiene un elemento
        {
            if (start->get_varoffset() == aoffset)//existe y es el primer elemento
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
            if (start->get_varoffset() == aoffset)//existe y es el primer elemento
            {
                return true;
            }
            else
            {
                Node* tmp = start->get_next();//se empieza a buscar a traves de la lista
                while (tmp != NULL)
                {
                    if (tmp->get_varoffset() == aoffset)//si el elemento es igual al que se busca
                    {
                        return true;
                    }
                    tmp = tmp->get_next();
                }
                return false;
            }
        }
    }

    /**
     * @brief findvar
     * @param aname
     * @return
     */
    bool findvar(string aname) {
        if (start == NULL)
        {
            return false;
        }
        else if (start == tail)
        {
            if (start->get_name() == aname)
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
            if (start->get_name() == aname)
            {
                return true;
            }
            else
            {
                Node* tmp = start->get_next();
                while (tmp != NULL)
                {
                    if (tmp->get_name() == aname)
                    {
                        return true;
                    }

                    tmp = tmp->get_next();
                }

                return false;
            }
        }
    }
    int findref(string aname) {
        if (start == NULL)
        {
            return 0;
        }
        else if (start == tail)
        {
            if (start->get_name() == aname)
            {
                return start->get_refnum();
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (start->get_name() == aname)
            {
                return start->get_refnum();;
            }
            else
            {
                Node* tmp = start->get_next();
                while (tmp != NULL)
                {
                    if (tmp->get_name() == aname)
                    {
                        return tmp->get_refnum();;
                    }

                    tmp = tmp->get_next();
                }

                return 0;
            }
        }
    }

    void changeref(string aname) {
        if (start == NULL)
        {
            //Lista vacia
        }
        else if (start == tail)
        {
            if (start->get_name() == aname)
            {
                start->add_refnum();
            }

        }
        else
        {
            if (start->get_name() == aname)
            {
                start->add_refnum();
            }
            else
            {
                Node* tmp = start->get_next();
                while (tmp != NULL)
                {
                    if (tmp->get_name() == aname)
                    {
                        tmp->add_refnum();
                        break;
                    }

                    tmp = tmp->get_next();
                }
            }
        }
    }
    void changemem(string aname,string value) {
        if (start == NULL)
        {
            //Lista vacia
        }
        else if (start == tail)
        {
            if (start->get_name() == aname)
            {
                start->set_mem(value);
            }

        }
        else
        {
            if (start->get_name() == aname)
            {
                start->set_mem(value);
            }
            else
            {
                Node* tmp = start->get_next();
                while (tmp != NULL)
                {
                    if (tmp->get_name() == aname)
                    {
                        tmp->set_mem(value);
                        break;
                    }

                    tmp = tmp->get_next();
                }
            }
        }
    }

    int findoffset(string aname) {
        if (start == NULL)
        {

            return -1;
        }
        else if (start == tail)
        {


            if (start->get_name() == aname)
            {
                cout<< "entro segundo if"<<endl;
                return start->get_offset();

            }
        }
        else
        {
            if (start->get_name() == aname)
            {
                return start->get_offset();
            }
            else
            {
                Node* tmp = start->get_next();
                while (tmp != NULL)
                {
                    if (tmp->get_name() == aname)
                    {
                        return tmp->get_offset();;
                    }

                    tmp = tmp->get_next();
                }
                cout<< "entro 4 if"<<endl;
                return -1;
            }
        }
    }

    void delete_elem(string aname){
        if (start == NULL){
            //
        }else {
            if (start == tail){
                if (start->get_name() == aname) {
                    free(start);
                    start = NULL;
                    tail = NULL;
                    size--;
                }
            }
            else{
                if (start->get_name() == aname) {
                    free(start);
                    start = start->get_next();
                    size--;
                }
                else{

                    Node* tmp = start;
                    while (tmp->get_next() != NULL)
                    {
                        if (tmp->get_next()->get_name() == aname)
                        {

                            Node* tmpnext = tmp->get_next();
                            if (tmpnext == tail){
                                tail = tmp;
                                tail->set_next(NULL);
                                size--;
                                break;
                            }
                            else{
                                tmp->set_next(tmpnext->get_next());
                                size--;
                                break;
                            }
                        }
                        tmp = tmp->get_next();
                    }
                }
            }
        }
    }
    void deleteall(){
        start = NULL;
        tail = NULL;
        size = 0;
    }
    //print list
    void printList() {

        if (size == 0)
        {
            cout << "Lista Vacia" << endl;

        }
        else {

            Node* tmp = start;

            while (tmp != NULL)
            {
                cout << "|" << tmp->get_varoffset()<<" : "<<tmp->name<< "|-->";
                tmp = tmp->get_next();
            }
            cout << " " << endl;

        }
    }
};


