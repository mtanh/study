#ifndef COMMON_TERMINATE_H_
#define COMMON_TERMINATE_H_

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdlib.h>

typedef enum { True, False } Boolean;

static void terminate(Boolean useExit3)
{
	char *s;
	/* Dump core if EF_DUMPCORE environment variable is defined and
	is a nonempty string; otherwise call exit(3) or _exit(2),
	depending on the value of 'useExit3'. */
	s = getenv("EF_DUMPCORE");
	if (s != NULL && *s != '\0')
	{
		abort();
	}
	else if (useExit3)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		_exit(EXIT_FAILURE);
	}
}


#endif /* COMMON_TERMINATE_H_ */
