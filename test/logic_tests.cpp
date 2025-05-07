#include "input_parser.h"
#include "computer_club.h"
#include <gtest/gtest.h>

class ComputerClubTest : public ::testing::Test {
protected:
    void SetUp() override {
        club = std::make_unique<ComputerClub>(3, Time(8, 0), Time(20, 0), 100);
        parser = std::make_unique<InputParser>();
    }

    void processEvents(const std::string& events) {
        std::istringstream input(events);
        auto eventPtrs = parser->parseEvents(input);
        for (auto& event : eventPtrs) {
            event->handle(*club);
        }
    }

    std::unique_ptr<ComputerClub> club;
    std::unique_ptr<InputParser> parser;
};

//TEST_F(ComputerClubTest, ClientFlow) {
//    processEvents(
//            "08:30 1 client1\n"
//            "09:00 2 client1 1\n"
//            "10:00 1 client2\n"
//            "10:30 3 client2\n"
//            "11:00 4 client1\n"
//    );
//
//    EXPECT_FALSE(club->isClientInside("client1"));
//    EXPECT_TRUE(club->isClientInside("client2"));
//    EXPECT_EQ(club->getClientTable("client2"), 1);
//}
//
//TEST_F(ComputerClubTest, MultipleClientsQueue) {
//    processEvents(
//            "08:00 1 client1\n"
//            "08:01 2 client1 1\n"
//            "08:02 1 client2\n"
//            "08:03 2 client2 2\n"
//            "08:04 1 client3\n"
//            "08:05 3 client3\n"
//            "08:06 1 client4\n"
//            "08:07 3 client4\n"
//            "08:08 4 client1\n"  // Освобождает стол 1, client3 садится
//            "08:09 4 client2\n"  // Освобождает стол 2, client4 садится
//    );
//
//    EXPECT_EQ(club->getClientTable("client3"), 1);
//    EXPECT_EQ(club->getClientTable("client4"), 2);
//}
//
//TEST_F(ComputerClubTest, ErrorHandling) {
//    std::istringstream input(
//            "08:30 1 client1\n"
//            "08:31 1 client1\n"  // Повторное прибытие
//            "08:32 2 client2 1\n" // Неизвестный клиент
//    );
//
//    auto events = parser->parseEvents(input);
//    for (auto& event : events) {
//        event->handle(*club);
//    }
//
//    EXPECT_EQ(club->getLastError(), "08:31 13 YouShallNotPass");
//}