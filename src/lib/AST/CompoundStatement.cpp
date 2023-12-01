#include "AST/CompoundStatement.hpp"

// TODO
CompoundStatementNode::CompoundStatementNode(const uint32_t line, const uint32_t col,
                                             std::vector<DeclNode *> *p_decllist,
                                             std::vector<AstNode *> *p_stmtlist)
    : AstNode{line, col}, decllist(p_decllist), stmtlist(p_stmtlist) {}

// TODO: You may use code snippets in AstDumper.cpp
void CompoundStatementNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("compound statement <line: %u, col: %u>\n", location.line, location.col);

    if (decllist != NULL)
    {
        for (auto node : *decllist)
        {
            node->print(level + 1);
        }
    }

    if (stmtlist != NULL)
    {
        for (auto node : *stmtlist)
        {
            node->print(level + 1);
        }
    }
}

// void CompoundStatementNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
