#ifndef __AST_BINARY_OPERATOR_NODE_H
#define __AST_BINARY_OPERATOR_NODE_H

#include "AST/expression.hpp"

#include <memory>
#include <string>

class BinaryOperatorNode : public ExpressionNode
{
public:
  BinaryOperatorNode(const uint32_t line, const uint32_t col,
                     /* TODO: operator, expressions */
                     const char *const p_operator,
                     ExpressionNode *p_leftexpression,
                     ExpressionNode *p_rightexpression);
  ~BinaryOperatorNode() = default;

  void print(int level) override;

private:
  // TODO: operator, expressions
  std::string operator_;
  ExpressionNode *leftexpression, *rightexpression;
};

#endif
