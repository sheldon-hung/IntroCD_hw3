#ifndef AST_AST_NODE_H
#define AST_AST_NODE_H

#include <cstdint>
#include <vector>

class AstNodeVisitor;

struct Location
{
  uint32_t line;
  uint32_t col;

  ~Location() = default;
  Location(const uint32_t line, const uint32_t col) : line(line), col(col) {}
};

class AstNode
{
protected:
  Location location;

public:
  virtual ~AstNode() = 0;
  AstNode(const uint32_t line, const uint32_t col);

  const Location &getLocation() const;

  virtual void print(int level) = 0;
};

enum VALTYPE
{
  Integer,
  Real,
  String,
  Boolean,
  Void
};

union CONSTVAL
{
  int intval;
  double realval;
  char *strval;
  bool boolval;
};

struct VARSTRUCT
{
  VALTYPE valtype;
  std::vector<int> *dim;
};

struct IDINFO
{
  uint32_t line;
  uint32_t column;
  char *name;
};

#endif
