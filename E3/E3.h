namespace E3 {
    enum InitializationAction {
//        作为左值的时候
        LEFT_VALUE,
//        作为右值的时候
        RIGHT_VALUE,
//        只对其寻址,但不检验初始化
        ADDRESSABLE
    };

    int program();

    int statement();

    int expression_stat();

    int expression();

    int bool_expr();

    int additive_expr();

    int term();

    int factor();

    int if_stat();

    int while_stat();

    int for_stat();

    int write_stat();

    int read_stat();

    int declaration_stat();

    int declaration_list();

    int statement_list();

    int compound_stat();

    int name_def(char *name);

    int lookup(char *name, int *paddress, InitializationAction action);

    int run(const char *lex = nullptr, const char *ir = nullptr);

    template<typename T>
    void DebugInfo(T t);


}

