/**
 * @file FlightManager.cpp
 * COMPLETAR!!!!
 */

#include "FlightManager.h"

void FlightManager::initialize()
{
    airlines = Read::read_airlines();
    airports = Read::read_airports();
    flights = Read::read_flights();

    cout << airlines.size() << endl;
    cout << airports.size() << endl;
}