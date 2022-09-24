#include "parser.h"
#include "node.h"
#include "token.h"
#include <cstdlib>
#include <stdexcept>
#include <fmt/core.h>

using Node = jason::impl::Node;

jason::impl::Parser::Parser(const std::string &contents)
    : m_lexer(contents)
{
    m_curr = m_lexer.next_tok();
}

jason::impl::Parser::~Parser()
{
}

void jason::impl::Parser::expect(TokenType type)
{
    if (m_curr.type == type)
    {
        m_prev = m_curr;
        m_curr = m_lexer.next_tok();
    }
    else
    {
        throw std::runtime_error(
            fmt::format("[jason::impl::Parser::expect] Error: Unexpected token of type {} on line {}.",
                    (int)m_curr.type, m_curr.line)
        );
    }
}

std::unique_ptr<Node> jason::impl::Parser::parse()
{
    return parse_value();
    // expect(TokenType::LBRACE);
    // std::unique_ptr<Node> root = std::make_unique<Node>(NodeType::COMPOUND);
    // root->cpd_values.emplace_back(parse_pair());

    // if (root->cpd_values[0])
    // {
    //     while (m_curr.type != TokenType::EOF_)
    //     {
    //         if (m_curr.type != TokenType::RBRACE) expect(TokenType::COMMA);
    //         else break;

    //         std::unique_ptr<Node> expr = parse_pair();
    //         if (!expr) break;

    //         root->cpd_values.emplace_back(std::move(expr));
    //     }
    // }
    // else
    // {
    //     root->cpd_values[0] = std::make_unique<Node>(NodeType::NOOP);
    // }

    // expect(TokenType::RBRACE);
    // return root;
}

std::unique_ptr<Node> jason::impl::Parser::parse_pair()
{
    std::unique_ptr<Node> pair = std::make_unique<Node>(NodeType::PAIR);
    pair->pair_key = parse_value();
    expect(TokenType::COLON);
    pair->pair_value = parse_value();

    return pair;
}

std::unique_ptr<Node> jason::impl::Parser::parse_value()
{
    switch (m_curr.type)
    {
    case TokenType::INT: return parse_int();
    case TokenType::STRING: return parse_str();
    case TokenType::LBRACKET: return parse_list();
    case TokenType::LBRACE: return parse_map();
    default: return nullptr;
    }
}

std::unique_ptr<Node> jason::impl::Parser::parse_str()
{
    std::unique_ptr<Node> n = std::make_unique<Node>(NodeType::STRING);
    n->string_value = m_curr.value;
    expect(TokenType::STRING);

    return n;
}

std::unique_ptr<Node> jason::impl::Parser::parse_int()
{
    std::unique_ptr<Node> n = std::make_unique<Node>(NodeType::INT);
    n->int_value = std::atoi(m_curr.value.c_str());
    expect(TokenType::INT);

    return n;
}

std::unique_ptr<Node> jason::impl::Parser::parse_list()
{
    std::unique_ptr<Node> list = std::make_unique<Node>(NodeType::LIST);
    expect(TokenType::LBRACKET);

    while (m_curr.type != TokenType::RBRACKET)
    {
        list->list_values.emplace_back(parse_value());

        if (m_curr.type != TokenType::RBRACKET)
            expect(TokenType::COMMA);
    }

    expect(TokenType::RBRACKET);
    return list;
}

std::unique_ptr<Node> jason::impl::Parser::parse_map()
{
    expect(TokenType::LBRACE);
    std::unique_ptr<Node> n = std::make_unique<Node>(NodeType::MAP);

    while (m_curr.type != TokenType::RBRACE)
    {
        n->map_pairs.emplace_back(parse_pair());

        if (m_curr.type != TokenType::RBRACE)
            expect(TokenType::COMMA);
    }

    return n;
}
