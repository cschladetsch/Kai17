#ifndef SIMPLE_TOKENIZER_H
#define SIMPLE_TOKENIZER_H

#include <string>
#include <vector>

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

    Token(Type type, const std::string& value, size_t line, size_t column)
        : type_(type), value_(value), line_(line), column_(column) {}

    Type getType() const { return type_; }
    const std::string& getValue() const { return value_; }
    size_t getLine() const { return line_; }
    size_t getColumn() const { return column_; }

private:
    Type type_;
    std::string value_;
    size_t line_;
    int column_;
};

class Tokenizer {
public:
    Tokenizer(const std::string& input);
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
