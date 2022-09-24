#pragma once
#include <string>
#include <cstdint>
#include <memory>
#include <vector>

namespace jason::impl
{
    enum class NodeType
    {
        NOOP = 0,
        INT,
        STRING,
        LIST,
        MAP,
        PAIR
    };

    struct Node
    {
        NodeType type{ NodeType::NOOP };
        std::size_t line{ 0 };

        // int
        int int_value{ 0 };

        // string
        std::string string_value;

        // list
        std::vector<std::unique_ptr<Node>> list_values;

        // pair
        std::unique_ptr<Node> pair_key, pair_value;

        // map
        std::vector<std::unique_ptr<Node>> map_pairs;

        Node(NodeType type)
            : type(type) {}
    };
}
