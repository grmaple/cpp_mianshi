#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// struct sockaddr{
     // unsigned short sa_family; /*地址族*/
     // char sa_data[14]; /*14字节的协议地址，包含该socket的IP地址和端口号。*/
// };

// struct sockaddr_in{
     // short int sa_family; /*地址族*/
     // unsigned short int sin_port; /*端口号*/
     // struct in_addr sin_addr; /*IP地址*/
     // unsigned char sin_zero[8]; /*填充0 以保持与struct sockaddr同样大小*/
// };

// struct in_addr{
	// unsigned long int  s_addr; /* 32位IPv4地址，网络字节序 */
// };

int sfd;

void *fun(){
	char buf[50];
	while(1){
		bzero(buf,sizeof(buf));
		
		scanf("%s",buf);
		write(sfd,buf,sizeof(buf));
		printf("%s\n",buf);
	}
}

int main(){
	// 参数：domain{ AF_INET：Ipv4网络协议   AF_INET6：IPv6网络协议}
	// type{ tcp：SOCK_STREAM   udp：SOCK_DGRAM}
	// protocol指定socket所使用的传输协议编号。通常为0.
	// 返回值：成功则返回套接口描述符，失败返回-1。
	
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1){
		perror("socket error\n");
		return -1;
	}
	struct sockaddr_in seraddr;//请求连接服务器
	//memset(&seraddr, 0, sizeof(struct sockaddr));
	seraddr.sin_family = AF_INET;
	// 端口号主机字节序转成网络字节序
	// h代表host,n代表network，s代表short，l代表long。通常16位的IP端口号用s代表，而IP地址用l来代表。
	seraddr.sin_port = htons(1234); //服务器的端口号
	// 将点分十进制数的IP地址转换成为网络字节序的32位二进制数值。若成功则返回32位二进制的网络字节序地址。
	seraddr.sin_addr.s_addr = inet_addr("192.168.22.64");  //服务器的ip
	// 将sockaddr_in强转成sockaddr
	// 参数：sockfdà为前面socket的返回值，即sfd
	// serv_addrà为结构体指针变量，存储着远程服务器的IP与端口号信息。
	// addrlenà表示结构体变量的长度
	// 返回值：成功则返回0，失败返回-1
	int conn = connect(sfd, (struct sockaddr*)&seraddr, sizeof(struct sockaddr));
	if( conn == -1){
		perror("connect error");
		close(sfd);
		return -1;
	}
	//创建线程
	pthread_t pid;
	pthread_create(&pid, NULL,fun,NULL);
	
	
	char buf[50];
	while(1){
		bzero(buf,sizeof(buf));
		read(sfd,buf,sizeof(buf));
		printf("服务端：");
		printf("%s\n",buf);
	}
	
	close(sfd);
	
	return 0;
}