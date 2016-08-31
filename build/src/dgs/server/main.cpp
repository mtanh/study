#include "dgsapi.h"
#include "lognew.h"

int main( int argc, char* argv[] )
{
  DGSStart();

  LogPrintf( "Done", LOG_INFO );
  return 0;
}
