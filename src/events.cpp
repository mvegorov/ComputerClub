#include "../include/events.h"
#include "../include/computer_club.h"
#include <utility>

ClientArrivedEvent::ClientArrivedEvent(const Time& time, std::string clientName)
        : Event(time, 1), clientName_(std::move(clientName)) {}

void ClientArrivedEvent::handle(ComputerClub& club) const {
    club.handleClientArrived(time_, clientName_);
}

ClientSatEvent::ClientSatEvent(const Time& time, std::string  clientName, int tableNum)
        : Event(time, 2), clientName_(std::move(clientName)), tableNum_(tableNum) {}

void ClientSatEvent::handle(ComputerClub& club) const {
    club.handleClientSat(time_, clientName_, tableNum_);
}


ClientWaitingEvent::ClientWaitingEvent(const Time& time, std::string  clientName)
        : Event(time, 3), clientName_(std::move(clientName)) {}

void ClientWaitingEvent::handle(ComputerClub& club) const {
    club.handleClientWaiting(time_, clientName_);
}

ClientLeftEvent::ClientLeftEvent(const Time& time, std::string clientName)
        : Event(time, 4), clientName_(std::move(clientName)) {}

void ClientLeftEvent::handle(ComputerClub &club) const {
    club.handleClientLeft(time_, clientName_);
}
