#include <iostream>
#include <cmath>
#include "Node.cpp"
using namespace std;


//List class
class LinkedList {


public:
    //Atributes
    Node* start;
    int size;
    Node* tail;

    //Constructor
    LinkedList() {
        start = NULL;
        tail = NULL;
        this->size = 0;
    }

    //Append element to list
    void append(int data,string type,string name) {

        if (start == NULL)
        {
            start = new Node(data,type, name);
            tail = start;
            size++;
        }
        else
        {
            Node* newNode = new Node(data, type, name);
            tail->set_next(newNode);
            tail = newNode;
            size++;

        }
    }


    bool find(int aoffset) {
        if (start == NULL)
        {
            return false;
        }
        else if (start == tail)
        {
            if (start->get_varoffset() == aoffset)
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
            if (start->get_varoffset() == aoffset)
            {
                return true;
            }
            else
            {
                Node* tmp = start->get_next();
                while (tmp != NULL)
                {
                    if (tmp->get_varoffset() == aoffset)
                    {
                        return true;
                    }

                    tmp = tmp->get_next();
                }

                return false;
            }
        }
    }

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

    int findoffset(string aname) {
        if (start == NULL)
        {
            return -1;
        }
        else if (start == tail)
        {
            if (start->get_name() == aname)
            {
                return start->get_offset();
            }
            else
            {
                return -1;
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

                return -1;
            }
        }
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


