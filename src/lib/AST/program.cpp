#include "AST/program.hpp"

// TODO
ProgramNode::ProgramNode(const uint32_t line, const uint32_t col,
                         const char *const p_name,
                         std::vector<DeclNode *> *p_decllist,
                         std::vector<FunctionNode *> *p_funclist,
                         CompoundStatementNode *p_cmpdstmt)
    : AstNode{line, col}, name(p_name), decllist(p_decllist), funclist(p_funclist), cmpdstmt(p_cmpdstmt) {}

// visitor pattern version: const char *ProgramNode::getNameCString() const { return name.c_str(); }

void ProgramNode::print(int level)
{
    // TODO
    // outputIndentationSpace();

    std::printf("program <line: %u, col: %u> %s %s\n",
                location.line, location.col,
                name.c_str(), "void");

    if (decllist != NULL)
    {
        for (auto node : *decllist)
        {
            node->print(level + 1);
        }
    }

    if (funclist != NULL)
    {
        for (auto node : *funclist)
        {
            node->print(level + 1);
        }
    }

    if (cmpdstmt != NULL)
    {
        cmpdstmt->print(level + 1);
    }

    // TODO
    // incrementIndentation();
    // visitChildNodes();
    // decrementIndentation();
}

// void ProgramNode::visitChildNodes(AstNodeVisitor &p_visitor) { // visitor pattern version
//     /* TODO
//      *
//      * for (auto &decl : var_decls) {
//      *     decl->accept(p_visitor);
//      * }
//      *
//      * // functions
//      *
//      * body->accept(p_visitor);
//      */
// }
