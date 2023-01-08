/**
 * @file Graph.h
 * Funções relacionadas com o grafo
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_


#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include "Flight.h"
#include "Airport.h"
#include "Airline.h"
#include <set>
#include <climits>
#include <queue>
#include <math.h>

using namespace std;

class Graph 
{
  private:
    struct Node
    {
      list<Flight> adj;
      bool visited;
    };
    void DFL_aux(string s, int d, set<string> &c);
    unordered_map<string, Airport> airports;
    unordered_map<string, Airline> airlines;

    int number_of_flights = 0;
    
  
  public:
    Graph();
    Graph(unordered_map<string, Airport> airports_, unordered_map<string, Airline> airlines_);
    void addEdge(Airport src, Airport dest, Airline line, float weight); 
    pair<int, vector<string>> BFS(string a, string b, bool use_weight = false, vector<string> lines = {}, int b_type = 0, float b_lat = 0, float b_lon = 0, float max_distance = 0); // Breadth First Search
    set<string> DFL(string s, int d); // Depth First Listing
    unordered_map<string, Node> nodes;
    static float get_distance(float lat1, float lon1, float lat2, float lon2);
    int get_number_of_flights() {return number_of_flights;};
    void plus_one_flight() {number_of_flights++;};
    // static int hash(string code);
    // static string unhash(int code);
};

#endif