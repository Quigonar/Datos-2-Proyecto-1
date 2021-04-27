#include <iostream>
#include <cmath>
using namespace std;

//Node list
class Node {
public:
    //Atributes
    string name;
    string refname;
    string type;
    int refnum;
    int offset;
    Node* next;
    string mem;


    //Constructor with argument
    Node(int adata,string atype, string aname) {
        offset = adata;
        type = atype;
        name = aname;
        next = NULL;
        refnum = 1;

    }

    //pointer setter
    void set_next(Node* ptr) {
        next = ptr;
    }
    void add_refnum() {
        refnum++;
    }
    void set_mem(string amem){
        mem = amem;
    }
    void set_refname(string arefname){
        refname = arefname;
    }


    //pointer getter
    Node* get_next() {
        return next;
    }

    int get_varoffset() {
        return offset;
    }

    int get_refnum(){
        return refnum;
    }
    int get_offset(){
        return offset;
    }
    string get_name() {
        return name;
    }
    string get_mem(){
        return mem;
    }
    string get_refname(){
        return refname;
    }

};



