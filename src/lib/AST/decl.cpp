#include "AST/decl.hpp"

// TODO
DeclNode::DeclNode(const uint32_t line, const uint32_t col, const std::vector<IDINFO> p_idlist,
                   const VARSTRUCT p_varstruct)
    : AstNode{line, col}, idlist(p_idlist), varstruct(p_varstruct)
{
    varlist.resize(idlist.size());
    for (long unsigned int i = 0; i < varlist.size(); i++)
    {
        varlist[i] = new VariableNode(idlist[i].line, idlist[i].column, idlist[i].name, varstruct);
    }
}

// TODO
DeclNode::DeclNode(const uint32_t line, const uint32_t col, const std::vector<IDINFO> p_idlist,
                   ConstantValueNode *p_constval)
    : AstNode{line, col}, idlist(p_idlist), constval(p_constval)
{
    varlist.resize(idlist.size());
    for (long unsigned int i = 0; i < varlist.size(); i++)
    {
        varlist[i] = new VariableNode(idlist[i].line, idlist[i].column, idlist[i].name, constval);
    }
}

// TODO: You may use code snippets in AstDumper.cpp
void DeclNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("declaration <line: %u, col: %u>\n", location.line, location.col);

    for (auto node : varlist)
    {
        node->print(level + 1);
    }
}

// void DeclNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
