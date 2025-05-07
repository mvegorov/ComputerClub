#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include "mytime.h"
#include "events.h"
#include <string>
#include <vector>
#include <iostream>

class InputParser {
public:
    static std::vector<std::string> splitAndValidateSpaces(const std::string& line);
    static int parseTableCount(std::istream& input);
    static std::pair<Time, Time> parseWorkingHours(std::istream& input);
    static int parseHourCost(std::istream& input);
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