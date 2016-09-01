#include <stdio.h>
#include "lognew.h"

void LogPrintf( char *msg, LogLevel level )
{
  printf( "%s\n", msg );
}
