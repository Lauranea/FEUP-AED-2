/**
 * @file Read.cpp
 * Funções para ler ficheiros
 */

#include "Read.h"

unordered_map<string, Airline> Read::read_airlines()
{
    unordered_map<string, Airline> v;
    ifstream fi;
    fi.open("../dados/airlines.csv");
    if (!fi.is_open())
    {
        return v;
    }

    string buffer;
    getline(fi, buffer, '\n');
    while (getline(fi, buffer, '\n'))
    {
        stringstream line(buffer);
        string code, name, callsign, country;
        getline(line, code, ',');
        getline(line, name, ',');
        getline(line, callsign, ',');
        getline(line, country, '\n');
        v[code] = Airline(code, name, callsign, country);
    }

    fi.close();
    return v;
}


unordered_map<string, Airport> Read::read_airports()
{
    unordered_map<string, Airport> v;
    ifstream fi;
    fi.open("../dados/airports.csv");
    if (!fi.is_open())
    {
        return v;
    }

    string buffer;
    getline(fi, buffer, '\n');
    while (getline(fi, buffer, '\n'))
    {
        stringstream line(buffer);
        string code, name, city, country, latitude_string, longitude_string;
        float latitude, longitude;
        getline(line, code, ',');
        getline(line, name, ',');
        getline(line, city, ',');
        getline(line, country, ',');
        getline(line, latitude_string, ',');
        getline(line, longitude_string, '\n');
        latitude = stof(latitude_string);
        longitude = stof(longitude_string);
        v[code] = Airport(code, name, city, country, latitude, longitude);
    }

    fi.close();
    return v;
}

Graph Read::read_flights(unordered_map<string, Airport> airports, unordered_map<string, Airline> airlines)
{
    Graph v;
    ifstream fi;
    fi.open("../dados/flights.csv");
    if (!fi.is_open())
    {
        return v;
    }

    string buffer;
    getline(fi, buffer, '\n');
    while (getline(fi, buffer, '\n'))
    {
        stringstream line(buffer);
        string src, dest, aline;
        getline(line, src, ',');
        getline(line, dest, ',');
        getline(line, aline, '\n');
        Airport a1 = airports[src];
        Airport a2 = airports[dest];
        v.addEdge(a1, a2, airlines[aline], Graph::get_distance(a1.get_latitude(), a1.get_longitude(), a2.get_latitude(), a2.get_longitude()));
    }

    fi.close();
    return v;
}
