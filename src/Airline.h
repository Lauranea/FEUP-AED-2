/**
 * @file Airline.h
 * Funções para ler ficheiros
 */

#ifndef _AIRLINE_H_
#define _AIRLINE_H_


#include <iostream>
#include <list>

using namespace std;

class Airline
{
  private:
    string code, name, callsign, country;

  public:
    Airline();
    Airline(string code_, string name_, string callsign_, string country_);
    string get_code() const {return code;};
    string get_name() const {return name;};
    string get_callsign() const {return callsign;};
    string get_country() const {return country;};
    bool operator<(const Airline &a2) const;
};

#endif