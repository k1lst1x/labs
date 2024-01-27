#ifndef MATRIXFUNCTIONS_H
#define MATRIXFUNCTIONS_H

#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <algorithm>
#include <iterator>
#include <stdexcept>

namespace MatrixFunctions {

	struct Line {
        std::vector<int> elements;
    };

    struct Matrix {
        std::vector<Line> lines;
    };

    template<class T>
    T getNum(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) {
        T a;
        while (true) {
            std::cin >> a;
            if (std::cin.eof()) // обнаружен конец файла
                throw std::runtime_error("Failed to read number: EOF");
            else if (std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            // прочие ошибки (неправильный формат ввода) либо число не входит в заданный диапазон
            else if (std::cin.fail() || a < min || a > max) {
                std::cin.clear(); // очищаем флаги состояния потока
                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            } else // успешный ввод
                return a;
        }
    }
    // прототипы функций
    Matrix input(); // ввод матрицы
    void output(const char *msg, const Matrix &matrix); // вывод матрицы
    void outputVectors(const Matrix &matrix);
    Matrix removeNonRepeatedElements(Matrix &matrix);
}


#endif //MATRIXFUNCTIONS_H