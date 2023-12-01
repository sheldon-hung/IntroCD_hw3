#include "AST/while.hpp"

// TODO
WhileNode::WhileNode(const uint32_t line, const uint32_t col,
                     ExpressionNode *p_expression,
                     CompoundStatementNode *p_cmpdstmt)
    : AstNode{line, col}, expression(p_expression), cmpdstmt(p_cmpdstmt) {}

// TODO: You may use code snippets in AstDumper.cpp
void WhileNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("while statement <line: %u, col: %u>\n", location.line, location.col);

    expression->print(level + 1);

    cmpdstmt->print(level + 1);
}

// void WhileNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
