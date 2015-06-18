/*************************************************************************
> File Name: getcodesfile.c
> Author: sky
> Mail: shikaidong@126.com 
> Created Time: Wed 20 May 2015 08:54:25 PM CST
************************************************************************/

 #include<stdio.h>
 #include<stdlib.h>
 #include<shares.h>

int getcodesfile()
{
	char cmdbuf[256+1];
	int ret, n, i;

	n = 43;
	for(i=0; i<n ; i++)
	{
		sprintf(cmdbuf,"wget http://vip.stock.finance.sina.com.cn/q/go.php/vIR_CustomSearch/index.phtml?p=%d -O %s/files/shares/codes/codes%d",i+1, getenv("HOME"), i);
		system(cmdbuf);

	}

	return NOERR;
}

int main()
{
	getcodesfile();
}
