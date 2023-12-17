#include <vector>
#include <deque>
#include <string>
#include <regex>
#include <iostream>
#include <map>
#include <set>
//#include "syntax.h"
#include <algorithm>
#include <fstream>

using namespace std;
/*
 *  <program> S
    <declaration_list> A
    <statement_list> B
    <declaration_stat> C
    <statement> D
    <if_stat> E
    <while_stat> F
    <for_stat> G
    <read_stat> H
    <write_stat> I
    <compound_stat> J
    <assignment_stat> K
    <bool_expression> L
    <assignment_expression> M
    <arithmetic_expression> N
    <term> O
    <factor> P
 */

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
        {"l", {"<",    ">",   "==",    "!=",    ">=",    "<="}},
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
        {"A", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}"}},
        {"B", {"}"}},
        {"C", {"int","if", "for", "while", "read", "write", "{",  "ID", ";", "}"}},
        {"D", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else"}},
        {"E", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else"}},
        {"e", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else"}},
        {"F", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else"}},
        {"G", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else"}},
        {"H", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else"}},
        {"I", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else"}},
        {"J", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else"}},
        {"K", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else"}},
        {"L", {"(", ";"}},
        {"l", {")",";"}},
        {"M", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else"}},
        {"N", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else",">","<",">=","<=","==","!=","(","NUM"}},
        {"n", {"<",  ">",   "==",    "!=",   ">=",    "<=", ")",  ";"}},
        {"O", {"<",  ">",   "==",    "!=",   ">=",    "<=", ")",  ";", "+", "-"}},
        {"o", {"<",  ">",   "==",    "!=",   ">=",    "<=", ")",  ";", "+", "-"}},
        {"P", {"*","/","+", "-", ">", "<", ">=", "<=", "==", "!=", ")", ";"}},
};
const set<string> B_STATUS_SET = {"E", "F", "G", "H", "I", "J", "K"};
// 词法结构
struct Lex {
    string type;    // 类型
    string letter;  // 字符串
};

Lex lex{};
deque<Lex> letters;// 词法序列

const char *INPUT_PATH = R"(D:\pack\CLionProjects\lex.txt)";
//const char *PTX = R"(WAXCS)";

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

// 下一个词法字符串
void next() {
    lex = letters.front();
    letters.pop_front();
}
void S();

void A();

void B();

void C();

void D();

void E();

void e();

void F();

void G();

void H();

void I();

void J();

void K();

void L();

void l();

void M();

void N();

void n();

void O();

void o();

void P();

//<program>   S
void S() {
    if (lex.letter == "{") {
        next();
        A();
        B();
        if (lex.letter == "}") {
            DebugInfo("OK");
        } else {
            DebugInfo(lex.letter.data());
            ErrorInfo("S:缺少右花括号");
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
                DebugInfo(lex.letter.data());
                ErrorInfo("C:3 缺少分号");
            }
        } else {
            DebugInfo(lex.letter.data());
            ErrorInfo("C:2 标识符错误");
        }
    } else {
        DebugInfo(lex.letter.data());
        ErrorInfo("C:1 缺少关键字");
    }
}

//<statement>  D
void D() {
    string type;
    //   特判else
    if (lex.letter == "else") {
        next();
        DebugInfo("Non LL 1");
        return;
    }
    for (const auto &item: FIRST_SET) {
        //item.second.count(lex.type):判断是否为ID和NUM，把变量类型命名为ID
        //(item.second.count(lex.letter):去找当前数据与有无first对应
        //B_STATUS_SET.count(item.first):判断分支
        if ((item.second.count(lex.letter) || item.second.count(lex.type)) && B_STATUS_SET.count(item.first)) {
//            DebugInfo(lex.letter.data());
//            DebugInfo(lex.type.data());
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
                DebugInfo(lex.letter.data());
                ErrorInfo("E:3 缺少右括号");
            }
        }
        else {
            DebugInfo(lex.letter.data());
            ErrorInfo("E:2 缺少左括号");
        }
    } else {
        DebugInfo(lex.letter.data());
        ErrorInfo("E:1 缺少关键字");
    }
}

void e() {
    //  判断空串
    if (FOLLOW_SET["e"].count(lex.letter)) {
        return;
    }
    if (lex.letter == "else") {
        next();
        D();
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
                DebugInfo(lex.letter.data());
                ErrorInfo("F:3 缺少右括号");
            }
        } else {
            DebugInfo(lex.letter.data());
            ErrorInfo("F:2 缺少左括号");
        }
    } else {
        DebugInfo(lex.letter.data());
        ErrorInfo("F:1 缺少关键字");
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
                        DebugInfo(lex.letter.data());
                        ErrorInfo("G:5 缺少右括号");
                    }
                } else {
                    DebugInfo(lex.letter.data());
                    ErrorInfo("G:4 缺少分号");
                }
            } else {
                DebugInfo(lex.letter.data());
                ErrorInfo("G:3 缺少分号");
            }
        } else {
            DebugInfo(lex.letter.data());
            ErrorInfo("G:2 缺少左括号");
        }
    } else {
        DebugInfo(lex.letter.data());
        ErrorInfo("G:1 缺少关键字");
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
                DebugInfo(lex.letter.data());
                ErrorInfo("H:3 缺少分号");
            }
        } else {
            DebugInfo(lex.letter.data());
            ErrorInfo("H:2 缺少标识符");
        }
    } else {
        DebugInfo(lex.letter.data());
        ErrorInfo("H:1 缺少关键字");
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
            DebugInfo(lex.letter.data());
            ErrorInfo("I:2 缺少分号");
        }
    } else {
        DebugInfo(lex.letter.data());
        ErrorInfo("I:1 缺少关键字");
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
            DebugInfo(lex.letter.data());
            ErrorInfo("J:2 缺少右花括号");
        }
    } else {
        DebugInfo(lex.letter.data());
        ErrorInfo("J:1 缺少左花括号");
    }
}

//<assignment_stat>  K
void K() {
    M();
    if (lex.letter == ";") {
        next();
        DebugInfo("K OK");
    } else {
        DebugInfo(lex.letter.data());
        ErrorInfo("K: 缺少分号");
    }
}

//<bool_expression >  L
void L() {
    N();
    l();
}

void l() {
    if (lex.letter == ">" || lex.letter == "<"
        || lex.letter == ">=" || lex.letter == "<="
        || lex.letter == "!=" || lex.letter == "==") {
        next();
        N();
    } else {
        DebugInfo(lex.letter.data());
        ErrorInfo("l :运算符不完整");
    }
}

//<assignment_expression>  M
void M() {
    if (lex.type == "ID") {
        next();
        if (lex.letter == "=") {
            next();
            N();
        } else {
            DebugInfo(lex.letter.data());
            ErrorInfo("M:2 缺少等号");
        }
    } else {
        DebugInfo(lex.letter.data());
        ErrorInfo("M:1 缺少标识符");
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
    }
//    else {
//        DebugInfo(lex.letter.data());
//        ErrorInfo("n：运算式不完整");
//    }

}

//<term>   O
void O() {
    P();
    o();
}

void o() {
    if (FOLLOW_SET["o"].count(lex.letter)) {
        DebugInfo("o Follow");
        DebugInfo(lex.letter.data());
        return;
    }
//    DebugInfo(lex.letter.data());
    if (lex.letter == "*" || lex.letter == "/") {
        next();
        P();
    }
//    else {
//        DebugInfo(lex.letter.data());
//        ErrorInfo("o : 运算符不完整");
//    }
}
//< factor >   P
void P() {
//    DebugInfo(lex.letter.data());
    if (lex.type == "ID") {
        DebugInfo("P:1 ID");
        next();
    } else if (lex.type == "NUM") {
        DebugInfo("p:2 NUM");
        next();
    } else if (lex.letter == "(") {
        next();
        N();
        if (lex.letter == ")") {
            next();
            DebugInfo("OK");
        } else {
            DebugInfo(lex.letter.data());
            ErrorInfo("P:2 缺少括号");
        }
    }
    else {
        DebugInfo(lex.letter.data());
        ErrorInfo("P:1 运算符不完整");
    }

}


int main() {
    init();
    next();
    S();
}