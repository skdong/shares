/*************************************************************************
  > File Name: getcurrentinfo.c
  > Author: sky
  > Mail: shikaidong@126.com 
  > Created Time: Wed 20 May 2015 09:34:29 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<shares.h>

int main()
{
	int ret;
	ret = gethistorcurrentdatas(CURRENTDATA);
	if( ret != NOERR )
	{
		fprintf(stderr,"travecodesfile err\n");
		return ERROR;
	}
	return NOERR;
}
