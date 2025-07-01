// #include <iostream>
// #include "http_client.hpp"
// #include "html_parser.hpp"
//
// int main(int argc, char** argv)
// {
//     if (argc != 3)
//     {
//         std::cerr << "Usage: " << argv[0] << " <URL> <Keyword>" << std::endl;
//
//         return 1;
//     }
//
//     std::string url = argv[1];
//     std::string keyword = argv[2];
//
//     try
//     {
//         HttpClient client;
//         std::string html = client.fetch(url);
//
//         HtmlParser parser(html);
//         bool found = parser.containsKeyword(keyword);
//         int total = parser.countOcurrences(keyword);
//         std::cout << (found ? "Found" : "Not Found") << " " << '\n';
//         std::cout << "Keyword '" << keyword << "' found " << total << " times" << '\n';
//
//         auto snippets = parser.getSnippets(keyword, 20);
//         for (const auto &snip : snippets)
//         {
//             std::cout << "..." << snip << "... " << '\n';
//         }
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "Error: " << e.what() << " " << std::endl;
//         return 1;
//     }
//
//     return 0;
// }
