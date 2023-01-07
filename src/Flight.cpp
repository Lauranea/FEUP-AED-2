/**
 * @file Flight.cpp
 * Funções relacionadas com os voos
 */

#include "Flight.h"

/**
 * @brief Construtor de new Flight:: Flight object
 * 
 */
Flight::Flight()
{
}

/**
 * @brief Construtor de um Flight
 * 
 * @param source_ de onde o voo parte
 * @param target_ destino do voo
 * @param airline_ airline do voo
 * @param weight_ distancia dos airports
 */
Flight::Flight(Airport source_, Airport target_, Airline airline_, float weight_)
{
    source = source_;
    target = target_;
    airline = airline_;
    weight = weight_;
}
