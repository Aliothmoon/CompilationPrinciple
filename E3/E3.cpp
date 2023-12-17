#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include "E3.h"

#define maxvartablep 500//������ű������
using std::map;
using std::string;
namespace E3 {


    template<typename T, typename S>
    void DebugInfo(T t, S s = nullptr) {
        if (s == nullptr) {
            std::cout << "Debug: " << t << std::endl;
        } else {
            std::cout << "Debug: " << t << ":" << s << std::endl;
        }

    }

    char token[20], token1[40];//token���浥�ʷ��ţ�token1���浥��ֵ
    char Scanout[300], Codeout[300]; //����ʷ���������ļ���
    FILE *fp, *fout; //����ָ����������ļ���ָ��

    struct VarSymbol {//������ű�ṹ
        string name; // ��̬��չ����������
        int address{};
        bool initialized{}; // �ж��Ƿ񱻸���ֵ
    };


    map <string, VarSymbol> SymbolTable; // ʹ��Hash�ṹ�ķ��ű�

    //�ķ��ű��������maxvartablep����¼

    int vartablep = 0, labelp = 0, datap = 0;


    //������ű���@name-def��n, t�ĳ������£�
    int name_def(char *name) {
        int es = 0;
        if (vartablep >= maxvartablep) return (21);
        //        ����
        //    for (i = vartablep - 1; i == 0; i--)//����ű�
        //����ű�
        auto sname = string{name};
        if (SymbolTable.count(sname)) {
            es = 22;//22��ʾ�����ظ�����
        }
        if (es > 0) return es;
//        ����������
        SymbolTable[sname] = VarSymbol{
                sname, datap,
        };
        datap++;//����һ����Ԫ��������ָ���1
        vartablep++;
        return es;
    }

    //��ѯ���ű��ص�ַ
    int lookup(char *name, int &paddress, InitializationAction action) {
        int es = 0;

//        �����жϳ�ʼ��  ADDRESSABLE
        auto sname = string{name};
//        �����ű��Ƿ����
        if (SymbolTable.count(sname)) {
            VarSymbol &symbol = SymbolTable[sname];
            paddress = symbol.address;
            if (action == LEFT_VALUE && !symbol.initialized) {
                DebugInfo("��ʼ��", name);
                symbol.initialized = true;
            } else if (action == RIGHT_VALUE && !symbol.initialized) {
//                    δ��ʼ��
                es = 24;
            }
            return es;
        }
        es = 23;//����û������
        return es;
    }

    //�﷨������������������ɳ���
    int TESTparse() {
        int es = program();
        printf("==�﷨������������������ɳ�����==\n");
        switch (es) {
            case 0:
                printf("�﷨����������ɹ������ɳ����������!\n");
                break;
            case 10:
                printf("���ļ� %sʧ��!\n", Scanout);
                break;
            case 1:
                printf("ȱ��{!\n");
                break;
            case 2:
                printf("ĩβȱ��}!\n");
                break;
            case 3:
                printf("ȱ�ٱ�ʶ��!\n");
                break;
            case 4:
                printf("�ٷֺ�!\n");
                break;
            case 5:
                printf("ȱ��(!\n");
                break;
            case 6:
                printf("ȱ��)!\n");
                break;
            case 7:
                printf("ȱ�ٲ�����!\n");
                break;
            case 8:
                printf("�м�ȱ��}!\n");
                break;
            case 21:
                printf("���ű����!\n");
                break;
            case 22:
                printf("�����ظ�����!\n");
                break;
            case 23:
                printf("����δ����!\n");
                break;
            case 24:
                printf("����δ����ֵ!\n");
                break;
            default:
                break;
        }
        fclose(fp);
        fclose(fout);
        return es;
    }

    //program::='{'<declaration_list><statement_list>'}'
    int program() {
        int es;
        fscanf(fp, "%s %s\n", token, token1);
        //�ж��Ƿ�'{'
        if (strcmp(token, "{") != 0) {
            es = 1;
            return es;
        }
        printf("%s %s\n", token, token1);
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = declaration_list();
        if (es > 0) return es;
        es = statement_list();
        if (es > 0) return es;
        //�ж��Ƿ�'}'
        if (strcmp(token, "}") != 0) {
            es = 2;
            return es;
        }
        fprintf(fout, "        STOP\n");//����ָֹͣ��

        printf("      ���ű�    \n");
        printf("   %-5s   %-5s   %-5s\n", "����", "��ַ", "�Ƿ��ʼ��");
        for (const auto &item: SymbolTable) {
            auto symbol = item.second;
            printf("   %-5s   %-5d   %-7s\n", symbol.name.c_str(), symbol.address,
                   symbol.initialized ? "��" : "��");

        }
        puts("");

        return es;
    }

    //<declaration_list>::=
    //<declaration_list><declaration_stat>|<declaration_stat>
    //�ĳ�<declaration_list>::={<declaration_stat>}
    int declaration_list() {
        int es = 0;
        while (strcmp(token, "int") == 0) {
            es = declaration_stat();
            if (es > 0) return es;
        }
        return es;
    }

    //<declaration_stat>��vartablep,datap,codep ->int ID��n@name-def��n,t;
    int declaration_stat() {
        int es = 0;
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        if (strcmp(token, "ID")) return (es = 3);  //���Ǳ�ʶ��
        es = name_def(token1);//������ű�
        if (es > 0) return es;
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        if (strcmp(token, ";") != 0) return (es = 4);
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        return es;
    }

    //<statement_list>::=<statement_list><statement>|<statement>
    //�ĳ�<statement_list>::={<statement>}
    int statement_list() {
        int es = 0;
        while (es == 0 && (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0 ||
                           strcmp(token, "if") == 0 || strcmp(token, "while") == 0 || strcmp(token, "for") == 0 ||
                           strcmp(token, "read") == 0 || strcmp(token, "write") == 0 ||
                           strcmp(token, "{") == 0))   //�ж�first����
        {
            es = statement();
            if (es > 0) return es;
        }
        return es;
    }

    //<statement>::= <if_stat>|<while_stat>|<for_stat>
    //               |<compound_stat> |<expression_stat>

    int statement() {
        int es = 0;
        if (strcmp(token, "if") == 0) es = if_stat();//<IF���>
        if (es == 0 && strcmp(token, "while") == 0) es = while_stat();//<while���>
        if (es == 0 && strcmp(token, "for") == 0) es = for_stat();//<for���>
        //���ڴ˴����do������
        if (es == 0 && strcmp(token, "read") == 0) es = read_stat();//<read���>
        if (es == 0 && strcmp(token, "write") == 0) es = write_stat();//<write���>
        if (es == 0 && strcmp(token, "{") == 0) {
            printf("AAA %s\n", token);
            es = compound_stat();
            return es;
        }  //!!<�������>ִ�к�Ӧ�����Ϸ��أ����򻹻�ִ����һ��if.
        if (es == 0 && (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0))
            es = expression_stat();//<���ʽ���>
        return es;
    }

    //<IF_stat>::= if (<expr>) <statement > [else < statement >]
    /*
    if (<expression>)@BRF��label1 <statement > @BR��label2 @SETlabel��label1
                      [ else < statement >] @SETlabel��label2

    ���ж������ŵĺ�������
      @BRF��label1 ����� BRF label1,
      @BR��label2����� BR label2,
      @SETlabel��label1�����ñ��label1
      @SETlabel��label2�����ñ��label2
    */
    int if_stat() {
        int es, label1, label2;  //if
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        if (strcmp(token, "(") != 0) return (es = 5);  //��������
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = expression();
        if (es > 0) return es;
        if (strcmp(token, ")") != 0) return (es = 6); //��������
        label1 = labelp++;//��label1��ס����Ϊ��ʱҪת��ı��
        fprintf(fout, "        BRF LABEL%d\n", label1);//�����ת��ָ��
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = statement();
        if (es > 0) return es;
        label2 = labelp++;//��label2��סҪת��ı��
        fprintf(fout, "        BR LABEL%d\n", label2);//���������ת��ָ��
        fprintf(fout, "LABEL%d:\n", label1);//����label1��ס�ı��
        if (strcmp(token, "else") == 0)//else���ִ���
        {
            fscanf(fp, "%s %s\n", token, token1);
            printf("%s %s\n", token, token1);
            es = statement();
            if (es > 0) return es;
        }
        fprintf(fout, "LABEL%d:\n", label2);//����label2��ס�ı��
        return es;
    }

    //<while_stat>::= while (<expr >) < statement >
    //<while_stat>::=while @SET��labellabel1(<expression>) @BRF��label2
    //				<statement >@BR��label1 @SETlabel��label2
    //�����������£�
    //@SETlabel��label1�����ñ��label1
    //@BRF��label2 ����� BRF label2,
    //@BR��label1����� BR label1,
    //@SETlabel��label2�����ñ��label2
    int while_stat() {
        int es, label1, label2;
        label1 = labelp++;
        fprintf(fout, "LABEL%d:\n", label1);//����label1���
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        if (strcmp(token, "(") != 0) return (es = 5);  //��������
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = expression();
        if (es > 0) return es;
        if (strcmp(token, ")") != 0) return (es = 6); //��������
        label2 = labelp++;
        fprintf(fout, "        BRF LABEL%d\n", label2);//�����ת��ָ��
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = statement();
        if (es > 0) return es;
        fprintf(fout, "        BR LABEL%d\n", label1);//���������ת��ָ��
        fprintf(fout, "LABEL%d:\n", label2);//����label2���
        return es;
    }

    //<for_stat>::= for(<expr>,<expr>,<expr>)<statement>
    /*
    <for_stat>::=for (<expression>;
                 @SETlabel��label1< expression >@BRF��label2@BR��label3;
                 @SETlabel��label4 < expression >@BR��label1)
                 @SETlabel��label3 <��� >@BR��label4@SETlabel��label2
    �������ͣ�
    1.	@SETlabel��label1�����ñ��label1
    2.	@BRF��label2 ����� BRF label2,
    3.	@BR��label3����� BR label3,
    4.	@SETlabel��label4�����ñ��label4
    5.	@BR��label1����� BR label1,
    6.	@SETlabel��label3�����ñ��label3
    7.	@BR��label4����� BR label4,
    8.	@SETlabel��label2�����ñ��label2
    */
    int for_stat() {
        int es, label1, label2, label3, label4;
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        if (strcmp(token, "(") != 0) return (es = 5);  //��������
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = expression();
        if (es > 0) return es;
        if (strcmp(token, ";") != 0) return (es = 4);  //�ٷֺ�
        label1 = labelp++;
        fprintf(fout, "LABEL%d:\n", label1);//����label1���
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = expression();
        if (es > 0) return es;
        label2 = labelp++;
        fprintf(fout, "        BRF LABEL%d\n", label2);//���������ת��ָ��
        label3 = labelp++;
        fprintf(fout, "        BR LABEL%d\n", label3);//���������ת��ָ��
        if (strcmp(token, ";") != 0) return (es = 4);  //�ٷֺ�
        label4 = labelp++;
        fprintf(fout, "LABEL%d:\n", label4);//����label4���
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = expression();
        if (es > 0) return es;
        fprintf(fout, "        BR LABEL%d\n", label1);//���������ת��ָ��
        if (strcmp(token, ")") != 0) return (es = 6); //��������
        fprintf(fout, "LABEL%d:\n", label3);//����label3���
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = statement();
        if (es > 0) return es;
        fprintf(fout, "        BR LABEL%d\n", label4);//���������ת��ָ��
        fprintf(fout, "LABEL%d:\n", label2);//����label2���
        return es;

    }

    //<write_stat>::=write <expression>;
    //<write_stat>::=write <expression>@OUT;
    //�������ͣ�
    //@ OUT����� OUT

    int write_stat() {
        int es = 0;
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = expression();
        if (es > 0)return es;
        if (strcmp(token, ";") != 0) return (es = 4);  //�ٷֺ�
        fprintf(fout, "        OUT\n");//���ָ��
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        return es;
    }

    //<read_stat>::=read ID;
    //<read_stat>::=read ID��n LOOK��n��d @IN@STI��d;
    //�������ͣ�
    //@LOOK��n��d:����ű�n������������ַd; û�У�����û����
    //@IN�����IN
    //@STI��d�����ָ�����STI  d
    int read_stat() {
        int es = 0, address;
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        if (strcmp(token, "ID") != 0) return (es = 3);  //�ٱ�ʶ��
        es = lookup(token1, address, LEFT_VALUE);
        if (es > 0) return es;
        fprintf(fout, "        IN   \n"); //����ָ��
        fprintf(fout, "        STI   %d\n", address); //ָ��
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        if (strcmp(token, ";") != 0) return (es = 4);  //�ٷֺ�
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        return es;
    }

    //<compound_stat>::='{'<statement_list>'}'
    //������亯��
    int compound_stat() {
        int es = 0;
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = statement_list();
        //�м���}
        if (strcmp(token, "}") != 0)
            return (es = 8);
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        return es;
    }

    //<expression_stat>::=<expression>;|;
    int expression_stat() {
        int es = 0;
        if (strcmp(token, ";") == 0) {
            fscanf(fp, "%s %s\n", token, token1);
            printf("%s %s\n", token, token1);
            return es;
        }
        es = expression();
        if (es > 0) return es;
        if (strcmp(token, ";") == 0) {
            fscanf(fp, "%s %s\n", token, token1);
            printf("%s %s\n", token, token1);
            return es;
        } else {
            es = 4;
            return es;//�ٷֺ�
        }
    }

    //<expression>::=ID��n@LOOK��n��d@ASSIGN=<bool_expr>@STO��d |<bool_expr>
    int expression() {
        int es = 0, fileadd;
        char token2[20], token3[40], copy[40];
        if (strcmp(token, "ID") == 0) {
            fileadd = ftell(fp);   //@ASSIGN��ס��ǰ�ļ�λ��
            fscanf(fp, "%s %s\n", token2, token3);
            //'='
            if (strcmp(token2, "=") == 0) {
                printf("%s %s\n", token2, token3);
                int address;
                es = lookup(token1, address, ADDRESSABLE);
                if (es > 0) return es;
                strcpy(copy, token1);
                fscanf(fp, "%s %s\n", token, token1);
                printf("%s %s\n", token, token1);
                es = bool_expr();
                if (es > 0) return es;
                es = lookup(copy, address, LEFT_VALUE);
                fprintf(fout, "        STO %d\n", address);

            } else {
                fseek(fp, fileadd, 0); //����'='���ļ�ָ��ص�'='ǰ�ı�ʶ��
//			printf("%s %s\n",token,token1);
                es = bool_expr();
                if (es > 0) return es;
            }
        } else es = bool_expr();
        return es;
    }


    //<bool_expr>::=<additive_expr>
    //           |< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >
    /*
    <bool_expr>::=<additive_expr>
    |< additive_expr >><additive_expr>@GT
    |< additive_expr ><<additive_expr>@LES
    |< additive_expr >>=<additive_expr >@GE
    |< additive_expr ><=< additive_expr >@LE
    |< additive_expr >==< additive_expr >@EQ
    |< additive_expr >!=< additive_expr >@NOTEQ
    */
    int bool_expr() {
        int es = 0;
        es = additive_expr();
        if (es > 0) return es;
        if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0
            || strcmp(token, "<") == 0 || strcmp(token, "<=") == 0
            || strcmp(token, "==") == 0 || strcmp(token, "!=") == 0) {
            char token2[20];
            strcpy(token2, token);//���������
            fscanf(fp, "%s %s\n", token, token1);
            printf("%s %s\n", token, token1);
            es = additive_expr();
            if (es > 0) return es;
            if (strcmp(token2, ">") == 0) fprintf(fout, "        GT\n");
            if (strcmp(token2, ">=") == 0) fprintf(fout, "        GE\n");
            if (strcmp(token2, "<") == 0) fprintf(fout, "        LES\n");
            if (strcmp(token2, "<=") == 0) fprintf(fout, "        LE\n");
            if (strcmp(token2, "==") == 0) fprintf(fout, "        EQ\n");
            if (strcmp(token2, "!=") == 0) fprintf(fout, "        NOTEQ\n");
        }
        return es;
    }

    //<additive_expr>::=<term>{(+|-)< term >}
    //< additive_expr>::=<term>{(+< term >@ADD |-<��>@SUB)}

    int additive_expr() {
        int es = 0;
        es = term();
        if (es > 0) return es;
        while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0) {
            char token2[20];
            strcpy(token2, token);
            fscanf(fp, "%s %s\n", token, token1);
            printf("%s %s\n", token, token1);
            es = term();
            if (es > 0) return es;
            if (strcmp(token2, "+") == 0) fprintf(fout, "        ADD\n");
            if (strcmp(token2, "-") == 0) fprintf(fout, "        SUB\n");
        }
        return es;
    }

    //< term >::=<factor>{(*| /)< factor >}
    //< term >::=<factor>{(*< factor >@MULT | /< factor >@DIV)}
    int term() {
        int es = 0;
        es = factor();
        if (es > 0) return es;
        while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
            char token2[20];
            strcpy(token2, token);
            fscanf(fp, "%s %s\n", token, token1);
            printf("%s %s\n", token, token1);
            es = factor();
            if (es > 0) return es;
            if (strcmp(token2, "*") == 0) fprintf(fout, "        MULT\n");
            if (strcmp(token2, "/") == 0) fprintf(fout, "        DIV\n");
        }
        return es;
    }

    //< factor >::=(<additive_expr>)| ID|NUM
    //< factor >::=(< expression >)| ID��n@LOOK��n��d@LOAD��d |NUM��i@LOADI��i
    int factor() {
        int es = 0;

        if (strcmp(token, "(") == 0) {
            fscanf(fp, "%s %s\n", token, token1);
            printf("%s %s\n", token, token1);
            es = expression();
            if (es > 0) return es;
            if (strcmp(token, ")") != 0) return (es = 6); //��������
            fscanf(fp, "%s %s\n", token, token1);
            printf("%s %s\n", token, token1);
        } else {

            if (strcmp(token, "ID") == 0) {
                int address;
                es = lookup(token1, address, RIGHT_VALUE); //����ű���ȡ������ַ
                if (es > 0) return es;//����û����
                fprintf(fout, "        LOAD %d\n", address);
                fscanf(fp, "%s %s\n", token, token1);
                printf("%s %s\n", token, token1);
                return es;
            }
            if (strcmp(token, "NUM") == 0) {
                fprintf(fout, "        LOADI %s\n", token1);
                fscanf(fp, "%s %s\n", token, token1);
                printf("%s %s\n", token, token1);
                return es;
            } else {
                es = 7;//ȱ�ٲ�����
                return es;
            }
        }
        return es;
    }

    int run(const char *lex, const char *ir) {
        int es;
        if (lex == nullptr) {
            printf("�������﷨������ȷ����ļ���������·������");
            scanf("%s", Scanout);
        } else {
            strcpy(Scanout, lex);
        }

        if ((fp = fopen(Scanout, "r")) == nullptr) {
            printf("\n��%s����!\n", Scanout);
            es = 10;
            return es;
        }

        if (ir == nullptr) {
            printf("�������м�����ļ���������·������");
            scanf("%s", Codeout);
        } else {
            strcpy(Codeout, ir);
        }

        if ((fout = fopen(Codeout, "w")) == nullptr) {
            printf("\n����%s����!\n", Codeout);
            es = 10;
            return es;
        }

        printf("========��ʼ�﷨���������========\n");

        es = TESTparse();    //���﷨����
        if (es == 0) printf("����������м����ɹ�!\n");
        else printf("�����������!\n");
        return 0;
    }
}