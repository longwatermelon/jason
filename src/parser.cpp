#include "parser.h"
#include "node.h"
#include "token.h"
#include <cstdlib>
#include <stdexcept>
#include <fmt/core.h>

Parser::Parser(const std::string &contents)
    : m_lexer(contents)
{
    m_curr = m_lexer.next_tok();
}

Parser::~Parser()
{
}

void Parser::expect(TokenType type)
{
    if (m_curr.type == type)
    {
        m_prev = m_curr;
        m_curr = m_lexer.next_tok();
    }
    else
    {
        throw std::runtime_error(
            fmt::format("[Parser::expect] Error: Unexpected token of type {} on line {}.",
                    (int)m_curr.type, m_curr.line)
        );
    }
}

std::unique_ptr<Node> Parser::parse()
{
    expect(TokenType::LBRACE);
    std::unique_ptr<Node> root = std::make_unique<Node>(NodeType::COMPOUND);
    root->cpd_values.emplace_back(parse_pair());

    if (root->cpd_values[0])
    {
        while (m_curr.type != TokenType::EOF_)
        {
            if (m_curr.type != TokenType::RBRACE) expect(TokenType::COMMA);
            else break;

            std::unique_ptr<Node> expr = parse_pair();
            if (!expr) break;

            root->cpd_values.emplace_back(std::move(expr));
        }
    }
    else
    {
        root->cpd_values[0] = std::make_unique<Node>(NodeType::NOOP);
    }

    expect(TokenType::RBRACE);
    return root;
}

std::unique_ptr<Node> Parser::parse_pair()
{
    std::unique_ptr<Node> pair = std::make_unique<Node>(NodeType::PAIR);
    pair->pair_key = parse_value();
    expect(TokenType::COLON);
    pair->pair_value = parse_value();

    return pair;
}

std::unique_ptr<Node> Parser::parse_value()
{
    switch (m_curr.type)
    {
    case TokenType::INT: return parse_int();
    case TokenType::STRING: return parse_str();
    default: return nullptr;
    }
}

std::unique_ptr<Node> Parser::parse_str()
{
    std::unique_ptr<Node> n = std::make_unique<Node>(NodeType::STRING);
    n->string_value = m_curr.value;
    expect(TokenType::STRING);

    return n;
}

std::unique_ptr<Node> Parser::parse_int()
{
    std::unique_ptr<Node> n = std::make_unique<Node>(NodeType::INT);
    n->int_value = std::atoi(m_curr.value.c_str());
    expect(TokenType::INT);

    return n;
}
