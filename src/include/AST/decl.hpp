#ifndef __AST_DECL_NODE_H
#define __AST_DECL_NODE_H

#include "AST/ast.hpp"
#include "AST/variable.hpp"
#include "AST/ConstantValue.hpp"

#include <vector>
#include <string>

class DeclNode : public AstNode
{
public:
  // variable declaration
  DeclNode(const uint32_t line, const uint32_t col,
           /* TODO: identifiers, type */
           const std::vector<IDINFO> p_idlist,
           const VARSTRUCT p_varstruct);

  // constant variable declaration
  DeclNode(const uint32_t, const uint32_t col,
           /* TODO: identifiers, constant */
           const std::vector<IDINFO> p_idlist,
           ConstantValueNode *p_constval);

  ~DeclNode() = default;

  void print(int level) override;

  VARSTRUCT varstruct;
  std::vector<IDINFO> idlist;

private:
  // TODO: variables

  ConstantValueNode *constval = NULL;

  std::vector<VariableNode *> varlist;
};

#endif
