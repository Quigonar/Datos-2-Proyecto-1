#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class RLVnode{



public:
    string info [4] = {};
    RLVnode* next;

    RLVnode(string mem,string value, string name, string ref){
        info[0] = mem;
        info[1] = value;
        info[2] = name;
        info[3] = ref;
        next = NULL;
    }

    RLVnode* get_next(){
        return next;
    }

    string get_mem(){
        return info[0];
    }

    string get_value(){
        return info[1];
    }

    string get_name(){
        return info[2];
    }

    string get_ref(){
        return info[3];
    }

    void set_next(RLVnode* node){
        next = node;
    }
    void set_value(string value){
        info[1] = value;
    }

    void set_ref(string ref){
        info[3] = ref;
    }
};

