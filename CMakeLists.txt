cmake_minimum_required(VERSION 3.10)
project(cpp_web_scraper LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Find libcurl
enable_language(C)
find_package(CURL REQUIRED)
# Find Gumbo (if installed via pkg-config)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GUMBO REQUIRED gumbo)

include_directories(
        ${CURL_INCLUDE_DIRS}
        ${GUMBO_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
)

add_executable(cpp_web_scraper
        src/main.cpp
        src/http_client.cpp
        src/html_parser.cpp
)

# Link libraries (using keyword signature)
target_link_libraries(cpp_web_scraper
        PRIVATE
        ${CURL_LIBRARIES}
        ${GUMBO_LIBRARIES}
        ${GUMBO_LDFLAGS}
)

# Compile flags for Gumbo (from pkg-config)
target_compile_options(cpp_web_scraper
        PRIVATE
        ${GUMBO_CFLAGS_OTHER}
)