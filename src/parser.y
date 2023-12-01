%{
#include "AST/BinaryOperator.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/FunctionInvocation.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/VariableReference.hpp"
#include "AST/assignment.hpp"
#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/expression.hpp"
#include "AST/for.hpp"
#include "AST/function.hpp"
#include "AST/if.hpp"
#include "AST/print.hpp"
#include "AST/program.hpp"
#include "AST/read.hpp"
#include "AST/return.hpp"
#include "AST/variable.hpp"
#include "AST/while.hpp"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define YYLTYPE yyltype

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

extern int32_t line_num;    /* declared in scanner.l */
extern char current_line[]; /* declared in scanner.l */
extern FILE *yyin;          /* declared by lex */
extern char *yytext;        /* declared by lex */

static AstNode *root;

extern "C" int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);
%}

%code requires {
    #include <vector>

    class AstNode;
    class ConstantValueNode;
    class DeclNode;
    class VariableReferenceNode;
    class FunctionNode;
    class ExpressionNode;

    // enum VALTYPE;

    union COSNTVAL;

    struct VARSTRUCT;

    struct IDINFO;
}

    /* For yylval */
%union {
    /* basic semantic value */
    char *identifier;

    int intval;
    double realval;
    bool boolval;
    char *strval;

    AstNode *node;
    ConstantValueNode *constantvaluenode;
    DeclNode *declnode;
    VariableReferenceNode *varref;
    FunctionNode *funcnode;
    ExpressionNode *expression;
    std::vector<AstNode*> *nodelist;
    std::vector<DeclNode*> *declnodelist;
    std::vector<FunctionNode*> *funcnodelist;
    std::vector<ExpressionNode*> *exprlist;

    std::vector<IDINFO> *idlist;

    VARSTRUCT *varstruct;
    // VALTYPE valtype;
    std::vector<int> *dim;

    
};

%type <identifier> ProgramName FunctionName

%type <node> Program
%type <declnodelist> Declarations DeclarationList FormalArgs FormalArgList
%type <declnode> Declaration FormalArg
%type <funcnodelist> Functions FunctionList
%type <funcnode> Function FunctionDeclaration FunctionDefinition
%type <varstruct> Type ScalarType ArrType ReturnType
%type <dim> ArrDecl

%type <idlist> IdList

%type <constantvaluenode> LiteralConstant
%type <boolval> NegOrNot
%type <constantvaluenode> StringAndBoolean IntegerAndReal

%type <nodelist> StatementList Statements
%type <node> Statement CompoundStatement 
%type <node> Condition While For
%type <node> Simple Return FunctionCall
%type <node> ElseOrNot FunctionInvocation

%type <varref> VariableReference
%type <exprlist> ArrRefList ArrRefs

%type <exprlist> ExpressionList Expressions
%type <expression> Expression

    /* Follow the order in scanner.l */

    /* Delimiter */
%token COMMA SEMICOLON COLON
%token L_PARENTHESIS R_PARENTHESIS
%token L_BRACKET R_BRACKET

    /* Operator */
%token ASSIGN
%left OR
%left AND
%right NOT
%left LESS LESS_OR_EQUAL EQUAL GREATER GREATER_OR_EQUAL NOT_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right UNARY_MINUS

    /* Keyword */
%token ARRAY BOOLEAN INTEGER REAL STRING
%token END BEGIN_ /* Use BEGIN_ since BEGIN is a keyword in lex */
%token DO ELSE FOR IF THEN WHILE
%token DEF OF TO RETURN VAR
%token <boolval> FALSE TRUE
%token PRINT READ

    /* Identifier */
%token <identifier> ID

    /* Literal */
%token <intval> INT_LITERAL
%token <realval> REAL_LITERAL
%token <strval> STRING_LITERAL

%%

Program:
    ProgramName SEMICOLON
    /* ProgramBody */
    DeclarationList FunctionList CompoundStatement
    /* End of ProgramBody */
    END {
        root = new ProgramNode(@1.first_line, @1.first_column, $1, $3, $4, (CompoundStatementNode*)$5);

        free($1);
    }
;

ProgramName:
    ID { $$ = $1; }
;

DeclarationList:
    Epsilon { $$ = NULL; }
    |
    Declarations { $$ = $1; }
;

Declarations:
    Declaration { $$ = new std::vector<DeclNode*>; $$->push_back($1); }
    |
    Declarations Declaration { $1->push_back($2); $$ = $1; }
;

FunctionList:
    Epsilon { $$ = NULL; }
    |
    Functions { $$ = $1; }
;

Functions:
    Function { $$ = new std::vector<FunctionNode*>; $$->push_back($1); }
    |
    Functions Function { $1->push_back($2); $$ = $1; }
;

Function:
    FunctionDeclaration { $$ = $1; }
    |
    FunctionDefinition { $$ = $1; }
;

FunctionDeclaration:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON {
        $$ = new FunctionNode(@1.first_line, @1.first_column, $1, $3, $5->valtype, NULL);
    }
;

FunctionDefinition:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType
    CompoundStatement
    END {
        $$ = new FunctionNode(@1.first_line, @1.first_column, $1, $3, $5->valtype, (CompoundStatementNode*)$6);
    }
;

FunctionName:
    ID { $$ = $1; }
;

FormalArgList:
    Epsilon { $$ = NULL; }
    |
    FormalArgs { $$ = $1; }
;

FormalArgs:
    FormalArg { $$ = new std::vector<DeclNode*>; $$->push_back($1); }
    |
    FormalArgs SEMICOLON FormalArg { $1->push_back($3); $$ = $1; }
;

FormalArg:
    IdList COLON Type {
        $$ = new DeclNode(@1.first_line, @1.first_column, *$1, *$3);
        free($1); free($3);
    }
;

IdList:
    ID {
        IDINFO idinfo; idinfo.line = @1.first_line; idinfo.column = @1.first_column; idinfo.name = $1;
        $$ = new std::vector<IDINFO>; $$->push_back(idinfo);
    }
    |
    IdList COMMA ID {
        IDINFO idinfo; idinfo.line = @3.first_line; idinfo.column = @3.first_column; idinfo.name = $3;
        $1->push_back(idinfo); $$ = $1;
    }
;

ReturnType:
    COLON ScalarType { $$ = $2; }
    |
    Epsilon { $$ = new VARSTRUCT; $$->valtype = Void; $$->dim = NULL; }
;

    /*
       Data Types and Declarations
                                   */

Declaration:
    VAR IdList COLON Type SEMICOLON {
        $$ = new DeclNode(@1.first_line, @1.first_column, *$2, *$4);
        free($2); free($4);
    }
    |
    VAR IdList COLON LiteralConstant SEMICOLON {
        $$ = new DeclNode(@1.first_line, @1.first_column, *$2, $4);
        free($2);
    }
;

Type:
    ScalarType { $$ = $1; }
    |
    ArrType { $$ = $1; }
;

ScalarType:
    INTEGER { $$ = new VARSTRUCT; $$->valtype = Integer; $$->dim = NULL; }
    |
    REAL { $$ = new VARSTRUCT; $$->valtype = Real; $$->dim = NULL; }
    |
    STRING { $$ = new VARSTRUCT; $$->valtype = String; $$->dim = NULL; }
    |
    BOOLEAN { $$ = new VARSTRUCT; $$->valtype = Boolean; $$->dim = NULL; }
;

ArrType:
    ArrDecl ScalarType {  $$ = $2; $$->dim = $1; }
;

ArrDecl:
    ARRAY INT_LITERAL OF { $$ = new std::vector<int>; $$->push_back($2); }
    |
    ArrDecl ARRAY INT_LITERAL OF { $1->push_back($3); $$ = $1; }
;

LiteralConstant:
    NegOrNot INT_LITERAL {
        CONSTVAL intarg;
        if ($1)
        {
            intarg.intval = -$2;
        }
        else
        {
            intarg.intval = $2;
            $$ = new ConstantValueNode(@2.first_line, @2.first_column, Integer, intarg);
        }
        
    }
    |
    NegOrNot REAL_LITERAL {
        CONSTVAL realarg;
        if ($1) realarg.realval = -$2;
        else realarg.realval = $2;
        $$ = new ConstantValueNode(@1.first_line, @1.first_column, Real, realarg);
    }
    |
    StringAndBoolean { $$ = $1; }
;

NegOrNot:
    Epsilon { $$ = false; }
    |
    MINUS %prec UNARY_MINUS { $$ = true; }
;

StringAndBoolean:
    STRING_LITERAL {
        CONSTVAL strarg; strarg.strval = $1;
        $$ = new ConstantValueNode(@1.first_line, @1.first_column, String, strarg);
    }
    |
    TRUE {
        CONSTVAL boolarg; boolarg.boolval = $1;
        $$ = new ConstantValueNode(@1.first_line, @1.first_column, Boolean, boolarg);
    }
    |
    FALSE {
        CONSTVAL boolarg; boolarg.boolval = $1;
        $$ = new ConstantValueNode(@1.first_line, @1.first_column, Boolean, boolarg);
    }
;

IntegerAndReal:
    INT_LITERAL {
        CONSTVAL intarg; intarg.intval = $1;
        $$ = new ConstantValueNode(@1.first_line, @1.first_column, Integer, intarg);
    }
    |
    REAL_LITERAL {
        CONSTVAL realarg; realarg.realval = $1;
        $$ = new ConstantValueNode(@1.first_line, @1.first_column, Real, realarg);
    }
;

    /*
       Statements
                  */

Statement:
    CompoundStatement { $$ = $1; }
    |
    Simple { $$ = $1; }
    |
    Condition { $$ = $1; }
    |
    While { $$ = $1; }
    |
    For { $$ = $1; }
    |
    Return { $$ = $1; }
    |
    FunctionCall { $$ = $1; }
;

CompoundStatement:
    BEGIN_
    DeclarationList
    StatementList
    END { $$ = new CompoundStatementNode(@1.first_line, @1.first_column, $2, $3); }
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON { $$ = new AssignmentNode(@2.first_line, @2.first_column, $1, $3); }
    |
    PRINT Expression SEMICOLON { $$ = new PrintNode(@1.first_line, @1.first_column, $2); }
    |
    READ VariableReference SEMICOLON { $$ = new ReadNode(@1.first_line, @1.first_column, $2); }
;

VariableReference:
    ID ArrRefList { $$ = new VariableReferenceNode(@1.first_line, @1.first_column, $1, $2); }
;

ArrRefList:
    Epsilon { $$ = NULL; }
    |
    ArrRefs { $$ = $1; }
;

ArrRefs:
    L_BRACKET Expression R_BRACKET { $$ = new std::vector<ExpressionNode*>; $$->push_back($2); }
    |
    ArrRefs L_BRACKET Expression R_BRACKET {  $1->push_back($3); $$ = $1; }
;

Condition:
    IF Expression THEN
    CompoundStatement
    ElseOrNot 
    END IF {
        $$ = new IfNode(@1.first_line, @1.first_column, $2, (CompoundStatementNode*)$4, (CompoundStatementNode*)$5);
    }
;

ElseOrNot:
    ELSE
    CompoundStatement { $$ = $2; }
    |
    Epsilon { $$ = NULL; }
;

While:
    WHILE Expression DO
    CompoundStatement
    END DO { $$ = new WhileNode(@1.first_line, @1.first_column, $2, (CompoundStatementNode*)$4); }
;

For:
    FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
    CompoundStatement
    END DO { 
        $$ = new ForNode(@1.first_line, @1.first_column, @2.first_line, @2.first_column,
                         @3.first_line, @3.first_column, @4.first_line, @4.first_column,
                         @6.first_line, @6.first_column, $2, $4, $6, (CompoundStatementNode*)$8);
    }
;

Return:
    RETURN Expression SEMICOLON { $$ = new ReturnNode(@1.first_line, @1.first_column, $2); }
;

FunctionCall:
    FunctionInvocation SEMICOLON { $$ = $1; }
;

FunctionInvocation:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS {
        $$ = new FunctionInvocationNode(@1.first_line, @1.first_column, $1, $3);
    }
;

ExpressionList:
    Epsilon { $$ = NULL; }
    |
    Expressions { $$ = $1; }
;

Expressions:
    Expression { $$ = new std::vector<ExpressionNode*>; $$->push_back($1); }
    |
    Expressions COMMA Expression { $1->push_back($3); $$ = $1; }
;

StatementList:
    Epsilon { $$ = NULL; }
    |
    Statements { $$ = $1; }
;

Statements:
    Statement { $$ = new std::vector<AstNode*>; $$->push_back($1); }
    |
    Statements Statement { $1->push_back($2); $$ = $1; }
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS { $$ = $2; }
    |
    MINUS Expression %prec UNARY_MINUS { $$ = new UnaryOperatorNode(@1.first_line, @1.first_column, "neg", $2); }
    |
    Expression MULTIPLY Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "*", $1, $3); }
    |
    Expression DIVIDE Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "/", $1, $3); }
    |
    Expression MOD Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "mod", $1, $3); }
    |
    Expression PLUS Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "+", $1, $3); }
    |
    Expression MINUS Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "-", $1, $3); }
    |
    Expression LESS Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "<", $1, $3); }
    |
    Expression LESS_OR_EQUAL Expression {
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "<=", $1, $3);
    }
    |
    Expression GREATER Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, ">", $1, $3); }
    |
    Expression GREATER_OR_EQUAL Expression {
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, ">=", $1, $3);
    }
    |
    Expression EQUAL Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "=", $1, $3); }
    |
    Expression NOT_EQUAL Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "<>", $1, $3); }
    |
    NOT Expression { $$ = new UnaryOperatorNode(@1.first_line, @1.first_column, "not", $2); }
    |
    Expression AND Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "and", $1, $3); }
    |
    Expression OR Expression { $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, "or", $1, $3); }
    |
    IntegerAndReal { $$ = (ExpressionNode*)$1; }
    |
    StringAndBoolean { $$ = (ExpressionNode*)$1; }
    |
    VariableReference { $$ = (ExpressionNode*)$1; }
    |
    FunctionInvocation { $$ = (ExpressionNode*)$1; }
;

    /*
       misc
            */
Epsilon:
;

%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            line_num, current_line, yytext);
    exit(-1);
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [--dump-ast]\n", argv[0]);
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        perror("fopen() failed");
        exit(-1);
    }

    yyparse();

    if (argc >= 3 && strcmp(argv[2], "--dump-ast") == 0) {
        root->print(0);
    }

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");

    delete root;
    fclose(yyin);
    yylex_destroy();
    return 0;
}
