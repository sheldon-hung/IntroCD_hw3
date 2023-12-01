#include "AST/BinaryOperator.hpp"

// TODO
BinaryOperatorNode::BinaryOperatorNode(const uint32_t line, const uint32_t col,
                                       const char *const p_operator,
                                       ExpressionNode *p_leftexpression,
                                       ExpressionNode *p_rightexpression)
    : ExpressionNode{line, col}, operator_(p_operator), leftexpression(p_leftexpression), rightexpression(p_rightexpression) {}

// TODO: You may use code snippets in AstDumper.cpp
void BinaryOperatorNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("binary operator <line: %u, col: %u> %s\n", location.line, location.col, operator_.c_str());

    leftexpression->print(level + 1);
    rightexpression->print(level + 1);
}

// void BinaryOperatorNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
