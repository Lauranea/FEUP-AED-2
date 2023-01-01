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

using namespace std;

class Graph 
{
  private:
    int size;

    unordered_map<string, list<Flight>> nodes;

  
  public:
    Graph();
    Graph(int v_);
    void addEdge(Airport src, Airport dest, Airline line); 
    vector<string> BFS(string s, string f);
    // static int hash(string code);
    // static string unhash(int code);
};

#endif