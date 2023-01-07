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
    nodes[src.get_code()].adj.push_back(Flight(src, dest, line, weight));
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
 
vector<string> Graph::BFS(string a, string b)
{
    unordered_map<string, pair<int, vector<string>>> ans;
    ans[a] = {0, {}};

    for (auto &[key, value] : nodes) value.visited = false; // c++17 flex

    queue<string> q;
    q.push(a);
    nodes[a].visited = true;

    if (a == b)
    {
        return {};
    }
    while (!q.empty())
    {
        for (auto e : nodes[q.front()].adj)
        {
            string w = e.get_target().get_code();
            if (!nodes[w].visited || ans[q.front()].first + e.get_weight() < ans[w].first)
            {
                ans[w] = {ans[q.front()].first + e.get_weight(), ans[q.front()].second};
                ans[w].second.push_back(e.get_target().get_code());
                q.push(w);
                nodes[w].visited = true;
            }
        }
        q.pop();
    }

    return ans[b].second;
}


void Graph::DFL_aux(string s, int d, set<string> &c)
{
    if (d == 0) return;
    nodes[s].visited = true;
    for (auto e : nodes[s].adj)
    {
        string u = e.get_target().get_code();
        if (!nodes[u].visited)
        {
            c.insert(u);
            DFL_aux(u, d-1, c);
        }
    }
}

set<string> Graph::DFL(string s, int d)
{
    for (auto &[key, value] : nodes) value.visited = false;

    set<string> c;
    DFL_aux(s, d, c);

    return c;
}