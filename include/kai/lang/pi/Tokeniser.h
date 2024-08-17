#ifndef SIMPLE_TOKENIZER_H
#define SIMPLE_TOKENIZER_H

#include </usr/lib/llvm-10/include/c++/v1/string>
#include <vector>

class Tokenizer {
public:
  Tokenizer(const std::string &input);
  std::vector<Token> tokenize();

private:
  std::string input_;
  size_t position_;
  size_t line_;
  size_t column_;

  char peek() const;
  char advance();
  bool isAtEnd() const;

  Token scanToken();
  Token scanNumber();
  Token scanString();
  Token scanIdentifier();
  Token scanOperatorOrPunctuator();

  bool isDigit(char c) const;
  bool isAlpha(char c) const;
  bool isAlphaNumeric(char c) const;
};

#endif // SIMPLE_TOKENIZER_H
