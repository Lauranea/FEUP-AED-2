/**
 * @file FlightManager.cpp
 * COMPLETAR!!!!
 */

#include "FlightManager.h"

void FlightManager::initialize()
{
    airports = Read::read_airports();
    airlines = Read::read_airlines();
    air = Read::read_flights(airports, airlines);
}