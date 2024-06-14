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
#ifndef PHP_D2GS_H
#define PHP_D2GS_H

extern zend_module_entry d2gs_module_entry;
#define phpext_d2gs_ptr &d2gs_module_entry

#define PHP_D2GS_VERSION "0.1.0"

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(d2gs);
PHP_RINIT_FUNCTION(d2gs);
PHP_MSHUTDOWN_FUNCTION(d2gs);
PHP_RSHUTDOWN_FUNCTION(d2gs);
PHP_MINFO_FUNCTION(d2gs);

PHP_FUNCTION(d2gs_open);

#endif /* PHP_D2GS_H */
