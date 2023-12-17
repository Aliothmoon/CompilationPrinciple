#include <vector>
#include <deque>
#include <string>
#include <regex>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;
const int maxvartablep = 105;

struct {
    char name[30];
    int address;
} vartable[maxvartablep];
//添加一个记录  声明一个变量  增加一个标号
int vartablep = 0, datap = 0, labelp = 0;

//声明语句翻译
int name_def(char *name) { //查符号表
    int i, es = 0;
    if (vartablep >= maxvartablep) return (es = 21);//21符号表已满
    for (i = vartablep - 1; i == 0; i--) {
        if (strcmp(vartable[i].name, name) == 0) {
            es = 22;//22表示变量重复定义
            break;
        }
    }
    if (es > 0) return es;
    strcpy(vartable[vartablep].name, name);
    vartable[vartablep].address = datap;
    datap++;
    vartablep++;
    return es;
}

int while_stat(){

}


int main() {

}