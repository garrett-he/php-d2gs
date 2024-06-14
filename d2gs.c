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
#include "d2gs.h"

d2gs_state* d2gs_connect(const char *host, unsigned short port, long timeout_sec TSRMLS_DC)
{
    d2gs_state *state;
    struct timeval tv;

    state = ecalloc(1, sizeof(*state));

    tv.tv_sec = timeout_sec;
    tv.tv_usec = 0;

    state->socket = php_network_connect_socket_to_host(host,
        port ? port : D2GS_PORT, SOCK_STREAM, 0, &tv, NULL, NULL, NULL,
        0 TSRMLS_CC);
    
    if (state->socket == -1) {
        d2gs_close(state);
        return NULL;
    }

    state->timeout_sec = timeout_sec;
    return state;
}

void d2gs_close(d2gs_state *state)
{
    if (!state) {
        return;
    }

    if (state->socket != -1) {
        closesocket(state->socket);
    }

    efree(state);
}
