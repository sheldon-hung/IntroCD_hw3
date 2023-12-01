#ifndef __AST_RETURN_NODE_H
#define __AST_RETURN_NODE_H

#include "AST/ast.hpp"
#include "AST/expression.hpp"

class ReturnNode : public AstNode
{
public:
  ReturnNode(const uint32_t line, const uint32_t col,
             /* TODO: expression */
             ExpressionNode *p_expression);
  ~ReturnNode() = default;

  void print(int level) override;

private:
  // TODO: expression
  ExpressionNode *expression;
};

#endif
