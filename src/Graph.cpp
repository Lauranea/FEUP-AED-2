/**
 * @file Graph.cpp
 * COMPLETAR!!!!
 */

#include "Graph.h"

Graph::Graph()
{
    nodes.resize(18278);
}

int Graph::hash(string code)
{
    return (int(code[0])-64)*676 + (int(code[1])-64)*26 + (int(code[2])-64);
}

string Graph::unhash(int code)
{
    string converted = "";
    while (code > 0)
    {
        int remainder = code % 26;
        converted = char(remainder - 1 + 'A') + converted;
        code = (code - remainder) / 26;
    }

    return converted;
}
 
void Graph::addEdge(Airport src, Airport dest, Airline line)
{
    nodes[hash(src.get_code())].close.push_back(Flight(src, dest, line));
}
 
vector<string> Graph::BFS(int s, int f)
{
    vector<bool> visited;
    visited.resize(nodes.size(), false);
 
    list<pair<int, vector<string>>> l;
 
    visited[s] = true;
    l.push_back({s, {unhash(s)}});
 
    while (!l.empty())
    {
        s = l.front().first;
 
        for (auto e : nodes[s].close)
        {
            int w = hash(e.get_target().get_code());
            if (w == f)
            {
                l.front().second.push_back(e.get_target().get_code());
                return l.front().second;
            }
            if (!visited[w])
            {
                visited[w] = true;
                vector<string> path = l.front().second;
                path.push_back(e.get_target().get_code());
                l.push_back({w, {path}});
            }
        }

        l.pop_front();
    }
}