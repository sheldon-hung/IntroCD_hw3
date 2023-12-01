#ifndef __AST_FUNCTION_INVOCATION_NODE_H
#define __AST_FUNCTION_INVOCATION_NODE_H

#include "AST/expression.hpp"
#include "AST/expression.hpp"

#include <string>
#include <vector>

class FunctionInvocationNode : public ExpressionNode
{
public:
  FunctionInvocationNode(const uint32_t line, const uint32_t col,
                         /* TODO: function name, expressions */
                         const char *const p_name,
                         std::vector<ExpressionNode *> *p_exprlist);
  ~FunctionInvocationNode() = default;

  // const char *getNameCString() const;

  void print(int level) override;

private:
  // TODO: function name, expressions
  std::string name;
  std::vector<ExpressionNode *> *exprlist = NULL;
};

#endif
