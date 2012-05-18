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

/* $Id: zoeeyguard.c,v c6126b06c302 2010/09/20 06:03:39 MoXie $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_zoeeyguard.h"

#include "encode.h"
#include "decode.h"
#include "guard.h"


/* If you declare any globals in php_zoeeyguard.h uncomment this:*/
ZEND_DECLARE_MODULE_GLOBALS(zoeeyguard)


/* True global resources - no need for thread safety here */
static int le_zoeeyguard;

/* {{{ zoeeyguard_functions[]
 *
 * Every user visible function must have an entry in zoeeyguard_functions[].
 */
zend_function_entry zoeeyguard_functions[] = {
    PHP_FE(zoeey_run, NULL)
    PHP_FE(zoeey_encode, NULL) {
        NULL, NULL, NULL
    }
};
/* }}} */

/* {{{ zoeeyguard_module_entry
 */
zend_module_entry zoeeyguard_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "zoeeyguard",
    zoeeyguard_functions,
    PHP_MINIT(zoeeyguard),
    PHP_MSHUTDOWN(zoeeyguard),
    PHP_RINIT(zoeeyguard), /* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(zoeeyguard), /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(zoeeyguard),
#if ZEND_MODULE_API_NO >= 20010901
    "0.1", /* Replace with version number for your extension */
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ZOEEYGUARD

ZEND_GET_MODULE(zoeeyguard)
#endif


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(zoeeyguard) {
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(zoeeyguard) {

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(zoeeyguard) {
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(zoeeyguard) {
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(zoeeyguard) {
    char * out;
    php_info_print_table_start();
    php_info_print_table_row(2, "zoeeyguard support", "enabled");
    php_info_print_table_row(2, "version", ZOEEYGUARD_VERSION);
    php_info_print_table_row(2, "site", ZOEEYGUARD_SITE_ADD);
    spprintf(&out, 0, "%s %s", __DATE__, __TIME__);
    php_info_print_table_row(2, "build date", out);
    php_info_print_table_end();
}
/* }}} */

/* Every user-visible function in PHP should document itself in the source */

/* {{{ proto string zoeey_run(string code)  */
PHP_FUNCTION(zoeey_run) {
    char * enc = NULL; /* encoded code */
    char * source = NULL;
    int enc_len;
    char * comp_name;
    char * eval_str; 
	 
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s"
            , &enc, &enc_len) == FAILURE) {
        return;
    }

    comp_name = zend_make_compiled_string_description("zoeeyguard" TSRMLS_CC);

    source = decode(enc, PRIVATE_KEY, PRIVATE_KEY_LEN);
	
    spprintf(&eval_str, 0, " ?>%s<?php ", source);
	
    free(source);

    if (zend_eval_string(eval_str, NULL, comp_name TSRMLS_CC) == FAILURE) {
        efree(comp_name);
        efree(eval_str);
        php_error_docref(NULL TSRMLS_CC, E_RECOVERABLE_ERROR, "Please make sure '<?php' end with '?>'", PHP_EOL);
        RETURN_FALSE;
    }

    efree(comp_name);
    efree(eval_str);
    RETURN_TRUE;
}
/* }}} */

/* {{{ proto string zoeey_encode(string code)   */
PHP_FUNCTION(zoeey_encode) {
    char * code = NULL;
    int code_len = 0;
    char * ciphertext = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s"
            , &code, &code_len) == FAILURE) {
        return;
    }

    ciphertext = encode(code, code_len, PRIVATE_KEY, PRIVATE_KEY_LEN);

    RETURN_STRING(ciphertext, 1);
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
