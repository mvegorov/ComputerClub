#include "input_parser.h"
#include "computer_club.h"
#include <gtest/gtest.h>

TEST(InputParserTest, ValidEventsParsing) {
    std::istringstream input(
            "08:30 1 client1\n"
            "09:00 2 client1 1\n"
            "10:00 3 client2\n"
            "11:00 4 client1\n"
    );

    InputParser parser;
    auto events = InputParser::parseEvents(input);
    ASSERT_EQ(events.size(), 4);
    EXPECT_EQ(events[0]->id(), 1);
    EXPECT_EQ(events[1]->id(), 2);
    EXPECT_EQ(events[2]->id(), 3);
    EXPECT_EQ(events[3]->id(), 4);
}

TEST(InputParserTest, InvalidEventFormat) {
    std::istringstream input(
            "08:30 1 client1\n"
            "09:00 2 client1\n"  // Не хватает номера стола
            "10:00 3 client2\n"
    );

    InputParser parser;
    EXPECT_THROW(parser.parseEvents(input), std::runtime_error);
}

TEST(InputParserTest, EmptyInput) {
    std::istringstream input("");
    InputParser parser;
    auto events = InputParser::parseEvents(input);
    EXPECT_TRUE(events.empty());
}

TEST(InputParserTest, EventsWithSpaces) {
    std::istringstream input(
            "08:30 1  client1  \n"  // Лишние пробелы
            "09:00 2 client1 1\n"
    );

    InputParser parser;
    auto events = InputParser::parseEvents(input);
    ASSERT_EQ(events.size(), 2);
    EXPECT_NO_THROW({
        dynamic_cast<ClientArrivedEvent&>(*events[0]);
        dynamic_cast<ClientSatEvent&>(*events[1]);
    });
}