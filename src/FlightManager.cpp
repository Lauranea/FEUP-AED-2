/**
 * @file FlightManager.cpp
 * Informaçao de todas as airlines, airports, e voos(grafos)
 */

#include "FlightManager.h"

/**
 * @brief inicializa a class FlightManager que  chamar o Read para guardar a informaçao de todos os airports, airlines e voos
 * 
 */
void FlightManager::initialize()
{
    airports = Read::read_airports();
    airlines = Read::read_airlines();
    air = Read::read_flights(airports, airlines);

    // vector<string> a = air.BFS("CDG", "WWK");
    // for (auto b : a)
    // {
    //     cout << b << endl;
    // }
}