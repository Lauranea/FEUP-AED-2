/**
 * @file main.cpp
 * inicializa o flight manager e corre o loop do IO
 */

#include <iostream>
#include "FlightManager.h"
#include "IO.h"


/**
 * @brief inicializa o flight manager e corre o loop do IO
 * 
 */
int main()
{
    FlightManager fm;
    fm.initialize();


    while (!IO::what_to_do(fm))
    {
        cout << "\033[34m------------------------------------------\033[0m" << endl;
    }
    
    return 0;
}