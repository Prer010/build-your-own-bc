#include "my_bc.h"
#include <stdio.h>

int evaluate(const t_vec *rpn) {
    t_vec stack;
    vec_init(&stack, sizeof(long long));

    for (size_t i = 0; i < rpn->size; i++) {
        t_token *tok = vec_at(rpn, i);
        if (tok->type == TOK_INT) {
            vec_push(&stack, &tok->ival);
        } else if (tok->type == TOK_OP) {
            long long b = *(long long *)vec_back(&stack);
            vec_pop(&stack);
            long long a = 0;
            if (tok->op != '~' && tok->op != '`') {
                a = *(long long *)vec_back(&stack);
                vec_pop(&stack);
            }
            long long res = 0;
            switch (tok->op) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': 
                    if (b == 0) {
                        err_set_parse();
                        vec_free(&stack);
                        return -1;
                    }
                    res = a / b; 
                    break;
                case '%': 
                    if (b == 0) {
                        err_set_parse();
                        vec_free(&stack);
                        return -1;
                    }
                    res = a % b; 
                    break;
                case '~': res = -b; break;
                case '`': res = +b; break;
                default:
                    err_set_parse();
                    vec_free(&stack);
                    return -1; // undefined
            }
            vec_push(&stack, &res);
        } else {
            err_set_parse();
            vec_free(&stack);
            return -1; // undefined
        }
    }

    long long result = *(long long *)vec_back(&stack);
    vec_free(&stack);
    return (int)result;
}