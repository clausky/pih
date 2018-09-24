/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_pih.h"



static int le_pih;

static int (*old_zend_stream_open)(const char *filename, zend_file_handle *fh TSRMLS_DC);

#define BEFORE_INCLUDE_HOOK "__before_include"
static int pih_zend_stream_open(const char *filename, zend_file_handle *fh TSRMLS_DC)
{
        char *new_filename = estrdup(filename);
	zend_execute_data *exd;
        zval *funname,*ret_ptr = NULL,*func_args,**params[0];
        zend_function *hook;
	exd=EG(current_execute_data);
	if (EG(in_execution) && (exd!=NULL) && (exd->opline != NULL)) {
            switch (exd->opline->extended_value) {
		case ZEND_INCLUDE:
		case ZEND_REQUIRE:
		case ZEND_INCLUDE_ONCE:
		case ZEND_REQUIRE_ONCE:
                     if(zend_hash_find(EG(function_table), BEFORE_INCLUDE_HOOK,
					  strlen(BEFORE_INCLUDE_HOOK) + 1, (void **) &hook) == SUCCESS){
                         MAKE_STD_ZVAL(funname);
                         ZVAL_STRING(funname, BEFORE_INCLUDE_HOOK, 1);
                         MAKE_STD_ZVAL(func_args);
                         ZVAL_STRING(func_args,filename,1);
                         params[0] = &func_args;

                         call_user_function_ex(EG(function_table), NULL, funname, &ret_ptr, 1, params, 0, EG(active_symbol_table));

                         new_filename = (char *) ret_ptr->value.str.val;
                         zval_ptr_dtor(&ret_ptr);
                     }
            }
        }

        return old_zend_stream_open(new_filename, fh TSRMLS_CC);
}





PHP_MINIT_FUNCTION(pih)
{
	return SUCCESS;
}


PHP_MSHUTDOWN_FUNCTION(pih)
{
	return SUCCESS;
}



PHP_RINIT_FUNCTION(pih)
{
    old_zend_stream_open = zend_stream_open_function;
    zend_stream_open_function = pih_zend_stream_open;
    return SUCCESS;
}



PHP_RSHUTDOWN_FUNCTION(pih)
{
	return SUCCESS;
}


PHP_MINFO_FUNCTION(pih)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "PIH (php include hook) support", "enabled");
        php_info_print_table_row(2, "PIH Version", PHP_PIH_VERSION);
        php_info_print_table_row(2, "hook function", BEFORE_INCLUDE_HOOK);
	php_info_print_table_end();
}


const zend_function_entry pih_functions[] = {
	PHP_FE_END
};

zend_module_entry pih_module_entry = {
	STANDARD_MODULE_HEADER,
	"PIH",
	pih_functions,
	PHP_MINIT(pih),
	PHP_MSHUTDOWN(pih),
	PHP_RINIT(pih),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(pih),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(pih),
	PHP_PIH_VERSION,
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_PIH
ZEND_GET_MODULE(pih)
#endif

