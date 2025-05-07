cmake_minimum_required(VERSION 3.22)
project(computer_club)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(SOURCE_FILES
        src/time.cpp
        src/events.cpp
        src/table.cpp
        src/computer_club.cpp
        src/main.cpp
        src/input_parser.cpp
        )

set(HEADER_FILES
        include/mytime.h
        include/events.h
        include/table.h
        include/computer_club.h
        include/input_parser.h
        )

add_executable(computer_club_app ${SOURCE_FILES} ${HEADER_FILES})

add_library(computer_club_lib
        src/computer_club.cpp
        src/events.cpp
        src/input_parser.cpp
        src/time.cpp
        src/table.cpp
        )

target_include_directories(computer_club_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(format_tests test/format_tests.cpp)
target_link_libraries(format_tests
        computer_club_lib
        GTest::gtest_main
        )

add_executable(logic_tests test/logic_tests.cpp)
target_link_libraries(logic_tests
        computer_club_lib
        GTest::gtest_main
        )

include(GoogleTest)
gtest_discover_tests(format_tests)
gtest_discover_tests(logic_tests)