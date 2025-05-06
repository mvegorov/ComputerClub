#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>
#include <iomanip>

class Time {
private:
    int hours;
    int minutes;

public:
    Time();
    Time(int h, int m);

    int toMinutes() const;

    bool operator<(const Time& other) const;
    bool operator<=(const Time& other) const;
    Time operator-(const Time& other) const;
    Time operator+(const Time& other) const;
    Time& operator+=(const Time& other);

    friend std::ostream& operator<<(std::ostream& os, const Time& time);
};

#endif