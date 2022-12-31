/**
 * @file Read.h
 * Funções para ler ficheiros
 */

#ifndef _READ_H_
#define _READ_H_

#include <list>
#include <vector>

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include "Airline.h"
#include "Airport.h"
#include "Flight.h"
#include "Graph.h"

using namespace std;

class Read
{
  public:
    static unordered_map<string, Airline> read_airlines();
    static unordered_map<string, Airport> read_airports();
    static Graph<Flight> read_flights();
};

#endif