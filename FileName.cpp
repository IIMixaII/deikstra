#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Graph {
    int V;
    vector<vector<pair<int, int>>> adj;
    vector<int> parent; // Добавлен вектор для хранения предков

    Graph(int V) : V(V), adj(V), parent(V, -1) {} 

    void addEdge(int u, int v, int w) {
        adj[u].push_back({ v, w });
    }

    void deikstra(int src) {
        vector<int> dist(V, numeric_limits<int>::max());
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, src });

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto& i : adj[u]) {
                int v = i.first;
                int weight = i.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({ dist[v], v });
                    parent[v] = u;
                    cout << "Обновление расстояния для вершины " << v << ": " << dist[v] << endl;
                }
            }
        }

        cout << "Кратчайшие расстояния от вершины " << src << " до всех остальных вершин:" << endl;
        for (int i = 0; i < V; i++)
            cout << src << " -> " << i << " = " << dist[i] << endl;

        cout << "Предки для каждой вершины:" << endl;
        for (int i = 0; i < V; i++)
            cout << "Предок вершины " << i << ": " << parent[i] << endl;
    }
};

int main() {
    int V = 5;
    Graph g(V);
    setlocale(LC_ALL, "rus");
    // Добавление ребер в граф
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 7);
    g.addEdge(0, 4, 6);
    g.addEdge(0, 3, 4);
    g.addEdge(1, 3, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(3, 1, 2);
    g.addEdge(3, 4, 1);

    g.deikstra(0);

    return 0;
}
