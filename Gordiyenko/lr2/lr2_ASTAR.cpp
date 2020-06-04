#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cfloat>
#include <algorithm>

using namespace std;


struct Edge { // ребро графа
    char from; // начальная вершина
    char to; // конечная вершина
    double weight; // вес ребра
};

struct Step { // возможные пути 
    string path; // путь
    double len; // длина пути
    char end; // конец пути
};

class A_star_graph
{
private:
    vector <Edge> edges;//список смежности
    vector <Step> result;//преоброзовываемый (открытый) список путей
    vector <char> cur;//закрытый список вершин, содержит текущий путь
    char begin;
    char end;

public:
    A_star_graph(){
    };
    
    void input_graph()
    {
        cin >> begin >> end;
        char temp;
        while(cin >> temp)
        {
            Edge element;
            element.from = temp;
            cin >> element.to;
            cin >> element.weight;
            edges.push_back(element);
        }
        string buf = "";
        buf += begin;
        for(auto & i : edges)
        {
            if(i.from == begin)
            {
                buf += i.to;
                result.push_back({buf, i.weight});
                result.back().end = end;
                buf.resize(1);//запись всех ребер, которые исходят из начальной позиции
            }
        }
        cur.push_back(begin);
    }

    size_t min_elem() //возвращает индекс минимального элемента из непросмотренных
    {
        double min;
        min = DBL_MAX;
        size_t temp = -1;
        for(size_t i(0); i < result.size(); i++)
        {
            if(result.at(i).len + abs(end - result.at(i).path.back()) < min)
            {
                if(is_visible(result.at(i).path.back()))
                {
                    result.erase(result.begin() + i);
                }
                else
                {
                    min = result.at(i).len + abs(end - result.at(i).path.back());
                    temp = i;
                }
            }
        }
        return temp;
    }

    bool is_visible(char value)//проверка доступа к вершине
    {
        for(char i : cur) {
            if (i == value) {
                return true;
            }
        }
        return false;
    }

    void Search()
    {
        sort(result.begin(), result.end(), [](const Step & a, const Step & b) -> bool
        {
            return a.len + a.end - a.path.back() > b.len + b.end - b.path.back();
        });
        while(true)
        {
            size_t min = min_elem();
            if(min == -1){
                cout << "Wrong edges";
                break;
            }
            if(result.at(min).path.back() == end)
            {
                cout << result.at(min).path;
                return;
            }
            for(auto & i : edges)
            {
                if(i.from == result.at(min).path.back())
                {
                    string buf = result.at(min).path;
                    buf += i.to;
                    //cout << buf << endl;
                    result.push_back({buf, i.weight + result.at(min).len});
                }
            }
            cur.push_back(result.at(min).path.back());
            result.erase(result.begin() + min);
        }
    }
};

int main() {
    A_star_graph element;
    element.input_graph();
    element.Search();
    return 0;
}
