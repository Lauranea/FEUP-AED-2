/**
 * @file Flight.h
 * Funções para ler ficheiros
 */

#ifndef _FLIGHT_H_
#define _FLIGHT_H_


#include "Airport.h"
#include "Airline.h"
#include <iostream>
#include <list>

using namespace std;

class Flight
{
  private:
    Airport source;
    Airport target;
    Airline airline;

  public:
    Flight();
    Flight(Airport source_, Airport target_, Airline airline_);
    Airport get_source() {return source;};
    Airport get_target() {return target;};
    Airline get_airline() {return airline;};
};

#endif