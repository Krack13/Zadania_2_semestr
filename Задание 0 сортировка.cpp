#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm> 

using namespace std;

class Registration {
public:
    string Name;
    string birth_date;
    int brain_volume;

    Registration(string name, string date, int volume) : Name(name), birth_date(date), brain_volume(volume) {}

    void displayRecord() const { cout << "ФИО: " << Name << endl; cout << "Дата рождения: " << birth_date << endl; cout << "Объем мозга: " << brain_volume << endl;}

    bool operator<(const Registration& other) const { return Name < other.Name; }


    bool compare(const Registration& other, int sortField) const {
        switch (sortField) {
        case 1:
            return Name < other.Name;
        case 2:
            return birth_date < other.birth_date;
        case 3:
            return brain_volume < other.brain_volume;
        default:
            return false;
        }
    }
};

class Record {
private:
    vector<Registration> records;

public:
    void addRecord(const Registration& record) {records.push_back(record);}

    void removeRecord(int index) {
        if (index >= 0 && index < records.size()) {records.erase(records.begin() + index);}}

    void displayRecords() const {for (size_t i = 0; i < records.size(); ++i) {cout << "Запись" << i + 1 << endl;records[i].displayRecord();cout << endl;}}

    void inputNewRecord() {
        string name, date;
        int volume;

        cout << "Введите ФИО: ";
        getline(cin, name);
        cout << "Введите дату рождения в формате (ДД.ММ.ГГГГ): ";
        getline(cin, date);
        cout << "Введите объем мозга: ";
        cin >> volume;
        cin.ignore();

        Registration record(name, date, volume);
        addRecord(record);
    }


    void blob_Sort(int sortField) {
        int n = records.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (!records[j].compare(records[j + 1], sortField)) {
                    swap(records[j], records[j + 1]);
                }
            }
        }
    }

    void sample_Sort(int sortField) {
        int n = records.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (records[j].compare(records[minIndex], sortField)) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                swap(records[i], records[minIndex]);
            }
        }
    }
    void insertion_Sort(int sortField) {
        int n = records.size();
        for (int i = 1; i < n; ++i) {
            Registration key = records[i];
            int j = i - 1;

            while (j >= 0 && !records[j].compare(key, sortField)) {
                records[j + 1] = records[j];
                --j;
            }
            records[j + 1] = key;
        }
    }
    void fast_Sort(int sortField, int low, int high) {
        if (low < high) {
            int pi = partition(sortField, low, high);

            fast_Sort(sortField, low, pi - 1);
            fast_Sort(sortField, pi + 1, high);
        }
    }
    void shake_Sort(int sortField) {
        int left = 0;
        int right = records.size() - 1;
        bool swapped = true;

        while (swapped) {
            swapped = false;


            for (int i = left; i < right; ++i) {
                if (records[i].compare(records[i + 1], sortField)) {
                    swap(records[i], records[i + 1]);
                    swapped = true;
                }
            }


            if (!swapped) break;
            --right;
            for (int i = right; i > left; --i) {
                if (records[i - 1].compare(records[i], sortField)) {
                    swap(records[i - 1], records[i]);
                    swapped = true;
                }
            }
            ++left;
        }
    }
    void combined_Sort(int sortField) {
        int n = records.size();
        int gap = n;
        float shrink = 1.3;
        bool sorted = false;

        while (!sorted) {
            gap = static_cast<int>(gap / shrink);
            if (gap > 1) {
                sorted = false;
            }
            else {
                gap = 1;
                sorted = true;
            }

            int i = 0;
            while (i + gap < n) {
                if (records[i].compare(records[i + gap], sortField)) {
                    swap(records[i], records[i + gap]);
                    sorted = false;
                }
                ++i;
            }
        }
    }

private:
    int partition(int sortField, int low, int high) {
        Registration pin = records[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (records[j].compare(pin, sortField)) {++i;swap(records[i], records[j]);}}

        swap(records[i + 1], records[high]);
        return i + 1;
    }

public:
    size_t size() const {return records.size();}

    void sink_Sort(int sortField) {
        int n = records.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                Registration temp = records[i];
                int j;
                for (j = i; j >= gap && records[j - gap].compare(temp, sortField); j -= gap) {
                    records[j] = records[j - gap];
                }
                records[j] = temp;
            }
        }
    }



    void stack_Sort(int sortField) {
        int n = records.size();
        for (int i = n / 2 - 1; i >= 0; --i) {stack(sortField, n, i);}
        for (int i = n - 1; i > 0; --i) {swap(records[0], records[i]);stack(sortField, i, 0);}
    }

private:
    void stack(int sortField, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && records[left].compare(records[largest], sortField)) {
            largest = left;
        }

        if (right < n && records[right].compare(records[largest], sortField)) {
            largest = right;
        }

        if (largest != i) {
            swap(records[i], records[largest]);
            stack(sortField, n, largest);
        }
    }


    string generateRandomdate() const {

        const vector<string> months = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(1, 28);
        int day = distribution(gen);
        uniform_int_distribution<int> monthDist(0, 11);
        string month = months[monthDist(gen)];
        uniform_int_distribution<int> yearDist(1950, 2020);
        int year = yearDist(gen);
        return to_string(day) + "." + month + "." + to_string(year);
    }


    string generateRandomName() const {
        const vector<string> names = { "Nikita", "Maria", "Viktoria", "Danil", "Ruslan", "Anna", "Leo", "Olga", "Ivan", "Denis" };
        random_device record;
        mt19937 gen(record());
        uniform_int_distribution<int> distribution(0, names.size() - 1);
        int index = distribution(gen);
        return names[index];
    }

public:

    void dateRandomRecords(size_t count) {
        for (size_t i = 0; i < count; ++i) {
            string name = generateRandomName();
            string date = generateRandomdate();
            int volume = rand() % 2000 + 1000;
            Registration record(name, date, volume);
            addRecord(record);
        }
    }




};


int main() {
    Record container;
    int choice;
    setlocale(LC_ALL, "rus");

    container.dateRandomRecords(10);

    do {
        cout << "Меню:" << endl;
        cout << "1.  Просмотр списка" << endl;
        cout << "2.  Ввод новых данных" << endl;
        cout << "3.  Сортировка списка пузырьковым методом" << endl;
        cout << "4.  Сортировка выборкой" << endl;
        cout << "5.  Сортировка вставками" << endl;
        cout << "6.  Быстрая сортировка" << endl;
        cout << "7.  Сортировка по Шеллу" << endl;
        cout << "8.  Сортировка пирамидами" << endl;
        cout << "9.  Сортировка перемешиванием" << endl;
        cout << "10. Сортировка гребнем" << endl;
        cout << "0.  Выход из программы" << endl;
        cout << "Введите свой выбор: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Все записи:" << endl;
            container.displayRecords();
            break;
        case 2:
            container.inputNewRecord();
            break;
        case 3:
            int sortField;
            cout << "Выберете поле сортировки:" << endl;
            cout << "1. ФИО" << endl;
            cout << "2. Дата рождения" << endl;
            cout << "3. Объем мозга" << endl;
            cout << "   Введите выбор: ";
            cin >> sortField;
            cin.ignore();
            container.blob_Sort(sortField);
            cout << "Записи отсортированны!" << endl;
            break;
        case 4:

            cout << "Выберете поле сортировки:" << endl;
            cout << "1. ФИО" << endl;
            cout << "2. Дата рождения" << endl;
            cout << "3. Объем мозга" << endl;
            cout << "   Введите выбор: ";;
            cin >> sortField;
            cin.ignore();
            break;
        case 5:

            cout << "Выберете поле сортировки:" << endl;
            cout << "1. ФИО" << endl;
            cout << "2. Дата рождения" << endl;
            cout << "3. Объем мозга" << endl;
            cout << "   Введите выбор: ";
            cin >> sortField;
            cin.ignore();
            if (choice == 3) {
                container.blob_Sort(sortField);
                cout << "Записи отсортированны пузырчатым методом." << endl;
            }
            else if (choice == 4) {
                container.sample_Sort(sortField);
                cout << "Записи, отсортированные с помощью выборочной сортировки." << endl;
            }
            else {
                container.insertion_Sort(sortField);
                cout << "Записи, отсортированные с помощью сортировки вставкой." << endl;
            }
            break;
        case 6:
            int quickSortField;
            cout << "Выберете поле сортировки:" << endl;
            cout << "1. ФИО" << endl;
            cout << "2. Дата рождения" << endl;
            cout << "3. Объем мозга" << endl;
            cout << "   Введите выбор: ";
            cin >> quickSortField;
            cin.ignore();
            container.fast_Sort(quickSortField, 0, container.size() - 1);
            cout << "Записи, отсортированные с помощью быстрой сортировки." << endl;
            break;
        case 7:
            int shellSortField;
            cout << "Выберете поле сортировки:" << endl;
            cout << "1. ФИО" << endl;
            cout << "2. Дата рождения" << endl;
            cout << "3. Объем мозга" << endl;
            cout << "   Введите выбор: ";
            cin >> shellSortField;
            cin.ignore();
            container.sink_Sort(shellSortField);
            cout << "Records sorted using Shell Sort." << endl;
            break;
        case 8:
            int heapSortField;
            cout << "Выберете поле сортировки:" << endl;
            cout << "1. ФИО" << endl;
            cout << "2. Дата рождения" << endl;
            cout << "3. Объем мозга" << endl;
            cout << "   Введите выбор: ";
            cin >> heapSortField;
            cin.ignore();
            container.stack_Sort(heapSortField);
            cout << "Записи, отсортированные с помощью пирамид." << endl;
            break;
        case 9:
            int shake_lSort_Field;
            cout << "Выберете поле сортировки:" << endl;
            cout << "1. ФИО" << endl;
            cout << "2. Дата рождения" << endl;
            cout << "3. Объем мозга" << endl;
            cout << "   Введите выбор: ";
            cin >> shake_lSort_Field;
            cin.ignore();
            container.shake_Sort(shake_lSort_Field);
            cout << "Записи, отсортированные перемешиванием." << endl;
            break;
        case 10:
            int combSortField;
            cout << "Выберете поле сортировки:" << endl;
            cout << "1. ФИО" << endl;
            cout << "2. Дата рождения" << endl;
            cout << "3. Объем мозга" << endl;
            cout << "   Введите выбор: ";
            cin >> combSortField;
            cin.ignore();
            container.combined_Sort(combSortField);
            cout << "Записи, отсортированные гребнем." << endl;
            break;
        case 0:
            cout << "Программа закончила свою работу" << endl;
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
        }
    } while (choice != 0);

    return 0;
}
