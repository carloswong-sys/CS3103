// Source - https://stackoverflow.com/a
// Posted by Schwern
// Retrieved 2025-11-17, License - CC BY-SA 3.0

#include "verbose.h"
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

bool Verbose = false;

void setVerbose(bool setting) {
    Verbose = setting;
}

int verbose(const char *format, ...) {
    if( !Verbose )
        return 0;

    va_list args;
    va_start(args, format);
    int ret = vprintf(format, args);
    va_end(args);

    return ret;
}
