cmake_minimum_required(VERSION 3.30)
project(Laba_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Laba_2 main.cpp
        Dynamic_array.hpp
        Linked_List.hpp
        ListNode.h
        All_test.cpp
        Error.hpp
        All_test.hpp
        Sequance.hpp
        ArraySequence.hpp
        ArrayList.hpp)
find_package(GTest REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest GTest::Main)
target_include_directories(${PROJECT_NAME} PRIVATE ${GTEST_INCLUDE_DIRS})