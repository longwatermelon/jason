#include "jason.h"
#include "parser.h"
#include <sstream>
#include <fmt/core.h>

jason::Json::Json(std::ifstream &ifs)
{
    std::stringstream ss;
    std::string buf;

    while (std::getline(ifs, buf))
        ss << buf << "\n";

    impl::Parser parser(ss.str());
    std::unique_ptr<impl::Node> root = parser.parse();

    m_pairs = std::move(root->cpd_values);
}

jason::Json::Json(const std::string &contents)
{
    impl::Parser parser(contents);
    std::unique_ptr<impl::Node> root = parser.parse();

    m_pairs = std::move(root->cpd_values);
}

jason::Json::~Json()
{
}

const jason::impl::Node &jason::Json::get(const std::string &key) const
{
    for (const auto &p : m_pairs)
    {
        if (p->pair_key->string_value == key)
            return *p->pair_value;
    }

    throw std::runtime_error(
        fmt::format("[jason::Json::get] Error: {} is not a valid key.",
                    key)
    );
}
