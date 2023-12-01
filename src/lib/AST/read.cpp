#include "AST/read.hpp"

// TODO
ReadNode::ReadNode(const uint32_t line, const uint32_t col,
                   VariableReferenceNode *p_varref)
    : AstNode{line, col}, varref(p_varref) {}

// TODO: You may use code snippets in AstDumper.cpp
void ReadNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("read statement <line: %u, col: %u>\n", location.line, location.col);

    varref->print(level + 1);
}

// void ReadNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
