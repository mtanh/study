#include "dgsapi.h"
#include "lognew.h"
#include "dgsserver.h"

static DGSServer dgsServer;

void DGSStart( void )
{
	//LogPrintf( "DGSStart", LOG_INFO );
	dgsServer.StartServer();
}