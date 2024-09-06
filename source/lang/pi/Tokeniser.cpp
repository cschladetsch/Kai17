#include "kai/lang/pi/pi-tokeniser.h"
#include <cctype>
#include <stdexcept>
#include <string>

Tokenizer::Tokenizer(const std::string &input)
    : input_(input), position_(0), line_(1), column_(1) {}

std::vector<Token> Tokenizer::tokenize() {
  std::vector<Token> tokens;
  while (!isAtEnd()) {
    tokens.push_back(scanToken());
  }
  tokens.push_back(Token(Token::Type::EndOfFile, "", line_, column_));
  return tokens;
}

char Tokenizer::peek() const {
  if (isAtEnd())
    return '\0';
  return input_[position_];
}

char Tokenizer::advance() {
  char current = peek();
  position_++;
  if (current == '\n') {
    line_++;
    column_ = 1;
  } else {
    column_++;
  }
  return current;
}

bool Tokenizer::isAtEnd() const { return position_ >= input_.length(); }

Token Tokenizer::scanToken() {
  char c = advance();
  switch (c) {
  case ' ':
  case '\t':
  case '\r':
    return Token(Token::Type::Whitespace, std::string(1, c), line_,
                 column_ - 1);
  case '\n':
    return Token(Token::Type::Whitespace, "\\n", line_ - 1, column_);
  case '+':
  case '-':
  case '*':
  case '/':
  case '=':
  case '<':
  case '>':
    return Token(Token::Type::Operator, std::string(1, c), line_, column_ - 1);
  case '(':
  case ')':
  case '{':
  case '}':
  case '[':
  case ']':
  case ',':
  case ';':
    return Token(Token::Type::Punctuator, std::string(1, c), line_,
                 column_ - 1);
  case '"':
    return scanString();
  default:
    if (isDigit(c)) {
      position_--;
      column_--;
      return scanNumber();
    } else if (isAlpha(c)) {
      position_--;
      column_--;
      return scanIdentifier();
    } else {
      throw std::runtime_error("Unexpected character: " + std::string(1, c));
    }
  }
}

Token Tokenizer::scanNumber() {
  size_t start = position_;
  size_t startColumn = column_;
  bool isFloat = false;

  while (isDigit(peek()))
    advance();

  if (peek() == '.' && isDigit(input_[position_ + 1])) {
    isFloat = true;
    advance(); // Consume the dot
    while (isDigit(peek()))
      advance();
  }

  std::string number = input_.substr(start, position_ - start);
  Token::Type type =
      isFloat ? Token::Type::FloatingPoint : Token::Type::Integer;

  return Token(type, number, line_, startColumn);
}

Token Tokenizer::scanString() {
  size_t start = position_;
  size_t startColumn =
      column_ - 1; // -1 because we've already consumed the opening quote

  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n')
      throw std::runtime_error("Unterminated string");
    advance();
  }

  if (isAtEnd()) {
    throw std::runtime_error("Unterminated string");
  }

  advance(); // Consume the closing "

  std::string value = input_.substr(start, position_ - start - 1);
  return Token(Token::Type::String, value, line_, startColumn);
}

Token Tokenizer::scanIdentifier() {
  size_t start = position_;
  size_t startColumn = column_;

  while (isAlphaNumeric(peek()))
    advance();

  std::string identifier = input_.substr(start, position_ - start);
  return Token(Token::Type::Identifier, identifier, line_, startColumn);
}

bool Tokenizer::isDigit(char c) const { return c >= '0' && c <= '9'; }

bool Tokenizer::isAlpha(char c) const {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Tokenizer::isAlphaNumeric(char c) const {
  return isAlpha(c) || isDigit(c);
}
