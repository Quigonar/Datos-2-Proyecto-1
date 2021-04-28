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
    Node* start;
    int size;
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
     * @brief findvar encuentra si la variable existe dentro de la lista
     * @param aname nombre de la variable quese quiere encontrar
     * @return retorna un booleano que indica si existe o no la variable
     */
    bool findvar(string aname) {
        if (start == NULL)//lista vacia
        {
            return false;
        }
        else if (start == tail)//lista solo tiene un elemento
        {
            if (start->get_name() == aname)//revisar el nombre del primero elemento
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
            if (start->get_name() == aname)//revisar el nombre del primer elemento
            {
                return true;
            }
            else
            {
                Node* tmp = start->get_next();//buscar a traves de toda la lista
                while (tmp != NULL)
                {
                    if (tmp->get_name() == aname)//revisar si el elemento es igual al nombre que se busca
                    {
                        return true;
                    }

                    tmp = tmp->get_next();//siguente elemento
                }

                return false;
            }
        }
    }

    /**
     * @brief findref buscar la cantidad de referencias que tenga la variable que se pida
     * @param aname nombre de la variable que se quiere obtener la referencia
     * @return retorna la cantidad de referencias
     */
    int findref(string aname) {
        if (start == NULL)//lista nula
        {
            return 0;
        }
        else if (start == tail)//lista solo tiene un elemento
        {
            if (start->get_name() == aname)//revisar el primer elemento
            {
                return start->get_refnum();//obtiene refnum
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (start->get_name() == aname)//revisar el primer elemento
            {
                return start->get_refnum();//obtiene refnum
            }
            else
            {
                Node* tmp = start->get_next();//buscar a traves de la lista
                while (tmp != NULL)
                {
                    if (tmp->get_name() == aname)//revisar si el elemento es name
                    {
                        return tmp->get_refnum();//retorna las referencias
                    }

                    tmp = tmp->get_next();//siguiente elemento
                }

                return 0;
            }
        }
    }

    string findrefname(string aname) {
        if (start == NULL)//lista nula
        {
            return "NULL";
        }
        else if (start == tail)//lista solo tiene un elemento
        {
            if (start->get_name() == aname)//revisar el primer elemento
            {
                return start->get_refname();//obtiene refnum
            }
            else
            {
                return "NULL";
            }
        }
        else
        {
            if (start->get_name() == aname)//revisar el primer elemento
            {
                return start->get_refname();//obtiene refnum
            }
            else
            {
                Node* tmp = start->get_next();//buscar a traves de la lista
                while (tmp != NULL)
                {
                    if (tmp->get_name() == aname)//revisar si el elemento es name
                    {
                        return tmp->get_refname();//retorna las referencias
                    }

                    tmp = tmp->get_next();//siguiente elemento
                }

                return "NULL";
            }
        }
    }

    /**
     * @brief changeref cambia la cantidad de referencias que tenga una variable
     * @param aname nombre de la variable
     */
    void changeref(string aname) {
        if (start == NULL)//lista vacia
        {
            //Lista vacia
        }
        else if (start == tail)//lista de un solo elemento
        {
            if (start->get_name() == aname)//revisar si elemento es name
            {
                start->add_refnum();//agrega referencia a variable
            }

        }
        else
        {
            if (start->get_name() == aname)//revisar si elemento es name
            {
                start->add_refnum();//agrega referencia a variable
            }
            else
            {
                Node* tmp = start->get_next();//buscar elemento
                while (tmp != NULL)
                {
                    if (tmp->get_name() == aname)//revisar si elemento es name
                    {
                        tmp->add_refnum();//agrega referencia a variable
                        break;
                    }

                    tmp = tmp->get_next();//siguiente elemento
                }
            }
        }
    }

    /**
     * @brief changemem cambia el espacio de memoria del puntero
     * @param aname nombre de la variable
     * @param value espacio de memoria en string
     */
    void changemem(string aname,string value) {
        if (start == NULL)//lista vacia
        {
            //Lista vacia
        }
        else if (start == tail)//lista de un elemento
        {
            if (start->get_name() == aname)//revisar si comple condicion
            {
                start->set_mem(value);//se hace set de nuevo mem
            }

        }
        else
        {
            if (start->get_name() == aname)//revisar si comple condicion
            {
                start->set_mem(value);//se hace set de nuevo mem
            }
            else
            {
                Node* tmp = start->get_next();//buscar en lista
                while (tmp != NULL)
                {
                    if (tmp->get_name() == aname)//revisar si comple condicion
                    {
                        tmp->set_mem(value);//se hace set de nuevo mem
                        break;
                    }

                    tmp = tmp->get_next();//siguiente elemento
                }
            }
        }
    }


    /**
     * @brief finsoffset retorna el offset de la variable
     * @param aname nombre de la variable
     * @return offset de la variable
     */
    int findoffset(string aname) {
        if (start == NULL)//lista nula
        {
            return -1;
        }
        else if (start == tail)//lista de 1 elemento
        {
            if (start->get_name() == aname)//revisra head
            {
                return start->get_offset();//retorna offset
            }
        }
        else
        {
            if (start->get_name() == aname)//revisra head
            {
                return start->get_offset();//retorna offset
            }
            else
            {
                Node* tmp = start->get_next();
                while (tmp != NULL)
                {
                    if (tmp->get_name() == aname)//revisar elemento
                    {
                        return tmp->get_offset();//retorna offset
                    }

                    tmp = tmp->get_next();//siguiente elemento
                }
                return -1;
            }
        }
    }

    /**
     * @brief delete_elem borra el elemento que se le indique de la memoria
     * @param aname nombre de variable
     */
    void delete_elem(string aname){
        if (start == NULL){//lista nula
            //
        }else {
            if (start == tail){//revisar head
                if (start->get_name() == aname) {
                    //inicializa lista
                    free(start);
                    start = NULL;
                    tail = NULL;
                    size--;
                }
            }
            else{
                if (start->get_name() == aname) {//revisar head
                    //inicializa lista
                    free(start);
                    start = start->get_next();
                    size--;
                }
                else{

                    Node* tmp = start;
                    while (tmp->get_next() != NULL)//busca el elemento
                    {
                        if (tmp->get_next()->get_name() == aname)//lo encuentra
                        {
                            Node* tmpnext = tmp->get_next();
                            if (tmpnext == tail){//si el nodo el el ultimo elemento
                                tail = tmp;
                                tail->set_next(NULL);
                                size--;
                                break;
                            }
                            else{
                                //se salta el elemento que se quiere borrar
                                tmp->set_next(tmpnext->get_next());
                                size--;
                                break;
                            }
                        }
                        tmp = tmp->get_next();//siguiente elemento
                    }
                }
            }
        }
    }

    /**
     * @brief deleteall borra toda la lisa
     */
    void deleteall(){
        start = NULL;
        tail = NULL;
        size = 0;
    }

    //print list
    /**
     * @brief printList imprime la lista en consola
     */
    void printList() {

        if (size == 0)//lista vacia
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


