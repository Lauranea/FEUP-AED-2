/**
 * @file Read.cpp
 * Funções para ler ficheiros
 */

#include "Read.h"


/**
 * @brief abre o ficheiro(verificando se existe) que contem a informação das airlines, e guarda a informação num  
 * unordered_map 
 * Complexidade: n 
 * @return unordered_map<string, Airline> (string é o codigo da airline, airline contem todas as informaçoes desse aeroporto)
 */
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

/**
 * @brief abre o ficheiro(verificando se existe) que contem a informação dos airport, e guarda a informação num  
 * unordered_map 
 * Complexidade: n 
 * @return unordered_map<string, Airline> (string é o codigo do aeroporto, airport contem todas as informaçoes desse aeroporto)
 */
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

/**
 * @brief cria um grafo com cada edge a conter o aeroporto inicial, o aeroporto destino, a airline e o peso(distancia)
 * Complexidade: n
 * @param airports unordered_map com informaçao dos aeroportos
 * @param airlines unordered_map com informação das airlines
 * @return Graph grafo com ligações de aeroportos através de airlines
 */

Graph Read::read_flights(unordered_map<string, Airport> airports, unordered_map<string, Airline> airlines)
{
    Graph v(airports, airlines);
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
        v.plus_one_flight();
        stringstream line(buffer);
        string src, dest, aline;
        getline(line, src, ',');
        getline(line, dest, ',');
        getline(line, aline, '\r');
        Airport a1 = airports[src];
        Airport a2 = airports[dest];
        float d = Graph::get_distance(a1.get_latitude(), a1.get_longitude(), a2.get_latitude(), a2.get_longitude());
        v.addEdge(a1, a2, airlines[aline], d);
    }

    fi.close();
    return v;
}
