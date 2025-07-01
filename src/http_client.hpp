//
// Created by rpena on 7/1/25.
//
#pragma once
#include <string>

class HttpClient
{
public:
    HttpClient();
    ~HttpClient();

    std::string fetch(const std::string &url);
private:
    // libcurl handle
    void *curl_handle;
    static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
};

