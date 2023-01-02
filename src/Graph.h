/**
 * @file Graph.h
 * Funções para ler ficheiros
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

using namespace std;

class Graph 
{
  private:
  
  public:
    Graph();
    Graph(int v_);
    void addEdge(Airport src, Airport dest, Airline line, float weight); 
    vector<string> BFS(string s, string f, unordered_map<string, Airport> airports); // Breadth First Search
    set<string> BFL(string s, int d); // Breadth First Listing
    unordered_map<string, list<Flight>> nodes;
    static float get_distance(float lat1, float lon1, float lat2, float lon2);
    // static int hash(string code);
    // static string unhash(int code);
};

#endif