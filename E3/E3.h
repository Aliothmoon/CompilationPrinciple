namespace E3 {
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

    int run(const char *lex = nullptr, const char *ir = nullptr);
}

