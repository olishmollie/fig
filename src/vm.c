#include "builtins.h"
#include "common.h"
#include "vm.h"

#define INITIAL_GC_THRESHOLD 500

VM *vm_new() {
    VM *vm = malloc(sizeof(VM));
    vm->alloc_list = NULL;
    vm->gc_threshold = INITIAL_GC_THRESHOLD;
    vm->sp = 0;
    vm->obj_count = 0;
    return vm;
}

void push(VM *vm, obj_t *item) {
    if (vm->obj_count >= MAX_STACK_SIZE) {
        fprintf(stderr, "stack overflow\n");
        builtin_exit(vm, NULL);
    }
    vm->stack[vm->sp++] = item;
}

obj_t *pop(VM *vm) {
    if (vm->obj_count == 0) {
        fprintf(stderr, "stack underflow\n");
        builtin_exit(vm, NULL);
    }
    return vm->stack[--vm->sp];
}

void popn(VM *vm, int n) {
    for (int i = 0; i < n; i++) {
        pop(vm);
    }
}

void stack_print(VM *vm) {
    printf("=========================\n");
    for (int i = 0; i < vm->sp; i++) {
        println(vm->stack[i]);
    }
    printf("=========================\n");
}

void mark(obj_t *object) {
    if (!object || object->marked)
        return;

    if (is_pair(object)) {
        mark(object->car);
        mark(object->cdr);
    } else if (is_fun(object)) {
        mark(object->fname);
        mark(object->params);
        mark(object->body);
    }

    object->marked = 1;
}

void mark_all(VM *vm) {
    mark(universe);
    for (int i = 0; i < vm->sp; i++) {
        mark(vm->stack[i]);
    }
}

void sweep(VM *vm) {
    obj_t **object = &vm->alloc_list;
    while (*object) {
        if (!(*object)->marked) {
            obj_t *unreached = *object;
            *object = unreached->next;
            obj_delete(unreached);
        } else {
            (*object)->marked = 0;
            object = &(*object)->next;
        }
    }
}

void gc(VM *vm) {
    mark_all(vm);
    sweep(vm);
}

void cleanup(VM *vm) {
    obj_t *object = vm->alloc_list;
    while (object) {
        obj_t *tmp = object->next;
        obj_delete(object);
        object = tmp;
    }

    free(vm);
    table_delete(symbol_table);
}
