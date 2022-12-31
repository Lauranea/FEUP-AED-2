/**
 * @file Graph.cpp
 * COMPLETAR!!!!
 */

#include "Graph.h"

Graph::Graph()
{
    size = 0;
}

Graph::Graph(int v_)
{
    size = v_;
}
 
void Graph::addEdge(Airport src, Airport dest, Airline line)
{
    if (src.get_index() >= nodes.size())
    {
        nodes.push_back({{Flight(src, dest, line)}});
    }
    else
    {
        nodes[src.get_index()].close.push_back(Flight(src, dest, line));
    }
}
 
void Graph::BFS(int s)
{
    vector<bool> visited;
    visited.resize(nodes.size(), false);
 
    list<int> l;
 
    visited[s] = true;
    l.push_back(s);
 
    while (!l.empty())
    {
        s = l.front();
        cout << s << " ";
        l.pop_front();
 
        for (auto e : nodes[s].close)
        {
            int w = e.get_target().get_index();
            if (!visited[w])
            {
                visited[w] = true;
                l.push_back(w);
            }
        }
    }
}