#include <iostream>
#include <string>

#pragma once
class User{
    private:
        std::string date;
        std::string hour;
        std::string origin_IP;
        std::string origin_Port;
        std::string origin_Name;
        std::string target_IP;
        std::string target_Port;
        std::string target_Name;

    public:
        User(){}
        User(std::string d, std::string h, std::string oIP, std::string oP, std::string oN, std::string dIP, std::string dP, std::string dN):
            date(d), hour(h), origin_IP(oIP), origin_Port(oP), origin_Name(oN), target_IP(dIP), target_Port(dP), target_Name(dN){}

        virtual std::string getDate(){return date;}
        virtual std::string getHour(){return hour;}
        virtual std::string getOriginIP(){return origin_IP;}
        virtual std::string getOriginPort(){return origin_Port;}
        virtual std::string getOriginName(){return origin_Name;}
        virtual std::string getTargetIP(){return target_IP;}
        virtual std::string getTargetPort(){return target_Port;}
        virtual std::string getTargetName(){return target_Name;}

/*
        friend std::ostream & operator<<(std::ostream & os, const User & user)
        {
            os << user.date << " - ";
            os << user.hour << " - ";
            os << user.origin_IP << " - ";
            os << user.origin_Port << " - ";
            os << user.origin_Name << " - ";
            os << user.target_IP << " - ";
            os << user.target_Port << " - ";
            os << user.target_Name;
            os << std::endl;
            
            return os;
        }   
*/     
        
}; 