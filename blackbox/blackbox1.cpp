#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/statvfs.h>

using namespace cv;
using namespace std;

const int VIDEO_WIDTH = 640;
const int VIDEO_HIGHT = 360;
const int RUN_TIME = 60;


char* command_call(char* path)
{
	FILE *read_fp;
	int chars_read;
	char buffer[BUFSIZ +1];
	char *str = (char*)malloc(BUFSIZ +1);

	memset(buffer, '\0', sizeof(buffer));
	read_fp = popen(path, "r");
	chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);

	strcpy(str ,buffer);

	pclose(read_fp);

	return str;
}
void remove_dir()
{
	char path[BUFSIZ + 1] = "ls -rt ./user/blackbox/";
	char *sArr[BUFSIZ + 1] = { NULL , };
	char rmdir[BUFSIZ + 1] = "rm -r ./user/blackbox/";
	int i = 0;
	int byte = 0;

	char buffer[BUFSIZ +1];
	strcpy(buffer, command_call(path));

	char* ptr = strtok(buffer, "\n ");

	while(ptr != NULL)
	{
		sArr[i] = ptr;
		i++;

		ptr = strtok(NULL, " ");
	}

	printf("remove directory = %s\n", sArr[0]);
	strcat(rmdir ,sArr[0]);
	system(rmdir);

}
float check_disk()
{
	struct statvfs stat;
	char path[BUFSIZ +1] = "./user/blackbox";
	
	if(statvfs(path, &stat) != 0){
		printf("statvfs error\n");
	}

	return (float)stat.f_bavail / (float)stat.f_blocks;
}

void getfiletime(time_t org_time, char *time_str)
{
	struct tm *tm_ptr;
	tm_ptr = localtime(&org_time);

	sprintf(time_str, "%02d%02d%02d_%02d%02d%02d",
			tm_ptr->tm_year+1900,
			tm_ptr->tm_mon+1,
			tm_ptr->tm_mday,
			tm_ptr->tm_hour,
			tm_ptr->tm_min,
			tm_ptr->tm_sec);
}

void getdirtime(time_t org_time, char *time_str)
{
	struct tm *tm_ptr;
	tm_ptr = localtime(&org_time);

	sprintf(time_str, "%02d%02d%02d_%02d",
			tm_ptr->tm_year+1900,
			tm_ptr->tm_mon+1,
			tm_ptr->tm_mday,
			tm_ptr->tm_hour
	       );

}

void mk_folderPath(){
	char buff[BUFSIZ + 1] = "./user/blackbox/";
	char *p_dirc = buff;

	buff[BUFSIZ + 1] = '\0';

	while(*p_dirc){
		if('/' == *p_dirc){
			*p_dirc = '\0';
			if( 0!= access(buff, F_OK)){
					mkdir(buff, 0777);
					}
				*p_dirc = '/';
				}
		else
			printf("file path make error\n");	

		p_dirc++;
	}
}

void mk_folder(){

	char buff[BUFSIZ + 1] = "./user/blackbox/";

	time_t the_time;
	char d_buffer[100];
	
	time(&the_time);
	getdirtime(the_time,d_buffer);
	
	strcat(buff, d_buffer);
	
	if(mkdir(buff, 0777) == 0)
		printf("folder make\n");
	else
		printf("folder make error\n");

}

int video_recode(){

	Mat img_color;
	time_t the_time;
	char v_buffer[100];
	char d_buffer[100];
	string videoName;
	string folderName;
	string v_w = to_string(VIDEO_WIDTH);
	string v_h = to_string(VIDEO_HIGHT);
	int s_time;
	bool first = true;

	s_time = the_time;
	folderName = d_buffer;

	// for jetson onboard camera
	string gst = "nvarguscamerasrc ! video/x-raw(memory:NVMM), width="+v_w+", height="+v_h+",format=(string)NV12, framerate=(fraction)24/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";

	VideoCapture cap(gst);

	//video open failed
	if(!cap.isOpened())
	{
		cout << "errororor" <<endl;
		return -1;
	}

	VideoWriter video;

	while(1)
	{
		cap >> img_color;

		time(&the_time);
		getdirtime(the_time,d_buffer);
		//hour divided folder,make new folder
		if(folderName != d_buffer)
		{
			folderName = d_buffer;
		}
		//make new record file 
		if(the_time >= s_time+ RUN_TIME || first) //first or after 10seconds
		{
			s_time = the_time;
			getfiletime(the_time,v_buffer);
			videoName = "./user/blackbox/"+folderName+"/";
			videoName += v_buffer;
			videoName += ".avi";
			first = false;

			video.open(videoName,CV_FOURCC('D','I','V','X'),24,Size(VIDEO_WIDTH,VIDEO_HIGHT));

			printf("DISK LEFT SIZE: %f\n",check_disk());
		}

		//read,write
		video.write(img_color);
		imshow("Color", img_color);
		if (waitKey(25) >= 0)
			return -1;
	}

}

int main(int argc, char* argv[])

{
	pid_t pid;
	pid_t pid_child;

	string folderName;
	time_t the_time;	
	char d_buffer[100];	
	int s_time;
	int status;
	

	printf("DISK LEFT SIZE: %f\n",check_disk());
	
	pid = fork();

	if(pid == -1){
		printf("can't fork, erro\n");
		exit(0);
	}

	if(pid == 0) {

		if(video_recode() == -1)
			exit(0);
	}
	else{
		mk_folderPath();
		mk_folder();

		while(1){
			
			time(&the_time);
			if(s_time == 0)
				s_time = the_time;

			getdirtime(the_time,d_buffer);
			
			if(folderName != d_buffer){
				mk_folder();
				folderName = d_buffer;
			}
			
			if(the_time >= s_time+RUN_TIME) //first or after 10seconds
			{
				if(check_disk() < 0.3)
				{
					printf("buffer over\n");
					remove_dir();
				}

				s_time = the_time;

				}

			}

			pid_child = waitpid(pid, &status, WNOHANG);

			if(0 != pid_child){
				exit(0);
			}

	}
	exit(0);

	return 0;
}

