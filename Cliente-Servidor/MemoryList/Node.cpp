#include <iostream>
#include <cmath>
using namespace std;

//Node list
class Node {
public:
    //Atributes
    string name;
    string type;
    int refnum;
    int offset;
    Node* next;


    //Constructor with argument
    Node(int adata,string atype, string aname) {
        offset = adata;
        type = atype;
        name = aname;
        next = NULL;
        refnum = 0;

    }

    //pointer setter
    void set_next(Node* ptr) {
        next = ptr;
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
    string get_name() {
        return name;
    }

};



