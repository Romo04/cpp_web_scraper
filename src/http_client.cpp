//
// Created by rpena on 7/1/25.
//

#include "http_client.hpp"

#include <curl/curl.h>
#include <stdexcept>

HttpClient::HttpClient()
{
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 10L);
}

HttpClient::~HttpClient()
{
    if (curl_handle)
    {
        curl_easy_cleanup(static_cast<CURL *>(curl_handle));
    }
}

size_t HttpClient::write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    auto *response = static_cast<std::string *>(userdata);
    response->append(ptr, size * nmemb);

    return size * nmemb;
}

std::string HttpClient::fetch(const std::string &url)
{
    std::string response;
    curl_easy_setopt(static_cast<CURL *>(curl_handle), CURLOPT_URL, url.c_str());
    curl_easy_setopt(static_cast<CURL *>(curl_handle), CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(static_cast<CURL *>(curl_handle), CURLOPT_WRITEDATA, &response);
    CURLcode code = curl_easy_perform(static_cast<CURL *>(curl_handle));

    if (code != CURLE_OK)
    {
        throw std::runtime_error(curl_easy_strerror(code));
    }

    return response;
}

