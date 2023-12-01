#ifndef AST_PROGRAM_NODE_H
#define AST_PROGRAM_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/function.hpp"
#include "AST/CompoundStatement.hpp"

#include <string>
#include <vector>

class ProgramNode final : public AstNode
{
private:
  std::string name;
  // TODO: return type, declarations, functions, compound statement

  std::vector<DeclNode *> *decllist = NULL;
  std::vector<FunctionNode *> *funclist = NULL;
  CompoundStatementNode *cmpdstmt = NULL;

public:
  ~ProgramNode() = default;
  ProgramNode(const uint32_t line, const uint32_t col,
              const char *const p_name,
              /* TODO: return type, declarations, functions,
               *       compound statement */
              std::vector<DeclNode *> *p_decllist,
              std::vector<FunctionNode *> *p_funclist,
              CompoundStatementNode *p_cmpdstmt);

  // visitor pattern version: const char *getNameCString() const;
  void print(int level) override;
};

#endif
