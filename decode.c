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

#ifndef ZG_DECODE_C
#define ZG_DECODE_C

#include "php.h"

#include <string.h>
#include "guard.h"
#include "decode.h"

/* alphabet to bytes  */
static void get_alphabet_bytes(char * alphabet_bytes) {
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        alphabet_bytes[OBFUSCATED_ALPHABET[i]] = i;
    }
}

/* decode */
char * decode(char * ciphertext, char * key, int key_len) {
    int equal_count, eq_len = 0, enc_len, code_len;
    int enc_idx, code_idx, idx, pos, pre, suf;
    int key_idx, i;
    char * enc, * code, * swaped_key, * swaped_code, * source;
    char ch;
    char alphabet_bytes[255] = {-1};

    get_alphabet_bytes(alphabet_bytes);

    equal_count = 0;
    eq_len = strlen(ciphertext);

    if (*(ciphertext + eq_len - 1) == '=') {
        equal_count++;
    }

    if (*(ciphertext + eq_len - 2) == '=') {
        equal_count++;
    }

    enc = substr_n(ciphertext, strlen(ciphertext), 0, eq_len - equal_count);

    enc_len = strlen(enc) + equal_count;
    code_len = ((eq_len * 3) / 4) - equal_count;
    code = calloc(sizeof (char), code_len + 1);

    ch = 0;
    enc_idx = 0;
    code_idx = 0;
    idx = 0;
    pos = 0;
    pre = 0;
    suf = 0;

    while (idx < enc_len) {
        if (code_idx == code_len) {
            break;
        }
        pre = alphabet_bytes[enc[enc_idx] & 0xFF];
        suf = alphabet_bytes[enc[++enc_idx] & 0xFF];
        pos = idx + 1;
        if (pos % 3 == 1) {
            pos = 1;
        } else if (pos % 3 == 2) {
            pos = 2;
        } else {
            pos = 3;
        }
        switch (pos) {
            case 1:
                ch = (((pre << 2) & 0xFC) | ((suf >> 4) & 3));
                break;
            case 2:
                ch = (((pre << 4) & 0xF0) | ((suf >> 2) & 0xF));
                break;
            case 3:
                ch = (((pre << 6) & 0xC0) | (suf & 0x3F));
                break;
        }
        *(code + code_idx++) = ch;

        if (enc_idx == enc_len || *(enc + enc_idx) == '=') {
            break;
        }

        if ((idx + 1) % 3 == 0) {
            enc_idx++;
        }
        idx++;
    }

    // </editor-fold>

    /**
     * xor
     */

    code_len = idx;

    key_idx = 0;

    // swap key
    swaped_key = malloc(sizeof (char) * key_len);
    swap_by_order(key, swaped_key, key_len);

    swaped_code = calloc(sizeof (char), code_len + 1);

    strcpy(swaped_code, code);

    i = 0;
    for (i = 0; i < code_len; i++, key_idx++) {
        if (key_idx == key_len) {
            key_idx = 0;
        }
        *(code + i) = *(code + i) ^ *(key + key_idx);
        *(code + i) = *(code + i) ^ *(swaped_key + key_idx);
    }

    source = calloc(sizeof (char), code_len + 1);
    deswap_by_order(code, source, code_len);
    free(enc);
    free(swaped_code);
    free(code);

    return source;
}

#endif /* ZG_DECODE_C */

