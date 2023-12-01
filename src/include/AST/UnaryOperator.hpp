#ifndef __AST_UNARY_OPERATOR_NODE_H
#define __AST_UNARY_OPERATOR_NODE_H

#include "AST/expression.hpp"

#include <string>

class UnaryOperatorNode : public ExpressionNode
{
public:
  UnaryOperatorNode(const uint32_t line, const uint32_t col,
                    /* TODO: operator, expression */
                    const char *const p_operator,
                    ExpressionNode *p_expression);
  ~UnaryOperatorNode() = default;

  void print(int level) override;

private:
  // TODO: operator, expression
  std::string operator_;
  ExpressionNode *expression;
};

#endif
