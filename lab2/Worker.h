#pragma once
#include <string>
#include <iostream>

class WorkerException {
private:
    std::string message;
public:
    WorkerException(std::string msg) : message(msg) {}
    std::string getMessage() const { return message; }
};

class WORKER {
private:
    std::string fio;       
    std::string position;   
    int year;     

public:
 
    WORKER();

    WORKER(std::string f, std::string p, int y);

    WORKER(const WORKER& other);

    ~WORKER();

    void setFio(std::string f);
    std::string getFio() const;

    void setPosition(std::string p);
    std::string getPosition() const;

    void setYear(int y);
    int getYear() const;

    friend std::ostream& operator<<(std::ostream& out, const WORKER& w);
    friend std::istream& operator>>(std::istream& in, WORKER& w);
};