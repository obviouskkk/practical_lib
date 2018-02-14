/* ***********************************************************************

  > File Name: apue.h
  > Author: zzy
  > Mail: 942744575@qq.com 
  > Created Time: Tue 28 Nov 2017 10:23:33 AM CST

 ********************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_LOG_BUF 1024

void err_exit(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	char buf[MAX_LOG_BUF];
	vsnprintf(buf, MAX_LOG_BUF, fmt, ap) ;
	strcat(buf, "\n");

	//printf("%s",buf); //和下面三行代码等效
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
	va_end(ap);
	exit(1);
}

void err_ret(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	char buf[MAX_LOG_BUF];
	vsnprintf(buf, MAX_LOG_BUF, fmt, ap) ;
	if(errno){
		snprintf(buf + strlen(buf), MAX_LOG_BUF - strlen(buf)-1 ," : %s", strerror(errno));
	}
	strcat(buf, "\n");

	//printf("%s",buf); //和下面三行代码等效
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
	va_end(ap);
}
