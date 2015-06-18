/*************************************************************************
  > File Name: regetcodedata.c
  > Author: sky
  > Mail: shikaidong@126.com 
  > Created Time: Thu 21 May 2015 10:02:57 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>

#include<shares.h>

int travelcodedir(char *dir)
{
	DIR *d = NULL;
	struct dirent *file = NULL;
	char filepath[512] = { 0 };
	struct stat sb;

	sethistorcurrenttype(HISTDATA);

	if( dir == NULL )
	{
		fprintf(stderr,"input dir is NULL\n");
		return ERROR;
	}
	if( !(d=opendir(dir)) )
	{
		fprintf(stderr,"open dir %s err\n",dir);
		return ERROR;
	}
	while ( ( file = readdir(d) ) != NULL)
	{
		/*printf("%d %d %d %c %s\n",
		  file->d_ino,file->d_off,file->d_reclen,file->d_type,file->d_name); 
		  */
		if(file->d_name[0] == '.')
		{
			continue;
		}
		sprintf(filepath,"%s/%s",dir,file->d_name); 
		//printf("file %s\n",filepath);
		if ( stat(filepath,&sb) != NOERR )
		{
			fprintf(stderr,"get file stat err %s\n",filepath);
			closedir(d);
			return ERROR;
		}
		if( sb.st_size == 0 )
		{
			//printf("file %s size %d\n",filepath,sb.st_size);
			memset(filepath,0,sizeof(filepath));
			memcpy(filepath,file->d_name,8);
			//printf("file %s\n",filepath);
			run_thread_pool(filepath);
		}
		memset(&sb,0,sizeof(sb));

	}
	closedir(d);

	while( thread_all_end() != NOERR )
	{
		//fprintf(stderr,"wait for all thread end\n");
		usleep(500); 
	}
	return NOERR;
}

int main()
{
	travelcodedir("/home/dong/files/shares/histdatas");

	return NOERR;
}
