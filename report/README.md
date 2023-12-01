# hw3 report

|||
|-:|:-|
|Name|洪慎廷|
|ID|110550162|

## How much time did you spend on this project

> e.g. 2 hours.

About 20 hours.

## Project overview

> Please describe the structure of your code and the ideas behind your implementation in an organized way.
> The point is to show us how you deal with the problems. It is not necessary to write a lot of words or paste all of your code here.

In this project, I modified the scanner, the parser and the AST tree nodes. The code structure will be described in the following.

For the scanner, I only add a few codes, mostly the yylval of the constant literal. The yylval is defined in the "union" part of the parrser, which can be "int", "double", "char*", "type". The scanner will set the yylval an "int" when the token is a demical or octal integer, a "double" when the token is a floating-point or scientific notation, a "char*" when the token is a string, a "bool" when the token is a boolean value.

For the parser and the AST tree nodes, I wrote both part of codes simultaneously and constructed the AST tree in the order from bottom to top, since it is more intuitive for me. First define the structure of the node in the ".hpp" and ".cpp" file, then define how to construct this node in the parser. For some part that the parse tree doesn't match the AST tree, I didn't use the inherit attributes, instead I defined some data structures which are in "ast.hpp" file to temporarily store and pass on the information that is needed, when the information is enough then construct the AST tree.

## What is the hardest you think in this project

> Not required, but bonus point may be given.

I think the hardest part of this project is constructing the declaration node. Because the parse tree doesn't match the syntax tree in this part. It is needed to store some data and do more processing when constructing the AST. 

## Feedback to T.A.s

> Not required, but bonus point may be given.

This project is way more harder than the previous projects. I think it is needed to give more examples in the part of coding.