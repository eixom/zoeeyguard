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

#ifndef ZG_GUARD_H
#define ZG_GUARD_H


/*  private key */
#define PRIVATE_KEY "28dsa7dsas12312389uy7aydh8h1h2i312"
#define PRIVATE_KEY_LEN sizeof(PRIVATE_KEY)

/* order */
static const unsigned char OBFUSCATED_ORDER[] = {
      13,  6,  5,  7,  1, 15, 14, 20
    ,  9, 16, 19,  4, 18, 10,  2,  8
    , 12,  3, 11,  0, 17
};
#define ORDER_SIZE sizeof(OBFUSCATED_ORDER) / sizeof(* OBFUSCATED_ORDER)

/* alphabet for base64 */
static const unsigned char OBFUSCATED_ALPHABET[] = {
      's', '4', 'N', 'E', 'k', 'X', 'c', 'u'
    , 'J', '2', 'U', 'o', 'O', 'w', 'K', 'v'
    , 'h', 'H', 'C', '/', 'D', 'q', 'l', 'R'
    , 'B', 'r', '5', 'Z', 'S', 'Q', '6', 'W'
    , '3', 'L', 'j', '8', '1', 'z', '0', 'G'
    , 'n', 'e', 'y', 'b', 'I', 'd', 'i', 'P'
    , 'A', '9', '7', '+', 'm', 'V', 'M', 'Y'
    , 'F', 'g', 'f', 'p', 'a', 'T', 't', 'x'
};
#define ALPHABET_SIZE 64


char * substr_n(char * source, int len, int offset, int size);
char * strrev_n(char * str, int len);

void swap_by_order(char * str, char * swaped, int str_len);
void deswap_by_order(char * str, char * deswaped, int str_len);

#endif    /* ZG_GUARD_H */

