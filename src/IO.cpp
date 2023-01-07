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
    pair<string, pair<float, float>> start = get_point(fm, "starting");
    if (start.first == "EXIT") return;
    
    pair<string, pair<float, float>> end = get_point(fm, "ending");
    if (end.first == "EXIT") return;

    vector<string> lines = which_airlines_to_use(fm);
}

pair<string, pair<float, float>> IO::get_point(FlightManager &fm, string point_name)
{
    cout << "---\n\nThe " << point_name << " point is ...\n\n"
            "1 - A certain Airport.\n"
            "2 - A certain City.\n"
            "3 - An Airport close to these coordinates\n" << endl;
    
    int point_type = 0;
    cin >> point_type;

    string point = "";
    float point_lat = 0; // Also stores if the point is an airport or a city
    float point_lon = 0;

    switch (point_type)
    {
        case 1:
            cout << "\nWhich Airport?\n" << endl;
            cin >> point;
            point_lat = 0;
            break;
        case 2:
            cout << "\nWhich City?\n" << endl;
            cin >> point;
            point_lat = 1;
            break;
        case 3:
            cout << "\nWhich Coordinates?\n" << endl;
            cout << "Latitude: ";
            cin >> point_lat;
            cout << "Longitude: ";
            cin >> point_lon;
            break;
        default:
            cout << RED << "\nInvalid choice\n" << RESET << endl;
            point = "EXIT";
            break;
    }

    return {point, {point_lat, point_lon}};
}

vector<string> which_airlines_to_use_aux()
{
    vector<string> lines;
    string li;
    cin >> li;
    stringstream st(li);
    string wo;
    while (getline(st, wo, ';'))
    {
        lines.push_back(wo);
    }
    cout << lines.size() << endl;

    return lines;
}

vector<string> IO::which_airlines_to_use(FlightManager &fm)
{
    vector<string> lines;

    cout << "---\n\nUse these airlines:\n\n"
            "1 - All\n"
            "2 - Certain Airline(s)\n" << endl;
    
    int choice = 0;
    cin >> choice;

    switch (choice)
    {
        case 1:
            break;
        case 2:
            cout << "---\n\nWhich Airlines?  (Separate multiple Airlines with a ;)\n" << endl;
            lines = which_airlines_to_use_aux();
        default:
            cout << RED << "\nInvalid choice\n" << RESET << endl;
            lines.push_back("EXIT");
            break;
    }

    return lines;
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