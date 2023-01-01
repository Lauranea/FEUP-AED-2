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

    int c = Graph::hash("DAU");
    int f = Graph::hash("GOH");

    for (auto p : air.BFS(c, f))
    {
        cout << p << endl;
    }
}