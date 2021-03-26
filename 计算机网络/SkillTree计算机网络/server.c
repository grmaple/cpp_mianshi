#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

int main(){
	int sfd;
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1){
		perror("socket error\n");
		return -1;
	}
	
	
	struct sockaddr_in my_addr;  //定义结构体变量
	bzero(&my_addr, sizeof(struct sockaddr));//清空结构体
	my_addr.sin_family = AF_INET;  //表示采用Ipv4网络协议
	my_addr.sin_port = htons(8888);  //表示端口号为1234，通常是大于1024的一个值。
	// inet_addr()用来将IP地址字符串转换成网络所使用的二进制数字，如果为INADDR_ANY，这表示服务器自动填充本机IP地址。
	my_addr.sin_addr.s_addr = inet_addr("192.168.22.64"); 
	// 绑定地址，bind用来绑定一个端口号和IP地址，使套接口与指定的端口号和IP地址相关联。
	if(bind(sfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1){
		perror("bind error");
		close(sfd);
		exit(-1);
	}
	// listen使服务器的这个端口和IP处于监听状态，等待网络中某一客户机的连接请求。
	// 如果客户端有连接请求，端口就会接受这个连接。
	if(listen(sfd, 10) == -1){
		perror("listen error");
		close(sfd);
		exit(-1);
	}
	// accept接受远程计算机的连接请求，建立起与客户机之间的通信连接。
	// 当accept函数接受一个连接时，会返回一个新的socket标识符，以后的数据传输和读取就要通过这个新的socket编号来处理，
	// 原来参数中的socket也可以继续使用，继续监听其它客户机的连接请求。
	struct sockaddr_in clientaddr;
	bzero(&clientaddr, sizeof(struct sockaddr));
	int addrlen = sizeof(struct sockaddr);
	int new_fd = accept(sfd, (struct sockaddr*)&clientaddr, &addrlen);

    if(new_fd == -1) {
	  perror("accept error");
	  close(sfd);
	  exit(-1);
	}

	printf("%s %d success connect\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	
	char buf[50];
	while(1){
		bzero(buf, sizeof(buf));
		read(new_fd,buf,sizeof(buf));
		printf("客户端：");
		printf("%s\n",buf);
	}
	
	
	
	close(new_fd);
	close(sfd);
	return 0;
}
