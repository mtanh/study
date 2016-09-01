#include <string>

#include "dgsserver.h"
#include "lognew.h"

Builder::Builder()
: mGeneration( 0 )
{
}

Builder::~Builder()
{
}

DGSServer::DGSServer()
: mBuilder_( NULL )
, mGeneration_( 0 )
{
}

DGSServer::~DGSServer()
{
}

void DGSServer::StartServer()
{
  LogPrintf( "StartServer", LOG_INFO );
  //fprintf( stderr, "Hello DGS\n" );
}
