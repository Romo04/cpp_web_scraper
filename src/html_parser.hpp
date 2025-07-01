//
// Created by rpena on 7/1/25.
//
#pragma once
#include <string>
#include <vector>
#include <gumbo.h>

class HtmlParser
{
public:
    explicit HtmlParser(const std::string &html);
    bool containsKeyword(const std::string &keyword);
    int countOcurrences(const std::string &keyword) const;
    std::vector<std::string> getSnippets(const std::string &keyword, size_t contextChars = 20) const;
private:
    std::string _text;
    std::string _lowerText;
    void extractText(GumboNode *node);
    void buildLowerText();
};

