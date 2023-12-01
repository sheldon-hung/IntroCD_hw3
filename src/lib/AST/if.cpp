#include "AST/if.hpp"

// TODO
IfNode::IfNode(const uint32_t line, const uint32_t col,
               ExpressionNode *p_expression,
               CompoundStatementNode *p_ifstmt,
               CompoundStatementNode *p_elsestmt)
    : AstNode{line, col}, expression(p_expression), ifstmt(p_ifstmt), elsestmt(p_elsestmt) {}

// TODO: You may use code snippets in AstDumper.cpp
void IfNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("if statement <line: %u, col: %u>\n", location.line, location.col);

    expression->print(level + 1);

    ifstmt->print(level + 1);

    if (elsestmt != NULL)
    {
        elsestmt->print(level + 1);
    }
}

// void IfNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
