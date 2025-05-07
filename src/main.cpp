#include "../include/computer_club.h"
#include "../include/input_parser.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    try {
        std::ifstream inputFile(argv[1]);
        InputParser::validateFileOpening(inputFile);

        int tableCount = InputParser::parseTableCount(inputFile);
        auto [openTime, closeTime] = InputParser::parseWorkingHours(inputFile);
        int hourCost = InputParser::parseHourCost(inputFile);
        auto events = InputParser::parseEvents(inputFile);

        ComputerClub club(tableCount, openTime, closeTime, hourCost, std::cout);

        for (const auto& event : events) {
            event->handle(club);
        }

        club.closeClub();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}