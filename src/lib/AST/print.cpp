#include "AST/print.hpp"

#include <cstdio>

// TODO
PrintNode::PrintNode(const uint32_t line, const uint32_t col,
                     ExpressionNode *p_expression)
    : AstNode{line, col}, expression(p_expression) {}

// TODO: You may use code snippets in AstDumper.cpp
void PrintNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("print statement <line: %u, col: %u>\n", location.line, location.col);

    expression->print(level + 1);
}

// void PrintNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
