cmake_minimum_required(VERSION 3.10)
project(cpp_web_scraper LANGUAGES CXX)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)

# Find libcurl
enable_language(C)
find_package(CURL REQUIRED)
# Find Gumbo (if installed via pkg-config)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GUMBO REQUIRED gumbo)

add_executable(cpp_web_scraper
        src/main.cpp
        src/http_client.cpp
        src/html_parser.cpp
        src/mainwindow.cpp
        src/mainwindow.hpp
        src/qt_main.cpp
        src/mainwindow.ui
)

# Link libraries (using keyword signature)
target_link_libraries(cpp_web_scraper
        PRIVATE
        Qt6::Widgets
        ${CURL_LIBRARIES}
        ${GUMBO_LIBRARIES}
        ${GUMBO_LDFLAGS}
)

include_directories(
        ${CURL_INCLUDE_DIRS}
        ${GUMBO_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
)

# Compile flags for Gumbo (from pkg-config)
target_compile_options(cpp_web_scraper
        PRIVATE
        ${GUMBO_CFLAGS_OTHER}
)