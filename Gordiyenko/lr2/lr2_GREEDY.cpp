#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Edge
{
    char from;
    char to;
    double weight;
};


class Greedy_graph
{
private:
    vector <Edge> edges;
    vector <char> result;
    vector <char> cur;
    char source;
    char estuary;
public:
    Greedy_graph() {}
    void readGraph(){
        cin >> source >> estuary;
        char tmp;
        while(cin >> tmp)
        {
            Edge Gr;
            Gr.from = tmp;
            if(!(cin >> Gr.to))
                break;
            if(!(cin >> Gr.weight))
                break;
            edges.push_back(Gr);
        }
        sort(edges.begin(), edges.end(), [](Edge first, Edge second)
        {
            return first.weight < second.weight;
        });
    }

    bool is_visible(char value) {
        for(char i : cur)
            if(i == value)
                return true;
        return false;
    }


    void solve() {
        if(source != estuary)
            Search(source);
    }

    bool Search(char value) {
        if(value == estuary) {
            result.push_back(value);
            return true;
        }
        cur.push_back(value);
        for(auto & i : edges) {
            if(value == i.from) {
                if(is_visible(i.to))
                    continue;
                result.push_back(i.from);
                bool flag = Search(i.to);
                if(flag)
                   return true;
                result.pop_back();
            }
        }
        return false;
    }

    void Print() {
        for(char i : result)
            cout << i;
    }
};

int main() {
    Greedy_graph Gr;
    Gr.readGraph();
    Gr.solve();
    Gr.Print();
    return 0;
}
