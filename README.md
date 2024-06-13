# php-d2gs

A PHP extension implements client access and maintenance to Diablo
II Game Server (aka D2GS).

## Functions

### d2gs_open

##### Description

`resource d2gs_open(string $host, string $password, int $timeout_sec)`

Opens a connection to a D2GS console.

##### Parameters

**host**

The D2GS server. It can also include a port number. e.g. "hostname:port".

**password**

The password for D2GS.

**timeout_sec**

This parameter specifies the timeout seconds for all subsequent network operations. If omitted, the default value is 10 seconds.

## License

Copyright (C) 2022 Garrett HE <garrett.he@outlook.com>

The GNU General Public License (GPL) version 3, see [COPYING](./COPYING).
