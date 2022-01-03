#include <pthread.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_data
{
	int				num;
	int				count;
	pthread_mutex_t	mutex;
}				t_data;


void	f1(t_data *d)
{
	for (int i = 0; i < d->num; i++)
	{
		pthread_mutex_lock(&d->mutex);
		printf("working thread 1(%d)\n", i + 1);
		d->count++;
		pthread_mutex_unlock(&d->mutex);
		usleep(1000);
	}
}

void	f2(t_data *d)
{
	for (int i = 0; i < d->num; i++)
	{
		usleep(50);
		pthread_mutex_lock(&d->mutex);
		printf("working thread 2(%d)\n", i + 1);
		d->count++;
		pthread_mutex_unlock(&d->mutex);
	}
}

int	main(void)
{
	pthread_t	t1, t2;
	int			r1, r2;
	t_data		d;

	d.num = 7;
	d.count = 0;
	printf("start thread 1\n");
	pthread_mutex_init(&d.mutex, NULL);
	r1 = pthread_create(&t1, NULL, (void *)f1, &d);
	r2 = pthread_create(&t2, NULL, (void *)f2, &d);
	if (r1 != 0)
		err(EXIT_FAILURE, "failed to create thread 1:%s\n", strerror(errno));
	if (r2 != 0)
		err(EXIT_FAILURE, "failed to create thread 2:%s\n", strerror(errno));
	printf("wait thread 2\n");
	if ((r2 = pthread_join(t2, NULL)) != 0)
		err(EXIT_FAILURE, "failed to join thread 2:%s\n", strerror(errno));
	else
		printf("thread 2 joined(count:%d)\n", d.count);
	printf("wait thread 1\n");
	if ((r1 = pthread_join(t1, NULL)) != 0)
		err(EXIT_FAILURE, "failed to join thread 1:%s\n", strerror(errno));
	else
		printf("thread 1 joined(count:%d)\n", d.count);
	printf("all threads joined(count:%d)\n", d.count);
	pthread_mutex_destroy(&d.mutex);
	return (0);
}
