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
#include<unistd.h>

static unsigned short getdatatype=0;
static const int trytimes=2;

int sethistorcurrenttype(unsigned short type )
{
	getdatatype = type;
	return NOERR;
}
int gethistorcurrentdatas(unsigned short type)
{
	getdatatype = type;
	if( travelcodesfile() != NOERR ) 
	{
		fprintf(stderr,"travelcodesfile err \n");
		return ERROR;
	}

	while( thread_all_end() != NOERR )
	{
		//fprintf(stderr,"wait for all thread end\n");
		usleep(500);
	}
	return NOERR;
}

int travelcodesfile()
{
	char file[256+1];
	int i,ret;
	for(i=0; i<43; i++)
	{
		sprintf(file,"%s/files/shares/codes/codes%d",getenv("HOME"),i);
		//printf("%s\n",file);
		ret = openfilegetcodelist(file);
		if(ret != NOERR )
		{
			fprintf(stderr,"openfilegetcodelist err %d\n");
			return ERROR;
		}
	}
	return NOERR;
}
int openfilegetcodelist(char *file)
{
	FILE *fp = NULL;
	char linebuf[1024] = { 0 };
	int ret;

	fp = fopen(file,"r");
	if(fp == NULL )
	{
		fprintf(stderr,"open file err %s\n",file);
		return ERROR;
	}
	while( fgets(linebuf, sizeof(linebuf)-1, fp) != NULL )
	{
		if( strstr(linebuf,"code_list") != NULL )
		{
			//printf("%s",linebuf);
			ret = getfilecodes(linebuf);
			if(ret != NOERR)
			{
				fprintf(stderr,"getfilecodes err %s \n",linebuf);
				fclose(fp);
				return ERROR;
			}
			break;
		}
		memset(linebuf,0,sizeof(linebuf));
	}
	fclose(fp);
	return NOERR;
}
int getfilecodes(char *buf)
{
	char *start = NULL ;
	char code[64+1] = { 0 };
	int i = 0, ret;

	start = strchr(buf,'\"');
	if( start == NULL )
	{
		fprintf(stderr,"the buf format err %s\n",buf);
		return ERROR;
	}
	start ++;

	while( *start != '\"' )
	{
		if( *start == ',')
		{
			if( NOERR != run_thread_pool(code) )
			{
				fprintf(stderr,"get code [%s] info err\n",code);
			}
			memset(code,0,sizeof(code));
			i = 0;
		}
		else
		{
			code[i] = *start;
			i++;
		}

		start ++;
	}

	return NOERR;
}

int threadgetcodeinfo(void *code)
{
	int ret = NOERR;
	if( getdatatype & CURRENTDATA )
	{
		ret = getcurrentinfo((char *)code);
		if( ret != NOERR )
		{
			fprintf(stderr,"getcurrentinfo err %s\n",code);
			return ERROR;
		}
	}
	if( getdatatype & HISTDATA )
	{
		ret = gethistdata((char *)code);
		if( ret != NOERR )
		{
			fprintf(stderr,"gethistdata err %s\n",code);
			return ERROR;
		}
	}
	free(code);
	refresh_thread_pool(-1);
	return NOERR;
}

int getcodeinfo(char *code)
{
	int ret = NOERR;
	if( getdatatype & CURRENTDATA )
	{
		ret = getcurrentinfo(code);
		if( ret != NOERR )
		{
			fprintf(stderr,"getcurrentinfo err %s\n",code);
			return ERROR;
		}
	}
	if( getdatatype & HISTDATA )
	{
		ret = gethistdata(code);
		if( ret != NOERR )
		{
			fprintf(stderr,"gethistdata err %s\n",code);
			return ERROR;
		}
	}
	return NOERR;
}

int getcurrentinfo(char *code)
{
	char cmdbuf[512+1];

	if( *code > 'z' || *code < 'a' )
	{
		fprintf(stderr,"the code format err %s \n",code);
		return NOERR;
	}
	sprintf(cmdbuf,"wget -t %d http://hq.sinajs.cn/?list=%s -O %s/files/shares/currentinfos/%s",
		 trytimes,code,getenv("HOME"),code);
	//printf("%s\n",code);
	system(cmdbuf);

	return NOERR;
}

int gethistdata(char *code)
{
	char cmdbuf[512+1];

	if( *code > 'z' || *code < 'a' )
	{
		fprintf(stderr,"the code format err %s \n",code);
		return NOERR;
	}
	if( *code == 's' && *(code+1) == 'h' )
	{
		sprintf(cmdbuf,"wget -t %d http://table.finance.yahoo.com/table.csv?s=%s.ss -O %s/files/shares/histdatas/%s",
		  trytimes,code+2,getenv("HOME"),code);
	}
	else
	{
		sprintf(cmdbuf,"wget -t %d http://table.finance.yahoo.com/table.csv?s=%s.%c%c -O %s/files/shares/histdatas/%s",
		  trytimes,code+2,*code,*(code+1),getenv("HOME"),code);
	}
	//printf("%s\n",cmdbuf);
	system(cmdbuf);

	return NOERR;
}
