cmake_minimum_required(VERSION 3.25)
project(IT_School)

include(FetchContent)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.10.0
)
FetchContent_MakeAvailable(spdlog)

set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
        boost
        URL https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.bz2
)
FetchContent_GetProperties(boost)
if(NOT boost_POPULATED)
    FetchContent_Populate(boost)
    set(BOOST_ROOT ${boost_SOURCE_DIR})
endif()

find_package(Boost 1.76.0 REQUIRED)

include_directories(include ${Boost_INCLUDE_DIRS})

add_executable(IT_School
        src/main.cpp
        src/Repository/Repository.cpp src/Repository/Repository.h
        src/Handlers/Handlers.cpp src/Handlers/Handlers.h
        src/Handlers/CountHandler.cpp
        src/Handlers/DeleteHandler.cpp
        src/Handlers/DumpHandler.cpp
        src/Handlers/GetHandler.cpp
        src/Handlers/PutHandler.cpp
        src/Server/TCPServer.cpp src/Server/TCPServer.h
        src/Server/TCPSession.cpp src/Server/TCPSession.h
        src/Settings.h
        src/Repository/IRepository.h)

target_link_libraries(IT_School ${Boost_LIBRARIES} ws2_32 mswsock spdlog::spdlog)

enable_testing()
add_subdirectory(tests)