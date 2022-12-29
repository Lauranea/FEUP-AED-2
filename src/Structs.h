/**
 * @file structs.h
 * defines the structs used
 */

#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct airlines
{
    //Code,Name,Callsign,Country
    string AirlineCode;
    string AirlineName;
    string AirlineCallsign;
    string AirlineCountry;
};

struct airports
{
    //Code,Name,City,Country,Latitude,Longitude
    string AirportCode;
    string AirportName;
    string AirportCity;
    string AirportCountry;
    string AirportLatitude;
    string AirportLongitude;
};

struct flights
{
    //Source,Target,Airline
    string FlightSource;
    string FlightTarget;
    string FlightAirline;
};
