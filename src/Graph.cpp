/**
 * @file Graph.cpp
 * COMPLETAR!!!!
 */

#include "Graph.h"
#include "Flight.h"

template <>
Graph<Flight>::Graph()
{
    size = 0;
    adj.resize(size);
}

template <class T>
Graph<T>::Graph(int v_)
{
    size = v_;
    adj.resize(size);
}
 
template <class T>
void Graph<T>::addEdge(T src, T dest)
{
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
}
 
template <class T>
void Graph<T>::BFS(int s)
{
    vector<bool> visited;
    visited.resize(v, false);
 
    list<int> queue;
 
    visited[s] = true;
    queue.push_back(s);
 
    while (!queue.empty()) {
        s = queue.front();
        cout << s << " ";
        queue.pop_front();
 
        for (auto adjecent : adj[s]) {
            if (!visited[adjecent]) {
                visited[adjecent] = true;
                queue.push_back(adjecent);
            }
        }
    }
}