#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
public:
    std::string name;
    bool isInside;
    int tableNumber;

    Client();
    Client(std::string n);
};

#endif