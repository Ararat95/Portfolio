#include <iostream>
#include <queue>
#include <vector>
#include <list>

const int INF = __INT_MAX__;

void dijkstra(int source, std::list<std::pair<int, int>> graph[], int size);

int main() {

    int vertices;
    int edges;
    std::cout << "input vertices and edges of graph";
    std::cin >> vertices >> edges;

    std::list<std::pair<int, int>> graph[vertices];
    int current_vertice;
    int neighbor;
    int weight;
    for (int i = 0; i < edges; ++i) {
        std::cout << "type c, n, w" << std::endl;
        std::cin >> current_vertice >> neighbor >> weight;
        graph[current_vertice].push_back({neighbor, weight});
        graph[neighbor].push_back({current_vertice, weight});
    }
    int ind = 0;
    for (auto& key : graph) {
        for (auto& n : key) {
            std::cout << ind++ << " --> " << n.first << '|' << n.second << '#';
        }
        std::cout << std::endl;
    }
    int source;
    std::cout << "type top vertex: ";
    std::cin >> source;
    dijkstra(source, graph, vertices);

    return 0;
}

void dijkstra(int source, std::list<std::pair<int, int>> graph[], int size) {
    
    std::vector<int> distance(size, INF);
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    distance[source] = 0;
    pq.push({0, source});

    while(!pq.empty()) {
        int current = pq.top().second;
        pq.pop();

        for (auto& key : graph[current]) {
            if (distance[current] + key.second < distance[key.first]) {
                distance[key.first] = distance[current] + key.second;
                pq.push({distance[key.first], key.first});
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        std::cout << "Distance from " << source << " to --> " << i << " --> " << distance[i] << std::endl;
    }
}