#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <map>

using namespace std;

class Graph {
private:
    unordered_map<string, map<string, double>> adj;

    void dfs_recursive(const string& vertex, vector<string>& visited, unordered_map<string, bool>& visited_map) const;

public:
    Graph& add_vertex(const string label);
    Graph& add_edge(const string src, const string dest, double w);

    double get_weight(const string src, const string dest) const;

    vector<string> dfs(const string starting_vertex) const;
    vector<string> bfs(const string starting_vertex) const;

    vector<string> dsp(const string& startV, const string& destV, double& cost) const;
    unordered_map<string, vector<string>> dsp_all(const string& src) const;

    string str() const;
};

ostream& operator<<(ostream& os, const Graph& g);

#endif