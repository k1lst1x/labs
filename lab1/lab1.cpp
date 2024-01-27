#include <iostream>
#include "MatrixFunctions.h"

/*
Для сборки проекта с использованием CMake, выполните следующие команды:
    mkdir build
    cd build
    cmake ..
    make
Для сборки проекта с использованием g++, выполните следующие команды:
    g++ lab1.cpp MatrixFunctions.cpp -o main
*/

using namespace MatrixFunctions;

int main() {
    Matrix matrix;
    Matrix newMatrix;
    try {
        matrix = input();
        output("Entered matrix", matrix);
        //outputVectors(matrix);

        newMatrix = removeNonRepeatedElements(matrix);

        output("New matrix after removing non-repeating elements", newMatrix);
        output("Entered matrix", matrix);

        //outputVectors(newMatrix);
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}