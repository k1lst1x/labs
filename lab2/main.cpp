#include <iostream>
#include "Resource.h"
using namespace std;

// Диалоговая функция для проверки класса
int main() {
    try {
        // Создание двух экземпляров класса Ресурс с разными конструкторами
        Resource r1("Нефть", 100, 150, 50);
        Resource r2("Уголь", 20);
        Resource r3;

        // Переменная для хранения команды пользователя
        int command;

        // Флаг для выхода из цикла
        bool exit = false;

        // Бесконечный цикл
        while (!exit) {
            // Вывод состояния ресурсов на экран
            cout << "Ресурс 1: ";
            //r1.output(cout);
            cout << r1;
            cout << "Ресурс 2: ";
            r2.output(cout);
            if (!r3.isEmpty()) {
                cout << "Ресурс 3: ";
                r3.output(cout);
            }

            // Вывод списка доступных команд
            cout << "Выберите команду:" << endl;
            cout << "1. Изменить значения атрибутов ресурса 1" << endl;
            cout << "2. Изменить значения атрибутов ресурса 2" << endl;
            cout << "3. Создать новый ресурс с вводом значений атрибутов" << endl;
            cout << "4. Объединить два ресурса" << endl;
            cout << "5. Сравнить два ресурса по наименованию" << endl;
            cout << "6. Вычислить прибыльность ресурса за неделю" << endl;
            cout << "7. Увеличить оборот ресурса в заданное число раз" << endl;
            cout << "8. Выйти из программы" << endl;

            // Получение команды от пользователя
            command = getNum<int>(1, 8);

            // Обработка команды
            switch (command) {
                case 1: {
                    // Изменение значений атрибутов ресурса 1
                    cout << "Введите новое наименование ресурса 1: ";
                    string name = getString(cin);
                    r1.setName(name);
                    cout << "Введите новое потребление ресурса 1: ";
                    double consumption = getNum<double>();
                    r1.setConsumption(consumption);
                    cout << "Введите новое производство ресурса 1: ";
                    double production = getNum<double>();
                    r1.setProduction(production);
                    cout << "Введите новую цену ресурса 1: ";
                    double price = getNum<double>();
                    r1.setPrice(price);

                    // Вывод нового состояния ресурса 1 на экран
                    cout << "Ресурс 1 после изменения: ";
                    r1.output(cout);
                    break;
                }
                case 2: {
                    // Изменение значений атрибутов ресурса 2
                    cout << "Введите новое наименование ресурса 2: ";
                    string name = getString(cin);
                    r2.setName(name);
                    cout << "Введите новое потребление ресурса 2: ";
                    double consumption = getNum<double>();
                    r2.setConsumption(consumption);
                    cout << "Введите новое производство ресурса 2: ";
                    double production = getNum<double>();
                    r2.setProduction(production);
                    cout << "Введите новую цену ресурса 2: ";
                    double price = getNum<double>();
                    r2.setPrice(price);

                    // Вывод нового состояния ресурса 2 на экран
                    cout << "Ресурс 2 после изменения: ";
                    r2.output(cout);
                    break;
                }
                case 3: {
                    // Создание нового ресурса с вводом значений атрибутов
                    cout << "Введите наименование, потребление, производство и цену нового ресурса: ";
                    r3.input(cin);

                    // Вывод состояния нового ресурса на экран
                    cout << "Новый ресурс: ";
                    r3.output(cout);
                    break;
                }
                case 4: {
                    // Объединение двух ресурсов
                    cout << "Введите номера двух ресурсов для объединения (1, 2 или 3): ";
                    int n1 = getNum<int>(1, 3);
                    int n2 = getNum<int>(1, 3);
                    if (n1 == n2) {
                        cout << "Нельзя объединять один и тот же ресурс!" << endl;
                        break;
                    }
                    Resource newr1, newr2, r;

                    switch (n1) {
                        case 1: newr1 = r1; break;
                        case 2: newr1 = r2; break;
                        case 3: newr1 = r3; break;
                    }
                    switch (n2) {
                        case 1: newr2 = r1; break;
                        case 2: newr2 = r2; break;
                        case 3: newr2 = r3; break;
                    }

                    r = newr1.operator+(newr2);
                    if (r.isEmpty()) {
                        cout << "Нельзя объединять разные или пустые ресурсы!" << endl;
                        break;
                    }

                    // Вывод состояния объединенного ресурса на экран
                    cout << "Объединенный ресурс: ";
                    r.output(cout);
                    break;
                }
                case 5: {
                    // Сравнение двух ресурсов по наименованию
                    cout << "Введите номера двух ресурсов для сравнения (1, 2 или 3): ";
                    int n1 = getNum<int>(1, 3);
                    int n2 = getNum<int>(1, 3);
                    if (n1 == n2) {
                        cout << "Нельзя сравнивать один и тот же ресурс!" << endl;
                        break;
                    }
                    Resource newr1, newr2;
                    switch (n1) {
                        case 1: newr1 = r1; break;
                        case 2: newr1 = r2; break;
                        case 3: newr1 = r3; break;
                    }
                    switch (n2) {
                        case 1: newr2 = r1; break;
                        case 2: newr2 = r2; break;
                        case 3: newr2 = r3; break;
                    }
                    if (newr1 == newr2) {
                        cout << "Ресурсы имеют одинаковое наименование" << endl;
                    }
                    else {
                        cout << "Ресурсы имеют разное наименование" << endl;
                    }
                    break;
                }
                case 6: {
                    // Вычисление прибыльности ресурса за неделю
                    cout << "Введите номер ресурса для вычисления прибыльности (1, 2 или 3): ";
                    int n = getNum<int>(1, 3);
                    Resource r;
                    switch (n) {
                        case 1: r = r1; break;
                        case 2: r = r2; break;
                        case 3: r = r3; break;
                    }
                    double p = r.profit();
                    cout << "Прибыльность ресурса за неделю: " << p << " у.е." << endl;
                    break;
                }
                case 7: {
                    // Увеличение оборота ресурса в заданное число раз
                    cout << "Введите номер ресурса для увеличения оборота (1, 2 или 3): ";
                    int n = getNum<int>(1, 3);
                    Resource r;
                    switch (n) {
                        case 1: r = r1; break;
                        case 2: r = r2; break;
                        case 3: r = r3; break;
                    }
                    cout << "Введите коэффициент увеличения оборота: ";
                    double factor = getNum<double>();
                    r.multiply(factor);

                    // Вывод нового состояния ресурса на экран
                    cout << "Ресурс после увеличения оборота: ";
                    r.output(cout);
                    break;
                }
                case 8: {
                    // Выход из программы
                    cout << "Спасибо за использование моей программы. До свидания!" << endl;
                    exit = true;
                    break;
                }
            }
        }
    }
    catch (const exception& e) {
        // Вывод сообщения об исключении
        cerr << "Произошла ошибка: " << e.what() << endl;
        // Освобождение ресурсов
        // Нет необходимости, так как все объекты класса Resource созданы на стеке
        // Завершение программы с кодом ошибки
        return 1;
    }
    // Завершение программы с кодом успеха
    return 0;
}