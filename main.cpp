#include <array>
#include <charconv>
#include <cstddef>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <string_view>

namespace
{
constexpr int Articles = 20;

bool readArticle(std::istream& input, int& article)
{
    std::string token;
    if (!(input >> token))
        return false;
    const char* end = token.data() + token.size();
    const auto result = std::from_chars(token.data(), end, article);
    return result.ec == std::errc{} && result.ptr == end && article >= 0 && article < Articles;
}

void run(std::istream& input, std::ostream& output)
{
    std::array<long long, Articles> stock{};
    std::string command;
    while (true)
    {
        output << "0 Exit | 1 Add | 2 Remove | 3 Article count | 4 Total | 5 Empty articles\n> ";
        if (!(input >> command) || command == "0")
            return;

        if (command == "4")
        {
            output << "Total: " << std::accumulate(stock.begin(), stock.end(), 0LL) << '\n';
            continue;
        }
        if (command == "5")
        {
            output << "Empty:";
            for (int article = 0; article < Articles; ++article)
                if (stock[article] == 0)
                    output << ' ' << article;
            output << '\n';
            continue;
        }
        if (command != "1" && command != "2" && command != "3")
        {
            output << "Unknown command\n";
            continue;
        }

        int article{};
        output << "Article (0-19): ";
        if (!readArticle(input, article))
        {
            output << "Invalid article\n";
            continue;
        }
        auto& count = stock[article];
        if (command == "1")
        {
            if (count < std::numeric_limits<long long>::max())
                ++count;
        }
        else if (command == "2")
        {
            if (count == 0)
                output << "Article is empty\n";
            else
                --count;
        }
        output << "Stock [" << article << "]: " << count << '\n';
    }
}
}

int main()
{
    run(std::cin, std::cout);
}
