#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <set>
#include <fstream>

using namespace std;

const set<char> SEPARATOR = {',', ';', '(', ')', '[', ']', '{', '}'};//分隔符表
const set<char> ARITHMETIC_OPERATOR = {'+', '-', '*', '/'};//算术运算符表
const set<char> RELATIONAL_OPERATOR = {'<', '>', '=', '!',};//关系运算符表


bool isSeparator(char &c) {
    return SEPARATOR.count(c);
}

bool isOperator(char &c) {
    return ARITHMETIC_OPERATOR.count(c);
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

bool checkState(int &state) {
    return state != 11;
}

vector<char> BUFFER;

void Record(int last, int state, char ch) {
    if (last == state && (state == 1 || state == 2)) {
        printf("ID");
        BUFFER.clear();
    }
}

void LineProcess(string &line) {
    int len = line.size();
    int status = 0;
    int last = status;
    for (int i = 0; i < len; ++i) {
        char ch = line[i];
        last = status;
        if ((checkState(status) && isAlpha(ch)) || (status == 1 && (isAlpha(ch) || isAlNum(ch)))) {
            if (status != 1) {
                printf("\nID: ");
            }
            status = 1;
            printf("%c", ch);;
        } else if ((checkState(status) && isNonZeroDigit(ch)) || (status == 2 && isDigit(ch))) {
            if (status != 2) {
                printf("\nNumber: ");
            }
            status = 2;
            printf("%c", ch);;
        } else if (checkState(status) && isZeroDigit(ch)) {
            if (status != 3) {
                printf("\nZero: ");
            }
            status = 3;
            printf("%c", ch);;
        } else if (checkState(status) && isNonDivOperator(ch)) {
            if (status != 4) {
                printf("\nOperator: ");
            }
            status = 4;
            printf("%c", ch);;
        } else if (checkState(status) && isSeparator(ch)) {
            if (status != 5) {
                printf("\nSeparator: ");
            }
            status = 5;
            printf("%c", ch);;
        } else if (status != 8 && checkState(status) && isNonEqualRelationalOperator(ch)) {
            if (status != 6) {
                printf("\nRelationalOperator: ");
            }
            status = 6;
            printf("%c", ch);;
        } else if (status == 6 && ch == '=') {
            status = 7;
            printf("%c", ch);;
        } else if (ch == '!') {
            if (status != 8) {
                printf("\nNonEqualOperator: ");
            }
            status = 8;
            printf("%c", ch);;
        } else if (status == 8 && ch == '=') {
            status = 9;
            printf("%c", ch);;
        } else if (checkState(status) && isDivOperator(ch)) {
            if (status != 10) {
                printf("\nDivOperator: ");
            }
            status = 10;
            printf("%c", ch);;
        } else if (isDivOperator(ch) && status == 10) {
            status = 11;
            printf("%c", ch);;
        } else {
            if (ch != ' ') {
                printf("<%c>", ch);
            }
            if (status != 11) {
                status = 0;
            }
        }
        Record(last, status, ch);
    }
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