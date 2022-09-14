#include "lexer.h"
#include "token.h"
#include <fmt/format.h>
#include <stdexcept>

jason::impl::Lexer::Lexer(const std::string &contents)
    : m_contents(contents)
{
    m_ch = m_contents[0];
}

jason::impl::Lexer::~Lexer()
{
}

void jason::impl::Lexer::advance()
{
    if (m_index < m_contents.size())
        m_ch = m_contents[++m_index];
}

std::string jason::impl::Lexer::collect_str()
{
    std::string res;
    advance();

    while (m_ch != '"')
    {
        res += m_ch;
        advance();
    }

    advance();

    return res;
}

std::string jason::impl::Lexer::collect_int()
{
    std::string res;

    while (std::isdigit(m_ch))
    {
        res += m_ch;
        advance();
    }

    return res;
}

Token jason::impl::Lexer::next_tok()
{
    auto adv = [&](TokenType type, std::string c){
        advance();
        return Token(type, c, m_line);
    };

    while (m_index < m_contents.size() - 1)
    {
        while (std::isspace(m_ch) && m_ch != '\n')
            advance();

        if (std::isdigit(m_ch))
            return Token(TokenType::INT, collect_int(), m_line);

        if (m_ch == '"')
            return Token(TokenType::STRING, collect_str(), m_line);

        switch (m_ch)
        {
        case '{': return adv(TokenType::LBRACE, "{");
        case '}': return adv(TokenType::RBRACE, "}");
        case ':': return adv(TokenType::COLON, ":");
        case ',': return adv(TokenType::COMMA, ",");
        case '\n':
            ++m_line;
            advance();
            break;
        default:
            throw std::runtime_error(
                fmt::format("[jason::impl::Lexer::next_tok] Unexpected character '{}' on line {}.", m_ch, m_line));
        }
    }

    return Token(TokenType::EOF_, "", 0);
}
