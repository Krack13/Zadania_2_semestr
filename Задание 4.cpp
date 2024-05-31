#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

class Graph {
public:
    int V; 
    vector<vector<int>> intervalMatrix;
    vector<vector<int>> timeMatrix;
    vector<vector<int>> priceMatrix;

public:
    Graph(int V) : V(V),
        intervalMatrix(V, vector<int>(V, INT_MAX)),
        timeMatrix(V, vector<int>(V, INT_MAX)),
        priceMatrix(V, vector<int>(V, INT_MAX)) {}

    void addEdge(int u, int v, int dist, int time, int cost) {intervalMatrix[u][v] = dist;timeMatrix[u][v] = time;priceMatrix[u][v] = cost;}
    //алгоритм Дейкстра
    vector<int> dijkstra(const vector<vector<int>>& matrix, int src) {
        vector<int> dist(V, INT_MAX);
        vector<bool> sptSet(V, false);
        dist[src] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = minDistance(dist, sptSet);
            sptSet[u] = true;

            for (int v = 0; v < V; v++) {
                if (!sptSet[v] && matrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + matrix[u][v] < dist[v]) {dist[v] = dist[u] + matrix[u][v];}
            }
        }
        return dist;
    }
    // алгоритм Прима
    vector<pair<int, int>> primMST(const vector<vector<int>>& matrix) {
        vector<int> key(V, INT_MAX);
        vector<bool> inMST(V, false);
        vector<int> parent(V, -1);
        key[0] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = minKey(key, inMST);
            inMST[u] = true;

            for (int v = 0; v < V; v++) {
                if (matrix[u][v] && matrix[u][v] < key[v] && !inMST[v]) {parent[v] = u;key[v] = matrix[u][v];}
            }
        }

        vector<pair<int, int>> mstEdges;
        for (int i = 1; i < V; i++) {mstEdges.push_back({ parent[i], i });}
        return mstEdges;
    }

private:
    int minDistance(const vector<int>& dist, const vector<bool>& sptSet) {
        int min = INT_MAX, minIndex;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] <= min) {min = dist[v];minIndex = v;}
        }
        return minIndex;
    }

    int minKey(const vector<int>& key, const vector<bool>& inMST) {
        int min = INT_MAX, minIndex;

        for (int v = 0; v < V; v++) {
            if (!inMST[v] && key[v] < min) {min = key[v];minIndex = v;}
        }
        return minIndex;
    }
};

class AirTravel {
private:
    Graph graph;

public:
    AirTravel(int V) : graph(V) {}

    void addF(int u, int v, int distance, int time, int cost) {graph.addEdge(u, v, distance, time, cost);}

    vector<int> bestTime(int src, int dest) {return graph.dijkstra(graph.timeMatrix, src);}

    vector<int> bestPrice(int src, int dest) {return graph.dijkstra(graph.priceMatrix, src);}

    vector<pair<int, int>> bestDistance() {return graph.primMST(graph.intervalMatrix);}

    vector<pair<int, int>> bestTime() {return graph.primMST(graph.timeMatrix);}

    vector<pair<int, int>> bestPrice() {return graph.primMST(graph.priceMatrix);}
};

int main() {
    setlocale(0, "rus");
    AirTravel travel(5);
    //добавляем рейсы
    travel.addF(0, 1, 100, 1, 50);
    travel.addF(0, 2, 300, 4, 150);
    travel.addF(1, 2, 200, 2, 100);
    travel.addF(1, 3, 400, 3, 200);
    travel.addF(2, 3, 100, 1, 50);
    travel.addF(3, 4, 500, 5, 300);

    int src = 0, dist = 4;

    vector<int> shortestTime = travel.bestTime(src, dist);
    vector<int> cheapestCost = travel.bestPrice(src, dist);

    vector<pair<int, int>> mstByDistance = travel.bestDistance();
    vector<pair<int, int>> mstByTime = travel.bestTime();
    vector<pair<int, int>> mstByCost = travel.bestDistance();

    cout << "Самое быстрое время: "   << shortestTime[dist] << endl;
    cout << "Самая дешевая стоимость:  " << cheapestCost[dist] << endl;

    cout << "Минимальный маршрут по расстоянию:" << endl;
    for (const auto& edge : mstByDistance) {cout << edge.first << " - " << edge.second << endl;}

    cout << "Минимальный маршрут по времени:" << endl;
    for (const auto& edge : mstByTime) {cout << edge.first << " - " << edge.second << endl;}

    cout << "Минимальный маршрут по стоимости:" << endl;
    for (const auto& edge : mstByCost) {cout << edge.first << " - " << edge.second << endl;}

    return 0;
}
