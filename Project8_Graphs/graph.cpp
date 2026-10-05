#include "graph.h"
#include <queue>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <iomanip>

Graph& Graph::add_vertex(const string label) {
    if (adj.find(label) == adj.end()) {
        adj[label] = map<string, double>();
    }
    return *this;
}

Graph& Graph::add_edge(const string src, const string dest, double w) {
    if (adj.find(src) == adj.end()) {
        throw invalid_argument("Source vertex not found");
    }

    if (adj.find(dest) == adj.end()) {
        throw invalid_argument("Destination vertex not found");
    }

    if (w < 0) {
        throw invalid_argument("Weight cannot be negative");
    }
    adj[src][dest] = w;
    return *this;
}

double Graph::get_weight(const string src, const string dest) const {
    auto it = adj.find(src);
    if (it == adj.end()) throw invalid_argument("Source vertex not found");

    auto dt = adj.find(dest);
    if (dt == adj.end()) throw invalid_argument("Destination vertex not found");

    const auto& neighbors = it->second;

    auto edge = neighbors.find(dest);
    if (edge == neighbors.end()) {
        return numeric_limits<double>::infinity();
    }

return edge->second;
}

void Graph::dfs_recursive(const string& vertex, vector<string>& visited, unordered_map<string, bool>& visited_map) const {
    visited.push_back(vertex);
    visited_map[vertex] = true;

    for (const auto& neighbor : adj.at(vertex)) {
        if (!visited_map[neighbor.first]) {
            dfs_recursive(neighbor.first, visited, visited_map);
        }
    }
}

vector<string> Graph::dfs(const string starting_vertex) const {
    if (adj.find(starting_vertex) == adj.end()) {
        throw invalid_argument("Starting vertex not found");
    }

    vector<string> visited;
    unordered_map<string, bool> visited_map;
    dfs_recursive(starting_vertex, visited, visited_map);

    return visited;

}


vector<string> Graph::bfs(const string starting_vertex) const {
    if (adj.find(starting_vertex) == adj.end()) {
        throw invalid_argument("Starting vertex not found");
    }

    queue<string> frontier;
    vector<string> visited;
    unordered_map<string, bool> visited_map;

    frontier.push(starting_vertex);
    visited_map[starting_vertex] = true;

    while (!frontier.empty()) {
        string vertex = frontier.front();
        frontier.pop();
        visited.push_back(vertex);

        for (const auto& neighbor : adj.at(vertex)) {
            const string& neighbor_vertex = neighbor.first;
            if (!visited_map[neighbor_vertex]) {
                visited_map[neighbor_vertex] = true;
                frontier.push(neighbor_vertex);
            }
        }
    }
    return visited;

}

vector<string> Graph::dsp(const string& startV,
                           const string& destV,
                           double& cost) const {

    if (adj.find(startV) == adj.end() || adj.find(destV) == adj.end()) {
        throw invalid_argument("Source or destination not found");
    }

    const double INF = numeric_limits<double>::infinity();

    // STEP 1: initialization (like your pseudocode loop)
    unordered_map<string, double> distance;
    unordered_map<string, string> pred;

    for (const auto& vertex : adj) {
        distance[vertex.first] = INF;
        pred[vertex.first] = "";
    }

    // startV has distance 0
    distance[startV] = 0;

    // STEP 2: unvisitedQueue replacement (min-priority queue)
    using P = pair<double, string>; // (distance, vertex)
    priority_queue<P, vector<P>, greater<P>> unvisitedQueue;

    unvisitedQueue.push({0, startV});

    // STEP 3: main loop
    while (!unvisitedQueue.empty()) {

        // DequeueMin unvisitedQueue
        auto [currentDist, currentV] = unvisitedQueue.top();
        unvisitedQueue.pop();

        // skip stale entries (important fix)
        if (currentDist > distance[currentV]) {
            continue;
        }

        // STEP 4: relax neighbors
        for (const auto& adjV : adj.at(currentV)) {

            const string& neighbor = adjV.first;
            double edgeWeight = adjV.second;

            double alternativePathDistance =
                distance[currentV] + edgeWeight;

            if (alternativePathDistance < distance[neighbor]) {
                distance[neighbor] = alternativePathDistance;
                pred[neighbor] = currentV;

                unvisitedQueue.push({alternativePathDistance, neighbor});
            }
        }
    }

    // STEP 5: no path case
    if (distance[destV] == INF) {
        cost = INF;
        return {};
    }

    // STEP 6: reconstruct path using predV
    vector<string> path;

    for (string at = destV; at != ""; at = pred[at]) {
        path.push_back(at);
    }

    reverse(path.begin(), path.end());

    cost = distance[destV];
    return path;
}

unordered_map<string, vector<string>> Graph::dsp_all(const string& src) const {

    if (adj.find(src) == adj.end()) {
        throw invalid_argument("Source not found");
    }

    const double INF = numeric_limits<double>::infinity();

    unordered_map<string, double> dist;
    unordered_map<string, string> prev;

    // initialize
    for (const auto& node : adj) {
        dist[node.first] = INF;
        prev[node.first] = "";
    }

    dist[src] = 0;

    using P = pair<double, string>;
    priority_queue<P, vector<P>, greater<P>> pq;

    pq.push({0, src});

    // ---- Dijkstra (single run) ----
    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        if (currentDist > dist[u]) continue;

        for (const auto& edge : adj.at(u)) {
            const string& v = edge.first;
            double weight = edge.second;

            double alt = dist[u] + weight;

            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push({alt, v});
            }
        }
    }

    // ---- build all paths ----
    unordered_map<string, vector<string>> all_paths;

    for (const auto& node : adj) {
        const string& dest = node.first;

        vector<string> path;

        if (dist[dest] == INF) {
            all_paths[dest] = {};  // unreachable
            continue;
        }

        for (string at = dest; at != ""; at = prev[at]) {
            path.push_back(at);
        }

        reverse(path.begin(), path.end());
        all_paths[dest] = path;
    }

    return all_paths;
}

string Graph::str() const {
    string result = "digraph G {\n";

    map<string, map<string, double>> sorted(adj.begin(), adj.end());

    for (const auto& node : sorted) {
        const string& src = node.first;

        for (const auto& edge : node.second) {
            const string& dest = edge.first;
            double weight = edge.second;

            ostringstream ss;
            ss << fixed << setprecision(1) << weight;
            string w = ss.str();

            result += "  " + src + " -> " + dest +
                      " [label=\"" + w +
                      "\",weight=\"" + w + "\"];\n";
        }
    }

    result += "}";
    return result;
}

ostream& operator<<(ostream& os, const Graph& g) {
    os << g.str();
    return os;
}