/**
 * @file Airline.cpp
 * COMPLETAR!!!!
 */

#include "Airline.h"

Airline::Airline()
{
}

Airline::Airline(string code_, string name_, string callsign_, string country_)
{
    code = code_;
    name = name_;
    callsign = callsign_;
    country = country_;
}

bool Airline::operator<(const Airline &a2) const
{
    return get_code() < a2.get_code();
}
