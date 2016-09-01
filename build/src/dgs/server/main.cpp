#include <stdio.h>
#include <dgsapi.h>
#include "dgsserver.h"
#include "lognew.h"

static DGSServer dgsServer;

int main( int argc, char* argv[] )
{
  DGSStart();
  //dgsServer.StartServer();

  LogPrintf( "Done", LOG_INFO );
  return 0;
}
