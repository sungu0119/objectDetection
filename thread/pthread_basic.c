#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

int glob_var = 6; //데이터 영역에 할당 초기값을 가지는 전역변수

//쓰레드 함수에서는 인자가 하나밖에 안들어옴 인자를 여러게 던지려면 구조체를 만들어서 인자를 여러개 만들고 구조체의 주소를 넘겨 주어 사용
//포인터의 타입이 정해지지 않은 주소값만 넘어옴
void *t_function(void *data)
{
	int id;
	//스레드의 아이디를 찍어보기 위한 변수
	pthread_t t_id;
	// id = 1
	id =*((int *)data);
	t_id = pthread_self();
	printf("pid = %d, t_id=%lu, id = %d , gloa_var = %d\n", getpid(), t_id, id, glob_var);

	return (void*)(id*id);
}



int main(void)
{
	pthread_t p_thread[2]; // 스레드 두개를 추가 
	int status;	//스레드 상태 확인 변수
	int a = 1;
	int b = 2;
	int err;

	//메인스레드의 프로세스 pid 확인
	printf("before pthread_create() pid  = %d, glob_var= %d\n ",getpid(),glob_var);

	//thread1 을 생성
	//(void*)&a ==> a 의 타입의 정보는 안넘기고  주소값만 넘겨줌
	if((err = pthread_create(&p_thread[0], NULL, t_function, (void*)&a))<0)
	{
			perror("thread create error : ");
			exit(1);
	}

	//create thread 2
	if((err = pthread_create(&p_thread[1], NULL, t_function, (void*)&b))<0)
	{
			perror("thread create error : ");
			exit(2);
	}

	pthread_join(p_thread[0], (void**)&status);
	printf("thread join : %d\n", status);


	pthread_join(p_thread[1], (void**)&status);
	printf("thread join : %d\n", status);
	
	printf("after pthread_create() glob_var = %d\n", glob_var);

	return 0;
}	
