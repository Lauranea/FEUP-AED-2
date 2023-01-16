/**
 * @file Graph.cpp
 * Funções relacionadas com o grafo
 */

#include "Graph.h"

/**
 * @brief Contrutor do Grafo
 * Complexidade 1
 * @param airports_ unordered_map com informação dos airports
 * @param airlines_ unordered_map com informação das lines
 */
Graph::Graph(unordered_map<string, Airport> airports_, unordered_map<string, Airline> airlines_)
{
    airports = airports_;
    airlines = airlines_;
}

/**
 * @brief Construtor de new Graph:: Graph object
 * 
 */
Graph::Graph()
{
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
 
 /**
  * @brief adiciona uma edge ao grafo 
  * Complexidade: 1
  * 
  * @param src airoporto de onde o voo parte
  * @param dest airoporto destino do voo
  * @param line airline do voo
  * @param weight distancia dos aeroportos
  */
void Graph::addEdge(Airport src, Airport dest, Airline line, float weight)
{
    nodes[src.get_code()].adj.push_back(Flight(src, dest, line, weight));
}

/**
 * @brief devolve a distancia entre 2 aeroportos
 * Complexidade 1
 * @param lat1 latitude do aeroporto 1
 * @param lon1 longitude do aeroporto 1
 * @param lat2 latitude do aeroporto 2
 * @param lon2 longitude do aeroporto 2
 * @return float distancia entre os dois aeroportos
 */
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
 
pair<int, vector<string>> Graph::BFS(string a, string b, bool use_weight, vector<string> lines, int b_type, float b_lat, float b_lon, float max_distance) // b_type = (0 Airport) / (1 City) / 2 (Coords)
{
    unordered_map<string, pair<int, vector<string>>> ans;
    ans[a] = {0, {a}};

    for (auto &[key, value] : nodes) value.visited = false; // c++17 flex

    queue<string> q;
    q.push(a);
    nodes[a].visited = true;

    if ((b_type == 0 && a == b) || (b_type == 1 && airports[a].get_city() == b) || (b_type == 2 && Graph::get_distance(airports[a].get_latitude(), airports[a].get_longitude(), b_lat, b_lon) <= max_distance))
    {
        return {};
    }
    while (!q.empty())
    {
        for (auto e : nodes[q.front()].adj)
        {
            string w = e.get_target().get_code();
            float weight = use_weight ? e.get_weight() : 1;
            auto lambda = [](string current_line, vector<string> list_of_lines) { for (int i = 0; i < list_of_lines.size(); i++) { if (current_line == list_of_lines[i]) return true; } return false; };
            if ((!nodes[w].visited || ans[q.front()].first + weight < ans[w].first) && (lines.size() == 0 || lambda(e.get_airline().get_code(), lines)))
            {
                ans[w] = {ans[q.front()].first + weight, ans[q.front()].second};
                ans[w].second.push_back(e.get_target().get_code());
                q.push(w);
                nodes[w].visited = true;
            }
        }
        q.pop();
    }
    
    if (b_type == 0)
    {
        return ans[b];
    }
    else if (b_type == 1)
    {
        string fastest;
        for (auto &[key, value] : airports)
        {
            if (value.get_city() == b && (fastest == "" || ans[value.get_code()] < ans[fastest]))
            {
                fastest = value.get_code();
            }
        }
        return ans[fastest];
    }
    else
    {
        string fastest;
        for (auto &[key, value] : airports)
        {
            if ((fastest == "" || ans[value.get_code()] < ans[fastest]) && Graph::get_distance(value.get_latitude(), value.get_longitude(), b_lat, b_lon) <= max_distance)
            {
                fastest = value.get_code();
            }
        }
        return ans[fastest];
    }
}

/**
 * @brief dfs que adiciona ao set os aeorportos em que e possivel voar de s para em d voos
 * Compelxidade |V+d|
 * @param s aeroporto inicial
 * @param d depth no momento
 * @param c todos os aeroportos em d voos
 */
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

/**
 * @brief devolve todos os aeroportos a uma distancia de d voos do aeroporto original
 * Complexidade:|V|
 * @param s aeroporto inicial
 * @param d quantidade de voos
 * @return set<string> set com os aeroportos a que da para chegar a partir de s com d voos
 */
set<string> Graph::DFL(string s, int d)
{
    for (auto &[key, value] : nodes) value.visited = false;

    set<string> c;
    DFL_aux(s, d, c);

    return c;
}