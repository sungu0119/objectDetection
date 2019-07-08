#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<errno.h>
#include<time.h>

#define DIRC_BUFF 1024

char* get_time(){
		time_t t;
		struct tm *lt;

		char *str = malloc(sizeof(char)*20);

		time(&t);
		lt = localtime(&t);

		sprintf(str, "%04d%02d%02d_%02d", lt->tm_year + 1900, lt->tm_mon +1,
					lt->tm_mday, lt->tm_hour);

		return str;
}


void mk_folder(){
		char buff[DIRC_BUFF+1];
		char *p_dirc = buff;
		char fPath[DIRC_BUFF+1] = {"/home/jk/user/blackbox/"};
		strcat(fPath, get_time());
 		
		memcpy(buff , fPath, DIRC_BUFF);
		buff[DIRC_BUFF] = '\0';

		while(*p_dirc){
				if('/' == *p_dirc){
						*p_dirc = '\0';
						if( 0 != access(buff, F_OK)){
								mkdir(buff, 0777);
						}
						*p_dirc = '/';
				}
				p_dirc++;
		}
		if( 0!= access(buff ,F_OK)){
				mkdir(buff, 0777);
		}
		
}


int main(int argc, char **argv)
{
		mk_folder();

		return 0;
}
