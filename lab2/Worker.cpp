#include "Worker.h"
#include <iostream>

using namespace std;


WORKER::WORKER() {
    fio = "Undefined";
    position = "None";
    year = 0;
    cout << ">> Вызван конструктор без параметров для: " << this << endl;
}

WORKER::WORKER(string f, string p, int y) {
    fio = f;
    position = p;

    if (y < 1900 || y > 2025) {
        throw WorkerException("Ошибка в конструкторе: Некорректный год поступления!");
    }
    year = y;
    cout << ">> Вызван конструктор с параметрами для: " << fio << endl;
}

WORKER::WORKER(const WORKER& other) {
    this->fio = other.fio;
    this->position = other.position;
    this->year = other.year;
    cout << ">> Вызван конструктор КОПИРОВАНИЯ. Копия создана из: " << other.fio << endl;
}

WORKER::~WORKER() {
    cout << "<< Вызван деструктор для объекта: " << fio << " (" << this << ")" << endl;
}


void WORKER::setFio(string f) {
    if (f.empty()) throw WorkerException("Ошибка: ФИО не может быть пустым!");
    fio = f;
}
string WORKER::getFio() const { return fio; }

void WORKER::setPosition(string p) { position = p; }
string WORKER::getPosition() const { return position; }

void WORKER::setYear(int y) {
    if (y < 1900 || y > 2100) {

        throw WorkerException("Ошибка: Некорректный год (должен быть > 1900)!");
    }
    year = y;
}
int WORKER::getYear() const { return year; }

ostream& operator<<(ostream& out, const WORKER& w) {
    out << "ФИО: " << w.fio
        << " | Должность: " << w.position
        << " | Год: " << w.year;
    return out;
}

istream& operator>>(istream& in, WORKER& w) {
    cout << "Введите ФИО (одним словом или используйте _ вместо пробела): ";
    in >> w.fio;
    cout << "Введите должность: ";
    in >> w.position;
    cout << "Введите год поступления: ";
    int tempYear;
    in >> tempYear;

    if (tempYear < 1900 || tempYear > 2100) {
        throw WorkerException("Ошибка ввода: Недопустимый год!");
    }
    w.year = tempYear;

    return in;
}