#include "AST/FunctionInvocation.hpp"

// TODO
FunctionInvocationNode::FunctionInvocationNode(const uint32_t line, const uint32_t col,
                                               const char *const p_name,
                                               std::vector<ExpressionNode *> *p_exprlist)
    : ExpressionNode{line, col}, name(p_name), exprlist(p_exprlist) {}

// TODO: You may use code snippets in AstDumper.cpp
void FunctionInvocationNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("function invocation <line: %u, col: %u> %s\n", location.line, location.col, name.c_str());

    if (exprlist != NULL)
    {
        for (auto node : *exprlist)
        {
            node->print(level + 1);
        }
    }
}

// void FunctionInvocationNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
