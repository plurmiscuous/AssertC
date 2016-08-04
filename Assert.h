//
//  Original source for assertion code:
//      http://www.acm.uiuc.edu/sigops/roll_your_own/2.a.html
//
//  Created by plurmiscuous on 2/18/15.
//  Copyright (c) 2015 </plurmiscuous>. All rights reserved.
//

#ifndef ASSERT_H
#define ASSERT_H

#include <string.h>
#include <stdlib.h>

#define FILEN (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

void p_errmsg(char*, const char*, const char*, int);
void p_strace(void);

#define Assert(exp)                                                 \
    do {                                                            \
        if (!(exp)) {                                               \
            p_errmsg( (char*)#exp, FILEN, __func__, __LINE__ );     \
            p_strace();                                             \
            abort();                                                \
        }                                                           \
    } while (0)

#endif  // ASSERT_H


