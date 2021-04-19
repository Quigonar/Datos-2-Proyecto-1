#include <iostream>
#include <cmath>
using namespace std;

//Node list
class Node {
public:
    //Atributes
    string name;
    string type;
    int offset;
    Node* next;


    //Simple Constructor
    Node() {
        type = "";
        name = "";
        offset = NULL;
        next = NULL;

    }
    //Constructor with argument
    Node(int adata,string atype, string aname) {
        offset = adata;
        type = atype;
        name = aname;
        next = NULL;

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
    string get_name() {
        return name;
    }

};



