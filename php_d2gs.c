/*
 * Copyright (C) 2019 Garrett HE <garrett.he@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_network.h"
#include "ext/standard/info.h"
#include "d2gs.h"
#include "php_d2gs.h"

#define LE_D2GS_STATE_NAME "D2GS State"

static int le_d2gs_state;

ZEND_BEGIN_ARG_INFO_EX(arginfo_d2gs_open, 0, 0, 2)
    ZEND_ARG_INFO(0, hostname)
    ZEND_ARG_INFO(0, password)
    ZEND_ARG_INFO(0, timeout_sec)
ZEND_END_ARG_INFO()

static void d2gs_destructor_state(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
    d2gs_state *state = (d2gs_state*) rsrc->ptr;

    d2gs_close(state);
}

PHP_MINIT_FUNCTION(d2gs)
{
    le_d2gs_state = zend_register_list_destructors_ex(d2gs_destructor_state, NULL, LE_D2GS_STATE_NAME, module_number);
    return SUCCESS;
}

PHP_RINIT_FUNCTION(d2gs)
{
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(d2gs)
{
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(d2gs)
{
    return SUCCESS;
}

PHP_MINFO_FUNCTION(d2gs)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "d2gs support", "enabled");
    php_info_print_table_end();
}

const zend_function_entry d2gs_functions[] = {
    PHP_FE(d2gs_open, arginfo_d2gs_open)
    PHP_FE_END
};

zend_module_entry d2gs_module_entry = {
    STANDARD_MODULE_HEADER,
    "d2gs",
    d2gs_functions,
    PHP_MINIT(d2gs),
    PHP_MSHUTDOWN(d2gs),
    PHP_RINIT(d2gs),
    PHP_RSHUTDOWN(d2gs),
    PHP_MINFO(d2gs),
    PHP_D2GS_VERSION,
    STANDARD_MODULE_PROPERTIES
};

PHP_FUNCTION(d2gs_open)
{
    char *host_and_port, *password, *host, *ch;
    int host_and_port_len, password_len;
    int timeout_sec = D2GS_TIMEOUT_SEC, port;
    struct timeval tv;
    d2gs_state *state;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|l", &host_and_port,
        &host_and_port_len, &password, &password_len, &timeout_sec) == FAILURE) {
        return;
    }

    if (timeout_sec <= 0) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Timeout seconds has to be greater than 0");
        RETURN_FALSE;
    }

    if (host_and_port && (ch = strchr(host_and_port, ':'))) {
        host = estrndup(host_and_port, ch - host_and_port);
        port = atoi(++ch);
    } else {
        host = host_and_port;
    }

    if (!(state = d2gs_connect(host, (unsigned short) port, timeout_sec TSRMLS_CC))) {
        RETURN_FALSE;
    }

    ZEND_REGISTER_RESOURCE(return_value, state, le_d2gs_state);
}

#ifdef COMPILE_DL_D2GS
ZEND_GET_MODULE(d2gs)
#endif
