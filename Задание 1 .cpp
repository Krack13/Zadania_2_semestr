#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// Определение структуры для представления вершины графа
struct Vertex {
    int value; // Значение вершины
    bool visited; // Флаг посещения вершины
};
const int SIZE = 4; // Размерность графа
class Graph {
private:
    vector<Vertex> vertices; // Вектор вершин графа
    int n; // Количество вершин
    int matrix[SIZE][SIZE]; // Матрица смежности
public:

    Graph( int size) : n(size), vertices(size) {
    
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = 0;
            }
        }
    }

    void addEdge(int from, int to) {
        vertices[from].visited = false;
        vertices[to].visited = true;
        queue<int> q;
        q.push(from);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int i = 0; i < n; ++i) {
                if (matrix[current][i] && !vertices[i].visited) {
                    vertices[i].visited = true;
                    q.push(i);
                }
            }
        
        }
    }
    void bfs(int start) {
        vertices[start].visited = true;
        queue<int> q;
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int i = 0; i < n; ++i) {
                if (matrix[current][i] && !vertices[i].visited) {
                    vertices[i].visited = true;
                    q.push(i);
                }
            }

        }
    }
    bool speedroadto(int start, int end) {
        return vertices[end].visited;
    }



};



int main()
{
    setlocale(LC_ALL, "rus");
    const int SIZE = 4;
    int matrix[SIZE][SIZE];
    int constanta;
    int constanta2;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> matrix[i][j];
        }
    }
    Graph graph(SIZE);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    // Проверка наличия кратчайшего пути между двумя вершинами
    constanta = graph.speedroadto(0, 1);
    if (constanta == -1) {
        cout << " Пути между вершинами не сущесствует" << endl;
    }
    else {
        cout << "Кратчайший путь между вершинами существует" << endl;

    }
    return 0;
}

