dnl $Id$
dnl config.m4 for extension pih

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(pih, for pih support,
dnl Make sure that the comment is aligned:
dnl [  --with-pih             Include pih support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(pih, whether to enable pih support,
dnl Make sure that the comment is aligned:
[  --enable-pih           Enable pih support])

if test "$PHP_PIH" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-pih -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/pih.h"  # you most likely want to change this
  dnl if test -r $PHP_PIH/$SEARCH_FOR; then # path given as parameter
  dnl   PIH_DIR=$PHP_PIH
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for pih files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PIH_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PIH_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the pih distribution])
  dnl fi

  dnl # --with-pih -> add include path
  dnl PHP_ADD_INCLUDE($PIH_DIR/include)

  dnl # --with-pih -> check for lib and symbol presence
  dnl LIBNAME=pih # you may want to change this
  dnl LIBSYMBOL=pih # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PIH_DIR/$PHP_LIBDIR, PIH_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PIHLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong pih lib version or lib not found])
  dnl ],[
  dnl   -L$PIH_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PIH_SHARED_LIBADD)

  PHP_NEW_EXTENSION(pih, pih.c, $ext_shared)
fi
