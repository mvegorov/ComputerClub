#ifndef COMPUTER_CLUB_H
#define COMPUTER_CLUB_H

#include "mytime.h"
#include "events.h"
#include "table.h"
#include <vector>
#include <map>
#include <queue>

class ComputerClub {
private:
    int tableCount;
    Time openTime;
    Time closeTime;

    /**
     * Соответствие "Имя клиента → номер стола".
     * Содержит информацию о текущем расположении клиентов:
     *          - Ключ: имя клиента (std::string).
     *          - Значение: индекс стола в массиве `tables`.
     *
     * Особые случаи:
     *   -1: клиент в клубе, но не за столом.
     *   Нет в map: клиент отсутствует.
     */
    std::map<std::string, int> clientToTableMap;

    std::vector<Table> tables;
    int totalOccupiedTables;
    std::queue<std::string> queue;

    static void generateError(const Time& time, const std::string& error);
public:
    ComputerClub(int count, const Time& open, const Time& close, int cost);

    void closeClub();

    void handleClientArrived(const Time& time, const std::string& clientName);

    void handleClientSat(const Time& time, const std::string& clientName, int tableNum);

    void handleClientWaiting(const Time& time, const std::string& clientName);

    void handleClientLeft(const Time& time, const std::string& clientName);
};

#endif