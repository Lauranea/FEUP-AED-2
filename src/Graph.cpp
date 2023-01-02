/**
 * @file Graph.cpp
 * COMPLETAR!!!!
 */

#include "Graph.h"

Graph::Graph()
{
    // nodes.resize(18278);
}

// int Graph::hash(string code)
// {
//     return (int(code[0])-64)*676 + (int(code[1])-64)*26 + (int(code[2])-64);
// }

// string Graph::unhash(int code)
// {
//     string converted = "";
//     while (code > 0)
//     {
//         int remainder = code % 26;
//         converted = char(remainder - 1 + 'A') + converted;
//         code = (code - remainder) / 26;
//     }
//     return converted;
// }
 
void Graph::addEdge(Airport src, Airport dest, Airline line, float weight)
{
    nodes[src.get_code()].push_back(Flight(src, dest, line, weight));
}

float Graph::get_distance(float lat1, float lon1, float lat2, float lon2)
{
    float dLat = (lat2 - lat1) * M_PI / 180.0;
    float dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    float a = pow(sin(dLat / 2), 2) +
              pow(sin(dLon / 2), 2) *
              cos(lat1) * cos(lat2);
    float rad = 6371;
    float c = 2 * asin(sqrt(a));
    return rad * c;
}
 
vector<string> Graph::BFS(string s, string f, unordered_map<string, Airport> airports)
{
    unordered_map<string, bool> visited;
 
    list<pair<string, vector<string>>> l;

    vector<vector<string>> all_cases;
 
    visited[s] = true;
    l.push_back({s, {s}});
 
    while (!l.empty())
    {
        s = l.front().first;
        bool add = true;
        for (auto e : nodes[s])
        {
            if (e.get_target().get_code() == f)
            {
                l.front().second.push_back({e.get_target().get_code()});
                all_cases.push_back(l.front().second);
                add = false;
            }
        }
        if (add)
        {
            for (auto e : nodes[s])
            {
                if (!visited[e.get_target().get_code()])
                {
                    visited[e.get_target().get_code()] = true;
                    vector<string> path = l.front().second;
                    path.push_back(e.get_target().get_code());
                    l.push_back({e.get_target().get_code(), {path}});
                }
            }
        }

        l.pop_front();
    }

    vector<string> best;
    float best_weight = INT_MAX;

    for (int i = 0; i < all_cases.size(); i++)
    {
        float weight = 0;
        for (int j = 0; j < all_cases[i].size() - 1; j++)
        {
            Airport a1 = airports[all_cases[i][j]];
            Airport a2 = airports[all_cases[i][j+1]];
            weight += get_distance(a1.get_latitude(), a1.get_longitude(), a2.get_latitude(), a2.get_longitude());
        }
        if (weight < best_weight)
        {
            best = all_cases[i];
            best_weight = weight;
        }
    }

    return best;
}

set<string> Graph::BFL(string s, int d)
{
    unordered_map<string, bool> visited;

    set<string> airports_visited;
    set<string> airports_visiting = {s};
    set<string> temp;

    visited[s] = true;

    for (int i = 0; i < d; i++)
    {
        for (string s : airports_visiting)
        {
            for (auto e : nodes[s])
            {
                if (!visited[e.get_target().get_code()])
                {
                    temp.insert(e.get_target().get_code());
                    visited[e.get_target().get_code()] = true;
                }
            }
            airports_visited.insert(s);
        }
        for (string s : temp)
        {
            airports_visiting.insert(s);
        }
    }
    return airports_visited;
}