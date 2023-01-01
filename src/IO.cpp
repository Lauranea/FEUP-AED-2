/**
 * @file IO.cpp
 * COMPLETAR!!!!
 */

#include "IO.h"

void IO::get_airport_info(FlightManager &fm)
{
    cout << "\n"
            "1 - How many flights start on certain Airport?\n"
            "2 - How many Airlines operate on this Airport?\n"
            "3 - How many different Airports can you fly to from a certain Airport?\n"
            "4 - How many different Countries can you fly to from a certain Airport?\n"
            "5 - How many different places can you fly to from from a certain Airport in X flights max?\n" << endl;
    
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
    cout << "\nWhich Airport?\n" << endl;
    string choice = "";
    cin >> choice;
    int sum = 0;
    set<string> diferent_airlines;
    list<Flight> flights = fm.get_flights().nodes[choice];
    for (Flight p : flights)
    {
        diferent_airlines.insert(p.get_airline().get_code());
    }
    cout << endl << diferent_airlines.size() << " Airlines operate on this Airport\n" << endl;
}

void IO::get_airport_info_3(FlightManager &fm)
{
    cout << "\nWhich Airport?\n" << endl;
    string choice = "";
    cin >> choice;
    int sum = 0;
    set<string> different_airports;
    list<Flight> flights = fm.get_flights().nodes[choice];
    for (Flight p : flights)
    {
        different_airports.insert(p.get_target().get_code());
    }
    cout << endl << "You can fly to " << different_airports.size() << " different Airports from this Airport\n" << endl;
}

void IO::get_airport_info_4(FlightManager &fm)
{
    cout << "\nWhich Airport?\n" << endl;
    string choice = "";
    cin >> choice;
    int sum = 0;
    set<string> different_airports;
    list<Flight> flights = fm.get_flights().nodes[choice];
    for (Flight p : flights)
    {
        different_airports.insert(p.get_target().get_country());
    }
    cout << endl << "You can fly to " << different_airports.size() << " different Countries from this Airport\n" << endl;
}

void IO::get_airport_info_5(FlightManager &fm)
{
    cout << "\nWhich Airport?\n" << endl;
    string choice = "";
    cin >> choice;
    cout << "\nMax Flights?\n" << endl;
    int max = 0;
    cin >> max;
    if (max > 0)
    {
        cout << endl << "You can fly to " << fm.get_flights().BFL(choice, max+1).size() << " different Airports within " << max << " flights from this Airport\n" << endl;
    }
}