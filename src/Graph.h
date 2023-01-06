/**
 * @file Graph.h
 * Funções para ler ficheiros
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_


#include <iostream>
#include <list>
#include <math.h>
#include <vector>
#include <unordered_map>
#include "Flight.h"
#include "Airport.h"
#include "Airline.h"
#include <set>
#include <climits>
#include <queue>

using namespace std;

class Graph 
{
  private:
    struct Node
    {
      list<Flight> adj;
      bool visited;
    };
  
  public:
    Graph();
    Graph(int v_);
    void addEdge(Airport src, Airport dest, Airline line, float weight); 
    vector<string> BFS(string s, string f, unordered_map<string, Airport> airports); // Breadth First Search
    set<string> BFL(string s, int d); // Breadth First Listing
    unordered_map<string, Node> nodes;
    static float get_distance(float lat1, float lon1, float lat2, float lon2);
    // static int hash(string code);
    // static string unhash(int code);
};

#endif