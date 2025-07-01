//
// Created by rpena on 7/1/25.
//

#include "html_parser.hpp"
#include <gumbo.h>
#include <algorithm>

HtmlParser::HtmlParser(const std::string &html)
{
    GumboOutput *output = gumbo_parse(html.c_str());
    extractText(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    buildLowerText();
}

void HtmlParser::buildLowerText()
{
    _lowerText = _text;
    std::transform(_lowerText.begin(), _lowerText.end(), _lowerText.begin(), ::tolower);
}

bool HtmlParser::containsKeyword(const std::string &keyword)
{
    auto lower = _text;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    auto key = keyword;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    return lower.find(key) != std::string::npos;
}

int HtmlParser::countOcurrences(const std::string &keyword) const
{
    std::string key = keyword;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    int count = 0;
    for (size_t pos = 0; (pos = _lowerText.find(key, pos)) != std::string::npos; pos += key.length())
    {
        ++count;
    }

    return count;
}

std::vector<std::string> HtmlParser::getSnippets(const std::string &keyword, size_t contextChars) const
{
    std::string key = keyword;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    std::vector<std::string> snippets;
    size_t keyLen = key.length();

    for (size_t pos = 0; (pos = _lowerText.find(key, pos)) != std::string::npos; pos += keyLen)
    {
        size_t start = (pos > contextChars) ? pos - contextChars : 0;
        size_t end = std::min(pos + keyLen + contextChars, _text.length());
        snippets.emplace_back(_text.substr(start, end - start));
    }

    return snippets;
}



void HtmlParser::extractText(GumboNode *node)
{
    if (node->type == GUMBO_NODE_TEXT)
    {
        _text += node->v.text.text;
        _text += ' ';
    }
    else if (node->type == GUMBO_NODE_ELEMENT || node->type == GUMBO_NODE_DOCUMENT)
    {
        GumboVector *children = &node->v.element.children;
        for (size_t i = 0; i < children->length; ++i)
        {
            extractText(static_cast<GumboNode *>(children->data[i]));
        }
    }
}

