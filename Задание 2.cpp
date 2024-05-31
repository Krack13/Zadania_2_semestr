#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;
class Graph {
private:
    int numVertical;
    list<int>* Listed;
    bool* visited;

public:
    Graph(int V);
    void addEdge(int src, int dest);
    void BFS(int startV);
    vector<int> sPath(int startV, int endV);
    vector<int> sCycle();
    vector<vector<int>> compon();
};
Graph::Graph(int vert) {numVertical = vert;Listed = new list<int>[vert];visited = new bool[vert];for (int i = 0; i < vert; ++i) {visited[i] = false;}}

void Graph::addEdge(int src, int dest) {Listed[src].push_back(dest);}

void Graph::BFS(int startV) {
    queue<int> bfsQueue;
    visited[startV] = true;
    bfsQueue.push(startV);
    while (!bfsQueue.empty()) {
        int cVer = bfsQueue.front();
        cout << cVer << " ";
        bfsQueue.pop();
        for (auto i = Listed[cVer].begin(); i != Listed[cVer].end(); ++i) {
            if (!visited[*i]) {visited[*i] = true;bfsQueue.push(*i);}
        }
    }
}

vector<int> Graph::sPath(int startV, int endV) {
    vector<int> dist(numVertical, numeric_limits<int>::max());
    vector<int> parent(numVertical, -1);
    queue<int> bfsQueue;
    dist[startV] = 0;
    bfsQueue.push(startV);
    while (!bfsQueue.empty()) {
        int cVer = bfsQueue.front();
        bfsQueue.pop();
        for (auto i = Listed[cVer].begin(); i != Listed[cVer].end(); ++i) {
            if (dist[*i] == numeric_limits<int>::max()) {dist[*i] = dist[cVer] + 1;parent[*i] = cVer;bfsQueue.push(*i);}
        }
    }
    vector<int> path;
    int curr = endV;
    while (curr != -1) {path.push_back(curr);curr = parent[curr];}
    reverse(path.begin(), path.end());
    return path;
}

vector<int> Graph::sCycle() {
    int Cyclen = numeric_limits<int>::max();
    vector<int> sCycle;
    for (int i = 0; i < numVertical; ++i) {
        fill(visited, visited + numVertical, false);
        queue<pair<int, int>> bfsQueue;
        bfsQueue.push({ i, i });
        visited[i] = true;
        while (!bfsQueue.empty()) {
            int cVer = bfsQueue.front().first;
            int startV = bfsQueue.front().second;
            bfsQueue.pop();
            for (auto neighbor : Listed[cVer]) {
                if (!visited[neighbor]) {visited[neighbor] = true;bfsQueue.push({ neighbor, startV });}
                else if (neighbor == startV) {
                    vector<int> cycle;
                    cycle.push_back(cVer);
                    cycle.push_back(neighbor);
                    if (cycle.size() < Cyclen) {Cyclen = cycle.size();sCycle = cycle;}
                    break;
                }
            }
        }
    }

    return sCycle;
}

vector<vector<int>> Graph::compon() {
    vector<vector<int>> components;
    fill(visited, visited + numVertical, false);
    for (int i = 0; i < numVertical; ++i) {
        if (!visited[i]) {
            vector<int> component;
            queue<int> bfsQueue;
            visited[i] = true;
            bfsQueue.push(i);
            while (!bfsQueue.empty()) {
                int cVer = bfsQueue.front();
                component.push_back(cVer);
                bfsQueue.pop();
                for (auto neighbor : Listed[cVer]) {
                    if (!visited[neighbor]) {visited[neighbor] = true;bfsQueue.push(neighbor);}
                }
            }
            components.push_back(component);
        }
    }
    return components;
}

int main() {
    int numVertical, numJoint;
    cout << "Введите количество вершин в графе: ";
    cin >> numVertical;
    cout << "Введите количество рёбер в графе: ";
    cin >> numJoint;
    Graph graph(numVertical);


    int src, dest;

    cout << "Введите рёбра:" << endl;
    for (int i = 0; i < numJoint; ++i) {cin >> src >> dest;graph.addEdge(src, dest);}
    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Выполнить обход в ширину\n";
        cout << "2. Выполнить поиск кратчайшего пути\n";
        cout << "3. Выполнить поиск кратчайшего цикла\n";
        cout << "4. Выполнить поиск компонент связности\n";
        cout << "5. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;


        switch (choice) {
        case 1: {
            int startVertical;
            cout << "Введите начальную вершину для обхода в ширину: ";
            cin >> startVertical;
            cout << "Результат обхода в ширину: ";
            graph.BFS(startVertical);
            break;
        }
        case 2: {
            int startVertical, endVertical;
            cout << "Введите начальную и конечную вершины для поиска кратчайшего пути: ";
            cin >> startVertical >> endVertical;
            vector<int> path = graph.sPath(startVertical, endVertical);
            cout << "Кратчайший путь: ";
            for (int vertex : path) {
                cout << vertex << " ";
            }
            cout << endl;
            break;
        }
        case 3: {
            vector<int> cycle = graph.sCycle();
            cout << "Кратчайший цикл: ";
            for (int vertex : cycle) {
                cout << vertex << " ";
            }
            cout << endl;
            break;
        }
        case 4: {
            vector<vector<int>> components = graph.compon();
            cout << "Компоненты связности:\n";
            for (const auto& component : components) {
                for (int vertex : component) {
                    cout << vertex << " ";
                }
                cout << endl;
            }
            break;
        }
        case 5:
            cout << "Конец\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте ещё раз.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}
