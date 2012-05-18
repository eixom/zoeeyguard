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
#ifndef ZG_ENCODE_C
#define ZG_ENCODE_C

#include "php.h"

#include "guard.h"
#include "encode.h"

char * encode(char * code, int code_len, char * key, int key_len) {
    char * swaped_key;
    char * swaped_code;
    int key_idx;
    int i;
    char * x_code;
    int idx;
    int j;
    int based_code_len;
    char * base_code;
    int base_idx;
    char chs[3] = {0};
    /**
     * swap postion
     */

    // swap key
    swaped_key = malloc(sizeof (char) * key_len);
    swap_by_order(key, swaped_key, key_len);

    // swap code
    swaped_code = malloc(sizeof (char) * code_len);
    swap_by_order(code, swaped_code, code_len);

    // xor
    key_idx = 0;
    i = 0;

    x_code = strdup(code);

    for (i = 0; i < code_len; i++, key_idx++) {
        if (key_idx == key_len) {
            key_idx = 0;
        }
        *(x_code + i) = *(swaped_code + i) ^ *(key + key_idx);
        *(x_code + i) = *(x_code + i)^ *(swaped_key + key_idx);
    }

    /**
     * base64 encode
     */

    /* <editor-fold desc="base64 encode"> defaultstate="collapsed" */
    idx = 0;
    j = 0;

    based_code_len = (code_len + 3) * 4 / 3;

    base_code = calloc(sizeof (char), based_code_len);

    base_idx = 0;
    while (idx < code_len) {

        for (i = 0; i < 3; i++) {
            idx++;
            chs[i] = *(x_code + idx - 1);
            if (idx == code_len) {
                break;
            }
        }
        i++;

        if (i > 0) {
            *(base_code + base_idx++) = OBFUSCATED_ALPHABET[(chs[0] >> 2) & 0x3F];
            *(base_code + base_idx++) = OBFUSCATED_ALPHABET[(((chs[0] & 3) << 4) & 0x30) + ((chs[1] >> 4) & 0xF)];
        }

        if (i > 1) {
            *(base_code + base_idx++) = OBFUSCATED_ALPHABET[(((chs[1] & 15) << 2) & 0x3C) + ((chs[2] >> 6) & 0x3)];
        }

        if (i > 2) {
            *(base_code + base_idx++) = OBFUSCATED_ALPHABET[chs[2] & 0x3F];
        }

        for (j = i; j < 3; j++) {
            *(base_code + base_idx++) = '=';
        }
    }
    *(base_code + base_idx++) = '\0';
    /* </editor-fold> */

    free(swaped_key);
    free(swaped_code);
    free(x_code);

    return base_code;
}


#endif /* ZG_ENCODE_C */

