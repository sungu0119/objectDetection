#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>
#include<time.h>


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

int mk_folder(){
		char fPath[50] = {"/home/jk/user/blackbox/"};
		strcat(fPath, get_time());
		int nResult = mkdir(fPath, 0776);

		if(nResult == 0)
		{
				printf("folder make\n");
				return 1;
		}
		else if(nResult == -1)
		{
				perror("folder make error");
				return -1;
		}
}


int main(int argc, char **argv)
{
		mk_folder();

		return 0;
}
