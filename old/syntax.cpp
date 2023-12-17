#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<stack>
#include<vector>
#include<windows.h>

using namespace std;
// 分析表
string M[21][27] =
        {
                {"",         "",             "",                    "",              "",          "",          "{ A B }", "",  "",       "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", ""},
                {"C A",      "ε",            "ε",                   "ε",             "ε",         "ε",         "ε",       "ε", "ε",      "ε",   "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", "ε"},
                {"",         "D B",          "D B",                 "D B",           "D B",       "D B",       "D B",     "ε", "D B",    "D B", "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", "ε"},
                {"int ID ;", "",             "",                    "",              "",          "",          "",        "",  "",       "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", ""},
                {"",         "E",            "G",                   "F",             "H",         "I",         "J",       "",  "K",      ";",   "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", ""},
                {"",         "if ( L ) D e", "",                    "",              "",          "",          "",        "",  "",       "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", ""},
                {"",         "ε",            "ε",                   "ε",             "ε",         "ε",         "ε",       "ε", "ε",      "ε",   "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "else D | ε", "",      "",  "",    "", "", "ε"},
                {"",         "",             "",                    "while ( L ) D", "",          "",          "",        "",  "",       "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", ""},
                {"",         "",             "for ( M ; L ; M ) D", "",              "",          "",          "",        "",  "",       "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", ""},
                {"",         "",             "",                    "",              "read ID ;", "",          "",        "",  "",       "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", ""},
                {"",         "",             "",                    "",              "",          "write N ;", "",        "",  "",       "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", ""},
                {"",         "",             "",                    "",              "",          "",          "{ B }",   "",  "",       "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", ""},
                {"",         "",             "",                    "",              "",          "",          "",        "",  "M ;",    "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", ""},
                {"",         "",             "",                    "",              "",          "",          "",        "",  "N l",    "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "N l",   "",  "N l", "", "", ""},
                {"",         "",             "",                    "",              "",          "",          "",        "",  "",       "",    "",      "",      "",      "",      "> N", "< N", ">= N", "<= N", "== N", "!= N", "",           "",      "",  "",    "", "", ""},
                {"",         "",             "",                    "",              "",          "",          "",        "",  "ID = N", "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "",      "",  "",    "", "", ""},
                {"",         "",             "",                    "",              "",          "",          "",        "",  "O n",    "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "O n",   "",  "O n", "", "", ""},
                {"",         "",             "",                    "",              "",          "",          "",        "",  "",       "ε",   "+ O n", "- O n", "",      "",      "ε",   "ε",   "ε",    "ε",    "ε",    "ε",    "",           "",      "ε", "",    "", "", "ε"},
                {"",         "",             "",                    "",              "",          "",          "",        "",  "P o",    "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "P o",   "",  "P o", "", "", ""},
                {"",         "",             "",                    "",              "",          "",          "",        "",  "",       "ε",   "ε",     "ε",     "* P o", "/ P o", "ε",   "ε",   "ε",    "ε",    "ε",    "ε",    "",           "",      "ε", "",    "", "", "ε"},
                {"",         "",             "",                    "",              "",          "",          "",        "",  "ID",     "",    "",      "",      "",      "",      "",    "",    "",     "",     "",     "",     "",           "( N )", "",  "NUM", "", "", ""}
        };

// 非终态集合
string VN[] = {"S", "A", "B", "C", "D", "E", "e", "F", "G", "H", "I", "J", "K", "L", "l", "M", "N", "n", "O", "o", "P"};
// 终态集合
string VT[] = {"int", "if", "for", "while", "read", "write", "{", "}", "ID", ";", "+", "-", "*", "/", ">", "<", ">=",
               "<=", "==", "!=", "else", "(", ")", "NUM", "=", ",", "#"};

// 判断是否属于终态集合
bool IsBelongToVT(string str) {
    for (int i = 0; i < sizeof(VT) / sizeof(string) - 1; ++i)
        if (str == VT[i])
            return true;
    return false;
}

// 错误
void Error(string lineOfWord, string errInfo) {
    cout << "Error in line " << lineOfWord << ", errInfo: " << errInfo << endl;
}

// 通过产生式左部和输入符号得到产生式右部
string GetFormulaRight(string formulaLeft, string inputSymbol) {
    int row = 0, col = 0;
    for (int i = 0; i < sizeof(VN) / sizeof(string); ++i) {
        if (formulaLeft == VN[i]) {
            row = i;
            break;
        }
    }
    for (int i = 0; i < sizeof(VT) / sizeof(string); ++i) {
        if (inputSymbol == VT[i]) {
            col = i;
            break;
        }
    }
    return M[row][col];
}

// 得到下一个单词
string GetNextSymbol(vector<string> words, int i) {
    if (i >= words.size())
        return "";
    return words[i];
}

// 语法分析代码
void Test(vector<string> &wordsType, vector<string> &words, vector<string> &lineOfWord, int &symbolIndex,
          stack<string> &istack, string &word, bool &flag) {
    string top = istack.top();
    istack.pop();
    if (IsBelongToVT(top))
        if (top == word) {
            word = GetNextSymbol(wordsType, ++symbolIndex);

        } else {
            Error(lineOfWord[symbolIndex], words[symbolIndex]);
            flag = false;
        }
    else if (top == "#")
        if (top == word) {
            cout << "成功" << endl;
            flag = false;
        } else {
            Error(lineOfWord[symbolIndex], words[symbolIndex]);
            flag = false;
        }
    else if (GetFormulaRight(top, word) != "") {
        string formulaRight = GetFormulaRight(top, word);
        if (formulaRight != "ε" && formulaRight.find("ε") != -1) {
            formulaRight = GetNextSymbol(wordsType, symbolIndex + 1) == "}" ? "ε" :
                           formulaRight.substr(0, formulaRight.find("|"));
        }
        if (formulaRight != "ε") {
            istringstream tempStream(formulaRight);
            vector<string> words;
            string tempStr = "";
            while (tempStream >> tempStr) {
                words.push_back(tempStr);
            }
            for (int i = words.size() - 1; i >= 0; --i) {
                istack.push(words[i]);
            }
        }
    } else {
        Error(lineOfWord[symbolIndex], words[symbolIndex]);
        flag = false;
    }

}

// 得到词法分析之后的所有单词的信息
void GetAllWords(ifstream &ifile, vector<string> &wordsType, vector<string> &lineOfWord, vector<string> &words) {
    string temp = "";
    while (true) {
        ifile >> temp;
        if (!ifile)
            break;
        wordsType.push_back(temp);
        ifile >> temp;
        lineOfWord.push_back(temp);
        ifile >> temp;
        ifile >> temp;
        words.push_back(temp);

    }
    wordsType.push_back("#");
    lineOfWord.push_back("last line");
    words.push_back("miss something");
}

// 调用词法分析程序，并生成lex.txt文件，文件中包含单词的类别，所在行号，单词本身
void WordAnalysis() {
    SHELLEXECUTEINFO shellInfo;
    memset(&shellInfo, 0, sizeof(shellInfo));
    shellInfo.cbSize = sizeof(shellInfo);
    shellInfo.hwnd = NULL;
    shellInfo.lpVerb = "open";
    shellInfo.lpFile = "F:\\vs2017\\编译原理\\test1\\Debug\\test1.exe";
    shellInfo.lpParameters = "F:\\vs2017\\编译原理\\test2\\test2\\test.txt F:\\vs2017\\编译原理\\test2\\test2\\lex.txt";
    shellInfo.nShow = SW_SHOWNORMAL;
    shellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    bool bResult = ShellExecuteEx(&shellInfo);
}

int main() {
    WordAnalysis();
    stack<string> istack; // 分析栈
    ifstream ifile("lex.txt", ios::in);
    istack.push("#");
    istack.push("S");
    vector<string> wordsType;  // 单词类别
    vector<string> words;  // 单词本身
    vector<string> lineOfWord;  // 单词所在行号
    GetAllWords(ifile, wordsType, lineOfWord, words);
    string word = wordsType[0];
    bool flag = true;  // 用来表示分析是否成功，false表示成功
    int symbolIndex = 0;    // 用来标识读到了第几个单词
    while (flag) {
        Test(wordsType, words, lineOfWord, symbolIndex, istack, word, flag);
    }
    return 0;
}