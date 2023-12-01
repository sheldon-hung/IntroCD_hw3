#ifndef __AST_COMPOUND_STATEMENT_NODE_H
#define __AST_COMPOUND_STATEMENT_NODE_H

#include "AST/ast.hpp"
#include "AST/decl.hpp"

#include <vector>

class CompoundStatementNode : public AstNode
{
public:
  CompoundStatementNode(const uint32_t line, const uint32_t col,
                        /* TODO: declarations, statements */
                        std::vector<DeclNode *> *p_decllist,
                        std::vector<AstNode *> *p_stmtlist);
  ~CompoundStatementNode() = default;

  void print(int level) override;

private:
  // TODO: declarations, statements
  std::vector<DeclNode *> *decllist;
  std::vector<AstNode *> *stmtlist;
};

#endif
