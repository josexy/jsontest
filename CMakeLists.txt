cmake_minimum_required(VERSION 3.17)
project(jsontest)

set(CMAKE_CXX_STANDARD 17)

add_executable(jsontest
        json/src/JsonConvert.cpp
        json/src/JsonArray.cpp
        json/src/JsonObject.cpp
        json/src/JsonParser.cpp
        json/src/JsonDocument.cpp
        main.cpp
        )