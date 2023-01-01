/**
 * @file main.cpp
 * COMPLETAR!!!!
 */

#include <iostream>
#include "FlightManager.h"
#include "IO.h"

int main()
{
    FlightManager fm;
    fm.initialize();

    IO::get_airport_info(fm);
    
    return 0;
}