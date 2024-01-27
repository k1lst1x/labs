#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Создаем абстрактный класс вклада
class Vklad {
    protected:
        int nomer; // Номер счета
        string fio; // Фамилия владельца
        string data; // Дата открытия вклада
        double sum; // Сумма вклада
        double proc; // Процент начисления по вкладу
    public:
        // Конструктор с параметрами
        Vklad(int n, string f, string d, double s, double p) {
            nomer = n;
            fio = f;
            data = d;
            sum = s;
            proc = p;
        }

        // Виртуальный деструктор
        virtual ~Vklad() {}

        // Геттеры и сеттеры для полей класса
        int getNomer() {
            return nomer;
        }

        string getFio() {
            return fio;
        }

        string getData() {
            return data;
        }

        double getSum() {
            return sum;
        }

        double getProc() {
            return proc;
        }

        void setNomer(int n) {
            nomer = n;
        }

        void setFio(string f) {
            fio = f;
        }

        void setData(string d) {
            data = d;
        }

        void setSum(double s) {
            sum = s;
        }

        void setProc(double p) {
            proc = p;
        }
        void addMoney(double sum) {
            // Прибавляем сумму к полю sum
            this->sum += sum;
        }
        // Метод для снятия денег с суммы вклада
        void withdrawMoney(double sum) {
            // Проверяем, достаточно ли денег на счету
            if (this->sum >= sum) {
                // Вычитаем сумму из поля sum
                this->sum -= sum;
            }
            else {
                // Бросаем исключение, если денег недостаточно
                throw std::runtime_error("Недостаточно денег на счету");
            }
        }

        // Метод для снятия начисленных процентов с вклада
        void withdrawNakop(string data) {
            // Вычисляем величину начислений по процентам
            double nakop = this->calcNakop();
            // Проверяем, положительна ли она
            if (nakop > 0) {
                // Добавляем начисления к сумме вклада
                this->sum += nakop;
                // Обновляем дату последней операции
                this->data = data;
            }
            else {
                // Бросаем исключение, если начислений нет
                throw std::runtime_error("Нет начислений по процентам");
            }
        }


        // Виртуальные методы для операций с вкладом
        virtual void showInfo() = 0; // Показать всю информацию о вкладе
        virtual double calcNakop() = 0; // Рассчитать величину начислений по процентам
        virtual void changeData(string d) = 0; // Изменить дату последней операции
};

// Создаем класс обычного вклада, наследуемый от класса вклада
class ObichniyVklad : public Vklad {
    private:
        string lastOp; // Дата последней операции с вкладом
    public:
        // Конструктор с параметрами
        ObichniyVklad(int n, string f, string d, double s, double p, string l) : Vklad(n, f, d, s, p) {
            lastOp = l;
        }

        string getlastOp() {
            return lastOp;
        }

        // Переопределяем виртуальные методы для операций с вкладом
        void showInfo() override {
            cout << "Номер счета: " << nomer << endl;
            cout << "Фамилия владельца: " << fio << endl;
            cout << "Дата открытия вклада: " << data << endl;
            cout << "Сумма вклада: " << sum << endl;
            cout << "Процент начисления по вкладу: " << proc << endl;
            cout << "Дата последней операции с вкладом: " << lastOp << endl;
        }

        double calcNakop() override {
            // Рассчитываем количество месяцев между датой последней операции и текущей датой
            // Для простоты будем считать, что дата имеет формат ГГГГММДД
            int year1 = stoi(lastOp.substr(0, 4)); // Год последней операции
            int month1 = stoi(lastOp.substr(4, 2)); // Месяц последней операции
            int year2 = stoi(data.substr(0, 4)); // Год текущей даты
            int month2 = stoi(data.substr(4, 2)); // Месяц текущей даты
            int months = (year2 - year1) * 12 + (month2 - month1); // Количество месяцев между датами
            // Рассчитываем величину начислений по процентам
            double nakop = sum * proc / 100 * months;
            return nakop;
        }

        void changeData(string d) override {
            lastOp = d; // Изменяем дату последней операции
        }
};

// Создаем класс срочного вклада, наследуемый от класса вклада
class SrochniyVklad : public Vklad {
    private:
        int srok; // Срок хранения вклада в месяцах
    public:
        // Конструктор с параметрами
        SrochniyVklad(int n, string f, string d, double s, double p, int sr) : Vklad(n, f, d, s, p) {
            srok = sr;
        }

        // Переопределяем виртуальные методы для операций с вкладом
        void showInfo() override {
            cout << "Номер счета: " << nomer << endl;
            cout << "Фамилия владельца: " << fio << endl;
            cout << "Дата открытия вклада: " << data << endl;
            cout << "Сумма вклада: " << sum << endl;
            cout << "Процент начисления по вкладу: " << proc << endl;
            cout << "Срок хранения вклада в месяцах: " << srok << endl;
        }

        double calcNakop() override {
            // Рассчитываем величину начислений по процентам
            double nakop = sum * proc / 100 * srok;
            return nakop;
        }

        void changeData(string d) override {
            // Ничего не делаем, так как дата последней операции не меняется для срочного вклада
        }
};

// Создаем класс валютного вклада, наследуемый от класса обычного вклада
class ValutniyVklad : public ObichniyVklad {
    private:
        string valuta; // Название валюты
        double kurs; // Курс обмена валюты к рублю
    public:
        // Конструктор с параметрами
        ValutniyVklad(int n, string f, string d, double s, double p, string l, string v, double k) : ObichniyVklad(n, f, d, s, p, l) {
            valuta = v;
            kurs = k;
        }

        // Переопределяем виртуальные методы для операций с вкладом
        void showInfo() override {
            string lastOp1 = getlastOp();
            cout << "Номер счета: " << nomer << endl;
            cout << "Фамилия владельца: " << fio << endl;
            cout << "Дата открытия вклада: " << data << endl;
            cout << "Сумма вклада: " << sum << endl;
            cout << "Процент начисления по вкладу: " << proc << endl;
            cout << "Дата последней операции с вкладом: " << lastOp1 << endl;
            cout << "Название валюты: " << valuta << endl;
            cout << "Курс обмена валюты к рублю: " << kurs << endl;
        }

        // Добавляем новый метод для операции с вкладом
        double convertToRub() {
            // Выполняем пересчет суммы вклада в рублях
            double rub = sum * kurs;
            return rub;
        }
};

// Создаем класс-итератор для таблицы вкладов
class Iterator {
    private:
        vector<Vklad*>::iterator it; // Итератор для вектора указателей на вклады
    public:
        // Конструктор с параметром
        Iterator(vector<Vklad*>::iterator i) {
            it = i;
        }

        // Перегружаем оператор разыменования
        Vklad* operator*() {
            return *it; // Возвращаем указатель на вклад
        }

        // Перегружаем оператор инкремента
        Iterator& operator++() {
            ++it; // Переходим к следующему элементу вектора
            return *this; // Возвращаем ссылку на себя
        }

        // Перегружаем оператор сравнения
        bool operator!=(const Iterator& other) {
            return it != other.it; // Сравниваем итераторы по значению
        }
};

// Добавляем методы для получения итераторов в класс Table
class Table {
    private:
        vector<Vklad*> vklads; // Вектор указателей на вклады
    public:
        // Метод для получения итератора на начало вектора
        Iterator begin() {
            return Iterator(vklads.begin());
        }

        // Метод для получения итератора на конец вектора
        Iterator end() {
            return Iterator(vklads.end());
        }
        void addVklad(Vklad* vklad) {
            // Добавляем указатель на вклад в вектор
            vklads.push_back(vklad);
        }
        Vklad* findVklad(int nomer) {
            // Проходим по вектору указателей на вклады
            for (Vklad* vklad : vklads) {
                // Если номер счета совпадает, возвращаем указатель на вклад
                if (vklad->getNomer() == nomer) {
                    return vklad;
                }
            }
            // Если не нашли вклад, возвращаем nullptr
            return nullptr;
        }
        void removeVklad(int nomer) {
            // Проходим по вектору указателей на вклады
            for (auto it = vklads.begin(); it != vklads.end(); ++it) {
                // Если номер счета совпадает, удаляем указатель из вектора
                if ((*it)->getNomer() == nomer) {
                    vklads.erase(it);
                    break;
                }
            }
        }
        // Метод для освобождения памяти, выделенной под вклады
        void clear() {
            // Проходим по вектору указателей на вклады
            for (Vklad* vklad : vklads) {
                // Удаляем каждый вклад
                delete vklad;
            }
            // Очищаем вектор
            vklads.clear();
        }

        void showAll() {
            // Проходим по вектору указателей на вклады
            for (Vklad* vklad : vklads) {
                // Показываем информацию о каждом вкладе
                vklad->showInfo();
                // Рассчитываем и показываем величину начислений по процентам
                cout << "Величина начислений по процентам: " << vklad->calcNakop() << endl;
            }
        }
};

int main() {
    Table table;
    int choice, nomer, srok;
    string fio, data, data2, valuta;
    double sum, proc, kurs;
    double total = 0;
    Vklad* vklad;
    bool exit = false;
    cout << "Добро пожаловать в программу для работы с банковскими вкладами!\n";
    cout << "Выберите операцию из списка:\n";
    cout << "1. Открыть новый счет\n";
    cout << "2. Показать текущее состояние счета\n";
    cout << "3. Закрыть счет\n";
    cout << "4. Модифицировать состояние счета\n";
    cout << "5. Показать информацию обо всех имеющихся счетах\n";
    cout << "6. Выполнить пересчет вкладов в указанную валюту\n";
    cout << "0. Выход из программы\n";
    while (!exit) {
        cout << "Введите номер операции: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Выберите тип вклада:\n";
                cout << "1. Обычный вклад\n";
                cout << "2. Срочный вклад\n";
                cout << "3. Валютный вклад\n";
                cin >> choice;
                cout << "Введите номер счета: ";
                cin >> nomer;
                cout << "Введите фамилию владельца: ";
                cin >> fio;
                cout << "Введите дату открытия вклада в формате ГГГГММДД: ";
                cin >> data;
                cout << "Введите сумму вклада: ";
                cin >> sum;
                cout << "Введите процент начисления по вкладу: ";
                cin >> proc;
                switch (choice) {
                    case 1:
                        cout << "Введите дату последней операции с вкладом в формате ГГГГММДД: ";
                        cin >> data2;
                        vklad = new ObichniyVklad(nomer, fio, data, sum, proc, data2);
                        table.addVklad(vklad);
                        break;
                    case 2:
                        cout << "Введите срок хранения вклада в месяцах: ";
                        cin >> srok;
                        vklad = new SrochniyVklad(nomer, fio, data, sum, proc, srok);
                        table.addVklad(vklad);
                        break;
                    case 3:
                        cout << "Введите дату последней операции с вкладом в формате ГГГГММДД: ";
                        cin >> data2;
                        cout << "Введите название валюты: ";
                        cin >> valuta;
                        cout << "Введите курс обмена валюты к рублю: ";
                        cin >> kurs;
                        vklad = new ValutniyVklad(nomer, fio, data, sum, proc, data2, valuta, kurs);
                        table.addVklad(vklad);
                        break;
                    default:
                        cout << "Неверный тип вклада, попробуйте еще раз\n";
                        break;
                }
                break;
            case 2:
                cout << "Введите номер счета: ";
                cin >> nomer;
                vklad = table.findVklad(nomer);
                if (vklad != nullptr) {
                    vklad->showInfo();
                    cout << "Величина начислений по процентам: " << vklad->calcNakop() << endl;
                }
                else {
                    cout << "Вклад с таким номером не найден\n";
                }
                break;
            case 3:
                cout << "Введите номер счета: ";
                cin >> nomer;
                vklad = table.findVklad(nomer);
                if (vklad != nullptr) {
                    vklad->showInfo();
                    cout << "Величина начислений по процентам: " << vklad->calcNakop() << endl;
                    table.removeVklad(nomer);
                    cout << "Счет закрыт\n";
                }
                else {
                    cout << "Вклад с таким номером не найден\n";
                }
                break;
            case 4:
                cout << "Введите номер счета: ";
                cin >> nomer;
                vklad = table.findVklad(nomer);
                if (vklad != nullptr) {
                    cout << "Выберите операцию с вкладом:\n";
                    cout << "1. Внести деньги\n";
                    cout << "2. Снять вклад\n";
                    cout << "3. Снять проценты\n";
                    cin >> choice;
                    switch (choice) {
                        case 1:
                            cout << "Введите сумму, которую хотите внести: ";
                            cin >> sum;
                            vklad->addMoney(sum);
                            break;
                        case 2:
                            cout << "Введите сумму, которую хотите снять: ";
                            cin >> sum;
                            vklad->withdrawMoney(sum);
                            break;
                        case 3:
                            cout << "Введите дату снятия процентов в формате ГГГГММДД: ";
                            cin >> data;
                            vklad->withdrawNakop(data);
                            break;
                        default:
                            cout << "Неверная операция, попробуйте еще раз\n";
                            break;
                    }
                }
                else {
                    cout << "Вклад с таким номером не найден\n";
                }
                break;
            case 5:
                table.showAll();
                break;
            case 6:
                cout << "Введите название валюты: ";
                cin >> valuta;
                cout << "Введите курс обмена валюты к рублю: ";
                cin >> kurs;
                for (Iterator it = table.begin(); it != table.end(); ++it) {
                    vklad = *it;
                    ValutniyVklad* valutniy = dynamic_cast<ValutniyVklad*>(vklad);
                    if (valutniy != nullptr) {
                        total += valutniy->convertToRub();
                    }
                    else {
                        total += vklad->getSum();
                    }
                }
                cout << "Сумма всех вкладов в рублях: " << total << endl;
                total /= kurs;
                cout << "Сумма всех вкладов в " << valuta << ": " << total << endl;
                break;
            case 0:
                exit = true;
                break;
            default:
                cout << "Неверный номер операции, попробуйте еще раз\n";
                break;
        }
    }
    // Завершаем программу
    try {
        // Освобождаем память, выделенную под вклады
        table.clear();
        // Выводим сообщение об успешном завершении программы
        cout << "Спасибо за использование программы, до свидания!\n";
        return 0; // Возвращаем код успешного завершения
    }
    catch (exception& e) {
        // Перехватываем исключение, если оно возникло
        cerr << "Произошла невосстановимая ошибка: " << e.what() << endl;
        return 1; // Возвращаем код ошибки
    }
}