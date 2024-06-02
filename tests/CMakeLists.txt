include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE TEST_SOURCES
        ${CMAKE_SOURCE_DIR}/src/Repository/*.cpp
        ${CMAKE_SOURCE_DIR}/src/Handlers/*.cpp
        ${CMAKE_SOURCE_DIR}/tests/*.cpp
        ${CMAKE_SOURCE_DIR}/tests/*.h
)

add_executable(Tests ${TEST_SOURCES} BadRewuestHandlersTests.cpp)

target_link_libraries(Tests GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

target_include_directories(Tests PUBLIC ${PROJECT_SOURCE_DIR}  ${PROJECT_SOURCE_DIR}/tests spdlog::spdlog)

target_include_directories(Tests PRIVATE
        ${spdlog_SOURCE_DIR}/include
)

include(GoogleTest)
gtest_discover_tests(Tests)
