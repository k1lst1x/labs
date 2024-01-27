#ifndef RESOURCETABLE_H
#define RESOURCETABLE_H

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

        bool operator>(const Resource& other) const {
            return name > other.name;
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

// Сложный класс Таблица ресурсов с динамической памятью
class ResourceTable {
    private:
        Resource* resources; // указатель на динамический массив ресурсов
        int size; // текущий размер таблицы
        int capacity; // максимальный размер таблицы

        // сортировка ресурсов по наименованию (пузырьковая сортировка)
        void sort() {
            for (int i = 0; i < size - 1; i++) {
                for (int j = i + 1; j < size; j++) {
                    if (resources[i] > resources[j]) {
                        Resource temp = resources[i];
                        resources[i] = resources[j];
                        resources[j] = temp;
                    }
                }
            }
        }

        // поиск ресурса по наименованию (двоичный поиск)
        int find(string name) {
            int left = 0;
            int right = size - 1;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (resources[mid].getName() == name) {
                    return mid;
                }
                else if (resources[mid].getName() < name) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
            return -1;
        }

        // расширение массива ресурсов в два раза
        void expand() {
            capacity *= 2; // увеличиваем максимальный размер
            Resource* new_resources = new Resource[capacity]; // создаем новый динамический массив
            for (int i = 0; i < size; i++) {
                new_resources[i] = resources[i]; // копируем старые ресурсы
            }
            delete[] resources; // удаляем старый массив
            resources = new_resources; // присваиваем новый массив
        }
    public:
        // конструктор по умолчанию
        ResourceTable() {
            size = 0;
            capacity = 10; // начальный максимальный размер
            resources = new Resource[capacity]; // выделяем динамическую память
        }

        ResourceTable(int cap) {
		    capacity = cap; // Инициализируем поле capacity
		    size = 0; // Инициализируем поле size
		    resources = new Resource[capacity]; // Выделяем память для массива ресурсов
		}

        // конструктор с двумя параметрами
        ResourceTable(Resource arr[], int n) {
            size = n;
            capacity = n * 2; // запасной максимальный размер
            resources = new Resource[capacity]; // выделяем динамическую память
            for (int i = 0; i < n; i++) {
                resources[i] = arr[i]; // копируем ресурсы из массива
            }
            sort();
        }

        // копирующий конструктор
        ResourceTable(const ResourceTable& other) {
            size = other.size;
            capacity = other.capacity;
            resources = new Resource[capacity]; // выделяем динамическую память
            for (int i = 0; i < size; i++) {
                resources[i] = other.resources[i]; // копируем ресурсы из другого объекта
            }
        }

        // перемещающий конструктор
        ResourceTable(ResourceTable&& other) {
            size = other.size;
            capacity = other.capacity;
            resources = other.resources; // забираем указатель на динамический массив
            other.resources = nullptr; // обнуляем указатель у другого объекта
        }

        // деструктор
        ~ResourceTable() {
            delete[] resources; // освобождаем динамическую память
        }

        int getSize() { // Геттер для поля size
	        return size;
	    }

	    Resource* getResources() { // Геттер для поля resources
	        return resources;
	    }

        // метод ввода состояния класса в входной поток
        void input(istream& in) {
            in >> size;
            if (size > capacity) { // если размер больше максимального
                delete[] resources; // удаляем старый массив
                capacity = size * 2; // увеличиваем максимальный размер
                resources = new Resource[capacity]; // создаем новый массив
            }
            for (int i = 0; i < size; i++) {
                resources[i].input(in); // вводим ресурсы
            }
            sort();
        }

        // метод вывода состояния класса в выходной поток
        void output(ostream& out) const {
            out << size << endl;
            for (int i = 0; i < size; i++) {
                resources[i].output(out); // выводим ресурсы
            }
        }
        
        // Перегрузка оператора >> для ввода экземпляра сложного класса из входного потока
        friend istream& operator>>(istream& in, ResourceTable& table) {
            table.input(in); // вызываем метод input класса ResourceTable
            return in; // возвращаем ссылку на поток
        }
        
        // Перегрузка оператора << для вывода экземпляра сложного класса в выходной поток
        friend ostream& operator<<(ostream& out, const ResourceTable& table) {
            table.output(out); // вызываем метод output класса ResourceTable
            return out; // возвращаем ссылку на поток
        }

        // добавление нового ресурса в таблицу
        ResourceTable& operator+=(const Resource& r) {
            if (size == capacity) { // если таблица полная
                expand(); // расширяем массив
            }
            resources[size] = r; // добавляем ресурс
            size++;
            sort();
            return *this;
        }

        // Оператор + для сложения двух таблиц ресурсов
		friend ResourceTable operator+(const ResourceTable& rt1, const ResourceTable& rt2) {
		    // Создаем новую таблицу ресурсов с суммарной емкостью
		    ResourceTable result(rt1.capacity + rt2.capacity);
		    // Копируем ресурсы из первой таблицы
		    for (int i = 0; i < rt1.size; i++) {
		        result += rt1.resources[i];
		    }
		    // Копируем ресурсы из второй таблицы
		    for (int i = 0; i < rt2.size; i++) {
		        result += rt2.resources[i];
		    }
		    // Возвращаем новую таблицу ресурсов
		    return result;
		}


        // получение ресурса по его наименованию (возврат по ссылке)
        Resource& operator[](const string& name) {
            int index = find(name);
            if (index != -1) {
                return resources[index];
            }
            /*
            else {
                return Resource(); // возвращаем пустой ресурс, если не найден
            }
            */
            throw out_of_range("Ресурс не найден");
        }

        // проверка состояния таблицы (пустая, частично заполнена или полная)
        string state() {
            if (size == 0) {
                return "пустая";
            }
            else if (size == capacity) {
                return "полная";
            }
            else {
                return "частично заполненная";
            }
        }

        // удаление ресурса с заданным наименованием из таблицы
        bool remove(string name) {
            int index = find(name);
            if (index != -1) {
                for (int i = index; i < size - 1; i++) {
                    resources[i] = resources[i + 1]; // сдвигаем ресурсы влево
                }
                size--;
                return true;
            }
            else {
                return false;
            }
        }

        // вычисление общей прибыльности по всем ресурсам
        double totalProfit() {
            double sum = 0;
            for (int i = 0; i < size; i++) {
                sum += resources[i].profit();
            }
            return sum;
        }

        // увеличение оборота всех ресурсов в заданное число раз
        void multiply(double factor) {
            for (int i = 0; i < size; i++) {
                resources[i].multiply(factor);
            }
        }

        // переименование заданного ресурса (передаются старое и новое наименования)
        bool rename(string oldName, string newName) {
            int index = find(oldName);
            if (index != -1) {
                resources[index].setName(newName);
                sort();
                return true;
            }
            else {
                return false;
            }
        }
        /*
        // перемещающий оператор присваивания
        ResourceTable& operator=(ResourceTable&& other) {
            if (this != &other) { // если не самоприсваивание
                delete[] resources; // удаляем старый массив
                size = other.size;
                capacity = other.capacity;
                resources = other.resources; // забираем указатель на динамический массив
                other.resources = nullptr; // обнуляем указатель у другого объекта
            }
            return *this;
        }
        */
        // Перегрузка оператора = для копирования экземпляра сложного класса
        ResourceTable& operator=(const ResourceTable& other) {
            if (this != &other) { // если не самоприсваивание
                delete[] resources; // освобождаем старую память
                size = other.size; // копируем размер
                capacity = other.capacity; // копируем вместимость
                resources = new Resource[capacity]; // выделяем новую память
                for (int i = 0; i < size; i++) { // копируем элементы
                    resources[i] = other.resources[i];
                }
            }
            return *this; // возвращаем ссылку на текущий объект
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

#endif //RESOURCETABLE_H