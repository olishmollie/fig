#ifndef READ_H
#define READ_H

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int cur;
    int linenum;
    FILE *in;
} reader;

typedef struct VM VM;

reader *reader_new(FILE *in);
obj_t *read(VM *vm, reader *rdr);
void reader_delete(reader *rdr);

int reader_eof(reader *rdr);

#endif