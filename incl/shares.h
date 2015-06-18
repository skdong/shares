/*************************************************************************
    > File Name: shares.h
    > Author: sky
    > Mail: shikaidong@126.com 
    > Created Time: Thu 21 May 2015 10:03:54 PM CST
 ************************************************************************/

#define NOERR 0
#define ERROR -1

#define CURRENTDATA 1  
#define HISTDATA 2     

int getcurrentinfo(char *code);
int getfilecodes(char *buf);
int gethistdata(char *code);
int openfilegetcodelist(char *file);
int travelcodesfile();
int gethistorcurrentdatas(unsigned short type);
int getcodeinfo(char *code);
int threadgetcodeinfo(void *code);
int sethistorcurrenttype(unsigned short type );
