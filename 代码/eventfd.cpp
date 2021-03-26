#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/eventfd.h>
#include <errno.h>
#include <stdio.h>
using namespace std;
 
int main()
{
	int evfd = eventfd(10,0);
	uint64_t wdata = 0;
	uint64_t rdata = 0;
 
	if(read(evfd,&rdata,8) == -1)
	{
		perror(NULL);
		if(errno!=EAGAIN)return 0;
	}
	cout<<"Init read : "<<rdata<<endl;  //读计数器初始值
	
	wdata = 20;
	
	if(write(evfd,&wdata,8) == -1) //父进程写20
	{
		perror(NULL);
		return 0;
	}
	cout<<"parent write : "<<wdata<<endl;
	
	if(fork() == 0)
	{
		wdata = 30;
		if(read(evfd,&rdata,8) == -1) //子进程读计数器
		{
			perror(NULL);
			return 0;
		}
		cout<<"child read : "<<rdata<<endl;
		if(write(evfd,&wdata,8) == -1)  //子进程写30
		{
			perror(NULL);
			return 0;
		}
		cout<<"child write : "<<wdata<<endl;
		exit(0);		
	}
	wait(NULL);
	if(read(evfd,&rdata,8) == -1)   //父进程读计数器
	{
			perror(NULL);
			return 0;
	}
	cout<<"parent read : "<<rdata<<endl;
 
	return 0;
}