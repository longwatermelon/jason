#pragma once
#include <string>
#include <cstdint>
#include <memory>
#include <vector>

enum class NodeType
{
    NOOP = 0,
    INT,
    STRING,
    PAIR,
    COMPOUND
};

struct Node
{
    NodeType type{ NodeType::NOOP };
    std::size_t line{ 0 };

    // int
    int int_value{ 0 };

    // string
    std::string string_value;

    // pair
    std::unique_ptr<Node> pair_key, pair_value;

    // compound
    std::vector<std::unique_ptr<Node>> cpd_values;

    Node(NodeType type)
        : type(type) {}
};