//
//  Created by plurmiscuous on 2/18/15.
//  Copyright (c) 2015 </plurmiscuous>. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>
#include <unistd.h>

#include "Assert.h"

#define DEPTH 32

void p_errmsg(char *exp, const char *file, const char* fn, int line) {
    fflush(NULL);
    fprintf(stderr, "\n");
    // standard assertion error message
    fprintf(stderr, "Assert(%s) failed in %s at %s:%d \n", exp, fn, file, line);
}

void p_strace(void) {
    // print a stack trace
    void* buffer[DEPTH];
    int count = backtrace(buffer, DEPTH);
    char** strings = backtrace_symbols(buffer, count);

    // example string[i]:
    // 1   assert                             0x0000000100000c36 main + 150

    // backtrace_symbols contain too much white space so breaking them up into
    // tokens and printing them closer together
    char* tokens[count][6];

    bool okay = true;
    char* ptr = NULL;
    for (int i = 1; i < count && okay; i++) {
        okay = (tokens[i][0] = strtok_r(strings[i], " ", &ptr)) != NULL;
        for (int j = 1; j < 6 && okay; j++)
            okay = (tokens[i][j] = strtok_r(NULL, " ", &ptr)) != NULL;
    }

    for (int i = 1; i < count && okay; i++)
        fprintf(stderr, " <%02d> %18s : %s\n", atoi(tokens[i][0]),
                tokens[i][2], tokens[i][3]);

    free(strings);
}
