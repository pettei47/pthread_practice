#include <pthread.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void	f1(int *n)
{
	for (int i = 0; i < *n; i++)
		printf("working thread 1(%d)\n", i + 1);
}

int	main(void)
{
	pthread_t	t1;
	int			r1;
	int			arg;

	arg = 7;
	printf("start thread 1\n");
	r1 = pthread_create(&t1, NULL, (void *)f1, &arg);
	if (r1 != 0)
		err(EXIT_FAILURE, "failed to create thread 1:%s\n", strerror(errno));
	printf("wait thread 1\n");
	r1 = pthread_join(t1, NULL);
	if (r1 != 0)
		err(EXIT_FAILURE, "failed to join thread 1:%s\n", strerror(errno));
	printf("thread 1 joined\n");
	return (0);
}
