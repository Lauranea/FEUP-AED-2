/**
 * @file Flight.h
 * Funções para ler ficheiros
 */

#ifndef _FLIGHT_H_
#define _FLIGHT_H_


#include "Airport.h"
#include <iostream>
#include <list>

using namespace std;

class Flight
{
  private:
    Airport source;
    Airport target;
    Airport airline;

  public:
    Flight();
    Flight(Airport source_, Airport target_, Airport airline_);
};

#endif