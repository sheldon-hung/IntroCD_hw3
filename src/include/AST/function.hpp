#ifndef __AST_FUNCTION_NODE_H
#define __AST_FUNCTION_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/CompoundStatement.hpp"

class FunctionNode : public AstNode
{
public:
  FunctionNode(const uint32_t line, const uint32_t col,
               /* TODO: name, declarations, return type,
                *       compound statement (optional) */
               const char *const p_name,
               std::vector<DeclNode *> *p_decllist,
               VALTYPE p_rettype,
               CompoundStatementNode *p_cmpdstmt);
  ~FunctionNode() = default;

  void print(int level) override;

private:
  // TODO: name, declarations, return type, compound statement
  std::string name;
  std::vector<DeclNode *> *decllist = NULL;
  VALTYPE rettype;
  CompoundStatementNode *cmpdstmt = NULL;
};

#endif
