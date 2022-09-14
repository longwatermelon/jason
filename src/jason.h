#pragma once
#include "node.h"
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

        const impl::Node &get(const std::string &key) const;

        template <typename T>
        const T &getv(const std::string &key) const
        {
            const impl::Node &n = get(key);

            if constexpr (std::is_same_v<T, int>) return n.int_value;
            else if constexpr (std::is_same_v<T, std::string>) return n.string_value;
            else
            {
                throw std::runtime_error("[jason::Json::getv] Colossal failure");
            }
        }

    private:
        std::vector<std::unique_ptr<impl::Node>> m_pairs;
    };
}
