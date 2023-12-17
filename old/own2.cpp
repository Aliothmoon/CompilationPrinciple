#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <set>
#include <fstream>

using namespace std;

const set<char> SEPARATOR_SET = {',', ';', '(', ')', '[', ']', '{', '}'};//分隔符表
const set<char> ARITHMETIC_OPERATOR = {'+', '-', '*', '/'};//算术运算符表

struct ErrorInfo {
    bool error = false;
    int row{}, column{};
};
char SPACE = ' ';

bool isSeparator(char &c) {
    return SEPARATOR_SET.count(c);
}


bool isNonZeroDigit(char &c) {
    return '1' <= c && c <= '9';
}

bool isZeroDigit(char &c) {
    return '0' == c;
}

bool isAlpha(char &c) {
    return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
}

bool isAlNum(char &c) {
    return isAlpha(c) || isNonZeroDigit(c) || isZeroDigit(c);
}

bool isDigit(char &c) {
    return isNonZeroDigit(c) || isNonZeroDigit(c);
}

bool isBlank(char &c) {
    return c == ' ' || c == '\n';
}

bool isNonDivOperator(char &c) {
    return c == '+' || c == '-' || c == '*';
}

bool isNonEqualRelationalOperator(char &c) {
    return c == '>' || c == '<' || c == '=';
}

bool isDivOperator(char &c) {
    return c == '/';
}


bool isSingleEqualOperator(char &c) {
    return c == '=';
}

bool isOperator(char &c) {
    return isNonDivOperator(c) || isNonEqualRelationalOperator(c) || isDivOperator(c) || isSingleEqualOperator(c);
}

string BUFFER;
enum NFA_STATUS {
    INITIALIZE, ID, NUMBER, ZERO,
    NON_DIV_OP, SEPARATOR, NON_EQUAL_OP,
    ANY_EQUAL_OP, EXCLAMATION,
    NOT_EQUAL, DIV, ANNOTATION
};

void RecordAnalyze(int &last, int &state, char &ch, ErrorInfo &err) {
    if (err.error) {
        printf("Error <%c>\n", ch);
    } else if (state != last && !BUFFER.empty()) {
        printf("%s\n", BUFFER.data());
        BUFFER.clear();
    }
    if (!isBlank(ch) && !err.error) {
        BUFFER.append({ch});
    }
    if (err.error) {
//        process error
        err.error = false;
    }

}

void LineProcess(string &line) {
    int len = line.size();
    int status = 0;
    ErrorInfo error{};
    int last = status;
    for (int i = 0; i < len; ++i) {
        char ch = line[i];
        last = status;
        if (isAlpha(ch) || (status == 1 && (isAlpha(ch) || isAlNum(ch)))) {
            status = 1;
        } else if (isNonZeroDigit(ch) || (status == 2 && isDigit(ch))) {
            status = 2;
        } else if (isZeroDigit(ch)) {
            status = 3;
        } else if (isNonDivOperator(ch)) {
            status = 4;
        } else if (isSeparator(ch)) {
            status = 5;
        } else if (status != 8 && isNonEqualRelationalOperator(ch)) {
            status = 6;
        } else if (status == 6 && isSingleEqualOperator(ch)) {
            status = 7;
        } else if (ch == '!') {
            status = 8;
        } else if (status == 8 && isSingleEqualOperator(ch)) {
            status = 9;
        } else if (isDivOperator(ch)) {
            status = 10;
        } else if (isDivOperator(ch) && status == 10) {
            status = 11;
        } else {
            error = ErrorInfo{!isBlank(ch)};
            if (error.error) {
                printf("%c\n", ch);
            }
//            Clear Status By Not expected or Blanks
            status = 0;
        }
        RecordAnalyze(last, status, ch, error);
    }
    // 处理最后一个
    last = status;
    status = 0;
    RecordAnalyze(last, status, SPACE, error);
}


void Input() {
    ifstream infile;
    ofstream outfile;
    infile.open(R"(E:\Projektes\Cpp\Compile\test.code)", ios::in);
    outfile.open(R"(E:\Projektes\Cpp\Compile\lex.txt)", ios::out);
    string line;
    while (getline(infile, line)) {
//        printf("%s\n", line.c_str());
        LineProcess(line);
    }
}

int main() {
    Input();
}