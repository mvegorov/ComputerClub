#ifndef EVENT_H
#define EVENT_H

#include "mytime.h"
#include <string>
#include <memory>
#include <iostream>

class ComputerClub;

class Event {
public:
    Event(const Time& time, int id) : time_(time), id_(id) {}
    virtual ~Event() = default;

    virtual void handle(ComputerClub& club) const = 0;

    const Time& time() const { return time_; }
    int id() const { return id_; }

protected:
    Time time_;
    int id_;
};

using EventPtr = std::unique_ptr<Event>;

std::ostream& operator<<(std::ostream& os, const Event& event);

class ClientArrivedEvent : public Event {
public:
    ClientArrivedEvent(const Time& time, std::string clientName);

    void handle(ComputerClub& club) const override;

private:
    std::string clientName_;
};

class ClientSatEvent : public Event {
public:
    ClientSatEvent(const Time& time, std::string clientName, int tableNum);

    void handle(ComputerClub& club) const override;

private:
    std::string clientName_;
    int tableNum_;
};

class ClientWaitingEvent : public Event {
public:
    ClientWaitingEvent(const Time& time, std::string clientName);

    void handle(ComputerClub& club) const override;

private:
    std::string clientName_;
};

class ClientLeftEvent : public Event {
public:
    ClientLeftEvent(const Time& time, std::string clientName);

    void handle(ComputerClub& club) const override;

private:
    std::string clientName_;
};

#endif // EVENT_H