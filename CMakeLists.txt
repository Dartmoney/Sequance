cmake_minimum_required(VERSION 3.30)
project(Laba3)
set(CMAKE_TOOLCHAIN_FILE "C:/Users/islam/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64/bin")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
set(CMAKE_PREFIX_PATH "C:/Users/islam/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic/share/gtest")

find_package(GTest CONFIG REQUIRED)
add_executable(Laba3 main.cpp
        mainwindow.cpp
        Dynamic_array.hpp
        Linked_List.hpp
        ListNode.h)
target_link_libraries(Laba3
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

add_executable(Laba3Test main.cpp
        Dynamic_array.hpp
        Linked_List.hpp
        ListNode.h
        Error.hpp
        All_test.hpp
        Sequance.hpp
        ArraySequence.hpp
        ArrayList.hpp
)

# 6. Исправленные цели GTest
target_link_libraries(Laba3Test PRIVATE
        GTest::gtest       # Правильное имя цели
        GTest::gtest_main  # Для main()
        GTest::gmock
        GTest::gmock_main
)
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
