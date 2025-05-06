#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include "time.h"
#include "events.h"
#include <string>
#include <vector>
#include <iostream>

class InputParser {
public:
    static std::vector<std::string> splitAndValidateSpaces(const std::string& line);
    static int readAndValidateTableCount(std::istream& input);
    static std::pair<Time, Time> readAndValidateWorkingHours(std::istream& input);
    static int readAndValidateHourCost(std::istream& input);
    static std::vector<EventPtr> parseEvents(std::istream& input);
    static void validateFileOpening(std::ifstream& file);

private:
    static void validateSpaces(const std::string& line);

    static Time parseTime(const std::string &timeStr);

    static void validateEventsChronologicalOrder(const std::vector<EventPtr> &events);

    static void validateEventCommonFormat(const std::vector<std::string> &parts, int expectedParts);

    static EventPtr parseClientArrivedEvent(const std::vector<std::string> &parts);

    static EventPtr parseClientSatEvent(const std::vector<std::string> &parts);

    static EventPtr parseClientWaitingEvent(const std::vector<std::string> &parts);

    static EventPtr parseClientLeftEvent(const std::vector<std::string> &parts);

    static bool validateClientName(const std::string &nameStr);
};

#endif // INPUT_VALIDATOR_H