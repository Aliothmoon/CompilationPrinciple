#include <vector>
#include <deque>
#include <string>
#include <regex>
#include <iostream>
#include <map>
#include <set>
#include "syntax.h"
#include <algorithm>
#include <fstream>

using namespace std;
const string EMPTY_STRING{"$$$"};// 空集的表示
// 非终结符的First集
map<string, set<string> > FIRST_SET = {
        {"S", {"{"}},
        {"A", {"int",  EMPTY_STRING}},
        {"B", {"if",   "for", "while", "read,", "write", "{", "ID", ";", EMPTY_STRING}},
        {"C", {"int"}},
        {"D", {"if",   "for", "while", "read,", "write", "{", "ID", ";",}},
        {"E", {"if"}},
        {"e", {"else", EMPTY_STRING}},
        {"F", {"while"}},
        {"G", {"for"}},
        {"H", {"read"}},
        {"I", {"write"}},
        {"J", {"{"}},
        {"K", {"ID"}},
        {"L", {"(",    "ID",  "NUM"}},
        {"I", {"<",    ">",   "==",    "!=",    ">=",    "<="}},
        {"M", {"ID"}},
        {"N", {"ID",   "(",   "NUM"}},
        {"n", {"-",    "+",   EMPTY_STRING}},
        {"O", {"(",    "ID",  "NUM"}},
        {"o", {"*",    "/",   EMPTY_STRING}},
        {"P", {"(",    "ID",  "NUM"}},
};
//非终结符的Follow集
map<string, set<string> > FOLLOW_SET = {
        {"S", {"#"}},
        {"A", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}",}},
        {"B", {"}"}},
        {"e", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else"}},
        {"n", {"<",  ">",   "==",    "!=",   ">=",    "<=", ")",  ";"}},
        {"o", {"<",  ">",   "==",    "!=",   ">=",    "<=", ")",  ";", "+", "-"}}
};
const set<string> B_STATUS_SET = {"E", "F", "G", "H", "I", "J", "K"};
// 词法记号结构
struct Lex {
    string type;    // 记号类型
    string letter;  // 记号字符
};


Lex lex{};// 当前的词法记号
deque<Lex> letters;// 词法记号序列
const char *INPUT_PATH = R"(E:\Projektes\Cpp\Compile\lex.txt)";

// 显示错误信息并退出程序
void ErrorInfo(const char *message) {
    cout << "Error: " << message << endl;
    exit(-1);
}

// 显示调试信息
void DebugInfo(const char *message) {
    cout << "Debug: " << message << endl;
}

// 初始化，读取输入文件并填充letters序列
void init() {
    ifstream infile;
    infile.open(INPUT_PATH, ios::in);
    string line;
    while (getline(infile, line)) {
        int index = line.find(':');
        string type = line.substr(0, index);
        string letter = line.substr(index + 1);
        if (type == "Number") {
            type = "NUM";
        } else if (type == "Identifier") {
            type = "ID";
        }
        letters.emplace_back(Lex{type, letter});
    }
    DebugInfo("=========读入单词结束========");
}

// 前进到下一个词法记号
void next() {
    lex = letters.front();
    letters.pop_front();
}


//<program>   S
void S() {
    if (lex.letter == "{") {
        next();
        A();
        B();
        if (lex.letter == "}") {
            DebugInfo("OK");
        } else {
            ErrorInfo("OK");
        }
    }

}

//<declaration_list>  A
void A() {
//  判断空串
    if (FOLLOW_SET["A"].count(lex.letter) || FOLLOW_SET["A"].count(lex.type)) {
        return;
    }
    C();
    A();
}

//<statement_list>  B
void B() {
    //  判断空串
    if (FOLLOW_SET["B"].count(lex.letter)) {
        return;
    }
    D();
    B();
}

//<declaration_stat>  C
void C() {
    if (lex.letter == "int") {
        next();
        if (lex.type == "ID") {
            next();
            if (lex.letter == ";") {
                next();
                DebugInfo("C 完成");
            } else {
                ErrorInfo("缺少分号");
            }
        } else {
            ErrorInfo("标识符错误");
        }
    } else {
        ErrorInfo("缺少定义符");
    }
}

//<statement>  D
void D() {
    string type;

    //    特判
    if (lex.letter == "else") {
        next();
        DebugInfo("Non LL 1");
        return;
    }

    for (const auto &item: FIRST_SET) {
        if ((item.second.count(lex.letter) || item.second.count(lex.type)) && B_STATUS_SET.count(item.first)) {
            type = item.first;
            break;
        }
    }

    if (type == "E") {
        E();
    } else if (type == "F") {
        F();
    } else if (type == "G") {
        G();
    } else if (type == "H") {
        H();
    } else if (type == "I") {
        I();
    } else if (type == "J") {
        J();
    } else if (type == "K") {
        K();
    }
    if (lex.letter == ";") {
        next();
        return;
    }

}

//<while_stat>  F
void F() {
    if (lex.letter == "while") {
        next();
        if (lex.letter == "(") {
            next();
            L();
            if (lex.letter == ")") {
                next();
                D();
            } else {
                ErrorInfo("5 Error");
            }
        } else {
            ErrorInfo("4 Error");
        }
    } else {
        ErrorInfo("3 Error");
    }
}

//<for_stat> G
void G() {
    if (lex.letter == "for") {
        next();
        if (lex.letter == "(") {
            next();
            M();
            if (lex.letter == ";") {
                next();
                L();
                if (lex.letter == ";") {
                    next();
                    M();
                    if (lex.letter == ")") {
                        next();
                        D();
                    } else {
                        ErrorInfo("9");
                    }
                } else {
                    ErrorInfo("8");
                }
            } else {
                ErrorInfo("7");
            }
        } else {
            ErrorInfo("7");
        }
    } else {
        ErrorInfo("6");
    }
}

void e() {
    if (FOLLOW_SET["e"].count(lex.letter)) {
        return;
    }
    if (lex.letter == "else") {
        next();
        D();
    }
}

//<write_stat>  I
void I() {
    if (lex.letter == "write") {
        next();
        N();
        if (lex.letter == ";") {
            next();
        } else {
            ErrorInfo("I 2");
        }
    } else {
        ErrorInfo("I 1");
    }
}

//<read_stat>  H
void H() {
    if (lex.letter == "read") {
        next();
        if (lex.type == "ID") {
            next();
            if (lex.letter == ";") {
                next();
            } else {
                ErrorInfo("H 缺少分号");
            }
        } else {
            ErrorInfo("H 2");
        }
    } else {
        ErrorInfo("H 1");
    }
}

//<compound_stat>  J
void J() {
    if (lex.letter == "{") {
        next();
        B();
        if (lex.letter == "}") {
            next();
            DebugInfo("J OK");
        } else {
            ErrorInfo("J 2");
        }
    } else {
        ErrorInfo("J 1");
    }
}

//<if_stat>  E
void E() {
    if (lex.letter == "if") {
        next();
        if (lex.letter == "(") {
            next();
            L();
            if (lex.letter == ")") {
                next();
                D();
                e();
            } else {
                ErrorInfo("2错误");
            }
        }
    } else {
        ErrorInfo("1错误");
    }
}

//<assignment_stat>  K
void K() {
    M();
    if (lex.letter == ";") {
        next();
        DebugInfo("K OK");
    } else {
        ErrorInfo("K 缺少分号");
    }
}

void l() {
    if (lex.letter == ">" || lex.letter == "<"
        || lex.letter == ">=" || lex.letter == "<="
        || lex.letter == "!=" || lex.letter == "==") {
        next();
        N();
    } else {
        ErrorInfo("l :运算符不完整");
    }
}

//<bool_expression >  L
void L() {
    N();
    l();
}

//<assignment_expression>  M
void M() {
    if (lex.type == "ID") {
        next();
        if (lex.letter == "=") {
            next();
            N();
        } else {
            ErrorInfo("M 2");
        }
    } else {
        ErrorInfo("M 1");
    }
}

//< arithmetic_expression >  N
void N() {
    O();
    n();
}

void n() {
    //  判断空串
    if (FOLLOW_SET["n"].count(lex.letter)) {
        return;
    }
    if (lex.letter == "-" || lex.letter == "+") {
        next();
        O();
        n();
    } else {
        ErrorInfo("运算式不完整");
    }

}

//<term>   O
void O() {
    P();
    o();
}

//< factor >   P
void P() {
    if (lex.type == "ID") {
        DebugInfo("1 ID");
        next();
    } else if (lex.type == "NUM") {
        DebugInfo("2 NUM");
        next();
    } else if (lex.letter == "(") {
        next();
        N();
        if (lex.letter == ")") {
            next();
            DebugInfo("OK");
        } else {
            ErrorInfo("P 缺少括号");
        }
    } else {
        ErrorInfo("P :运算符不完整");
    }
}

void o() {
    if (FOLLOW_SET["o"].count(lex.letter)) {
        return;
    }
    if (lex.letter == "*" || lex.letter == "/") {
        next();
        P();
    } else {
        DebugInfo(lex.letter.c_str());
        ErrorInfo("o : 运算符不完整");
    }
}

int main() {
    init();
    next();
    S();
}