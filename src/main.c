#include "my_bc.h"
#include <stdio.h>

static void print_token(const t_token *tok) {
    if (tok->type == TOK_INT) {
        printf("%ld ", (long)tok->ival);
    } else if (tok->type == TOK_OP) {
        printf("%c ", tok->op);
    } else if (tok->type == TOK_LPAREN) {
        printf("( ");
    } else if (tok->type == TOK_RPAREN) {
        printf(") ");
    }
}

static void print_tokens(const t_vec *tokens, const char *label) {
    printf("%s: ", label);
    for (size_t i = 0; i < tokens->size; i++) {
        t_token *tok = vec_at(tokens, i);
        print_token(tok);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        err_set_parse();
        err_print_and_clear();
        return 1;
    }
    (void)argv;

    // vector tokens, vector rpn
    t_vec tokens, rpn;
    vec_init(&tokens, sizeof(t_token));
    vec_init(&rpn, sizeof(t_token));

    // lexer
    lex(argv[1], &tokens);
    print_tokens(&tokens, "Tokens");

    // shunting yard -> rpn 
    to_rpn(&tokens, &rpn);
    print_tokens(&rpn, "RPN");

    // evaluate rpn
    int result = evaluate(&rpn);

    // success
    printf("Result: %d\n", result);

    vec_free(&tokens);
    vec_free(&rpn);
    return 0;
}
