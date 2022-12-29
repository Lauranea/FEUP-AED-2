/**
 * @file Read.cpp
 * Funções para ler ficheiros
 */

#include "Read.h"

#define RESET "\033[0m"

vector<airlines> Read::read_airlines()
{
    vector<airlines> v;
    ifstream fi;
    fi.open("../airlines.csv");
    if (!fi.is_open())
    {
        return v;
    }

    string buffer;
    getline(fi, buffer, '\n');
    while (getline(fi, buffer, '\n'))
    {
        stringstream line(buffer);
        string buf;
        airlines p;
        getline(line, buf, ',');
        p.AirlineCode = buf;
        getline(line, buf, ',');
        p.AirlineName = buf;
        getline(line, buf, ',');
        p.AirlineCallsign = buf;
        getline(line, buf, '\r');
        p.AirlineCountry = buf;
        v.push_back(p);
    }

    fi.close();
    return v;
}


vector<airports> Read::read_airports()
{
    vector<airports> v;
    ifstream fi;
    fi.open("../airports.csv");
    if (!fi.is_open())
    {
        return v;
    }

    string buffer;
    getline(fi, buffer, '\n');
    while (getline(fi, buffer, '\n'))
    {
        stringstream line(buffer);
        string buf;
        airports p;
        getline(line, buf, ',');
        p.AirportCode = buf;
        getline(line, buf, ',');
        p.AirportName = buf;
        getline(line, buf, ',');
        p.AirportCity = buf;
        getline(line, buf, ',');
        p.AirportCountry = buf;
          getline(line, buf, ',');
        p.AirportLatitude = buf;
        getline(line, buf, '\r');
        p.AirportLongitude = buf;
        v.push_back(p);
    }

    fi.close();
    return v;
}

vector<flights> Read::read_flights()
{
    vector<flights> v;
    ifstream fi;
    fi.open("../flights.csv");
    if (!fi.is_open())
    {
        return v;
    }

    string buffer;
    getline(fi, buffer, '\n');
    while (getline(fi, buffer, '\n'))
    {
        stringstream line(buffer);
        string buf;
        flights p;
        getline(line, buf, ',');
        p.FlightSource = buf;
        getline(line, buf, ',');
        p.FlightTarget = buf;
        getline(line, buf, '\r');
        p.FlightAirline = buf;
        v.push_back(p);
    }

    fi.close();
    return v;
}
