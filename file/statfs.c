#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <sys/vfs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<unistd.h>
#include<stdlib.h>

const char *MMOUNT = "/proc/mounts";
//파일에 접근하려면 그에 앞서 파일을 포함하고 있는 파일 시스템을 mount 명령어를 이용하여 마운트 된 상태여야 한다 . sd 카드 usb 저장소 dbd 기타 이동식 저장소에 자주 사용된다
struct f_size
{
		    long blocks;
			    long avail; 
};

typedef struct _mountinfo 
{
		FILE *fp;                // 파일 스트림 포인터    
		char devname[80];        // 장치 이름
		char mountdir[80];        // 마운트 디렉토리 이름
		char fstype[12];        // 파일 시스템 타입
		struct f_size size;        // 파일 시스템의 총크기/사용율 
} MOUNTP;

MOUNTP *dfopen()
{
		    MOUNTP *MP;
			// /proc/mounts 파일을 연다.
			MP = (MOUNTP *)malloc(sizeof(MOUNTP));
		    if(!(MP->fp = fopen(MMOUNT, "r")))
			{
					return NULL;
		    }
			else
					return MP;
}

MOUNTP *dfget(MOUNTP *MP)
{
		    char buf[256];
			char *bname;
		    char null[16];
			struct statfs lstatfs; //마운트 된 파일 시스템에 대한 정보를 반환하는 구조체
			struct stat lstat; //파일의 상태를 확인할 수 있는 구조체
			int is_root = 0;
			// /proc/mounts로 부터 마운트된 파티션의 정보를 얻어온다.
			while(fgets(buf, 255, MP->fp))
			{
					is_root = 0;
					//sscanf 문자열로 함수가 데이터를 얻어옴
					sscanf(buf, "%s%s%s",MP->devname, MP->mountdir, MP->fstype);
					if (strcmp(MP->mountdir,"/") == 0) is_root=1;
					if (stat(MP->devname, &lstat) == 0 || is_root)
					{
							if (strstr(buf, MP->mountdir) && S_ISBLK(lstat.st_mode) || is_root)
							{
									// 파일시스템의 총 할당된 크기와 사용량을 구한다.        
									statfs(MP->mountdir, &lstatfs);
									MP->size.blocks = lstatfs.f_blocks * (lstatfs.f_bsize/1024); 
									MP->size.avail  = lstatfs.f_bavail * (lstatfs.f_bsize/1024); 
									return MP;
									}
							}
					}
					//stream 과 연관된 파일 포인터를 파일 시작으로 이동한다.
					rewind(MP->fp);
					return NULL;
}

int dfclose(MOUNTP *MP)
{
		    fclose(MP->fp);
}

int main()
{
		    MOUNTP *MP;
			if ((MP=dfopen()) == NULL)
			{
					perror("error");
					return 1;
					}
					while(1)
					{
							while(dfget(MP))
							{
									printf("%-14s%-20s%10lu%10lu\n", MP->mountdir, MP->devname,
									MP->size.blocks,
									MP->size.avail);
							}
									printf("=========================\n\n");
									sleep(1);
					}

}
