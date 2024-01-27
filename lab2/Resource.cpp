#include <iostream>
#include "Resource.h"

// Функция для получения строки из входного потока
string getString(istream& in) {
    string s;
    in >> s;
    if (in.fail()) {
        in.clear();
        in.ignore(10000, '\n');
        throw invalid_argument("Неверный формат ввода!");
    }
    return s;
}