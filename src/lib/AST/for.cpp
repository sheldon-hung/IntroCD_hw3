#include "AST/for.hpp"

// TODO
ForNode::ForNode(const uint32_t line, const uint32_t col,
                 const uint32_t declaration_line, const uint32_t declaration_col,
                 const uint32_t assignment_line, const uint32_t assignment_col,
                 const uint32_t initconstval_line, const uint32_t initconstval_col,
                 const uint32_t finconstval_line, const uint32_t finconstval_col,
                 char *p_name,
                 const int p_initval, const int p_finval,
                 CompoundStatementNode *p_cmpdstmt)
    : AstNode{line, col}, id(p_name), initval(p_initval), finval(p_finval), cmpdstmt(p_cmpdstmt)
{
    IDINFO idinfo;
    std::vector<IDINFO> idlist;
    idinfo.line = declaration_line;
    idinfo.column = declaration_col;
    idinfo.name = id;
    idlist.push_back(idinfo);

    VARSTRUCT varstruct;
    varstruct.valtype = Integer;
    varstruct.dim = NULL;

    declaration = new DeclNode(declaration_line, declaration_col, idlist, varstruct);

    CONSTVAL initconstvalu, finconstvalu;
    initconstvalu.intval = initval;
    finconstvalu.intval = finval;

    initconstval = new ConstantValueNode(initconstval_line, initconstval_col, Integer, initconstvalu);
    finconstval = new ConstantValueNode(finconstval_line, finconstval_col, Integer, finconstvalu);

    varref = new VariableReferenceNode(declaration_line, declaration_col, id);

    assignment = new AssignmentNode(assignment_line, assignment_col, varref, initconstval);
}

// TODO: You may use code snippets in AstDumper.cpp
void ForNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("for statement <line: %u, col: %u>\n", location.line, location.col);

    declaration->print(level + 1);

    assignment->print(level + 1);

    finconstval->print(level + 1);

    cmpdstmt->print(level + 1);
}

// void ForNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
