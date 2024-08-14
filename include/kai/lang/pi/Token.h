#pragma once

#include <string>

class Token {
public:
  enum class Type {
    Integer,
    FloatingPoint,
    String,
    Identifier,
    Operator,
    Punctuator,
    Whitespace,
    EndOfFile
  };

  Token(Type type, const std::string &value, size_t line, size_t column)
      : type_(type), value_(value), line_(line), column_(column) {}

  Type getType() const { return type_; }
  const std::string &getValue() const { return value_; }
  size_t getLine() const { return line_; }
  size_t getColumn() const { return column_; }

private:
  Type type_;
  std::string value_;
  size_t line_;
  int column_;
};
