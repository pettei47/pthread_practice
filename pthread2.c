#include <pthread.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	f1(int *n)
{
	for (int i = 0; i < *n; i++)
	{
		printf("working thread 1(%d)\n", i + 1);
		usleep(1000);
	}
}

void	f2(int *n)
{
	for (int i = 0; i < *n; i++)
	{
		usleep(50);
		printf("working thread 2(%d)\n", i + 1);
	}
}

int	main(void)
{
	pthread_t	t1, t2;
	int			r1, r2;
	int			arg;

	arg = 7;
	printf("start thread 1\n");
	r1 = pthread_create(&t1, NULL, (void *)f1, &arg);
	r2 = pthread_create(&t2, NULL, (void *)f2, &arg);
	if (r1 != 0)
		err(EXIT_FAILURE, "failed to create thread 1:%s\n", strerror(errno));
	if (r2 != 0)
		err(EXIT_FAILURE, "failed to create thread 2:%s\n", strerror(errno));
	printf("wait thread 2\n");
	if ((r2 = pthread_join(t2, NULL)) != 0)
		err(EXIT_FAILURE, "failed to join thread 2:%s\n", strerror(errno));
	else
		printf("thread 2 joined\n");
	printf("wait thread 1\n");
	if ((r1 = pthread_join(t1, NULL)) != 0)
		err(EXIT_FAILURE, "failed to join thread 1:%s\n", strerror(errno));
	else
		printf("thread 1 joined\n");
	printf("all threads joined\n");
	return (0);
}
