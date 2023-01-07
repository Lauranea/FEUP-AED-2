/**
 * @file Airport.cpp
 * Funções relacionadas com os aeroportos
 */

#include "Airport.h"

/**
 * @brief Construtor de new Airport:: Airport object
 * 
 */
Airport::Airport()
{
}

/**
 * @brief Construtor de Airport
 * 
 * @param code_ codigo do aeroporto
 * @param name_ nome do aeroporto
 * @param city_ cidade do aeroporto
 * @param country_ país do aeroporto
 * @param latitude_ latitude do aereoporto
 * @param longitude_ longitude do aeroporto
 */
Airport::Airport(string code_, string name_, string city_, string country_, float latitude_, float longitude_)
{
    code = code_;
    name = name_;
    city = city_;
    country = country_;
    latitude = latitude_;
    longitude = longitude_;
}