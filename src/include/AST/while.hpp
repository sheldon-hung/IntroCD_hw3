#ifndef __AST_WHILE_NODE_H
#define __AST_WHILE_NODE_H

#include "AST/ast.hpp"
#include "AST/expression.hpp"
#include "AST/CompoundStatement.hpp"

class WhileNode : public AstNode
{
public:
  WhileNode(const uint32_t line, const uint32_t col,
            /* TODO: expression, compound statement */
            ExpressionNode *p_expression,
            CompoundStatementNode *p_cmpdstmt);
  ~WhileNode() = default;

  void print(int level) override;

private:
  // TODO: expression, compound statement
  ExpressionNode *expression;
  CompoundStatementNode *cmpdstmt;
};

#endif
