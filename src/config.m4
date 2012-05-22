dnl $Id$
dnl config.m4 for extension zoeeyguard

PHP_ARG_WITH(zoeeyguard, for zoeeyguard support,
[  --with-zoeeyguard             Include zoeeyguard support])
 
if test "$PHP_ZOEEYGUARD" != "no"; then
  PHP_NEW_EXTENSION(zoeeyguard, guard.c encode.c decode.c zoeeyguard.c , $ext_shared)
fi
