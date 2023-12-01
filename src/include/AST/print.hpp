#ifndef __AST_PRINT_NODE_H
#define __AST_PRINT_NODE_H

#include "AST/ast.hpp"
#include "AST/expression.hpp"

class PrintNode : public AstNode
{
public:
  PrintNode(const uint32_t line, const uint32_t col,
            /* TODO: expression */
            ExpressionNode *p_expression);
  ~PrintNode() = default;

  void print(int level) override;

private:
  // TODO: expression
  ExpressionNode *expression;
};

#endif
