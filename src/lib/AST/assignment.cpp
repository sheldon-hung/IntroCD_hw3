#include "AST/assignment.hpp"

// TODO
AssignmentNode::AssignmentNode(const uint32_t line, const uint32_t col,
                               VariableReferenceNode *p_varref,
                               ExpressionNode *p_expression)
    : AstNode{line, col}, varref(p_varref), expression(p_expression) {}

// TODO: You may use code snippets in AstDumper.cpp
void AssignmentNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("assignment statement <line: %u, col: %u>\n", location.line, location.col);

    varref->print(level + 1);

    expression->print(level + 1);
}

// void AssignmentNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
