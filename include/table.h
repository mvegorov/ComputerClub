#ifndef TABLE_H
#define TABLE_H

#include "time.h"
#include <string>

class Table {
public:
    std::string currentClient;
    Time startTime;
    Time totalTime;
    int revenue;
    int hourCost;

    Table(int cost);
    void occupy(const std::string& client, const Time& time);
    void release(const Time& endTime);
    bool isOccupied() const;
};

#endif