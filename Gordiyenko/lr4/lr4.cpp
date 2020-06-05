#include <iostream>
#include <vector>
#include <string>
#define DBG

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<int> prefixFunction(string P) // функция считает префикс функцию от всех префиксов строки и записывет значение для всех префиксов в массив p
{
    vector<int> p;
    p.resize(P.size() + 1);
    p[0] = 0;
    for (size_t i = 1; i < P.size() + 1; i++)
    {
        int k = p[i - 1];               // получение значение максималной прификс-функции, от строки s[0 ... i - 1]

        while (k > 0 && P[i] != P[k])   // перебираем все строки, которые являются прификсами и суфиксами
        {                               // строки s[0 ... i - 1] и пытаемся расширить их символом s[i]
            k = p[k - 1];
        }
        if (P[i] == P[k])               // если символ s[i] совпал c s[k] значит префикс удалось расширить
            k++;
        p[i] = k;                       // запоминаем длину прифекс-функции для строки s[0 ... i]
    }
    return p;
}

int checkCicle(const string& P, const string& T){
    vector<int> p;
    p = prefixFunction(T); // для всех префиксов строки T

#ifdef DBG
    cout << "Prefix function of " << T << " : ";
    for (size_t i = 1;i < p.size(); i++)
        cout << p[i] << ' ';
    cout << endl;
#endif

    int k = 0;

    for (size_t i = 0; i < P.size(); i++){ // алгоритм считает значение префикс функции для всех префиксов строки T + P + P,
        while (k > 0 && T[k] != P[i]) // чтобы не использовать дополнительной памяти и не сохранять нигде строку P + P алгоритм два раза проходит по
            k = p[k - 1]; // строке P. Вычисление префикс функции начинается с начала строки А так как для строки T все уже вычислено
        if (T[k] == P[i]) // если значение прификс функции для строки P + P стало равно длине строки T значит, алгоритм нашел значением циклического сдвига
            k++;


        if (k == T.size())
            return (static_cast<int>(i) - static_cast<int>(T.size()) + 1);
    }

    for (size_t i = P.size(); i < P.size() + P.size(); i++){
        while (k > 0 && T[k] != P[i - P.size()])
            k = p[k - 1];
        if (T[k] == P[i - P.size()])
            k++;
        if (k == T.size())
            return (static_cast<int>(i) - static_cast<int>(T.size()) + 1);
    }
    return -1;
}

vector<int> KMP(const string& P, const string& T){ // функция ищет все вхождение строки P в строку T и возвращает массив индексов этих вхождений
    vector<int> ans;
    vector<int> p;


    p = prefixFunction(P);              // для всех префиксов строки P

#ifdef DBG
    cout << "Prefix function of " << P << " : ";
    for (size_t i = 0;i < p.size(); i++)
        cout << p[i] << ' ';
    cout << endl;
#endif

    int k = 0;
    for(size_t i = 0; i < T.size(); i++){  // считаем значение префикс-функции для всех префиксов строки P + T
        while (k > 0 && P[k] != T[i])
            k = p[k - 1];
        if (P[k] == T[i])
            k++;

#ifdef DBG
        cout << "Prefix function of \""
            << P.substr(0, k)
            << '|' + P.substr(k, P.size()-k) <<
            "\" and \"" + T.substr(0, i-k+1) + '|'
            << T.substr(i-k+1, k)
            << "\" = " << k << endl;
#endif

        if (k == P.size())                // если длинна прификс-функции совпало с длинной строки P значит в строке Т была найдена строка Р
            ans.push_back(i - P.size() + 1);

    }
    return ans;
}

int main(){
    string P;
    string T;
    
    cin >> P >> T;
    std::vector<int> a = KMP(P, T);

    if (a.empty()){
        std::cout << -1;
    }else {
        for(size_t i = 0; i < a.size(); i++) {
            std::cout << a[i];
            if (i + 1 != a.size()) std::cout << ',';
        }
    }
    std::cout << std::endl;
    return 0;
}