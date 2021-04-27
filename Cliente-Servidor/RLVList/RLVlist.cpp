#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include "RLVnode.cpp"


using namespace std;

class RLVlist{



public:
    RLVnode* start;
    int size;
    RLVnode* tail;

    RLVlist(){
        start = NULL;
        int size = 0;
        tail = NULL;
    }

    //Append element to list
    void append(string mem, string value, string name, string ref) {

        if (start == NULL)
        {
            start = new RLVnode(mem,value,name,ref);
            tail = start;
            size++;
        }
        else
        {
            if (find(name)){
                if(value !="empty"){
                    change_val(name,value);
                }

                change_ref(name,ref);
            }
            else{
                RLVnode* newNode = new RLVnode(mem,value,name,ref);
                tail->set_next(newNode);
                tail = newNode;
                size++;
            }

        }
    }

    bool find(string name) {
        if (start == NULL)
        {
            return false;
        }
        else if (start == tail)
        {
            if (start->get_name() == name)
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
            if (start->get_name() == name)
            {
                return true;
            }
            else
            {
                RLVnode* tmp = start->get_next();
                while (tmp != NULL)
                {
                    if (tmp->get_name() == name)
                    {
                        return true;
                    }

                    tmp = tmp->get_next();
                }

                return false;
            }
        }
    }

    void change_val(string name,string value) {
        if (start == NULL)
        {
            //
        }
        else if (start == tail)
        {
            if (start->get_name() == name)
            {
                start->set_value(value);
            }
        }
        else
        {
            if (start->get_name() == name)
            {
                start->set_value(value);
            }
            else
            {
                RLVnode* tmp = start->get_next();
                while (tmp != NULL)
                {
                    if (tmp->get_name() == name)
                    {
                        tmp->set_value(value);
                    }

                    tmp = tmp->get_next();
                }
            }
        }
    }

    string findmem(string name) {
        if (start == NULL)
        {
            return "NULL";
        }
        else if (start == tail)
        {
            if (start->get_name() == name)
            {
                return start->get_mem();
            }
            else
            {
                return "NULL";
            }
        }
        else
        {
            if (start->get_name() == name)
            {
                return start->get_mem();
            }
            else
            {
                RLVnode* tmp = start->get_next();
                while (tmp != NULL)
                {
                    if (tmp->get_name() == name)
                    {
                        return tmp->get_mem();
                    }

                    tmp = tmp->get_next();
                }

                return "NULL";
            }
        }
    }

    string findvalue(string mem) {
        if (start == NULL)
        {
            return "NULL";
        }
        else if (start == tail)
        {
            if (start->get_mem() == mem)
            {
                return start->get_value();
            }
            else
            {
                return "NULL";
            }
        }
        else
        {
            if (start->get_mem() == mem)
            {
                return start->get_value();
            }
            else
            {
                RLVnode* tmp = start->get_next();
                while (tmp != NULL)
                {
                    if (tmp->get_mem() == mem)
                    {
                        return tmp->get_value();
                    }
                    tmp = tmp->get_next();
                }

                return "NULL";
            }
        }
    }

    void change_ref(string name,string ref) {
        if (start == NULL)
        {
            //
        }
        else if (start == tail)
        {
            if (start->get_name() == name)
            {
                start->set_ref(ref);
            }
        }
        else
        {
            if (start->get_name() == name)
            {
                start->set_ref(ref);
            }
            else
            {
                RLVnode* tmp = start->get_next();
                while (tmp != NULL)
                {
                    if (tmp->get_name() == name)
                    {
                        tmp->set_ref(ref);
                    }

                    tmp = tmp->get_next();
                }
            }
        }
    }

    string get_memory(){
        if(start == NULL){
            return "";
        }
        else{
            string memory = start->get_mem() + "\n\n";
            RLVnode* tmp = start->get_next();
            while (tmp != NULL)
            {
                memory += tmp->get_mem() + "\n\n";
                tmp = tmp->get_next();
            }
            return memory;
        }
    }

    string get_value(){
        if(start == NULL){
            return "";
        }
        else{
            string value = start->get_value() + "\n\n";
            RLVnode* tmp = start->get_next();
            while (tmp != NULL)
            {
                value += tmp->get_value() + "\n\n";
                tmp = tmp->get_next();
            }
            return value;
        }
    }

    string get_name(){
        if(start == NULL){
            return "";
        }
        else{
            string name = start->get_name() + "\n\n";
            RLVnode* tmp = start->get_next();
            while (tmp != NULL)
            {
                name += tmp->get_name() + "\n\n";
                tmp = tmp->get_next();
            }
            return name;
        }
    }

    string get_ref(){
        if(start == NULL){
            return "";
        }
        else{
            string ref = start->get_ref() + "\n\n";
            RLVnode* tmp = start->get_next();
            while (tmp != NULL)
            {
                ref += tmp->get_ref() + "\n\n";
                tmp = tmp->get_next();
            }
            return ref;
        }
    }
    void RLVupdate(string aname){
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

                    RLVnode* tmp = start;
                    while (tmp->get_next() != NULL)
                    {
                        if (tmp->get_next()->get_name() == aname)
                        {

                            RLVnode* tmpnext = tmp->get_next();
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
    void clear(){
        start = NULL;
        tail = NULL;
        size = 0;
    }
};