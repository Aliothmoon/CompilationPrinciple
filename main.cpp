#include "E3/E3.h"
#include "E1/E1.h"
#include "E3/Simulator.h"
#include <cstring>
#include <cstdio>

const char *JoinPath(const char *target);
// 程序所在目录
const char *ROOT_PATH = R"(E:\Projektes\Cpp\Compile)";

const char *SourceProgramPath = JoinPath(R"(Summary\E.code)");
const char *LexicalTextPath = JoinPath(R"(Summary\E.lex)");
const char *IRPath = JoinPath(R"(Summary\E.ir)");

int main() {
//    词法分析
    E1::Process(SourceProgramPath, LexicalTextPath);
//    进行语法语义分析
    E3::run(LexicalTextPath, IRPath);
//    模拟机运行
    Simulator::emulate(IRPath);
}

const char *JoinPath(const char *target) {
    auto size = strlen(ROOT_PATH) + strlen(target);
    auto path = new char[size + 1]{0};
    sprintf(path, R"(%s\%s)", ROOT_PATH, target);
    return path;
}