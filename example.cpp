#include "lexer.h"
#include "parser.h"
#include "token.h"
#include <fmt/format.h>
#include <fstream>
#include <sstream>

int main()
{
    std::ifstream ifs("test.json");
    std::stringstream ss;
    std::string buf;

    while (std::getline(ifs, buf))
        ss << buf << "\n";

    ifs.close();

    // Lexer lexer(ss.str());
    // Token t;

    // while ((t = lexer.next_tok()).type != TokenType::EOF_)
    // {
    //     fmt::print("{} | {}\n", (int)t.type, t.value);
    // }

    Parser parser(ss.str());
    std::unique_ptr<Node> n = parser.parse();
    fmt::print("hoo hee\n");

    return 0;
}
