#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdlib.h>
#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <limits>
#include <sys/mman.h>
#include <iostream>
#include <string>

#include <boost/thread.hpp>
#include <boost/filesystem.hpp>

static const char* SHM_NAME = "/demo_shm";

#define CREATE_SHM 1
#define CREATE_SHM_FAKE 0

int main (int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf (stdout, "Usage: %s <flag>\n", argv[0]);
		exit (EXIT_FAILURE);
	}

	/* Test the O_EXCL flag */
	int flag = atoi (argv[1]);
	if (CREATE_SHM == flag)
	{
		int shfd = shm_open (SHM_NAME, O_RDWR|O_CREAT|O_EXCL, 0666);
		if (shfd == -1)
		{
			perror ("shm_open");
			exit (EXIT_FAILURE);
		}
	}
	else
	{
		/*struct stat buff;
		if (stat ("/dev/shm/demo_shm", &buff) == -1)*/
		char buf[512];
		memset (buf, '\0', 512);
		sprintf (buf, "/dev/shm/%s", SHM_NAME);
		if (boost::filesystem::exists (buf) == 0)
		{
			boost::this_thread::sleep_for (boost::chrono::milliseconds (5000));

			int shfd = shm_open (SHM_NAME, O_RDWR|O_CREAT|O_EXCL, 0666);
			if (shfd == -1)
			{
				perror ("shm_open");
				exit (EXIT_FAILURE);
			}
		}
	}

	return (EXIT_SUCCESS);
}
