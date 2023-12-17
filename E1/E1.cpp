#include "E1.h"

namespace E1 {

    char SPACE = ' ';
    const char *INPUT_PATH = R"(E:\Projektes\Cpp\Compile\E1\E3.code)";
    const char *LEX_PATH = R"(E:\Projektes\Cpp\Compile\E1\E3.lex)";

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

    std::string BUFFER;

    const char *StatusInfo(int status, const char *str) {
        if (status == ID) {
            if (str != nullptr && KEY_WORDS_SET.count(str)) {
                return "Reserved word";
            }
            return "Identifier";
        } else if (status == NUMBER || status == ZERO) {
            return "Number";
        } else if (status == NON_DIV_OP || status == DIV || status == ANY_EQUAL_OP || status == NON_EQUAL_OP ||
                   status == NOT_EQUAL) {
            return "Operator";
        } else if (status == SEPARATOR) {
            return "Separator";
        } else if (status == ANNOTATION) {
            return "Annotation";
        } else {
            return "Unknown";
        }
    }

    void RecordAnalyze(int &last, int &state, char &ch, ErrorInfo &err) {
        if (err.annotation) {
            printf("\n");
        }
        if (err.error) {
            printf("Error <%c>  %9s:%d Column:%d\n", ch, "Row", err.row, err.column);
            state = last;
        } else if (state != last && !BUFFER.empty() && last != EXCLAMATION) {
            if (state == ANNOTATION && last == DIV) {
                err.annotation = true;
//            printf("%s://", StatusInfo(state));
                printf("//");
            } else if (!err.annotation) {
//            printf("%s:%s\n", StatusInfo(last, BUFFER.data()), BUFFER.data());
                const char *str = BUFFER.data();
                const char *res = nullptr;
                if (last == ID) {
                    if (str != nullptr && KEY_WORDS_SET.count(str)) {
                        res = BUFFER.data();
                    } else {
                        res = "ID";
                    }
                } else if (last == NUMBER) {
                    res = "NUM";
                } else {
                    res = BUFFER.data();

                }
                printf("%s %s\n", res, BUFFER.data());
            }

            BUFFER.clear();
        }
        if (!isBlank(ch) && !err.error) {
            BUFFER.append({ch});

        }
        //        process error
        if (err.error) {
            err.error = false;
        }

    }

    void LineProcess(std::string &line, int row) {
        int len = (int) line.size();
        int status = INITIALIZE;
        ErrorInfo error{false, false, row, 1};
        int last = status;
        for (int i = 0; i < len; ++i) {
            char ch = line[i];
            last = status;
            if (status == ANNOTATION) {
                printf("%c", ch);
                continue;
            }
            if (isAlpha(ch) || (status == ID && (isAlpha(ch) || isAlNum(ch)))) {
                status = ID;
            } else if (isNonZeroDigit(ch) || (status == NUMBER && isDigit(ch))) {
                status = NUMBER;
            } else if (isZeroDigit(ch)) {
//                status = NUMBER;
                status = NUMBER;
            } else if (isNonDivOperator(ch)) {
                status = NON_DIV_OP;
            } else if (isSeparator(ch)) {
                status = SEPARATOR;
            } else if (status != EXCLAMATION && isNonEqualRelationalOperator(ch)) {
                status = NON_EQUAL_OP;
            } else if (status == NON_EQUAL_OP && isSingleEqualOperator(ch)) {
                status = ANY_EQUAL_OP;
            } else if (ch == '!') {
                status = EXCLAMATION;
            } else if (status == EXCLAMATION && isSingleEqualOperator(ch)) {
                status = NOT_EQUAL;
            } else if (isDivOperator(ch) && status == DIV) {
                status = ANNOTATION;
            } else if (isDivOperator(ch)) {
                status = DIV;
            } else {
                error.error = !isBlank(ch);
                error.column = i + 1;
//            Clear Status By Not expected or Blanks
                status = INITIALIZE;
            }
            RecordAnalyze(last, status, ch, error);
        }
        // 处理最后一个
        last = status;
        status = 0;
        RecordAnalyze(last, status, SPACE, error);
    }

    void Process(const char *path = INPUT_PATH, const char *lexPath = LEX_PATH) {
        printf("========开始词法分析========\n");
        std::ifstream infile;
        infile.open(path, std::ios::in);
        std::string line;
        freopen(lexPath, "w", stdout);
        int row = 1;
        while (getline(infile, line)) {
            LineProcess(line, row++);
        }
        std::string EMPTY;
        LineProcess(EMPTY, row++);
        freopen("CON", "w", stdout);
        printf("========%s========\n", "词法分析结束");
    }
}
