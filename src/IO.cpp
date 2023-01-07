/**
 * @file IO.cpp
 * COMPLETAR!!!!
 */

#include "IO.h"

bool IO::what_to_do(FlightManager &fm)
{
    cout << "\n"
            "1 - Find the optimal flight.\n"
            "2 - Get info about a certain airport.\n"
            "\n"
            "3 - Exit the program.\n" << endl;
    
    int choice = 0;
    cin >> choice;

    switch (choice)
    {
        case 1:
            IO::find_optimal_path(fm);
            break;
        case 2:
            IO::get_airport_info(fm);
            break;
        case 3:
            return true;
        default:
            cout << RED << "\nInvalid choice\n" << RESET << endl;
            break;
    }

    return false;
}

void IO::find_optimal_path(FlightManager &fm)
{
    // Stating Point
    cout << "---\n\nThe starting point is ...\n\n"
            "1 - A certain Airport.\n"
            "2 - A certain City.\n"
            "3 - An Airport close to these coordinates\n" << endl;
    
    int start_type = 0;
    cin >> start_type;

    string start;
    float start_lat = 0;
    float start_lon = 0;

    switch (start_type)
    {
        case 1:
            cout << "\nWhich Airport?\n" << endl;
            cin >> start;
            break;
        case 2:
            cout << "\nWhich City?\n" << endl;
            cin >> start;
            break;
        case 3:
            cout << "\nWhich Coordinates?\n" << endl;
            cout << "Latitude: ";
            cin >> start_lat;
            cout << "Longitude: ";
            cin >> start_lon;
            break;
        default:
            cout << RED << "\nInvalid choice\n" << RESET << endl;
            return;
    }
}

void IO::get_airport_info(FlightManager &fm)
{
    cout << "---\n\n"
            "1 - How many flights start on a certain Airport?\n"
            "2 - How many Airlines operate on a certain Airport?\n"
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
            cout << RED << "\nInvalid choice\n" << RESET << endl;
            return;
    }
}

void IO::get_airport_info_1(FlightManager &fm)
{
    cout << "\nWhich Airport?\n" << endl;
    string choice = "";
    cin >> choice;
    int sum = fm.get_flights().nodes[choice].adj.size();
    cout << BOLDWHITE << endl << sum << " flights start on this Airport\n" << RESET << endl;
}

void IO::get_airport_info_2(FlightManager &fm)
{
    cout << "\nWhich Airport?\n" << endl;
    string choice = "";
    cin >> choice;
    int sum = 0;
    set<string> diferent_airlines;
    list<Flight> flights = fm.get_flights().nodes[choice].adj;
    for (Flight p : flights)
    {
        diferent_airlines.insert(p.get_airline().get_code());
    }
    cout << BOLDWHITE << endl << diferent_airlines.size() << " Airlines operate on this Airport\n" << RESET << endl;
}

void IO::get_airport_info_3(FlightManager &fm)
{
    cout << "\nWhich Airport?\n" << endl;
    string choice = "";
    cin >> choice;
    int sum = 0;
    set<string> different_airports;
    list<Flight> flights = fm.get_flights().nodes[choice].adj;
    for (Flight p : flights)
    {
        different_airports.insert(p.get_target().get_code());
    }
    cout << BOLDWHITE << endl << "You can fly to " << different_airports.size() << " different Airports from this Airport\n" << RESET << endl;
}

void IO::get_airport_info_4(FlightManager &fm)
{
    cout << "\nWhich Airport?\n" << endl;
    string choice = "";
    cin >> choice;
    int sum = 0;
    set<string> different_airports;
    list<Flight> flights = fm.get_flights().nodes[choice].adj;
    for (Flight p : flights)
    {
        different_airports.insert(p.get_target().get_country());
    }
    cout << BOLDWHITE << endl << "You can fly to " << different_airports.size() << " different Countries from this Airport\n" << RESET << endl;
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
        cout << BOLDWHITE << endl << "You can fly to " << fm.get_flights().DFL(choice, max+1).size() << " different Airports within " << max << " flights from this Airport\n" << RESET << endl;
    }
}