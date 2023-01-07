/**
 * @file Flight.h
 * Funções relacionadas com os voos
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
    float weight;

  public:
    Flight();
    Flight(Airport source_, Airport target_, Airline airline_, float weight_);
    Airport get_source() {return source;};
    Airport get_target() {return target;};
    Airline get_airline() {return airline;};
    float get_weight() {return weight;};
};

#endif