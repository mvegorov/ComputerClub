#include <utility>

#include "../include/client.h"

Client::Client() : isInside(false), tableNumber(-1) {}
Client::Client(std::string n) : name(std::move(n)), isInside(false), tableNumber(-1) {}