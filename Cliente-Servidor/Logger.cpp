#include <string>
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;


class Logger{

    tm *ltm;

public:

    Logger(){
        time_t now = time(0);

        ltm = localtime(&now);
    }

    string get_date(){
        string year = parse_int(1900+ltm->tm_year);
        string month = parse_int( 1+ltm->tm_mon);
        string day = parse_int(ltm->tm_mday);

        return year +"/"+month+"/"+day;
    }
    string get_time(){
        string hour = parse_int(ltm->tm_hour);
        string min = parse_int(ltm->tm_min);
        string sec = parse_int(ltm->tm_sec);
        return hour+":"+min+":"+sec;
    }
    string get_infolog(string msg){
        return "["+get_date()+" | "+get_time()+"]" + " [info] " +msg;
    }
    string get_errorlog(string msg){
        return "["+get_date()+" | "+get_time()+"]" + " [error] " +msg;
    }
    string get_warninglog(string msg){
        return "["+get_date()+" | "+get_time()+"]" + " [waring] " +msg;
    }

    string parse_int(int num){
        ostringstream o;
        o << num;
        string snum = o.str();
        return snum;
    }
};



