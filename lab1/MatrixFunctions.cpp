#include <iostream>
#include "MatrixFunctions.h"

namespace MatrixFunctions {
	Matrix input() {
		Matrix matrix;

        try {
            // вводим количество строк
            std::cout << "Enter number of lines: --> ";
            int m = getNum<int>(0);

            // выделяем память под массив структур - строк матрицы
            matrix.lines.resize(m);

            for (int i = 0; i < m; i++) {
                // запоминаем ссылку на обрабатываемую строку
                Line &line = matrix.lines[i];

                // для каждой строки матрицы вводим количество столбцов
                // в симметричной матрице количество столбцов равно индексу строки + 1
                int n = i + 1;

                // выделение необходимой памяти под элемент строки
                line.elements.resize(m);

                // ввод элементов строки матрицы
                std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
                for (int j = 0; j < n; j++) {
                    line.elements[j] = getNum<int>(0);
                }
            }
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < i; j++) {
                    matrix.lines[j].elements[i] = matrix.lines[i].elements[j];
                }
            }

        } catch (...) // в случае любого исключения
        {
            // очищаем уже выделенную память
            matrix.lines.clear();
            throw; // перекидываем то же исключение дальше
        }
        return matrix;
    }

	void output(const char *msg, const Matrix &matrix) {
	    std::cout << msg << ":\n";
	    for (size_t i = 0; i < matrix.lines.size(); ++i) {
	        const Line &line = matrix.lines[i];
	        for (size_t j = 0; j < line.elements.size(); ++j) {
	            int elem = line.elements[j];
	            std::cout << elem << " ";
	        }
	        std::cout << std::endl;
	    }
	}

    void outputVectors(const Matrix &matrix) {
        std::cout << "Vectors of each line:\n";
        for (size_t i = 0; i < matrix.lines.size(); ++i) {
            std::cout << "Line " << i + 1 << ": ";
            std::copy(matrix.lines[i].elements.begin(), matrix.lines[i].elements.end(),
                      std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
    }

    Matrix removeNonRepeatedElements(Matrix &matrix) {
	    Matrix newMatrix;

	    for (size_t i = 0; i < matrix.lines.size(); ++i) {
	        const Line &line = matrix.lines[i];
	        Line newLine;

	        std::vector<int> elementCount;

	        for (size_t j = 0; j < line.elements.size(); ++j) {
	            int element = line.elements[j];

	            if (elementCount.size() <= static_cast<size_t>(element)) {
	                elementCount.resize(element + 1, 0);
	            }

	            ++elementCount[element];
	        }

	        for (size_t j = 0; j < line.elements.size(); ++j) {
	            int element = line.elements[j];

	            if (elementCount[element] >= 2) {
	            	if (element != 0) {
	            		newLine.elements.push_back(element);
	            	}
	            }
	        }

	        if (!newLine.elements.empty()) {
	            newMatrix.lines.push_back(newLine);
	        }
	    }

	    return newMatrix;
	}

}