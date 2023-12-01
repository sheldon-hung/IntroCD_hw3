#include "AST/function.hpp"

// TODO
FunctionNode::FunctionNode(const uint32_t line, const uint32_t col,
                           const char *const p_name,
                           std::vector<DeclNode *> *p_decllist,
                           VALTYPE p_rettype,
                           CompoundStatementNode *p_cmpdstmt)
    : AstNode{line, col}, name(p_name), decllist(p_decllist), rettype(p_rettype), cmpdstmt(p_cmpdstmt) {}

// TODO: You may use code snippets in AstDumper.cpp
void FunctionNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("function declaration <line: %u, col: %u> %s ", location.line, location.col, name.c_str());

    switch (rettype)
    {
    case Integer:
        std::printf("integer ");
        break;
    case Real:
        std::printf("real ");
        break;
    case String:
        std::printf("string ");
        break;
    case Boolean:
        std::printf("boolean ");
        break;
    default:
        std::printf("void ");
    }

    std::printf("(");

    if (decllist != NULL)
    {
        VALTYPE paratype;
        std::vector<int> *paradim;
        long unsigned int paranum;
        for (long unsigned int i = 0; i < decllist->size(); i++)
        {
            paratype = (*decllist)[i]->varstruct.valtype;
            paradim = (*decllist)[i]->varstruct.dim;
            paranum = (*decllist)[i]->idlist.size();

            for (long unsigned int j = 0; j < paranum; j++)
            {
                switch (paratype)
                {
                case Integer:
                    std::printf("integer");
                    break;
                case Real:
                    std::printf("real");
                    break;
                case String:
                    std::printf("string");
                    break;
                case Boolean:
                    std::printf("boolean");
                    break;
                default:;
                }

                if (paradim != NULL)
                {
                    printf(" ");
                    for (auto dim : *paradim)
                    {
                        printf("[%d]", dim);
                    }
                }

                if (i != decllist->size() - 1 || j != paranum - 1)
                {
                    std::printf(", ");
                }
            }
        }
    }

    std::printf(")\n");

    if (decllist != NULL)
    {
        for (auto node : *decllist)
        {
            node->print(level + 1);
        }
    }

    if (cmpdstmt != NULL)
    {
        cmpdstmt->print(level + 1);
    }
}

// void FunctionNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
