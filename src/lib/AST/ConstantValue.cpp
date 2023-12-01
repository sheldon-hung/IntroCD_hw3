#include "AST/ConstantValue.hpp"

#include <cstdio>

// TODO
ConstantValueNode::ConstantValueNode(const uint32_t line, const uint32_t col,
                                     const VALTYPE p_valtype,
                                     const CONSTVAL p_constval)
    : ExpressionNode{line, col}, valtype(p_valtype), constval(p_constval) {}

// TODO: You may use code snippets in AstDumper.cpp
void ConstantValueNode::print(int level)
{
    for (int i = 0; i < level; i++)
    {
        std::printf("  ");
    }

    std::printf("constant <line: %u, col: %u> ", location.line, location.col);

    switch (valtype)
    {
    case Integer:
        std::printf("%d", constval.intval);
        break;
    case Real:
        std::printf("%f", constval.realval);
        break;
    case String:
        std::printf("%s", constval.strval);
        break;
    case Boolean:
        if (constval.boolval)
            std::printf("true");
        else
            std::printf("false");
        break;
    default:;
    }

    std::printf("\n");
}
