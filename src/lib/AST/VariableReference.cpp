#include "AST/VariableReference.hpp"

// TODO
VariableReferenceNode::VariableReferenceNode(const uint32_t line, const uint32_t col,
                                             const char *const p_name)
    : ExpressionNode{line, col}, name(p_name) {}

// TODO
VariableReferenceNode::VariableReferenceNode(const uint32_t line, const uint32_t col,
                                             const char *const p_name,
                                             std::vector<ExpressionNode *> *p_exprlist)
    : ExpressionNode{line, col}, name(p_name), exprlist(p_exprlist) {}

// TODO: You may use code snippets in AstDumper.cpp
void VariableReferenceNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("variable reference <line: %u, col: %u> %s\n", location.line, location.col, name.c_str());

    if (exprlist != NULL)
    {
        for (auto node : *exprlist)
        {
            node->print(level + 1);
        }
    }
}

// void VariableReferenceNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
