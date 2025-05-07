#include "../include/computer_club.h"

ComputerClub::ComputerClub(int count, const Time& open, const Time& close, int cost)
        : totalOccupiedTables(0), tableCount(count), openTime(open), closeTime(close) {
    std::cout << openTime << std::endl;

    tables.reserve(count);
    for (int i = 0; i < count; ++i) {
        tables.emplace_back(cost);
    }
}

void ComputerClub::closeClub() {
    for (const auto &[clientName, tableIndex]: clientToTableMap){
        tables[tableIndex].release(closeTime);
        totalOccupiedTables--;
        clientToTableMap.erase(clientName);

        std::cout << closeTime << " 11 " << clientName << std::endl;
    }

    std::cout << closeTime << std::endl;
    for (size_t i = 0; i < tables.size(); ++i) {
        std::cout << i + 1 << " " << tables[i].revenue << " " << tables[i].totalTime << std::endl;
    }
}

void ComputerClub::handleClientArrived(const Time& time, const std::string& clientName) {
    std::cout << time << " 1 " << clientName << std::endl;

    // При нормальной работе системы такого не случиться, но перестраховаться стоит
    if (clientName.empty()){
        generateError(time, "NoName");
        return;
    }

    if (clientToTableMap.find(clientName) != clientToTableMap.end()) {
        generateError(time, "YouShallNotPass");
        return;
    }

    if (time < openTime || closeTime < time) {
        generateError(time, "NotOpenYet");
        return;
    }

    clientToTableMap[clientName] = - 1;
}

void ComputerClub::handleClientSat(const Time& time, const std::string& clientName, int tableNum) {
    std::cout << time << " 2 " << clientName << " " << tableNum<< std::endl;

    if (clientToTableMap.find(clientName) == clientToTableMap.end()) {
        generateError(time, "ClientUnknown");
        return;
    }

    if (tables[tableNum - 1].isOccupied()) {
        generateError(time, "PlaceIsBusy");
        return;
    }

    int actualTable = clientToTableMap[clientName];
    if (actualTable != -1) {
        tables[actualTable].release(time);
        totalOccupiedTables--;
    }

    tables[tableNum - 1].occupy(clientName, time);
    totalOccupiedTables++;
    clientToTableMap[clientName] = tableNum - 1;
}

void ComputerClub::handleClientWaiting(const Time& time, const std::string& clientName) {
    std::cout << time << " 3 " << clientName << " " << std::endl;

    if (clientToTableMap.find(clientName) == clientToTableMap.end()) {
        generateError(time, "ClientUnknown");
        return;
    }

    if (totalOccupiedTables != tableCount) {
        generateError(time, "ICanWaitNoLonger!");
        return;
    }

    if (queue.size() > tableCount) {
        std::cout << time << " 11 " << clientName << std::endl;
        clientToTableMap.erase(clientName);
    } else {
        queue.push(clientName);
    }
}

void ComputerClub::handleClientLeft(const Time& time, const std::string& clientName) {
    std::cout << time << " 4 " << clientName << std::endl;

    if (clientToTableMap.find(clientName) == clientToTableMap.end()) {
        generateError(time, "ClientUnknown");
        return;
    }

    int tableIndex = clientToTableMap[clientName];
    if (tableIndex != -1) {
        tables[tableIndex].release(time);
        totalOccupiedTables--;
        clientToTableMap.erase(clientName);

        if (!queue.empty()) {
            std::string nextClient = queue.front();
            queue.pop();

            tables[tableIndex].occupy(nextClient, time);
            totalOccupiedTables++;
            clientToTableMap[nextClient] = tableIndex;

            std::cout << time << " 12 " << nextClient << " " << tableIndex + 1 << std::endl;
        }
    }
}

void ComputerClub::generateError(const Time& time, const std::string& error) {
    std::cout << time << " 13 " << error << std::endl;
}