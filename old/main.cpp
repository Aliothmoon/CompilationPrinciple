#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// 关键字
string keywords[] = {"if", "else", "for", "while", "int", "write", "read"};
// 是否是注释
bool isAnnotator = false;
// 分析表
int AnalysisTable[12][12] =
        {
                {3,  2,  1,  4,  5,  5,  5,  8,  6,  6,  6,  7},
                {1,  1,  1,  -1, -1, -1, -1, -1, -1, -1, -1, -1},
                {2,  2,  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                {-1, -1, -1, -1, -1, -1, -1, -1, 5,  -1, -1, -1},
                {-1, -1, -1, -1, -1, -1, -1, -1, 5,  -1, -1, -1},
                {-1, -1, -1, -1, -1, -1, 9,  -1, -1, -1, -1, -1},
                {9,  9,  9,  9,  9,  9,  10, 9,  9,  9,  9,  9},
                {9,  9,  9,  9,  9,  9,  10, 11, 9,  9,  9,  9},
                {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        };
// 终态表
int FinalStateTable[7] = {1, 2, 3, 4, 5, 6, 11};
// 单词类型
string wordType[] = {"ID", "NUM"};

// 判断输入字符是否是标识符;如果是就返回分析表的所在的列
int IsAlpha(char ch) {
    int col = -1;
    switch (ch) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
            col = 2;
            break;
    }
    return col;
}

// 判断输入字符是否是数字,如果是就返回分析表的所在的列
int IsNum(char ch) {
    int col = -1;
    switch (ch) {
        case '0':
            col = 0;
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            col = 1;
            break;
    }
    return col;
}

// 判断输入字符是否是分界符,如果是就返回分析表的所在的列
int IsDemarcation(char ch) {
    int col = -1;
    switch (ch) {
        case '(':
        case ')':
        case ';':
        case '{':
        case '}':
        case ',':
            col = 3;
            break;
    }
    return col;
}

// 判断输入字符是否是运算符,如果是就返回分析表的所在的列
int IsOperator(char ch) {
    int col = -1;
    switch (ch) {
        case '+':
            col = 4;
            break;
        case '-':
            col = 5;
            break;
        case '*':
            col = 6;
            break;
        case '/':
            col = 7;
            break;
        case '=':
            col = 8;
            break;
        case '<':
            col = 9;
            break;
        case '>':
            col = 10;
            break;
        case '!':
            col = 11;
            break;
    }
    return col;
}

// 判断输入字符是否是注释符,如果是就返回分析表的所在的列
int IsAnnotator(char ch) {
    int col = -1;
    switch (ch) {
        case '/':
            col = 7;
            break;
        case '*':
            col = 6;
            break;
        default:
            if (isAnnotator)
                col = 6;
            break;
    }
    return col;
}

// 状态转换函数
int StateChange(int state, char ch) {
    // 如果是非法状态，直接返回
    if (state < 0)
        return -1;
    // col 表示字符 ch 出现在分析表中的列
    int col = -1;
    col = IsAnnotator(ch);
    if (col != -1)
        return AnalysisTable[state][col];
    col = IsAlpha(ch);
    if (col != -1)
        return AnalysisTable[state][col];
    col = IsNum(ch);
    if (col != -1)
        return AnalysisTable[state][col];
    col = IsDemarcation(ch);
    if (col != -1)
        return AnalysisTable[state][col];
    col = IsOperator(ch);
    if (col != -1)
        return AnalysisTable[state][col];

    return -1;
}

// 判断是否构成保留字,如果是，就返回wordType中对应的下标
int IsKeyWord(string word) {
    for (const auto & keyword : keywords) {
        if (word == keyword)
            return 5;
    }
    return -1;
}

// 判断单词是否合法
bool WordIsValid(int state) {
    for (int i : FinalStateTable) {
        if (state == i)
            return true;
    }
    return false;
}

// 保存合法的单词到文件中
void SaveWordIntoFile(string word, string wordType, ostream &out) {
    out << word << "	:	" << wordType << endl;
}

// 根据最后得到的状态，映射出这个单词的类型
int StateMapping(int state) {
    int mappingRes = -1;
    switch (state) {
        case 1:
            mappingRes = 0;
            break;
        case 2:
        case 3:
            mappingRes = 1;
            break;
    }
    return mappingRes;
}

// 检查单词属于哪一类，或者是错误的
void Check(int state, const string& word, ostream &out) {
    bool isValid = WordIsValid(state);
    if (isValid) {
        if (isAnnotator) {
            isAnnotator = false;
            return;
        }
        // 是否是关键字？
        if (IsKeyWord(word) != -1)
            SaveWordIntoFile(word, word, out);
            // 是否是ID或NUM？
        else if (StateMapping(state) != -1)
            SaveWordIntoFile(word, wordType[StateMapping(state)], out);
            // 其他
        else
            SaveWordIntoFile(word, word, out);
    } else {
        cout << word << "	:	" << "错误" << endl;
    }

}

int main() {
    ifstream infile;
    ofstream outfile;
    infile.open("test.txt", ios::in);
    outfile.open("lex.txt", ios::out);
    if (!infile) {
        cerr << "打开文件失败" << endl;
    }
    // 初始状态
    int state = 0;
    // 读到的字符
    string word = "";
    char ch;
    while (infile.get(ch)) {
        if (StateChange(state, ch) != -1) {
            word += ch;
            state = StateChange(state, ch);
            if (state == 9)
                isAnnotator = true;
        } else {
            Check(state, word, outfile);
            state = StateChange(0, ch);
            word = ch;
            if (ch == ' ' || ch == '\t' || ch == '\n') {
                word = "";
                state = 0;
            }
        }
    }
    if (isAnnotator)
        Check(state, word, outfile);
    infile.close();
    outfile.close();
    return 0;
}