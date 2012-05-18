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

/* $Id: php_zoeeyguard.h,v c6126b06c302 2010/09/20 06:03:39 MoXie $ */

#ifndef PHP_ZOEEYGUARD_H
#define PHP_ZOEEYGUARD_H

extern zend_module_entry zoeeyguard_module_entry;
#define phpext_zoeeyguard_ptr &zoeeyguard_module_entry

#ifdef PHP_WIN32
#define PHP_ZOEEYGUARD_API __declspec(dllexport)
#else
#define PHP_ZOEEYGUARD_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/* #define PHP_ZOEEYGUARD_EDITION "CLIENT" */

PHP_MINIT_FUNCTION(zoeeyguard);
PHP_MSHUTDOWN_FUNCTION(zoeeyguard);
PHP_RINIT_FUNCTION(zoeeyguard);
PHP_RSHUTDOWN_FUNCTION(zoeeyguard);
PHP_MINFO_FUNCTION(zoeeyguard);

PHP_FUNCTION(zoeey_run);
PHP_FUNCTION(zoeey_encode);

#ifdef PHP_ZOEEYGUARD_EDITION
/* PHP_FUNCTION(zoeey_encode); */
#endif
ZEND_BEGIN_MODULE_GLOBALS(zoeeyguard)
ZEND_END_MODULE_GLOBALS(zoeeyguard)

/* client has encode() and run() ,otherwise there's just run()*/

#define ZOEEYGUARD_VERSION "1.0" /* 2012-03-29 */
#define ZOEEYGUARD_SITE_ADD "http://code.google.com/p/zoeeyguard/"

/* In every utility function you add that needs to use variables 
   in php_zoeeyguard_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as ZOEEYGUARD_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
 */

#ifdef ZTS
#define ZOEEYGUARD_G(v) TSRMG(zoeeyguard_globals_id, zend_zoeeyguard_globals *, v)
#else
#define ZOEEYGUARD_G(v) (zoeeyguard_globals.v)
#endif

#endif	/* PHP_ZOEEYGUARD_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
