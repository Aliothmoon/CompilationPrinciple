#include <vector>
#include <deque>
#include <string>
#include <regex>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <thread>

using namespace std;
const string EMPTY_STRING{"$$$"};
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
map<string, set<string> > FOLLOW_SET = {
        {"S", {"#"}},
        {"A", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}",}},
        {"B", {"}"}},
        {"e", {"if", "for", "while", "read", "write", "{",  "ID", ";", "}", "else"}},
        {"n", {"<",  ">",   "==",    "!=",   ">=",    "<=", ")",  ";"}},
        {"o", {"<",  ">",   "==",    "!=",   ">=",    "<=", ")",  ";", "+", "-"}}
};
const set<string> B_STATUS_SET = {"E", "F", "G", "H", "I", "J", "K"};
struct Lex {
    string type;
    string letter;
};


Lex lex{};

deque<Lex> letters;
const char *INPUT_PATH = R"(E:\Projektes\Cpp\Compile\lex.txt)";


void ErrorInfo(const char *message) {
    cout << "Error: " << message << endl;
    exit(-1);
}

void DebugInfo(const char *message) {
    cout << "Debug: " << message << endl;
}

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

void A() {
//  判断空串
    if (FOLLOW_SET["A"].count(lex.letter) || FOLLOW_SET["A"].count(lex.type)) {
        return;
    }
    C();
    A();
}

void B() {
    //  判断空串
    if (FOLLOW_SET["B"].count(lex.letter)) {
        return;
    }
    D();
    B();
}

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

void L() {
    N();
    l();
}

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

void O() {
    P();
    o();
}

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
        ErrorInfo("o : 运算符不完整");
    }
}

int main() {

    init();
    next();
    S();
}