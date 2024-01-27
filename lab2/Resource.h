#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <cstring>
#include <stdexcept>
using namespace std;

// Класс Ресурс
class Resource {
    private:
        // Атрибуты класса
        string name; // наименование ресурса
        double consumption; // потребление (кг/д)
        double production; // производство (кг/д)
        double price; // цена (у.е./кг)
    public:
        // Пустой конструктор
        Resource() {
            name = "";
            consumption = 0;
            production = 0;
            price = 0;
        }

        // Конструктор с инициализацией наименованием, потреблением, производством и ценой
        Resource(const string& n, double c, double p, double pr) {
            name = n;
            consumption = c;
            if (p < 0) {
                throw invalid_argument("Производство не может быть отрицательным");
            }
            production = p;
            if (pr < 0) {
                throw invalid_argument("Цена не может быть отрицательной");
            }
            price = pr;
        }

        // Конструктор с инициализацией только наименованием и ценой
        Resource(const string& n, double pr) {
            name = n;
            consumption = 0;
            production = 0;
            if (pr < 0) {
                throw invalid_argument("Цена не может быть отрицательной");
            }
            price = pr;
        }

        // Геттеры
        string getName() const {
            return name;
        }

        double getConsumption() const {
            return consumption;
        }

        double getProduction() const {
            return production;
        }

        double getPrice() const {
            return price;
        }

        // Сеттеры
        void setName(const string& n) {
            name = n;
        }

        void setConsumption(double c) {
            consumption = c;
        }

        void setProduction(double p) {
            if (p < 0) {
                throw invalid_argument("Производство не может быть отрицательным");
            }
            production = p;
        }

        void setPrice(double pr) {
            if (pr < 0) {
                throw invalid_argument("Цена не может быть отрицательной");
            }
            price = pr;
        }

        // Метод ввода состояния класса из входного потока
        void input(istream& in) {
            double tmpProduction = production;
            if (tmpProduction < 0) {
                throw invalid_argument("Производство не может быть отрицательным");
            }
            double tmpPrice = price;
            if (tmpPrice < 0) {
                throw invalid_argument("Цена не может быть отрицательной");
            }
            in >> name >> consumption >> production >> price;

        }

        // Метод вывода состояния класса в выходной поток
        void output(ostream& out) const {
            out << name << " " << consumption << " " << production << " " << price << endl;
        }

        // Перегрузка оператора >> для ввода экземпляра простого класса из входного потока
        friend istream& operator>>(istream& in, Resource& r) {
            r.input(in); // вызываем метод input класса Resource
            return in; // возвращаем ссылку на поток
        }

        // Перегрузка оператора << для вывода экземпляра простого класса в выходной поток
        friend ostream& operator<<(ostream& out, const Resource& r) {
            r.output(out); // вызываем метод output класса Resource
            return out; // возвращаем ссылку на поток
        }

        // Метод объединения двух одинаковых ресурсов
        Resource operator+(const Resource& other) const {
            // Проверка на совпадение наименований
            if (name != other.name) {
                //cerr << "Нельзя объединять разные ресурсы!" << endl;
                throw invalid_argument("Нельзя объединять ресурсы с разными именами");
            }
            // Складывание потребления и производства
            double new_consumption = consumption + other.consumption;
            double new_production = production + other.production;
            // Выбор наименьшей цены
            double new_price = min(price, other.price);
            // Создание нового экземпляра класса с новыми значениями
            Resource new_resource(name, new_consumption, new_production, new_price);
            return new_resource;
        }

        // Оператор равенства
        bool operator==(const Resource& other) const {
            return name == other.name;
        }
    
        // Оператор меньше
        bool operator<(const Resource& other) const {
            return name < other.name;
        }

        // Метод вычисления ориентировочной прибыльности ресурса за неделю
        double profit() {
            // Прибыльность = (производство - потребление) * цена * 7
            return (production - consumption) * price * 7;
        }

        // Метод увеличения оборота ресурса в заданное число раз
        void multiply(double factor) {
            // Умножение потребления и производства на фактор
            consumption *= factor;
            production *= factor;
        }
        bool isEmpty() const {
            return name.empty() && consumption == 0 && production == 0 && price == 0;
        }
};

//прототипы функций
string getString(istream& in);

template<class T>
T getNum(T min = numeric_limits<T>::lowest(), T max = numeric_limits<T>::max()) {
    T a;
    while (true) {
        cin >> a;
        if (cin.eof()) // обнаружен конец файла
            throw runtime_error("Failed to read number: EOF");
        else if (cin.bad()) // обнаружена невосстановимая ошибка входного потока
            throw runtime_error(string("Failed to read number: ") + strerror(errno));
        // прочие ошибки (неправильный формат ввода) либо число не входит в заданный диапазон
        else if (cin.fail() || a < min || a > max) {
            cin.clear(); // очищаем флаги состояния потока
            // игнорируем все символы до конца строки
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You are wrong; repeat please!" << endl;
        } else // успешный ввод
            return a;
    }
}

#endif //RESOURCE_H