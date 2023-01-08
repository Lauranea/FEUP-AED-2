/**
 * @file FlightManager.cpp
 * Informaçao de todas as airlines, airports, e voos(grafos)
 */

#include "FlightManager.h"

/**
 * @brief inicializa a class FlightManager que  chamar o Read para guardar a informaçao de todos os airports, airlines e voos
 * Complexidade: 1
 */
void FlightManager::initialize()
{
    airports = Read::read_airports();
    airlines = Read::read_airlines();
    air = Read::read_flights(airports, airlines);
}