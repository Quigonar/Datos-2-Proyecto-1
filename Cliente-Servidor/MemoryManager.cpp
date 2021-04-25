#include <iostream>
#include "MemoryList/LinkedList.cpp"
#include <stdlib.h>

using namespace std;

class MemoryManager {

    int offset;
    char* mem;
    int bytes;
    int used;

    LinkedList intarray;
    LinkedList floatarray;
    LinkedList doublearray;
    LinkedList chararray;
    LinkedList longarray;
    LinkedList refarray;
    LinkedList structarray;

public:

    MemoryManager(int abytes) {
        offset = 0;
        mem = (char*)malloc(abytes);
        bytes = abytes;
        used = 0;
    }

    //Memory offset manager ***************************************
    int* getmemoryoffsetint(int off) {
        return (int*)(mem + off);
    }

    float* getmemoryoffsetfloat(int off) {
        return (float*)(mem + off);
    }
    double* getmemoryoffsetdouble(int off) {
        return (double*)(mem + off);
    }
    char* getmemoryoffsetchar(int off) {
        return (char*)(mem + off);
    }

    long long* getmemoryoffsetlong(int off) {
        return (long long*)(mem + off);
    }

    int* getmemoryoffsetref(int off) {
        return (int*)(mem + off);
    }

    int* getmemoryoffsetstruct(int off) {
        return (int*)(mem + off);
    }
    //Memory variable add *****************************************

    bool addvariableint(int value,string name) {
        if(outofmemory(4)){
            int tmp = getoffset();
            cout << "This is offset: " << getoffset() << endl;
            int* mtp = getmemoryoffsetint(tmp);

            *mtp = value;
            cout << "Value: " << value << endl;
            intarray.append(tmp, "int", name);
            offset = offset+4;
            used = used + 4;
            return true;
        }
        else
        {
            return false;
            //return error en consola
        }


    }

    bool addvariablefloat(float value, string name) {
        if(outofmemory(4)){
            int tmp = getoffset();
            cout << "This is offset: " << getoffset() << endl;

            float* mtp = (float*)getmemoryoffsetfloat(tmp);

            *mtp = value;

            floatarray.append(tmp, "float", name);
            offset = offset+4;
            used = used + 4;
            return true;
        }
        else
        {
            //return error en consola
            return false;
        }


    }

    bool addvariabledouble(double value, string name) {
        if (outofmemory(8))
        {
            int tmp = getoffset();
            cout << "This is offset: " << getoffset() << endl;
            double* mtp = getmemoryoffsetdouble(tmp);

            *mtp = value;

            doublearray.append(getoffset(), "double", name);
            offset = offset+8;
            used = used + 8;
            return true;
        }
        else
        {
            //return error en consola
            return false;
        }

    }


    bool addvariablechar(char value, string name) {
        if (outofmemory(1))
        {
            int tmp = getoffset();
            cout << "This is offset: " << getoffset() << endl;
            char* mtp = getmemoryoffsetchar(tmp);

            *mtp = value;

            chararray.append(getoffset(), "char", name);
            offset = offset+1;
            used = used + 1;
            return true;
        }
        else
        {
            //return error console
            return false;
        }

    }

    bool addvariablelong(long long value, string name) {
        if (outofmemory(8))
        {
            int tmp = getoffset();
            cout << "This is offset: " << getoffset() << endl;
            long long* mtp = getmemoryoffsetlong(tmp);

            *mtp = value;

            longarray.append(getoffset(), "long", name);
            offset = offset + 8;
            used = used + 8;
            return true;
        }
        else
        {
            //return error console
            return false;
        }

    }

    void addvariableref(int* addr, string type, string name) {
        int tmp = getoffset();
        cout << "This is offset: " << getoffset() << endl;
        cout << "This is address value: " << *addr<< endl;

        if (type == "int")
        {
            int* mtp = getmemoryoffsetint(tmp);
            mtp = addr;
        }
        else if (type == "float")
        {
            float* mtp = getmemoryoffsetfloat(tmp);
            mtp = (float*) addr;
        }
        else if (type == "double")
        {
            double* mtp = getmemoryoffsetdouble(tmp);
            mtp = (double*) addr;
        }
        else if (type == "char")
        {
            char* mtp = getmemoryoffsetchar(tmp);
            mtp = (char*) addr;
        }
        else if (type == "long")
        {
            long long* mtp = getmemoryoffsetlong(tmp);
            mtp = (long long*) addr;
        }

        refarray.append(getoffset(), type, name);
        offset++;
    }

    int change_intvar(string name,int value){
        int aoffset = intarray.findoffset(name);
        int* ptr = getmemoryoffsetint(aoffset);
        *ptr = value;
        return aoffset;
    }

    int change_floatvar(string name,float value){
        int aoffset = floatarray.findoffset(name);
        float* ptr = getmemoryoffsetfloat(aoffset);
        *ptr = value;
        return aoffset;
    }

    int change_longvar(string name,long long value){
        int aoffset = longarray.findoffset(name);
        long long* ptr = getmemoryoffsetlong(aoffset);
        *ptr = value;
        return aoffset;
    }

    int change_charvar(string name, char value){
        int aoffset = chararray.findoffset(name);
        char* ptr = getmemoryoffsetchar(aoffset);
        *ptr = value;
        return aoffset;
    }

    int change_doublevar(string name, double value){
        int aoffset = doublearray.findoffset(name);
        double* ptr = getmemoryoffsetdouble(aoffset);
        *ptr = value;
        return aoffset;
    }

    void change_structvar(string name, int value){

    }
    void add_varref(string type, string name){
        if (type == "int")
        {
            intarray.changeref(name);
        }
        else if (type == "float")
        {
            floatarray.changeref(name);
        }
        else if (type == "double")
        {
            doublearray.changeref(name);
        }
        else if (type == "char")
        {
            chararray.changeref(name);
        }
        else if (type == "long")
        {
            longarray.changeref(name);
        }
        else if (type == "ref")
        {

        }
    }

    int get_varref(string type, string name){
        if (type == "int")
        {
            if(intarray.findvar(name)){
                int xref = intarray.findref(name);
                return xref;
            }
            else{
                return -1;
            }

        }
        else if (type == "float")
        {
            if(floatarray.findvar(name)){
                int xref = floatarray.findref(name);
                return xref;
            }
            else{
                return -1;
            }
        }
        else if (type == "double")
        {
            if(doublearray.findvar(name)){
                int xref = doublearray.findref(name);
                return xref;
            }
            else{
                return -1;
            }
        }
        else if (type == "char")
        {
            if(chararray.findvar(name)){
                int xref = chararray.findref(name);
                return xref;
            }
            else{
                return -1;
            }
        }
        else if (type == "long")
        {
            if(longarray.findvar(name)){
                int xref = longarray.findref(name);
                return xref;
            }
            else{
                return -1;
            }
        }
        else if (type == "ref")
        {
            return 0;
        }
    }

    void free_memory(){
        free(mem);
        offset = 0;
        used = 0;
        mem = (char*)malloc(bytes);
        intarray.deleteall();
        floatarray.deleteall();
        doublearray.deleteall();
        longarray.deleteall();
        chararray.deleteall();

    }
    void printmem() {
        for (int i = 0; i < this->offset; i++) {

            bool isint = intarray.find(i);
            bool isfloat = floatarray.find(i);
            bool isdouble = doublearray.find(i);
            bool ischar = chararray.find(i);
            bool islong = longarray.find(i);
            bool isref = refarray.find(i);

            if(isint||isfloat||isdouble||ischar||islong||isref){
                cout << "===============" << endl;
                cout << "offset: " << i << endl;
                cout << "int: " << isint << endl;
                cout << "float: " << isfloat << endl;
                cout << "double: " << isdouble << endl;
                cout << "char: " << ischar << endl;
                cout << "long: " << islong << endl;
                cout << "res: " << isref << endl;
                if (isint)
                {
                    int* tmp = getmemoryoffsetint(i);
                    cout << *tmp << endl;
                    cout << "size: " << sizeof(*tmp) << endl;
                    cout << "Memory: " << tmp << endl;
                }
                else if (isfloat)
                {
                    float* tmp = getmemoryoffsetfloat(i);
                    cout << *tmp << endl;
                    cout << "size: " << sizeof(*tmp) << endl;
                    cout << "Memory: " << tmp << endl;
                }
                else if (isdouble)
                {
                    double* tmp = getmemoryoffsetdouble(i);
                    cout << *tmp << endl;
                    cout << "size: " << sizeof(*tmp) << endl;
                    cout << "Memory: " << tmp << endl;
                }
                else if (ischar)
                {
                    char* tmp = getmemoryoffsetchar(i);
                    cout << *tmp << endl;
                    cout << "size: " << sizeof(*tmp) << endl;

                    cout << "Memory: " << getmemoryoffsetchar(i) << endl;
                    cout << "Memory: " << tmp << endl;

                }
                else if (islong)
                {
                    long long* tmp = getmemoryoffsetlong(i);
                    cout << *tmp << endl;
                    cout << "size: " << sizeof(*tmp) << endl;
                    cout << "Memory: " << tmp << endl;

                }
                else if (isref)
                {
                    int* tmp = getmemoryoffsetint(i);
                    cout << *tmp << endl;
                    cout << "size: " << sizeof(*tmp) << endl;
                    cout << "Memory: " << tmp << endl;

                }
            }
        }
    }

    int getoffset() {
        return offset;
    }

    void* get_mem() {
        return mem;
    }

    LinkedList* getlist(string type) {
        if (type == "int")
        {
            return &intarray;
        }
        else if (type == "float")
        {
            return &floatarray;
        }
        else if (type == "double")
        {
            return &doublearray;
        }
        else if (type == "char")
        {
            return &chararray;
        }
        else if (type == "long")
        {
            return &longarray;
        }
        else if (type == "ref")
        {
            return &refarray;
        }
    }


    bool outofmemory(int abytes) {
        if (used + abytes <= bytes )
        {
            return true;
        }
        else {
            return false;
        }
    }
};


int main(){

    MemoryManager m(10000);

    m.addvariableint(10,"a");
    m.addvariableref(m.getmemoryoffsetint(0),"int","b");

    m.printmem();

    return 0;
}
