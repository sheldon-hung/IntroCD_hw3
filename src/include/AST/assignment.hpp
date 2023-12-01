#ifndef __AST_ASSIGNMENT_NODE_H
#define __AST_ASSIGNMENT_NODE_H

#include "AST/ast.hpp"
#include "AST/VariableReference.hpp"
#include "AST/expression.hpp"

class AssignmentNode : public AstNode
{
public:
  AssignmentNode(const uint32_t line, const uint32_t col,
                 /* TODO: variable reference, expression */
                 VariableReferenceNode *p_varref,
                 ExpressionNode *p_expression);
  ~AssignmentNode() = default;

  void print(int level) override;

private:
  // TODO: variable reference, expression
  VariableReferenceNode *varref;
  ExpressionNode *expression;
};

#endif
