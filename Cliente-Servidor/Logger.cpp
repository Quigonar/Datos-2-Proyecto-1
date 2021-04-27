/**
 * @file Logger.cpp
 * @version 1.0
 * @title Logger
 * @brief Logger para el servidor del IDE
 */
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

/**
 * @brief Clase Logger se encarga de crear mensajes con formato log4j
 */

class Logger{

    tm *ltm;//struct de tiempo de ctime

public:

    /**
     * @brief Constructor de clase Logger
     */
    Logger(){
        time_t now = time(0);
        ltm = localtime(&now);
    }
    /**
     * @brief resettime resets the time so it can be updated
     */
    void resettime(){
        time_t now = time(0);
        ltm = localtime(&now);
    }

    /**
     * @brief get_datese encarga de obtener la fecha actual
     * @return un string con la fecha
     */
    string get_date(){
        string year = parse_int(1900+ltm->tm_year);//año
        string month = parse_int( 1+ltm->tm_mon);//mes
        string day = parse_int(ltm->tm_mday);//dia

        return year +"/"+month+"/"+day;//formato calendario
    }

    /**
     * @brief get_time se encarga de obtener el tiempo actual
     * @return string con el tiempo
     */
    string get_time(){
        string hour = parse_int(ltm->tm_hour);//horas
        string min = parse_int(ltm->tm_min);//minutos
        string sec = parse_int(ltm->tm_sec);//segundos
        cout<<"segundos " << sec <<endl;
        return hour+":"+min+":"+sec;//formato reloj
    }
    /**
     * @brief get_infolog crea un formato de log con fecha, tipo info y con mensaje
     * @param msg el mensaje que se quiere mandar
     * @return string en formato log4j
     */
    string get_infolog(string msg){
        resettime();
        return "["+get_date()+" | "+get_time()+"]" + " [info] " +msg;
    }
    /**
     * @brief get_errorlog crea un formato de log con fecha, tipo error y con mensaje
     * @param msg el mensaje que se quiere mandar
     * @return string en formato log4j
     */
    string get_errorlog(string msg){
        resettime();
        return "["+get_date()+" | "+get_time()+"]" + " [error] " +msg;
    }

    /**
     * @brief get_warninglog crea un formato de log con fecha, tipo warning y con mensaje
     * @param msg el mensaje que se quiere mandar
     * @return string en formato log4j
     */
    string get_warninglog(string msg){
        resettime();
        return "["+get_date()+" | "+get_time()+"]" + " [waring] " +msg;
    }

    /**
     * @brief parse_int cambia de int a string
     * @param num numero que se quiere cambiar
     * @return string de num
     */
    string parse_int(int num){
        ostringstream o;
        o << num;
        string snum = o.str();//parsea
        return snum;
    }
};




