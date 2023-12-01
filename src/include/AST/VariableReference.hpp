#ifndef __AST_VARIABLE_REFERENCE_NODE_H
#define __AST_VARIABLE_REFERENCE_NODE_H

#include "AST/expression.hpp"

#include <string>
#include <vector>

class VariableReferenceNode : public ExpressionNode
{
public:
  // normal reference
  VariableReferenceNode(const uint32_t line, const uint32_t col,
                        /* TODO: name */
                        const char *const p_name);
  // array reference
  VariableReferenceNode(const uint32_t line, const uint32_t col,
                        /* TODO: name, expressions */
                        const char *const p_name,
                        std::vector<ExpressionNode *> *exprlist);
  ~VariableReferenceNode() = default;

  void print(int level) override;

private:
  // TODO: variable name, expressions
  std::string name;
  std::vector<int> dim;
  std::vector<ExpressionNode *> *exprlist = NULL;
};

#endif
