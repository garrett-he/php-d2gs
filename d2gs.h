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
#ifndef D2GS_H
#define D2GS_H

#define D2GS_TIMEOUT_SEC 10
#define D2GS_PORT 8888

#include "php_network.h"

typedef struct {
    php_socket_t socket;
    long timeout_sec;
    char *buff;
    int buff_len;
} d2gs_state;

d2gs_state* d2gs_connect(const char *host, unsigned short port, long timeout_sec TSRMLS_DC);

void d2gs_close(d2gs_state *state);

#endif /* D2GS_H */
