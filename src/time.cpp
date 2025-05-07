#include "../include/mytime.h"

Time::Time() : hours(0), minutes(0) {}
Time::Time(int h, int m) : hours(h), minutes(m) {}

int Time::toMinutes() const {
    return hours * 60 + minutes;
}

bool Time::operator<(const Time& other) const {
    return toMinutes() < other.toMinutes();
}

bool Time::operator<=(const Time& other) const {
    return toMinutes() <= other.toMinutes();
}

Time Time::operator-(const Time& other) const {
    int diff = toMinutes() - other.toMinutes();
    return {diff / 60, diff % 60};
}

Time Time::operator+(const Time& other) const {
    int total = toMinutes() + other.toMinutes();
    return {total / 60, total % 60};
}

Time& Time::operator+=(const Time& other) {
    int total = toMinutes() + other.toMinutes();
    hours = total / 60;
    minutes = total % 60;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    if (time.hours < 10) os << '0';
    os << time.hours << ":";
    if (time.minutes < 10) os << '0';
    os << time.minutes;
    return os;
}
