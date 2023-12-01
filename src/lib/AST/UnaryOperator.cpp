#include "AST/UnaryOperator.hpp"

// TODO
UnaryOperatorNode::UnaryOperatorNode(const uint32_t line, const uint32_t col,
                                     const char *const p_operator,
                                     ExpressionNode *p_expression)
    : ExpressionNode{line, col}, operator_(p_operator), expression(p_expression) {}

// TODO: You may use code snippets in AstDumper.cpp
void UnaryOperatorNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("unary operator <line: %u, col: %u> %s\n", location.line, location.col, operator_.c_str());

    expression->print(level + 1);
}

// void UnaryOperatorNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
