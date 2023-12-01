#include "AST/variable.hpp"

// TODO
VariableNode::VariableNode(const uint32_t line, const uint32_t col,
                           const char *const p_varname,
                           ConstantValueNode *p_constval)
    : AstNode{line, col}, varname(p_varname), constval(p_constval) {}

VariableNode::VariableNode(const uint32_t line, const uint32_t col,
                           const char *const p_varname,
                           VARSTRUCT p_varstruct)
    : AstNode{line, col}, varname(p_varname), varstruct(p_varstruct) {}

// TODO: You may use code snippets in AstDumper.cpp
void VariableNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("variable <line: %u, col: %u> %s ", location.line, location.col, varname.c_str());

    if (constval != NULL)
    {
        switch (constval->valtype)
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

        std::printf("\n");

        constval->print(level + 1);
    }
    else
    {
        switch (varstruct.valtype)
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

        if (varstruct.dim != NULL)
        {
            std::printf(" ");
            for (auto i : *(varstruct.dim))
            {
                std::printf("[%d]", i);
            }
        }

        std::printf("\n");
    }
}

// void VariableNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
