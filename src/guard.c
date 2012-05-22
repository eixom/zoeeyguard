/*
   +----------------------------------------------------------------------+
   | ZoeeyGuard                                                           |
   +----------------------------------------------------------------------+
   | Copyright (c) 2011-2012 moxie(system128@gmail.com)                   |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
 */

#ifndef ZG_GUARD_C
#define ZG_GUARD_C

#include "php.h"
#include "guard.h"

char * substr_n(char * source, int len, int offset, int size) {
    int sub_len = 0;
    char * sub = NULL;
    int i = 0;
    int j = 0;

    sub_len = size > 0 ? size : len - offset;
    sub = calloc(sizeof (char), (sub_len + 1));

    i = offset;
    j = 0;
    while (i < len) {
        if (i >= offset) {
            *(sub + j) = *(source + i);
            j++;
            if (size != 0 && j == size) {
                break;
            }
        }
        i++;
    }
    return sub;
}

/*  */
char * strrev_n(char * str, int len) {
    char * rev = calloc(sizeof (char), (len + 1));
    int i = 0;
    while (i < len) {
        *(rev + len - i - 1) = *(str + i);
        i++;
    }
    return rev;
}

void swap_by_order(char * str, char * swaped, int str_len) {
    int order_len = ORDER_SIZE;
    int pos = 0;
    int last_len;
    int pre_str_len;
    char * last;
    int i;
    int offset;
    char * last_order;
    int j = 0;

    last_len = str_len % order_len;
    pre_str_len = str_len - last_len;
    last = substr_n(str, str_len, pre_str_len, 0);

    offset = 0;
    if (pre_str_len > 0) {

        for (i = 0; i < pre_str_len; i++) {
            pos = (i - i % order_len) + OBFUSCATED_ORDER[i % order_len];
            *(swaped + i) = *(str + pos % pre_str_len);
        }
        offset = i;
    }

    if (last_len > 0) {
        last_order = calloc(sizeof (char), last_len);
        j = 0;
        for (i = 0; i < order_len; i++) {
            if (OBFUSCATED_ORDER[i] < last_len) {
                *(last_order + j) = OBFUSCATED_ORDER[i];
                j++;
                if (j == last_len) {
                    break;
                }
            }
        }

        for (i = 0; i < last_len; i++) {
            pos = last_order[i % last_len];
            *(swaped + i + offset) = *(last + pos % last_len);
        }
        free(last_order);
    }
    free(last);
}

/* deswap */
void deswap_by_order(char * str, char * deswaped, int str_len) {
    int order_len, pos, last_len, pre_str_len, i, offset;
    int j;
    char * last;
    char order_bytes[ORDER_SIZE] = {0};
    char * last_order;
    char * last_order_bytes;

    order_len = ORDER_SIZE;
    pos = 0;


    last_len = str_len % order_len;
    pre_str_len = str_len - last_len;
    last = substr_n(str, str_len, pre_str_len, 0);

    offset = 0;
    for (i = 0; i < ORDER_SIZE; i++) {
        order_bytes[OBFUSCATED_ORDER[i]] = i;
    }

    if (pre_str_len > 0) {
        for (i = 0; i < pre_str_len; i++) {
            pos = i - i % order_len + order_bytes[i % order_len ];
            *(deswaped + i) = *(str + pos);
        }
        offset = i;
    }

    if (last_len > 0) {
        last_order = calloc(sizeof (char), last_len + 1);

        j = 0;
        for (i = 0; i < order_len; i++) {
            if (OBFUSCATED_ORDER[i] < last_len) {
                *(last_order + j) = OBFUSCATED_ORDER[i];
                j++;
                if (j == last_len) {
                    break;
                }
            }
        }
        last_order_bytes = calloc(sizeof (char), last_len + 1);

        for (i = 0; i < last_len; i++) {
            *(last_order_bytes + last_order[i]) = i;
        }

        for (i = 0; i < last_len; i++) {
            pos = last_order_bytes[i];
            *(deswaped + offset + i) = *(last + pos % last_len);
        }

        free(last_order);
        free(last_order_bytes);
    }
    free(last);
}

#endif /* ZG_GUARD_C */
