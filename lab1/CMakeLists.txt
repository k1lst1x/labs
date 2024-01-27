# установка версии CMake
cmake_minimum_required(VERSION 3.16)

# название проекта (обязательно)
project(lab1)

# установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 20)

# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# создание библиотеки MatrixFunctions
add_library(matrixFunctions MatrixFunctions.h MatrixFunctions.cpp)

# подключение библиотеки MatrixFunctions ко всем таргетам, создаваемым далее
# альтернатива: target_link_libraries(main matrixFunctions)
link_libraries(matrixFunctions)

# создание исполняемого файла
add_executable(main lab1.cpp)

# для сборки из консоли:
#
# mkdir build   # создание директории для файлов сборки
# cd build      # переход в директорию сборки
# cmake ..      # генерация файлов сборки на основе CMakeLists.txt
# make          # сборка проекта