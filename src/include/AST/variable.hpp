#ifndef __AST_VARIABLE_NODE_H
#define __AST_VARIABLE_NODE_H

#include "AST/ast.hpp"
#include "AST/ConstantValue.hpp"

#include <string>
#include <vector>

class VariableNode : public AstNode
{
public:
  VariableNode(const uint32_t line, const uint32_t col,
               /* TODO: variable name, type, constant value */
               const char *const p_varname,
               ConstantValueNode *p_constval);

  VariableNode(const uint32_t line, const uint32_t col,
               /* TODO: variable name, type */
               const char *const p_varname,
               const VARSTRUCT p_varstruct);

  ~VariableNode() = default;

  void print(int level) override;

private:
  // TODO: variable name, type, constant value
  std::string varname;
  VARSTRUCT varstruct;

  ConstantValueNode *constval = NULL;
};

#endif
