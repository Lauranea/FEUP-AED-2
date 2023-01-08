/**
 * @file Airline.cpp
 * Funções relacionadas com as airlines
 */

#include "Airline.h"

/**
 * @brief Construtor de uma new Airline:: Airline object
 * 
 */
Airline::Airline()
{
}

/**
 * @brief Construtor da airline
 * Complexidade: 1
 * @param code_ codigo da airline
 * @param name_ nome da airline
 * @param callsign_ callsign da airline
 * @param country_ país da airline
 */
Airline::Airline(string code_, string name_, string callsign_, string country_)
{
    code = code_;
    name = name_;
    callsign = callsign_;
    country = country_;
}

