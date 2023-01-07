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


    while (!IO::what_to_do(fm))
    {
        cout << "----------------" << endl;
    }
    
    return 0;
}