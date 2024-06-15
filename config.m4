PHP_ARG_ENABLE(d2gs, whether to enable d2gs support,
[  --enable=d2gs           Enable d2gs support])

if test "$PHP_D2GS" != "no"; then
    PHP_NEW_EXTENSION(d2gs, php_d2gs.c d2gs.c, $ext_shared)
fi
