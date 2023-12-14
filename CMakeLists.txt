cmake_minimum_required(VERSION 3.26)
project(AsyncTest)

set(CMAKE_CXX_STANDARD 20)

add_executable(AsyncTest main.cpp
        authentication_system.h authentication_system.cpp
        logger/logger.h logger/logger.cpp
        transaction.h transaction.h
        transaction.cpp
        logger/authentication_logger.h
        logger/authentication_logger.cpp
        user.h
)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(AsyncTest PRIVATE nlohmann_json::nlohmann_json)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/users.json
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/log.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})