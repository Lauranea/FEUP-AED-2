/**
 * @file Airport.h
 * Funções para ler ficheiros
 */

#ifndef _AIRPORT_H_
#define _AIRPORT_H_


#include <iostream>
#include <list>

using namespace std;

class Airport
{
  private:
    int index;
    string code, name, city, country;
    float latitude, longitude;

  public:
    Airport();
    Airport(string code_, string name_, string city_, string country_, float latitude_, float longitude_);
    string get_code() const {return code;};
    string get_name() const {return name;};
    string get_city() const {return city;};
    string get_country() const {return country;};
    float get_latitude() const {return latitude;};
    float get_longitude() const {return longitude;};
    bool operator<(const Airport &a2) const;
};

#endif