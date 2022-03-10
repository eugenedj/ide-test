#include <stdio.h>
#include <unistd.h>
#include "pthread.h"

int global_cnt = 0;

void my_print(int number)
{
    printf("number is %d\n",number);
}
/*
*这个是注释
*/
void *process(void * arg)
{
	int i,j;
	printf("Starting process %s\n", (char *)arg);
	j = 0;
	for (i = 0; i < 10000; i++)
	{
		write(1, (char *) arg, 1);
		sleep(1);
		printf("test test test test\n");
		global_cnt++;
		j++;
		printf("i = %d\n",i);
		printf("j = %d\n",j);
		my_print(i);
	}
	return NULL;
}

#define sucfail(r) (r != 0 ? "failed" : "succeeded")
int main(void)
{
	int pret, ret = 0;
	pthread_t th_a, th_b;
	void *retval;

	ret += (pret = pthread_create(&th_a, NULL, process, (void *)"a"));
	printf("create a %s %d\n", sucfail(pret), pret);
	ret += (pret = pthread_create(&th_b, NULL, process, (void *)"b"));
	printf("create b %s %d\n", sucfail(pret), pret);
	ret += (pret = pthread_join(th_a, &retval));
	printf("join a %s %d\n", sucfail(pret), pret);
	ret += (pret = pthread_join(th_b, &retval));
	printf("join b %s %d\n", sucfail(pret), pret);
	return ret;
}
