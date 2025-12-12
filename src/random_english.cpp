#include <cstddef>
#include <deque>
#include <iostream>
#include <map>
#include <random>
#include <vector>

namespace
{
std::size_t random(std::size_t min, std::size_t max)
{
    auto thread_local static engine =
        std::default_random_engine{std::random_device{}()};
    return std::uniform_int_distribution<std::size_t>{min, max}(engine);
}

enum
{
    NPREF = 2,   // number of preifx words
    MAXGEN = 200 // maximum words generated
};

using Prefix = std::deque<std::string>;
std::map<Prefix, std::vector<std::string>> statetab; // preifx -> suffixes

// add: add word to suffix list, update prefix
void add(Prefix& prefix, std::string const& s)
{
    if (prefix.size() == NPREF)
    {
        statetab[prefix].push_back(s);
        prefix.pop_front();
    }

    prefix.push_back(s);
}

// build: read input words, build state table
void build(Prefix& prefix, std::istream& in)
{
    std::string buf;
    while (in >> buf)
    {
        add(prefix, buf);
    }
}

std::string NOWWORD("\n"); // cannot appear as real word

// generate: produce output, one word per line
void generate(int nwords)
{
    Prefix prefix;
    for (int i = 0; i < NPREF; i++) // reset initial prefix
    {
        add(prefix, NOWWORD);
    }

    for (int i = 0; i < nwords; i++)
    {
        std::vector<std::string>& suf = statetab[prefix];
        std::string const& w = suf[random(0, suf.size() - 1)];
        if (w == NOWWORD) { break; }
        std::cout << w << " ";
        prefix.pop_front(); // advance
        prefix.push_back(w);
    }
}
} // namespace

int main()
{
    int nwords = MAXGEN;
    Prefix prefix;                  // current input prefix
    for (int i = 0; i < NPREF; i++) // set up initial prefix
    {
        add(prefix, NOWWORD);
    }

    build(prefix, std::cin);
    add(prefix, NOWWORD);
    generate(nwords);
    std::cout << '\n';
    return 0;
}
