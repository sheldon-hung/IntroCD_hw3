#ifndef __AST_CONSTANT_VALUE_NODE_H
#define __AST_CONSTANT_VALUE_NODE_H

#include "AST/expression.hpp"

class ConstantValueNode : public ExpressionNode
{
public:
  ConstantValueNode(const uint32_t line, const uint32_t col,
                    /* TODO: constant value */
                    const VALTYPE p_valtype,
                    const CONSTVAL p_constval);
  ~ConstantValueNode() = default;

  void print(int level) override;

  VALTYPE valtype;

private:
  // TODO: constant value

  CONSTVAL constval;
};

#endif
