/*************************************************************************
    > File Name: sharethreadtool.c
    > Author: sky
    > Mail: shikaidong@126.com 
    > Created Time: Mon 15 Jun 2015 09:10:31 PM CST
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<shares.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

static int pool_num=20;
static int thread_num=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int clear_thread_pool()
{
	thread_num=0;
	return NOERR;
}

int init_thread_pool(int num)
{
	if(num < 1)
	{
		fprintf(stderr,"the thread pool num input err\n",num);
		return ERROR;
	}
	pool_num = num;
	thread_num = 0;
}

int thread_all_end()
{
	if( thread_num != 0 )
	{
		return ERROR;
	}
	return NOERR;
}

int refresh_thread_pool( type )
{
	pthread_mutex_lock(&mutex);
	thread_num += type ;
	pthread_mutex_unlock(&mutex);
	return NOERR;
}


int run_thread_pool( char *code )
{
	pthread_t thread;
	char *thread_code;

	thread_code = (char *)malloc( sizeof(char)*32 );
	if( thread_code == NULL )
	{
		fprintf(stderr,"get memory err\n");
		return ERROR;
	}
	strcpy(thread_code,code);
	while( thread_num+1 > pool_num )
	{
		usleep(500);	
	}
	refresh_thread_pool(1);
	printf("%d\n",thread_num);
	pthread_create(&thread,NULL,(void *)&threadgetcodeinfo, (void *)thread_code );
	return NOERR;
}


