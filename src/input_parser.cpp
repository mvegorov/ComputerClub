#include "../include/input_parser.h"
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

void InputParser::validateFileOpening(std::ifstream& file) {
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
}

void InputParser::validateSpaces(const string &line) {
    if (line.empty()) return;

    bool isSpaceAllowed = false;
    for (char c: line) {
        if (c == ' ') {
            if (!isSpaceAllowed) {
                throw runtime_error("Invalid spacing in line: " + line);
            }
            isSpaceAllowed = false;
        } else {
            if (isspace(c)){
                throw runtime_error("Use whitespace: " + line);
            }
            isSpaceAllowed = true;
        }
    }

    if (!isSpaceAllowed) {
        throw runtime_error("Trailing space in line: " + line);
    }
}

vector<string> InputParser::splitAndValidateSpaces(const string& line) {
    validateSpaces(line);

    vector<string> parts;
    istringstream iss(line);
    string part;

    while (iss >> part) {
        parts.emplace_back(std::move(part));
    }

    return parts;
}

int InputParser::parseTableCount(istream& input) {
    string line;
    if (!getline(input, line)) {
        throw runtime_error("Expected number of tables");
    }

    auto parts = splitAndValidateSpaces(line);
    if (parts.size() != 1) {
        throw runtime_error("Expected single number for table count: " + line);
    }

    try {
        int tableCount = stoi(parts[0]);
        if (tableCount <= 0) {
            throw runtime_error("Number of tables must be positive: " + line);
        }
        return tableCount;
    } catch (...) {
        throw runtime_error("Invalid number of tables: " + line);
    }
}

Time InputParser::parseTime(const std::string& timeStr) {
    size_t colonPos = timeStr.find(':');
    int h = std::stoi(timeStr.substr(0, colonPos));
    int m = std::stoi(timeStr.substr(colonPos + 1));

    if (timeStr.length() != 5 || timeStr[2] != ':') {
        throw runtime_error("Wrong time format: " + timeStr);
    }

    int hours = stoi(timeStr.substr(0, 2));
    int minutes = stoi(timeStr.substr(3, 2));
    if (hours < 0 || hours >= 24 || minutes < 0 || minutes >= 60){
        throw runtime_error("Wrong time format: " + timeStr);
    }

    return {h, m};
}

bool InputParser::validateClientName(const std::string& nameStr) {
    if (nameStr.empty()){
        return false;
    }

    for (auto c: nameStr){
        if (!isalnum(c) && c != '_' && c != '-'){
            return false;
        }
    }

    return true;
}

pair<Time, Time> InputParser::parseWorkingHours(istream& input) {
    string line;
    if (!getline(input, line)) {
        throw runtime_error("Expected opening and closing time");
    }

    auto parts = splitAndValidateSpaces(line);
    if (parts.size() != 2) {
        throw runtime_error("Expected two time values: " + line);
    }

    const auto& openStr = parts[0];
    const auto& closeStr = parts[1];

    Time openTime, closeTime;
    try{
        openTime = InputParser::parseTime(openStr);
        closeTime = InputParser::parseTime(closeStr);
    }catch (...){
        throw runtime_error("Can't parse time: " + line);
    }

    if (closeTime <= openTime) {
        throw runtime_error("Closing time must be after opening time: " + line);
    }

    return {openTime, closeTime};
}

int InputParser::parseHourCost(istream& input) {
    string line;
    if (!getline(input, line)) {
        throw runtime_error("Expected hour cost");
    }

    auto parts = splitAndValidateSpaces(line);
    if (parts.size() != 1) {
        throw runtime_error("Expected single number for hour cost: " + line);
    }

    try {
        int hourCost = stoi(parts[0]);
        if (hourCost <= 0) {
            throw runtime_error("Hour cost must be positive: " + line);
        }
        return hourCost;
    } catch (...) {
        throw runtime_error("Invalid hour cost: " + line);
    }
}

vector<EventPtr> InputParser::parseEvents(istream &input) {
    vector<EventPtr> events;
    string line;

    while (getline(input, line)) {
        if (line.empty()) {
            throw runtime_error("Expected event");
        }

        auto parts = splitAndValidateSpaces(line);

        int eventId;
        try {
            eventId = std::stoi(parts[1]);
        } catch (...) {
            throw std::runtime_error("Invalid event ID format: " + line);
        }

        try{
            switch (eventId) {
                case 1:
                    events.emplace_back(InputParser::parseClientArrivedEvent(parts));
                    break;
                case 2:
                    events.emplace_back(InputParser::parseClientSatEvent(parts));
                    break;
                case 3:
                    events.emplace_back(InputParser::parseClientWaitingEvent(parts));
                    break;
                case 4:
                    events.emplace_back(InputParser::parseClientLeftEvent(parts));
                    break;
                default:
                    throw std::runtime_error("Unknown event ID: " + std::to_string(eventId));
            }
        }catch (const std::exception& e){
            throw std::runtime_error(std::string(e.what()) + "\nIn line: " + line);
        }
    }

    validateEventsChronologicalOrder(events);
    return events;
}

void InputParser::validateEventCommonFormat(const std::vector<std::string>& parts, int expectedParts) {
    if (parts.size() != expectedParts) {
        std::ostringstream oss;
        oss << "Invalid number of parts in event: must be "
            << expectedParts << ", found " << parts.size();
        throw std::runtime_error(oss.str());
    }

    if (parts[1].length() != 1 || parts[1][0] < '1' || parts[1][0] > '4') {
        throw std::runtime_error("Invalid event ID");
    }
}

EventPtr InputParser::parseClientArrivedEvent(const std::vector<std::string>& parts) {
    InputParser::validateEventCommonFormat(parts, 3);

    Time time = parseTime(parts[0]);
    const std::string& clientName = parts[2];

    if (!validateClientName(clientName)) {
        throw std::runtime_error("Invalid client name");
    }

    return std::make_unique<ClientArrivedEvent>(time, clientName);
}

EventPtr InputParser::parseClientSatEvent(const std::vector<std::string>& parts) {
    InputParser::validateEventCommonFormat(parts, 4);

    Time time = parseTime(parts[0]);
    const std::string& clientName = parts[2];
    int tableNumber;

    if (!validateClientName(clientName)) {
        throw std::runtime_error("Invalid client name");
    }

    try {
        tableNumber = std::stoi(parts[3]);
    } catch (...) {
        throw std::runtime_error("Invalid table number format");
    }
    if (tableNumber <= 0) {
        throw std::runtime_error("Table number must be positive");
    }

    return std::make_unique<ClientSatEvent>(time, clientName, tableNumber);
}

EventPtr InputParser::parseClientWaitingEvent(const std::vector<std::string>& parts) {
    if (parts.size() != 3) {
        throw std::runtime_error("ClientWaiting event requires exactly 3 parts");
    }

    Time time = parseTime(parts[0]);
    const std::string& clientName = parts[2];

    if (!validateClientName(clientName)) {
        throw std::runtime_error("Invalid client name");
    }

    return std::make_unique<ClientWaitingEvent>(time, clientName);
}

EventPtr InputParser::parseClientLeftEvent(const std::vector<std::string>& parts) {
    if (parts.size() != 3) {
        throw std::runtime_error("ClientLeft event requires exactly 3 parts");
    }

    Time time = parseTime(parts[0]);
    const std::string& clientName = parts[2];

    if (!validateClientName(clientName)) {
        throw std::runtime_error("Invalid client name");
    }

    return std::make_unique<ClientLeftEvent>(time, clientName);
}

void InputParser::validateEventsChronologicalOrder(const vector<EventPtr>& events) {
    for (size_t i = 1; i < events.size(); ++i) {
        if (events[i]->time() < events[i-1]->time()) {
            ostringstream oss;
            oss << "Events not in chronological order: " << events[i-1]->time() << " -> " << events[i]->time();
            throw runtime_error(oss.str());
        }
    }
}
