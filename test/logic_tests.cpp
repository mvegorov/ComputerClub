#include "input_parser.h"
#include "computer_club.h"
#include <gtest/gtest.h>
#include <sstream>

class ComputerClubTest : public ::testing::Test {
protected:
    void SetUp() override {
        output_stream = std::make_shared<std::ostringstream>();
        club = std::make_unique<ComputerClub>(3, Time(8, 0), Time(20, 0), 100, *output_stream);
        parser = std::make_unique<InputParser>();
    }

    void processEvents(const std::string& events) {
        std::istringstream input(events);
        auto eventPtrs = parser->parseEvents(input);
        for (auto& event : eventPtrs) {
            event->handle(*club);
        }
    }

    std::shared_ptr<std::ostringstream> output_stream;
    std::unique_ptr<ComputerClub> club;
    std::unique_ptr<InputParser> parser;
};

TEST_F(ComputerClubTest, ClientCannotWaitWhenTablesAvailable) {
    processEvents(
            "08:00 1 client1\n"
            "08:01 3 client1\n"
    );

    std::string output = output_stream->str();
    EXPECT_NE(output.find("08:01 13 ICanWaitNoLonger!"), std::string::npos);

    EXPECT_EQ(club->getClientTable("client1"), -1);
}

TEST_F(ComputerClubTest, ClientWaitsWhenAllTablesOccupied) {
    processEvents(
            "08:00 1 client1\n"
            "08:01 2 client1 1\n"  // Стол 1 занят
            "08:02 1 client2\n"
            "08:03 2 client2 2\n"  // Стол 2 занят
            "08:04 1 client3\n"
            "08:05 2 client3 3\n"  // Стол 3 занят
            "08:06 1 client4\n"
            "08:07 3 client4\n"    // Все столы заняты - встаёт в очередь
    );

    std::string output = output_stream->str();
    EXPECT_EQ(output.find("13 ICanWaitNoLonger!"), std::string::npos);
    EXPECT_EQ(club->getClientTable("client4"), -1);
}

TEST_F(ComputerClubTest, QueueAutoAssignment) {
    processEvents(
            "08:00 1 client1\n"
            "08:01 2 client1 1\n"  // Стол 1 занят
            "08:02 1 client2\n"
            "08:03 2 client2 2\n"  // Стол 2 занят
            "08:04 1 client3\n"
            "08:04 2 client3 3\n"  // Стол 3 занят
            "08:04 1 client4\n"
            "08:05 3 client4\n"    // Встаёт в очередь
            "08:06 4 client1\n"    // Освобождает стол 1
    );

    std::string output = output_stream->str();
    EXPECT_NE(output.find("08:06 12 client4 1"), std::string::npos);
    EXPECT_EQ(club->getClientTable("client4"), 1);
}

// Очередь не превышает количество столов
TEST_F(ComputerClubTest, QueueSizeLimit) {
    processEvents(
            "08:00 1 client1\n"
            "08:01 2 client1 1\n"
            "08:02 1 client2\n"
            "08:03 2 client2 2\n"
            "08:04 1 client3\n"
            "08:05 2 client3 3\n"  // Все столы заняты

            // Первые 3 клиента в очереди
            "08:06 1 client4\n"
            "08:07 3 client4\n"
            "08:08 1 client5\n"
            "08:09 3 client5\n"
            "08:10 1 client6\n"
            "08:11 3 client6\n"
            "08:12 1 client7\n"
            "08:13 3 client7\n"

            // Этот клиент не помещается в очередь
            "08:14 1 client8\n"
            "08:15 3 client8\n"
    );

    std::string output = output_stream->str();
    EXPECT_NE(output.find("08:15 11 client8"), std::string::npos);
}