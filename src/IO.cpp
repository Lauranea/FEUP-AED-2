/**
 * @file IO.cpp
 * COMPLETAR!!!!
 */

#include "IO.h"

int IO::cin_int()
{
    int choice = 0;
    cin >> choice;
    if (cin.fail())
    {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}

float IO::cin_float()
{
    float choice = 0;
    cin >> choice;
    if (cin.fail())
    {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}

bool IO::what_to_do(FlightManager &fm)
{
    cout << "\n"
            "1 - Find the optimal flights.\n"
            "2 - Get info about a certain airport.\n"
            "\n"
            "3 - Exit the program.\n" << endl;
    
    int choice = 0;
    choice = cin_int();

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
    vector<string> optimal;

    pair<string, pair<float, pair<float, float>>> start = get_point(fm, "starting");
    if (start.first == "EXIT") return;
    
    pair<string, pair<float, pair<float, float>>> end = get_point(fm, "ending");
    if (end.first == "EXIT") return;

    vector<string> lines = which_airlines_to_use(fm);
    if (lines.size() == 1 && lines[0] == "EXIT") return;

    cout << "\n---\n\n1 - Min number of flights\n"
                     "2 - Min distance\n" << endl;
    
    int min_what = 0;
    min_what = cin_int();

    min_what--;

    if (0 != min_what && 1 != min_what)
    {
        return;
    }

    if (start.first != "" && end.first != "")
    {
        if (start.second.second.first == 0)
        {
            optimal = fm.get_flights().BFS(start.first, end.first, min_what, lines, end.second.second.first).second;
        }
        else
        {
            vector<string> current_optimal;
            int current_optimal_weight = INT_MAX;
            for (auto &[key, value] : fm.get_airports())
            {
                if (value.get_city() == start.first)
                {
                    pair<int, vector<string>> opt = fm.get_flights().BFS(start.first, end.first, min_what, lines, end.second.second.first);
                    if (opt.first < current_optimal_weight)
                    {
                        current_optimal = opt.second;
                    }
                }
            }
            optimal = current_optimal;
        }
    }
    else if (start.first != "" && end.first == "" && end.second.second.second != 0)
    {
        optimal = fm.get_flights().BFS(start.first, end.first, min_what, lines, 2, end.second.second.first, end.second.second.second, start.second.first).second;
    }
    else if (start.first == "" && end.first != "" && start.second.second.first != 0)
    {
        vector<string> current_optimal;
        int current_optimal_weight = INT_MAX;
        for (auto &[key, value] : fm.get_airports())
        {
            if (Graph::get_distance(value.get_latitude(), value.get_longitude(), start.second.second.first, start.second.second.second) <= start.second.first)
            {
                pair<int, vector<string>> opt = fm.get_flights().BFS(key, end.first, min_what, lines, end.second.second.first);
                if (opt.first < current_optimal_weight)
                {
                    current_optimal = opt.second;
                }
            }
        }
        optimal = current_optimal;
    }
    else if (start.first == "" && end.first == "" && end.second.second.first != 0 && start.second.second.first != 0)
    {
        vector<string> current_optimal;
        int current_optimal_weight = INT_MAX;
        for (auto &[key, value] : fm.get_airports())
        {
            if (Graph::get_distance(value.get_latitude(), value.get_longitude(), start.second.second.first, start.second.second.second) <= start.second.first)
            {
                pair<int, vector<string>> opt = fm.get_flights().BFS(key, end.first, min_what, lines, 2, end.second.second.first, end.second.second.second, end.second.first);
                if (opt.first < current_optimal_weight)
                {
                    current_optimal = opt.second;
                }
            }
        }
        optimal = current_optimal;
    }

    cout << BOLDWHITE << endl;
    for (int i = 0; i < optimal.size(); i++)
    {
        if (i == optimal.size()-1)
        {
            cout << optimal[i];
        }
        else
        {
            cout << optimal[i] << " -> ";
        }
    }
    cout << RESET << endl << endl;
}

pair<string, pair<float, pair<float, float>>>  IO::get_point(FlightManager &fm, string point_name)
{
    cout << "---\n\nThe " << point_name << " point is ...\n\n"
            "1 - A certain Airport.\n"
            "2 - A certain City.\n"
            "3 - An Airport close to these coordinates\n" << endl;
    
    int point_type = 0;
    point_type = cin_int();

    string point = "";
    float point_lat = 0; // Also stores if the point is an airport or a city
    float point_lon = 0;
    float max_distance = 0;

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
            point_lat = cin_float();
            cout << "Longitude: ";
            point_lon = cin_float();
            cout << "Max Distance: ";
            max_distance = cin_float();
            break;
        default:
            cout << RED << "\nInvalid choice\n" << RESET << endl;
            point = "EXIT";
            break;
    }

    return {point, {max_distance, {point_lat, point_lon}}};
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
    choice = cin_int();

    switch (choice)
    {
        case 1:
            break;
        case 2:
            cout << "---\n\nWhich Airlines?  (Separate multiple Airlines with a ;)\n" << endl;
            lines = which_airlines_to_use_aux();
            break;
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
    choice = cin_int();

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
    choice = cin_int();
    if (max > 0)
    {
        cout << BOLDWHITE << endl << "You can fly to " << fm.get_flights().DFL(choice, max+1).size() << " different Airports within " << max << " flights from this Airport\n" << RESET << endl;
    }
}