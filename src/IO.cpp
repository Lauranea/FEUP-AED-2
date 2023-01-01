/**
 * @file IO.cpp
 * COMPLETAR!!!!
 */

#include "IO.h"

void IO::get_airport_info(FlightManager &fm)
{
    cout << "\n"
            "1 - How many flights start on certain Airport?\n"
            "2 - How many Airlines use this Airport?\n"
            "3 - How many diferent Airports can you fly to from a certain Airport?\n"
            "4 - How many diferent Countries can you fly to from a certain Airport?\n"
            "5 - How many diferent places can you fly to from from a certain Airport in X flights max?\n" << endl;
    
    int choice = 0;
    cin >> choice;

    switch (choice)
    {
        case 1:
            get_airport_info_1(fm);
            break;
        case 2:
            get_airport_info_2(fm);
            break;
        case 3:
            get_airport_info_3(fm);
            break;
        case 4:
            get_airport_info_4(fm);
            break;
        case 5:
            get_airport_info_5(fm);
            break;
        default:
            cout << "\nInvalid choice\n" << endl;
            return;
    }
}

void IO::get_airport_info_1(FlightManager &fm)
{
    cout << "\nWhich Airport?\n" << endl;
    string choice = "";
    cin >> choice;
    int sum = fm.get_flights().nodes[choice].size();
    cout << endl << sum << " flights start on this Airport\n" << endl;
}

void IO::get_airport_info_2(FlightManager &fm)
{
    cout << "info" << endl;
}

void IO::get_airport_info_3(FlightManager &fm)
{
    cout << "info" << endl;
}

void IO::get_airport_info_4(FlightManager &fm)
{
    cout << "info" << endl;
}

void IO::get_airport_info_5(FlightManager &fm)
{
    cout << "info" << endl;
}