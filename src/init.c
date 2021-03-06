#include "common.h"
#include "init.h"

/* TODO: possible to specity a relative path instead? */
#define STDLIB "/usr/local/Cellar/fig/"VERSION"/lib/lib.fig"

void register_builtin(VM *vm, obj_t *env, builtin fun, char *bname) {
    obj_t *var = mk_sym(vm, bname);
    obj_t *fn = mk_builtin(vm, bname, fun);
    env_define(vm, env, var, fn);

    /* pop global symbols and builtins off the stack */
    pop(vm);
    pop(vm);
}

obj_t *global_env(VM *vm) {
    obj_t *env = mk_env(vm);

    register_builtin(vm, env, builtin_plus, "+");
    register_builtin(vm, env, builtin_minus, "-");
    register_builtin(vm, env, builtin_times, "*");
    register_builtin(vm, env, builtin_divide, "/");
    register_builtin(vm, env, builtin_remainder, "mod");

    register_builtin(vm, env, builtin_gt, ">");
    register_builtin(vm, env, builtin_gte, ">=");
    register_builtin(vm, env, builtin_lt, "<");
    register_builtin(vm, env, builtin_lte, "<=");
    register_builtin(vm, env, builtin_numeq, "=");

    register_builtin(vm, env, builtin_is_null, "null?");
    register_builtin(vm, env, builtin_is_boolean, "boolean?");
    register_builtin(vm, env, builtin_is_symbol, "symbol?");
    register_builtin(vm, env, builtin_is_num, "number?");
    register_builtin(vm, env, builtin_is_integer, "integer?");
    register_builtin(vm, env, builtin_is_char, "char?");
    register_builtin(vm, env, builtin_is_string, "string?");
    register_builtin(vm, env, builtin_is_pair, "pair?");
    register_builtin(vm, env, builtin_is_list, "list?");
    register_builtin(vm, env, builtin_is_vector, "vector?");
    register_builtin(vm, env, builtin_is_proc, "procedure?");
    register_builtin(vm, env, builtin_is_equal, "eq?");

    register_builtin(vm, env, builtin_char_to_int, "char->int");
    register_builtin(vm, env, builtin_int_to_char, "int->char");
    register_builtin(vm, env, builtin_number_to_string, "number->string");
    register_builtin(vm, env, builtin_string_to_number, "string->number");
    register_builtin(vm, env, builtin_symbol_to_string, "symbol->string");
    register_builtin(vm, env, builtin_string_to_symbol, "string->symbol");

    register_builtin(vm, env, builtin_cons, "cons");
    register_builtin(vm, env, builtin_car, "car");
    register_builtin(vm, env, builtin_cdr, "cdr");
    register_builtin(vm, env, builtin_setcar, "set-car!");
    register_builtin(vm, env, builtin_setcdr, "set-cdr!");

    register_builtin(vm, env, builtin_make_vector, "make-vector");
    register_builtin(vm, env, builtin_vector_length, "vector-length");
    register_builtin(vm, env, builtin_vector_ref, "vector-ref");
    register_builtin(vm, env, builtin_vector_set, "vector-set!");

    register_builtin(vm, env, builtin_string_append, "string-append");

    register_builtin(vm, env, builtin_display, "display");
    register_builtin(vm, env, builtin_env, "env");
    register_builtin(vm, env, builtin_load, "load");
    register_builtin(vm, env, builtin_exit, "exit");

    register_builtin(vm, env, builtin_raise, "raise");

    return env;
}

void init() {
    vm = vm_new();
    symbol_table = table_new();

    true = mk_bool(vm, 1);
    false = mk_bool(vm, 0);

    the_empty_list = mk_nil(vm);

    quote_sym = mk_sym(vm, "quote");
    quasiquote_sym = mk_sym(vm, "quasiquote");
    unquote_sym = mk_sym(vm, "unquote");

    define_sym = mk_sym(vm, "define");
    set_sym = mk_sym(vm, "set!");
    if_sym = mk_sym(vm, "if");
    lambda_sym = mk_sym(vm, "lambda");
    begin_sym = mk_sym(vm, "begin");

    universe = global_env(vm);
    read_file(vm, STDLIB);
}
