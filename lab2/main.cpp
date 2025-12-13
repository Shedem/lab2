#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <ctime>   
#include "Worker.h"

using namespace std;

WORKER* workers = nullptr; 
int countWorkers = 0;    

void addWorker() {
    try {
        WORKER newWorker;
        cin >> newWorker; 

        WORKER* temp = new WORKER[countWorkers + 1];

        for (int i = 0; i < countWorkers; i++) {
            temp[i] = workers[i]; 
        }

        temp[countWorkers] = newWorker;

        if (workers != nullptr) {
            delete[] workers;
        }

        workers = temp;
        countWorkers++;

        cout << ">>> Работник успешно добавлен!\n";
    }
    catch (const WorkerException& e) {
        cout << "!!! ОШИБКА ДОБАВЛЕНИЯ: " << e.getMessage() << endl;
    }
}

void removeWorker() {
    if (countWorkers == 0) {
        cout << "Список пуст, удалять некого.\n";
        return;
    }

    int index;
    cout << "Введите номер записи для удаления (1 - " << countWorkers << "): ";
    cin >> index;
    index--; 

    if (index < 0 || index >= countWorkers) {
        cout << "Неверный номер!\n";
        return;
    }

    WORKER* temp = new WORKER[countWorkers - 1];

    int j = 0;
    for (int i = 0; i < countWorkers; i++) {
        if (i == index) continue; 
        temp[j] = workers[i];
        j++;
    }

    delete[] workers;
    workers = temp;
    countWorkers--;

    cout << ">>> Запись удалена.\n";
}

void sortWorkers() {
    if (countWorkers < 2) return;

    for (int i = 0; i < countWorkers - 1; i++) {
        for (int j = 0; j < countWorkers - i - 1; j++) {
            if (workers[j].getFio() > workers[j + 1].getFio()) {
                WORKER temp = workers[j];
                workers[j] = workers[j + 1];
                workers[j + 1] = temp;
            }
        }
    }
    cout << ">>> Список отсортирован по алфавиту.\n";
}

void printAll() {
    if (countWorkers == 0) {
        cout << "Список пуст.\n";
        return;
    }
    cout << "\n--- СПИСОК РАБОТНИКОВ ---\n";
    for (int i = 0; i < countWorkers; i++) {
        cout << "#" << (i + 1) << ". " << workers[i] << endl;
    }
    cout << "-------------------------\n";
}

void findExperienced() {
    if (countWorkers == 0) {
        cout << "Список пуст.\n";
        return;
    }

    int minExp;
    cout << "Введите минимальный стаж (лет): ";
    cin >> minExp;

    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int currentYear = now->tm_year + 1900;

    bool found = false;
    cout << "\n--- РЕЗУЛЬТАТЫ ПОИСКА ---\n";
    for (int i = 0; i < countWorkers; i++) {
        int exp = currentYear - workers[i].getYear();
        if (exp > minExp) {
            cout << workers[i].getFio() << " (Стаж: " << exp << " лет)\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Работников со стажем более " << minExp << " лет не найдено.\n";
    }
}


void fileTask() {


    string filename;
    cout << "Введите имя файла для чтения (например, text.txt): ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл!\n";
        return;
    }

    cout << "\n--- ПРЕДЛОЖЕНИЯ БЕЗ ЗАПЯТЫХ ---\n";

    char ch;
    string sentence = "";

    while (file >> noskipws >> ch) {
        sentence += ch;

        if (ch == '.' || ch == '!' || ch == '?') {
            
            if (sentence.find(',') == string::npos) {
                cout << sentence; 
            }
           
            sentence = "";
        }
    }

    file.close();
    cout << "\n\n--- КОНЕЦ ОБРАБОТКИ ФАЙЛА ---\n";
}



int main() {
    setlocale(LC_ALL, "Russian"); 
    int choice;

    do {
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Добавить работника\n";
        cout << "2. Удалить работника\n";
        cout << "3. Редактировать работника\n";
        cout << "4. Показать всех (сортировка)\n";
        cout << "5. Найти опытных сотрудников (Задание 1)\n";
        cout << "6. Обработка файла (Задание 2)\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        try {
            switch (choice) {
            case 1:
                addWorker();
                
                sortWorkers();
                break;
            case 2:
                printAll();
                removeWorker();
                break;
            case 3:
                printAll();
                int id;
                cout << "Введите номер для редактирования: ";
                cin >> id;
                if (id > 0 && id <= countWorkers) {
                    cout << "Введите новые данные:\n";
                    cin >> workers[id - 1];
                    sortWorkers();
                }
                else {
                    cout << "Неверный номер.\n";
                }
                break;
            case 4:
                sortWorkers();
                printAll();
                break;
            case 5:
                sortWorkers();
                findExperienced();
                break;
            case 6:
                fileTask();
                break;
            case 0:
                cout << "Выход...\n";
                break;
            default:
                cout << "Неверный пункт меню.\n";
            }
        }
        catch (const WorkerException& e) {
            cout << "Поймано исключение: " << e.getMessage() << endl;
        }
        catch (...) {
            cout << "Неизвестная ошибка!\n";
        }

    } while (choice != 0);

    if (workers != nullptr) {
        delete[] workers;
    }

    return 0;
}