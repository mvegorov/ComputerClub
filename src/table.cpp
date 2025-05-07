#include "../include/table.h"

Table::Table(int cost) : revenue(0), hourCost(cost) {}

void Table::occupy(const std::string& client, const Time& time) {
    currentClient = client;
    startTime = time;
}

void Table::release(const Time& endTime) {
    if (currentClient.empty()) return;

    Time duration = endTime - startTime;
    totalTime += duration;

    int hours = duration.toMinutes() / 60;
    if (duration.toMinutes() % 60 != 0) {
        hours++;
    }

    revenue += hours * hourCost;
    currentClient = "";
}

bool Table::isOccupied() const {
    return !currentClient.empty();
}
