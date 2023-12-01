#ifndef __AST_FOR_NODE_H
#define __AST_FOR_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/assignment.hpp"
#include "AST/CompoundStatement.hpp"

#include <string>
#include <vector>

class ForNode : public AstNode
{
public:
  ForNode(const uint32_t line, const uint32_t col,
          /* TODO: declaration, assignment, expression,
           *       compound statement */
          const uint32_t declaration_line, const uint32_t declaration_col,
          const uint32_t assignment_line, const uint32_t assignment_col,
          const uint32_t initconstval_line, const uint32_t initconstval_col,
          const uint32_t finconstval_line, const uint32_t finconstval_col,
          char *p_name,
          const int p_initval, const int p_finval,
          CompoundStatementNode *p_cmpdstmt);
  ~ForNode() = default;

  void print(int level) override;

private:
  // TODO: declaration, assignment, expression, compound statement
  char *id;
  int initval, finval;

  DeclNode *declaration;
  AssignmentNode *assignment;
  VariableReferenceNode *varref;
  ConstantValueNode *initconstval, *finconstval;
  CompoundStatementNode *cmpdstmt;
};

#endif
