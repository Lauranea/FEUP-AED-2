/**
 * @file IO.h
 * Funções para ler ficheiros
 */

#ifndef _IO_H_
#define _IO_H_


#include <iostream>
#include <list>
#include "Graph.h"
#include "Flight.h"
#include "FlightManager.h"
#include "Airline.h"
#include "Airport.h"
#include <unordered_map>
#include "Read.h"
#include <set>


using namespace std;

class IO
{
  private:
    static void get_airport_info_1(FlightManager &fm);
    static void get_airport_info_2(FlightManager &fm);
    static void get_airport_info_3(FlightManager &fm);
    static void get_airport_info_4(FlightManager &fm);
    static void get_airport_info_5(FlightManager &fm);
    

  public:
    static void get_airport_info(FlightManager &fm);


};

#endif