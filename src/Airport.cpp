/**
 * @file Airport.cpp
 * COMPLETAR!!!!
 */

#include "Airport.h"

Airport::Airport()
{
}

Airport::Airport(string code_, string name_, string city_, string country_, float latitude_, float longitude_)
{
    code = code_;
    name = name_;
    city = city_;
    country = country_;
    latitude = latitude_;
    longitude = longitude_;
}

bool Airport::operator<(const Airport &a2) const
{
    return get_code() < a2.get_code();
}