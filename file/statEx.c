#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
		struct stat sb; //파일의 상태를 정의한 구조체

	    if (argc != 2)
		{
			fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
			return 1;
	    }

	    if (stat(argv[1], &sb) == -1) 
	    {
	        perror("stat");																				        return 1;
	    }
	    printf("File type:                ");
	
		switch (sb.st_mode & S_IFMT) //파일 타입과 퍼미션
	    {
		      case S_IFBLK:  printf("block device\n");            break; //일반 파일 여부
			  case S_IFCHR:  printf("character device\n");        break; //char device
			  case S_IFDIR:  printf("directory\n");               break; //directory
			  case S_IFIFO:  printf("FIFO/pipe\n");               break; //FIFO
			  case S_IFLNK:  printf("symlink\n");                 break; //SYMBOLIC LINK
			  case S_IFREG:  printf("regular file\n");            break; //REGULAR FILE
			  case S_IFSOCK: printf("socket\n");                  break; //SOCKET
			  default:       printf("unknown?\n");                break;
		}
	   
	   printf("I-node number:            %ld\n", (long) sb.st_ino); //inode number
	   printf("Mode:                     %lo (octal)\n", (unsigned long) sb.st_mode); //파일종류 및 접근 권한
	   printf("Link count:               %ld\n", (long) sb.st_nlink); 
	   printf("Ownership:                UID=%ld   GID=%ld\n", (long) sb.st_uid, (long) sb.st_gid);
	   printf("Preferred I/O block size: %ld bytes\n",         (long) sb.st_blksize);
	   printf("File size:                %lld bytes\n",        (long long) sb.st_size);
	   printf("Blocks allocated:         %lld\n",              (long long) sb.st_blocks);
	   printf("Last status change:       %s", ctime(&sb.st_ctime));
	   printf("Last file access:         %s", ctime(&sb.st_atime));
	   printf("Last file modification:   %s", ctime(&sb.st_mtime));
	   
	   return 0;
} 

