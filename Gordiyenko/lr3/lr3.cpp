#include <iostream>
#include <map>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;

using Graph = map<char, map<char, int>>; // Хранение графа

bool BFS(Graph &graph, char start, char end, map<char, char>& path) { // Функция поиска в ширину
    cout << "##########################################################" << endl;
    cout << "Wide search started" << endl;
    map<char,bool> findVertex; // Посещенные вершины
    queue<char> queueVertex; // Очередь вершин
    queueVertex.push(start);
    bool canReachAnother; // Флаг на то, имеет ли вершина непосещенных соседей
    findVertex[start] = true;
    while (!queueVertex.empty()) // Пока очередь не пустая
    {
        char vertex = queueVertex.front();
        queueVertex.pop();
        cout << "Current vertex " << vertex << " has paths to: " << endl;
        canReachAnother = false;
        for (auto const neighbour : graph[vertex]){                      //Просматриваются соседи и кладутся в очередь
            if (neighbour.second > 0 && !(findVertex[neighbour.first])) {
                queueVertex.push(neighbour.first);
                findVertex[neighbour.first] = true;
                path[neighbour.first] = vertex;
                cout << "\t->" << neighbour.first << " with possible flow =  " << neighbour.second << endl;
                canReachAnother = true;
                if (neighbour.first == end) {
                    queueVertex = *(new queue<char>());
                    break;
                }
            }
        }
        if (!canReachAnother){
            cout << "\t>>haven't visited neighbour";
        }
        cout << endl;
    }
    return findVertex[end]; // Была ли достигнута финишная вершина графа
}

void printCurrentFlows(Graph& flowGraph, int pathFlow, int maxCurrentFlow, string& pathStr){  //Функция печати текущего состояния графа, найденного нового пути и найденного нового потока
    cout << "\nNew flow path found = " << pathFlow << ": " + pathStr << endl;
    cout << "Flow graph: " << endl;
    for (auto const& vertex: flowGraph) {
        for (auto const neighbour: flowGraph[vertex.first]) {
            cout << "\t" << vertex.first << " " << neighbour.first << " " << neighbour.second << endl;
        }
    }
    cout << "Current flow - " << maxCurrentFlow << endl;
}

void printResult(Graph& graph, Graph& flowGraph, int maxFlow){           //Функция печати результата
    cout << "##########################################################" << endl;
    cout << "\nResult of algorithm: " <<endl;
    int flow;
    cout << "Maximal flow = "<< maxFlow << endl;                              //Печать максимального потока
    for (auto const& vertex: graph)
        for (auto const neighbour: graph[vertex.first]) {
            if (neighbour.second - flowGraph[vertex.first][neighbour.first] < 0)
                flow = 0;
            else
                flow = neighbour.second - flowGraph[vertex.first][neighbour.first];
            cout << vertex.first << " " << neighbour.first << " " << flow << endl;   // Печать потока через ребро
        }
}

void FFA(Graph &graph, char start, char finish) { // Функция, реализующая алгоритм Форда-Фалкерсона
    Graph flowGraph = graph; // Граф с потоками
    char fromVertex, toVertex;
    map<char,char> path; // Пары, составляющие путь
    string pathStr;

    int maxFlow = 0;
    while (BFS(flowGraph, start, finish, path)) // Пока возможен поиск в ширину
    {
        int pathFlow = INT_MAX;
        pathStr = finish;
        for (toVertex = finish; toVertex != start; toVertex = path[toVertex])           //Восстанавливается путь от финиша к началу
        {
            fromVertex = path[toVertex];
            pathFlow = std::min(pathFlow, flowGraph[fromVertex][toVertex]);           //Находится поток пути
        }
        for (toVertex = finish; toVertex != start; toVertex = path[toVertex])           //Восстанавливается путь от финиша к началу
        {
            fromVertex = path[toVertex];
            flowGraph[fromVertex][toVertex] -= pathFlow;                               //Изменяется граф с потоком
            flowGraph[toVertex][fromVertex] += pathFlow;
            pathStr = string(1, fromVertex) + " --> " + pathStr;
        }

        maxFlow += pathFlow;                                                   //Изменяется число максимального потока
        printCurrentFlows(flowGraph, pathFlow, maxFlow, pathStr);
    }

    printResult(graph, flowGraph, maxFlow);
}

int main() {
    Graph graph;
    char start, finish, vertexFrom, vertexTo;
    int pathLength, countVertex;
    cout << "Your input" << endl;
    cin >> countVertex;
    cin >> start;
    cin >> finish;

    for (int i=0; i < countVertex; i++) {                                         //Считывание вершин графа
        cin >> vertexFrom;
        cin >> vertexTo;
        cin >> pathLength;
        graph[vertexFrom][vertexTo] = pathLength;
    }
    FFA(graph, start, finish); // Запуск алгоритма Форда-Фалкерсона

    return 0;
}