cmake_minimum_required(VERSION 3.31)
project(cpp_web_scraper)

set(CMAKE_CXX_STANDARD 20)

# Find libcurl
find_package(CURL REQUIRED)
# Find Gumbo (if installed via pkg-config)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GUMBO REQUIRED gumbo)

include_directories(
        ${CURL_INCLUDE_DIRS}
        ${GUMBO_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
)

add_executable(cpp_web_scraper src/main.cpp
        src/http_client.cpp
        src/http_client.hpp
        src/html_parser.cpp
        src/html_parser.hpp)

target_link_libraries(cpp_web_scraper
        ${CURL_LIBRARIES}
        ${GUMBO_LIBRARIES}
)

# pkg-config linking flags
target_compile_options(cpp_web_scraper PRIVATE ${GUMBO_CFLAGS_OTHER})
target_link_libraries(cpp_web_scraper PRIVATE ${GUMBO_LDFLAGS})
