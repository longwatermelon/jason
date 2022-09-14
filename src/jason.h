#pragma once
#include "parser.h"
#include <fstream>

namespace jason
{
    class Json
    {
    public:
        Json(std::ifstream &ifs);
        Json(const std::string &contents);
        ~Json();

        const impl::Node &get(const std::string &key);

    private:
        std::vector<std::unique_ptr<impl::Node>> m_pairs;
    };
}
