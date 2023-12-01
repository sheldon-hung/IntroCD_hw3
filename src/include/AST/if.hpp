#ifndef __AST_IF_NODE_H
#define __AST_IF_NODE_H

#include "AST/ast.hpp"
#include "AST/expression.hpp"
#include "AST/CompoundStatement.hpp"

class IfNode : public AstNode
{
public:
  IfNode(const uint32_t line, const uint32_t col,
         /* TODO: expression, compound statement, compound statement */
         ExpressionNode *p_expression,
         CompoundStatementNode *p_ifstmt,
         CompoundStatementNode *p_elsstmt);
  ~IfNode() = default;

  void print(int level) override;

private:
  // TODO: expression, compound statement, compound statement
  ExpressionNode *expression = NULL;
  CompoundStatementNode *ifstmt, *elsestmt = NULL;
};

#endif
