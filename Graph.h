#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Graph {
    vector<vector<int>> adjMatrix;
};

vector<int> dijkstra(const Graph& graph, int start, int ziel, vector<int>& dist, vector<int>& prev) {
    int n = graph.adjMatrix.size();
    dist.assign(n, INF);
    prev.assign(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0;
    for (int i = 0; i < n; ++i) {
        // Finde den unbesuchten Knoten mit der kleinsten Distanz
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        }
        if (dist[u] == INF) break; // Alle erreichbaren Knoten besucht
        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            int weight = graph.adjMatrix[u][v];
            if (weight > 0 && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
        }
    }

    // Pfad rekonstruieren
    vector<int> path;
    for (int at = ziel; at != -1; at = prev[at])
        path.push_back(at);
    reverse(path.begin(), path.end());
    if (path[0] != start) path.clear(); // Kein Pfad gefunden
    return path;
}

int main() {
    // Beispielgraph (Adjazenzmatrix)
    Graph graph;
    graph.adjMatrix = {
        {0, 2, 0, 1, 0},
        {2, 0, 3, 2, 0},
        {0, 3, 0, 0, 1},
        {1, 2, 0, 0, 3},
        {0, 0, 1, 3, 0}
    };

    int start = 0; // Startknoten
    int ziel = 4;  // Zielknoten
    vector<int> dist, prev;
    vector<int> path = dijkstra(graph, start, ziel, dist, prev);

    if (!path.empty()) {
        cout << "Kürzester Weg: ";
        for (int node : path) cout << node << " ";
        cout << "\nDistanz: " << dist[ziel] << endl;
    } else {
        cout << "Kein Weg gefunden." << endl;
    }

    return 0;
}
