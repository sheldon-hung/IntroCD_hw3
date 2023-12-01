#include "AST/return.hpp"

#include <cstdio>

// TODO
ReturnNode::ReturnNode(const uint32_t line, const uint32_t col,
                       ExpressionNode *p_expression)
    : AstNode{line, col}, expression(p_expression) {}

// TODO: You may use code snippets in AstDumper.cpp
void ReturnNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("return statement <line: %u, col: %u>\n", location.line, location.col);

    expression->print(level + 1);
}

// void ReturnNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
