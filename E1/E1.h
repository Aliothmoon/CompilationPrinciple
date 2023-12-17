#include <string>
#include <iostream>
#include <map>
#include <set>
#include <fstream>

const std::set<char> SEPARATOR_SET = {',', ';', '(', ')', '[', ']', '{', '}'};//分隔符表
const std::set<char> ARITHMETIC_OPERATOR = {'+', '-', '*', '/'};//算术运算符表
const std::set<std::string> KEY_WORDS_SET = {"if", "else", "for", "while", "int", "write", "read"};
namespace E1 {


    struct ErrorInfo {
        bool error = false;
        bool annotation = false;
        int row{}, column{};
    };


    bool isSeparator(char &c);


    bool isNonZeroDigit(char &c);

    bool isZeroDigit(char &c);

    bool isAlpha(char &c);

    bool isAlNum(char &c);

    bool isDigit(char &c);

    bool isBlank(char &c);

    bool isNonDivOperator(char &c);

    bool isNonEqualRelationalOperator(char &c);

    bool isDivOperator(char &c);

    bool isSingleEqualOperator(char &c);

    bool isOperator(char &c);

    void Process(const char *path , const char *lexPath );

    void LineProcess(std::string &line, int row);

    void RecordAnalyze(int &last, int &state, char &ch, ErrorInfo &err);

    //打印状态 更加友好的打印显示结果
    const char *StatusInfo(int status, const char *str = nullptr);

    enum NFA_STATUS {
//    初态
        INITIALIZE,
//    标识符
        ID,
//    非零数字
        NUMBER,
//    零
        ZERO,
//    +-*
        NON_DIV_OP,
//    分隔符
        SEPARATOR,
//    <,>,=
        NON_EQUAL_OP,
//    <=,>=,==
        ANY_EQUAL_OP,
//    !
        EXCLAMATION,
//    !=
        NOT_EQUAL,
//    /
        DIV,
//    //
        ANNOTATION
    };
}