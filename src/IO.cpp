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
            "3 - Get info about a certain country.\n"
            "4 - Get info about a certain airline.\n"
            "5 - Get info about every flight.\n"
            "\n"
            "6 - Exit the program.\n" << endl;
    
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
            IO::get_country_info(fm);
            break;
        case 4:
            IO::get_airline_info(fm);
            break;
        case 5:
            IO::get_info(fm);
            break;
        case 6:
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
            "5 - How many different places can you fly to from a certain Airport in X flights max?\n" << endl;
    
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

void IO::get_country_info(FlightManager &fm)
{
    cout << "---\n\n"
            "1 - How many flights start on a certain Country?\n"
            "2 - How many Airlines operate on a certain Country?\n"
            "3 - How many different Airports can you fly to from a certain Country?\n"
            "4 - How many different Countries can you fly to from a certain Country?\n"
            "5 - How many different places can you fly to from a certain Country in X flights max?\n" << endl;
    
    int choice = 0;
    choice = cin_int();

    switch (choice)
    {
        case 1:
            get_country_info_1(fm);
            break;
        case 2:
            get_country_info_2(fm);
            break;
        case 3:
            get_country_info_3(fm);
            break;
        case 4:
            get_country_info_4(fm);
            break;
        case 5:
            get_country_info_5(fm);
            break;
        default:
            cout << RED << "\nInvalid choice\n" << RESET << endl;
            return;
    }
}

void IO::get_country_info_1(FlightManager &fm)
{
    cout << "\nWhich Country?\n" << endl;
    string choice = "";
    cin >> choice;
    bool found = false;
    int sum = 0;
    for(auto i : fm.get_flights().nodes)
    {
        if(fm.get_airports()[i.first].get_country() == choice)
        {
            sum += i.second.adj.size();
            found = true;
        }
    }
    if(found)
    {
        cout << BOLDWHITE << endl << sum << " flights start on this Country\n" << RESET << endl;
        return;
    }
    cout << RED << endl << choice << " is not an available country.\n" << RESET << endl;
}

void IO::get_country_info_2(FlightManager &fm)
{
    cout << "\nWhich Country?\n" << endl;
    string choice = "";
    cin >> choice;
    int sum = 0;
    bool found = false;
    set<string> diferent_airlines;
    for(auto i : fm.get_flights().nodes)
    {
        if(fm.get_airports()[i.first].get_country() == choice)
        {
            diferent_airlines.insert(i.first);
            found = true;
        }
    }
    if(found)
    {
        cout << BOLDWHITE << endl << diferent_airlines.size() << " Airlines operate on this Country\n" << RESET << endl;
        return;
    }
    cout << RED << endl << choice << " is not an available country.\n" << RESET << endl;
}

void IO::get_country_info_3(FlightManager &fm)
{
    cout << "\nWhich Country?\n" << endl;
    string choice = "";
    cin >> choice;
    int sum = 0;
    set<string> different_airports;
    list<Flight> flights;
    set<string> airports;
    bool found = false;
    unordered_map<string, Airport> airports2 = fm.get_airports();
    for(auto i : airports2)
    {
        if(i.second.get_country() == choice)
        {
            found = true;
            airports.insert(i.second.get_code());
        }
    }
    for(auto i : airports)
    {
        flights = fm.get_flights().nodes[i].adj;
        for (Flight p : flights)
        {
            different_airports.insert(p.get_target().get_code());
        }
    }
    if(found)
    {
        cout << BOLDWHITE << endl << "You can fly to " << different_airports.size() << " different Airports from this Country\n" << RESET << endl;
        return;
    }
    cout << RED << endl << choice << " is not an available country.\n" << RESET << endl;
}

void IO::get_country_info_4(FlightManager &fm)
{
    cout << "\nWhich Country?\n" << endl;
    string choice = "";
    cin >> choice;
    int sum = 0;
    set<string> different_airports;
    list<Flight> flights;
    set<string> airports;
    bool found = false;
    unordered_map<string, Airport> airports2 = fm.get_airports();
    set<string> country;
    for(auto i : airports2)
    {
        if(i.second.get_country() == choice)
        {
            found = true;
            airports.insert(i.second.get_code());
        }
    }
    for(auto i : airports)
    {
        flights = fm.get_flights().nodes[i].adj;
        for (Flight p : flights)
        {
            different_airports.insert(p.get_target().get_code());
        }
    }
    for(auto i : different_airports)
    {
        country.insert(airports2[i].get_country());
    }
    if(found)
    {
        cout << BOLDWHITE << endl << "You can fly to " << country.size() << " different Countries from this Country\n" << RESET << endl;
        return;
    }
    cout << RED << endl << choice << " is not an available country.\n" << RESET << endl;
}

void IO::get_country_info_5(FlightManager &fm)
{
    cout << "\nWhich Country?\n" << endl;
    string choice1 = "";
    int choice;
    cin >> choice1;
    cout << "\nMax Flights?\n" << endl;
    int max = 0;
    int sum = 0;
    choice = cin_int();
    unordered_map<string, Airport> airports2 = fm.get_airports();
    set<string> airports;
    set<string> airportstot;
    set<string> b;
    bool found = false;
    max = choice;
    for(auto i : airports2)
    {
        if(i.second.get_country() == choice1)
        {
            found = true;
            airports.insert(i.second.get_code());
        }
    }
    if(!found)
    {
        cout << RED << endl << choice << " is not an available country.\n" << RESET << endl;
        return;
    }
    if (max > 0)
    {
        for(auto i : airports)
        {
            b = fm.get_flights().DFL(i, max+1);
            airportstot.insert(b.begin(), b.end());
        }
    }
    cout << BOLDWHITE << endl << "You can fly to " << airportstot.size() << " different Airports within " << max << " flights from this Country\n" << RESET << endl;
}



void IO::get_info(FlightManager &fm)
{
    cout << "---\n\n"
            "1 - How many flights are there?\n"
            "2 - How many Airlines are there?\n"
            "3 - How many Airports are there?\n" << endl;
    
    int choice = 0;
    choice = cin_int();

    switch (choice)
    {
        case 1:
            get_info_1(fm);
            break;
        case 2:
            get_info_2(fm);
            break;
        case 3:
            get_info_3(fm);
            break;
        default:
            cout << RED << "\nInvalid choice\n" << RESET << endl;
            return;
    }

    return;
}

void IO::get_info_1(FlightManager &fm)
{
    int sum = fm.get_flights().get_number_of_flights();
    cout << BOLDWHITE << endl << "There are " << sum << " flights\n" << RESET << endl;
}

void IO::get_info_2(FlightManager &fm)
{
    int sum = fm.get_airlines().size();
    cout << BOLDWHITE << endl << "There are " << sum << " Airlines\n" << RESET << endl;
}

void IO::get_info_3(FlightManager &fm)
{
    int sum = fm.get_airports().size();
    cout << BOLDWHITE << endl << "There are " << sum << " Airports\n" << RESET << endl;
}

void IO::get_airline_info(FlightManager &fm)
{
    cout << "---\n\n"
            "1 - How many flights does a certain Airline do?\n"
            "2 - How many different Airports can you fly to with a certain Airline?\n"
            "3 - How many different Countries can you fly to with a certain Airline?\n";
    
    int choice = 0;
    choice = cin_int();

    switch (choice)
    {
        case 1:
            get_airline_info_1(fm);
            break;
        case 2:
            get_airline_info_2(fm);
            break;
        case 3:
            get_airline_info_3(fm);
            break;
        default:
            cout << RED << "\nInvalid choice\n" << RESET << endl;
            break;
            return;
    }
}

void IO::get_airline_info_1(FlightManager &fm)
{
    cout << "\nWhich Airline?\n" << endl;
    string choice = "";
    cin >> choice;
    int sum = 0;
    bool found = false;
    for (auto &[key, value] : fm.get_flights().nodes)
    {
        for(auto d : value.adj)
        {
            if(d.get_airline().get_name() == choice || d.get_airline().get_code() == choice)
            {
                sum++;
                found = true;
            }
        }
    }
    if(!found)
    {
        cout << RED << endl << choice << " is not a valid airline.\n" << RESET << endl;
        return;
    }
    cout << BOLDWHITE << endl << choice << " does a total of " << sum << " flights" << RESET << endl;
}

void IO::get_airline_info_2(FlightManager &fm)
{
    cout << "\nWhich Airline?\n" << endl;
    string choice = "";
    cin >> choice;
    bool found = false;
    set<string> airports;
    for (auto &[key, value] : fm.get_flights().nodes)
    {
        for(auto d : value.adj)
        {
            if(d.get_airline().get_name() == choice || d.get_airline().get_code() == choice)
            {
                airports.insert(d.get_target().get_code());
                found = true;
            }
        }
    }
    if(!found)
    {
        cout << RED << endl << choice << " is not a valid airline.\n" << RESET << endl;
        return;
    }
    cout << BOLDWHITE << endl << choice << " goes to a total of " << airports.size() << " airports." << RESET << endl;
    return;
}

void IO::get_airline_info_3(FlightManager &fm)
{
    cout << "\nWhich Airline?\n" << endl;
    string choice = "";
    cin >> choice;
    bool found = false;
    set<string> countries;
    for (auto &[key, value] : fm.get_flights().nodes)
    {
        for(auto d : value.adj)
        {
            if(d.get_airline().get_name() == choice || d.get_airline().get_code() == choice)
            {
                countries.insert(d.get_target().get_country());
                found = true;
            }
        }
    }
    if(!found)
    {
        cout << RED << endl << choice << " is not a valid airline.\n" << RESET << endl;
        return;
    }
    cout << BOLDWHITE << endl << choice << " goes to a total of " << countries.size() << " countries." << RESET << endl;
    return;
}