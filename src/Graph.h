/**
 * @file Graph.h
 * Funções para ler ficheiros
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_


#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <typename T>
class Graph 
{
  private:
    int size;
    list<T> adj;
  
  public:
    Graph();
    Graph(int v_);
    void addEdge(T src, T dest); 

};

#endif