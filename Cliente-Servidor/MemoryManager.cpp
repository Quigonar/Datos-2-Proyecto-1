/**
 * @file MemoryManager.cpp
 * @version 1.0
 * @title MemoryManager
 * @brief Manejo de memoria del servidor
 */
#include <iostream>
#include "MemoryList/LinkedList.cpp"
#include <sstream>
#include <stdlib.h>

using namespace std;

/**
 *@brief Clase MemoryManager que se encarga de manejar la memoria del server
 */
class MemoryManager {

    /**
     * @brief int offset es el offset de la memoria
     */
    int offset;
    /**
     * @brief char* mem es el espacio de memoria reservado
     */
    char* mem;
    /**
     * @brief int bytes es la cantidad de bytes que reservaron
     */
    int bytes;
    /**
     * @brief int used es la cantidad de bytes que han sido utilizados
     */
    int used;
    //Memoria virtual
    LinkedList intarray;
    LinkedList floatarray;
    LinkedList doublearray;
    LinkedList chararray;
    LinkedList longarray;
    LinkedList refarray;
    LinkedList structarray;

public:
    /**
     * @brief Constructor de la clase MemoryManager
     * @param abytes numero de bytes que se quieren reservar
     */
    MemoryManager(int abytes) {
        offset = 0;
        mem = (char*)malloc(abytes);
        bytes = abytes;
        used = 0;
    }

    //Memory offset manager ***************************************
    /**
     * @brief getmemoryoffsetint devuleve el espacio de memoria en el offset que se le pida
     * @param off es le offset de la memoria que se quiere accesar
     * @return puntero int que apunta al espacio de memoria que se desea accesar
     */
    int* getmemoryoffsetint(int off) {
        return (int*)(mem + off);
    }
    /**
     * @brief getmemoryoffsetfloat devuleve el espacio de memoria en el offset que se le pida
     * @param off es le offset de la memoria que se quiere accesar
     * @return puntero float que apunta al espacio de memoria que se desea accesar
     */
    float* getmemoryoffsetfloat(int off) {
        return (float*)(mem + off);
    }
    /**
     * @brief getmemoryoffsetdouble devuleve el espacio de memoria en el offset que se le pida
     * @param off es le offset de la memoria que se quiere accesar
     * @return puntero double que apunta al espacio de memoria que se desea accesar
     */
    double* getmemoryoffsetdouble(int off) {
        return (double*)(mem + off);
    }
    /**
     * @brief getmemoryoffsetchar devuleve el espacio de memoria en el offset que se le pida
     * @param off es le offset de la memoria que se quiere accesar
     * @return puntero char que apunta al espacio de memoria que se desea accesar
     */
    char* getmemoryoffsetchar(int off) {
        return (char*)(mem + off);
    }
    /**
     * @brief getmemoryoffsetlong devuleve el espacio de memoria en el offset que se le pida
     * @param off es le offset de la memoria que se quiere accesar
     * @return puntero long que apunta al espacio de memoria que se desea accesar
     */
    long long* getmemoryoffsetlong(int off) {
        return (long long*)(mem + off);
    }


    //Memory variable add *****************************************
    /**
     * @brief addvariableint se encarga de asignarle valor int al ultimo espacio de memoria disponible
     * @param value es el valor que se quiere insertar
     * @param name es el nombre de la variable
     * @return retorna un booleano si se logró o no insertar el valor en memoria
     */
    bool addvariableint(int value,string name) {
        if(outofmemory(4)){//revisar si hay espacio en la memoria
            //se hagarra el ultimo espacio de memoria disponible
            int tmp = getoffset();
            int* mtp = getmemoryoffsetint(tmp);
            //se le asigna el valor
            *mtp = value;
            //se agrega esa variable a una memoria virtual
            intarray.append(tmp, "int", name);
            offset = offset+4;
            used = used + 4;
            return true;
        }
        else
        {
            //no hay espacio en memoria
            return false;
        }


    }
    /**
     * @brief addvariablefloat se encarga de asignarle valor float al ultimo espacio de memoria disponible
     * @param value es el valor que se quiere insertar
     * @param name es el nombre de la variable
     * @return retorna un booleano si se logró o no insertar el valor en memoria
     */
    bool addvariablefloat(float value, string name) {
        if(outofmemory(4)){//revisar si hay espacio en la memoria
            //se hagarra el ultimo espacio de memoria disponible
            int tmp = getoffset();
            float* mtp = (float*)getmemoryoffsetfloat(tmp);
            //se le asigna el valor
            *mtp = value;
            //se agrega esa variable a una memoria virtual
            floatarray.append(tmp, "float", name);
            offset = offset+4;
            used = used + 4;
            return true;
        }
        else
        {
            //no hay espacio en memoria
            return false;
        }


    }
    /**
     * @brief addvariabledouble se encarga de asignarle valor double al ultimo espacio de memoria disponible
     * @param value es el valor que se quiere insertar
     * @param name es el nombre de la variable
     * @return retorna un booleano si se logró o no insertar el valor en memoria
     */
    bool addvariabledouble(double value, string name) {
        if (outofmemory(8))
        {//revisar si hay espacio en la memoria
            //se hagarra el ultimo espacio de memoria disponible
            int tmp = getoffset();
            double* mtp = getmemoryoffsetdouble(tmp);
            //se le asigna el valor
            *mtp = value;
            //se agrega esa variable a una memoria virtual
            doublearray.append(getoffset(), "double", name);
            offset = offset+8;
            used = used + 8;
            return true;
        }
        else
        {
            //No hay espacio en memoria
            return false;
        }

    }

    /**
     * @brief addvariablechar se encarga de asignarle valor char al ultimo espacio de memoria disponible
     * @param value es el valor que se quiere insertar
     * @param name es el nombre de la variable
     * @return retorna un booleano si se logró o no insertar el valor en memoria
     */
    bool addvariablechar(char value, string name) {
        if (outofmemory(1))
        {//revisar si hay espacio en la memoria
            //se hagarra el ultimo espacio de memoria disponible
            int tmp = getoffset();
            char* mtp = getmemoryoffsetchar(tmp);
            //se le asigna el valor
            *mtp = value;
            //se agrega esa variable a una memoria virtual
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

    /**
     * @brief addvariablelong se encarga de asignarle valor long al ultimo espacio de memoria disponible
     * @param value es el valor que se quiere insertar
     * @param name es el nombre de la variable
     * @return retorna un booleano si se logró o no insertar el valor en memoria
     */
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
    /**
     * @brief mem_parse cambia el espacio de memoria en un string
     * @param ptr puntero al espacio de memoria que se quiere parsear
     * @return un string con el espacio de memoria
     */
    string mem_parse(void* ptr){
        ostringstream o;
        o<<ptr;
        string addr = o.str();
        return addr;
    }

    /**
     * @brief addvariablecref se encarga de asignarle valor puntero al ultimo espacio de memoria disponible
     * @param value es el valor que se quiere insertar
     * @param name es el nombre de la variable
     * @return retorna un booleano si se logró o no insertar el valor en memoria
     */
    bool addvariableref(string type, string name, string value) {
        if (outofmemory(4)) {//rear si hay espacio en memoria
            //se hagarra el ultimo espacio de memoria
            int aoffset = getoffset();
            string mem = mem_parse((void *) getmemoryoffsetint(aoffset));
            //se agrega a la memoria virtual
            refarray.append(aoffset, type, name, mem,value);
            offset += 4;
            used += 4;
            return true;
        }
        else{
            //no hay espacio en memoria
            return false;
        }
    }

    /**
     * @brief change_intvar cambia el valor de la variable int que se le indique
     * @param name nombre de la variable
     * @param value valor al cual se quiere redefinir
     * @return retorna el offset de la variable que se cambio
     */
    int change_intvar(string name,int value){
        int aoffset = intarray.findoffset(name);//encontar offset
        int* ptr = getmemoryoffsetint(aoffset);
        *ptr = value;//redefininr
        return aoffset;
    }
    /**
     * @brief change_floatvar cambia el valor de la variable float que se le indique
     * @param name nombre de la variable
     * @param value valor al cual se quiere redefinir
     * @return retorna el offset de la variable que se cambio
     */
    int change_floatvar(string name,float value){
        int aoffset = floatarray.findoffset(name);
        float* ptr = getmemoryoffsetfloat(aoffset);
        *ptr = value;
        return aoffset;
    }
    /**
     * @brief change_longvar cambia el valor de la variable long que se le indique
     * @param name nombre de la variable
     * @param value valor al cual se quiere redefinir
     * @return retorna el offset de la variable que se cambio
     */
    int change_longvar(string name,long long value){
        int aoffset = longarray.findoffset(name);
        long long* ptr = getmemoryoffsetlong(aoffset);
        *ptr = value;
        return aoffset;
    }
    /**
     * @brief change_charvar cambia el valor de la variable char que se le indique
     * @param name nombre de la variable
     * @param value valor al cual se quiere redefinir
     * @return retorna el offset de la variable que se cambio
     */
    int change_charvar(string name, char value){
        int aoffset = chararray.findoffset(name);
        char* ptr = getmemoryoffsetchar(aoffset);
        *ptr = value;
        return aoffset;
    }
    /**
     * @brief change_doublevar cambia el valor de la variable double que se le indique
     * @param name nombre de la variable
     * @param value valor al cual se quiere redefinir
     * @return retorna el offset de la variable que se cambio
     */
    int change_doublevar(string name, double value){
        int aoffset = doublearray.findoffset(name);
        double* ptr = getmemoryoffsetdouble(aoffset);
        *ptr = value;
        return aoffset;
    }
    /**
     * @brief change_refvar cambia el valor de la variable ref que se le indique
     * @param name nombre de la variable
     * @param value valor al cual se quiere redefinir
     * @return retorna el offset de la variable que se cambio
     */
    int change_refvar(string name, string value){
        int aoffset = refarray.findoffset(name);

        refarray.changemem(name,value);
        return aoffset;
    }

    /**
     * @brief add_varref le suma la cantidad de veces que la variable esta siendo referenciada
     * @param type tipo de variable
     * @param name nombre de la variable
     */
    void add_varref(string type, string name){
        if (type == "int")
        {
            intarray.changeref(name);//le suma 1 a la referencias de la variable
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
            refarray.changeref(name);//------------------------revisar
        }
    }

    /**
     * @brief get_varref se encarga de retornar la cantidad de referencias que tenga la variable que se le indique
     * @param type tipo de variable
     * @param name nombre de la variable
     * @return la cantidad de referencias que tenga esa variable
     */
    int get_varref(string type, string name){
        if (type == "int")//revisa el tipo de variable
        {
            if(intarray.findvar(name)){//busca a la variable dento de la memoria virtual
                int xref = intarray.findref(name);//busca la cantidad de referencias
                return xref;
            }
            else{
                //no existe la variable
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

    /**
     * @brief free_memory se encarga de borrar toda la memoria despues de parar la ejecución y la reinicia
     */
    void free_memory(){
        free(mem);//liberar la memoria
        //hacer reset a todos los valores
        offset = 0;
        used = 0;
        mem = (char*)malloc(bytes);//volver a reservar la memoria
        //Borra la memoria virtual
        intarray.deleteall();
        floatarray.deleteall();
        doublearray.deleteall();
        longarray.deleteall();
        chararray.deleteall();
    }
    /**
     * @brief deleteint se encarga de borrar la variable int que se le indique de memoria
     * @param name nome de la variable a borrar
     */
    void deleteint(string name){
        intarray.delete_elem(name);//elimina la variable que se le indique
    }
    /**
     * @brief deleteint se encarga de borrar la variable double que se le indique de memoria
     * @param name nome de la variable a borrar
     */
    void deletedouble(string name){
        doublearray.delete_elem(name);
    }
    /**
     * @brief deleteint se encarga de borrar la variable float que se le indique de memoria
     * @param name nome de la variable a borrar
     */
    void deletefloat(string name){
        floatarray.delete_elem(name);
    }
    /**
     * @brief deleteint se encarga de borrar la variable char que se le indique de memoria
     * @param name nome de la variable a borrar
     */
    void deletechar(string name){
        chararray.delete_elem(name);
    }
    /**
     * @brief deleteint se encarga de borrar la variable long que se le indique de memoria
     * @param name nome de la variable a borrar
     */
    void deletelong(string name){
        longarray.delete_elem(name);
    }
    /**
     * @brief deleteint se encarga de borrar la variable ref que se le indique de memoria
     * @param name nome de la variable a borrar
     */
     void deleteref(string name){
         refarray.delete_elem(name);
     }

     /**
      * @brief printmem imprime la memoria en consola para hacer casos de prueba
      */
    void printmem() {
        for (int i = 0; i < this->offset; i++) {//revisa cada offset posible

            //revisa que tipo de variable se encuentra en este offset
            bool isint = intarray.find(i);
            bool isfloat = floatarray.find(i);
            bool isdouble = doublearray.find(i);
            bool ischar = chararray.find(i);
            bool islong = longarray.find(i);
            bool isref = refarray.find(i);

            if(isint||isfloat||isdouble||ischar||islong||isref){//si existe
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

    /**
     * @brief getoffset retorna el offset en que se encuentre la memoria
     * @return el offset de la memoria
     */
    int getoffset() {
        return offset;
    }

    /**
     * @brief get_mem retorna el puntero de la memoria
     * @return puntero al primer elemento de la memoria reservada
     */
    void* get_mem() {
        return mem;
    }

    /**
     * @brief getlist se encarga de retornar el puntero de la memoria virtual para hacer otras operaciones con ella
     * @param type tipo de lista que se quiere accesar
     * @return puntero de la lista que se desea
     */
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

    /**
     * @brief outofmemory se encarga de revisar si todavia le queda espacio a la memoria
     * @param abytes numero de bytes que se quieren agregar
     * @return booleano si hay o no espacio
     */
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


/*int main(){

    MemoryManager m(10000);

    m.addvariableint(10,"a");
    m.addvariableint(20,"b");
    m.addvariableint(10,"c");
    m.addvariableint(10,"z");
    m.addvariableint(10,"d");
    m.getlist("int")->printList();
    m.deleteint("a");

    m.getlist("int")->printList();

    return 0;
}*/