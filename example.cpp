#include "jason.h"
#include <fmt/core.h>

int main()
{
    std::ifstream ifs("test.json");
    jason::Json json(ifs);
    fmt::print("{}\n", json.getv<std::string>("key"));

    return 0;
}
