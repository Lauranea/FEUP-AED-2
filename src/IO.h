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
#include <istream>
#include <sstream>  
#include <climits>


using namespace std;

#define RESET "\033[0m"
#define BOLDWHITE "\033[1m\033[37m"
#define RED "\033[31m"
#define VIMERR "\e[38;5;015m\e[48;2;255;0;0m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"

class IO
{
  private:
    static pair<string, pair<float, float>> get_point(FlightManager &fm, string point_name);
    static vector<string> which_airlines_to_use(FlightManager &fm);

    static void get_airport_info_1(FlightManager &fm);
    static void get_airport_info_2(FlightManager &fm);
    static void get_airport_info_3(FlightManager &fm);
    static void get_airport_info_4(FlightManager &fm);
    static void get_airport_info_5(FlightManager &fm);
    

  public:
    static void find_optimal_path(FlightManager &fm);

    static void get_airport_info(FlightManager &fm);

    static bool what_to_do(FlightManager &fm);


};

#endif