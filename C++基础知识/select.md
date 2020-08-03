# select多路复用机制

select在使用前，先将需要监控的描述符对应的bit位置1，然后将其传给select,当有任何一个事件发生时，select将会返回所有的描述符，需要在应用程序自己遍历去检查哪个描述符上有事件发生，效率很低，并且其不断在内核态和用户态进行描述符的拷贝，开销很大

函数作用：

系统提供select函数来实现多路复用输入/输出模型。

select系统调用是用来让我们的程序监视多个文件句柄的状态变化的。程序会停在select这里等待，直到被监视的文件句柄有一个或多个发生了状态改变。关于文件句柄，其实就是一个整数，我们最熟悉的句柄是0、1、2三个，0是标准输入，1是标准输出，2是标准错误输出。0、1、2是整数表示的，对应的FILE *结构的表示就是stdin、stdout、stderr。

\#include <sys/select.h>

\#include <sys/time.h>

函数原型：

int select(int maxfd,//需要监视的最大的文件描述符值+1

fd_set *readset,//需要检测的可读文件描述符的集合

fd_set *writeset, //可写文件描述符的集合

fd_set *exceptset,//异常文件描述符的集合

struct timeval *timeout);  //描述一段时间长度，如果在这个时间内，需要监视的描述符没有事件发生则函数返回，返回值为0。

下面的**宏**提供了处理这三种描述词组的方式:
FD_CLR(inr fd,fd_set* set)；用来清除描述词组set中相关fd 的位

用来将你指定的文件描述符(套接字)fd从指定fd_set对象fdsetp中清除，即表示不再关心此fd。注意：fdsetp需要传入fd_set结构体对象的指针。

FD_ISSET(int fd,fd_set \*set)；用来测试描述词组set中相关fd 的位是否为真

用来判断你指定的文件描述符(套接字)fd是否满足可读、可写或者错误条件，如果满足则返回非0值，否则返回0。

FD_SET（int fd,fd_set\*set）；用来设置描述词组set中相关fd的位

用来将你关心的文件描述符(套接字)fd存入fd_set结构体对象fdsetp中去。

FD_ZERO（fd_set \*set）；用来清除描述词组set的全部位

用来清空整个fd_set结构体对象，形象地说就是fd_set结构体对象用来存储一组你关心的文件描述符(套接字)，FD_ZERO负责清空该对象中已有的文件描述符(套接字)。

参数timeout为结构timeval，用来设置select()的等待时间，其结构定义如下：

struct timeval  

{  

​    time_t tv_sec;//second  

​    time_t tv_usec;//minisecond  

};  

如果参数**timeout**设为：

NULL，则表示select（）没有timeout，select将一直被阻塞，直到某个文件描述符上发生了事件。

0：仅检测描述符集合的状态，然后立即返回，并不等待外部事件的发生。

特定的时间值：如果在指定的时间段里没有事件发生，select将超时返回。

**函数返回值**：

返回对应位仍然为1的fd的总数。

执行成功则返回文件描述词状态已改变的个数，如果返回0代表在描述词状态改变前已超过timeout时间，没有返回；当有错误发生时则返回-1，错误原因存于errno，此时参数readfds，writefds，exceptfds和timeout的值变成不可预测。错误值可能为：
EBADF 文件描述词为无效的或该文件已关闭
EINTR 此调用被信号所中断
EINVAL 参数n 为负值。
ENOMEM 核心内存不足

http://www.cpplive.com/html/876.html

```cpp
#include <stdio.h>  
#include <types.h>  
#include <time.h>  
#define SLEEP_TIME 10  
#define MAX_SESSION_UP 100  
int main(void)  
{  
    int i;  
    int fd_num;  
    int accept_fd_up[MAX_SESSION_UP] = {0};  
    fd_set readfds;  
    struct timeval select_timeval;  
    //you can add some task here, so the fd in accept_fd_up maybe changed here  
    while (1)  
    {  
        FD_ZERO(&readfds);  
        for (i=0; i<MAX_SESSION_UP; i++)  
        {  
            if (accept_fd_up[i] > max_sock)  
                max_sock = accept_fd_up[i];  
            if (accept_fd_up[i] > 0)  
                FD_SET(accept_fd_up[i], &readfds);  
        }  
        fd_num = select(max_sock+1, &readfds, NULL, NULL, &select_timeval);  
        if (fd_num < 0)  
        {  
            perror("select");  
            continue;  
        }  
        else if (0 == fd_num)  
        {  
            printf("select timeout...\n");  
            //resert the select_time after timeout  
            select_timeval.tv_sec = SLEEP_TIME;  
            select_timeval.tv_usec = 0;  
            //you can add some task here, so the task could work a time every SLEEP_TIME  
            //the fd in accept_fd_up maybe changed here  
            continue;  
        }  
        for (i=0; i<MAX_SESSION_UP; i++)  
        {  
            if (FD_ISSET(accept_fd_up[i], &readfds))  
            {  
                printf("do case in do_fd_up: %d,%d", accept_fd_up[i], i);  
                //you can add some task here to deal with the change of the fd  
                //the fd in accept_fd_up also maybe changed here  
            }  
        }  
    }  
}
```

该实例仅仅只是一个框架而已，它假设有一组大小为MAX_SESSION_UP的int类型数组存储了一堆文件描述符，其中凡是大于0的则默认为我们关心的文件描述符，需要select监管它，小于等于0的则被忽视。

### 理解select模型

理解select模型的关键在于理解fd_set,为说明方便，取fd_set长度为1字节，fd_set中的每一bit可以对应一个文件描述符fd。则1字节长的fd_set最大可以对应8个fd。

（1）执行fd_set set; FD_ZERO(&set);则set用位表示是0000,0000。

（2）若fd＝5,执行FD_SET(fd,&set);后set变为0001,0000(第5位置为1)

（3）若再加入fd＝2，fd=1,则set变为0001,0011

（4）执行select(6,&set,0,0,0)阻塞等待

（5）若fd=1,fd=2上都发生可读事件，则select返回，此时set变为0000,0011。注意：没有事件发生的fd=5被清空。

### select的作用

比如你有一个服务器程序，维护着N多个TCP连接，你如何去判断这些TCP连接上有数据传送过来了呢？最傻瓜的办法就是隔一定时间去循环读一次所有TCP连接对应的文件描述符，如果read返回正值则说明有数据过来。这样做未免也太傻瓜太浪费CPU了一点，无法做到及时的检测到结果，还好，select函数可以帮我们自动检测指定的文件描述符是否有数据可读，即已经建立好的连接那端有新的数据过来或者有新的尚未建立好的连接请求过来。

再比如你想编写一个非阻塞的连接程序，即你非阻塞的调用connect函数去连接另一台服务器，让系统去帮我们维护connect的返回结果，以便我们在connect尝试的这段时间可以执行其他任务，但是我们该如何去捕捉已经被系统所接管的connect函数的返回结果呢？傻瓜的办法就是隔一定时间调用getsockopt函数检测一下指定文件描述符是否异常，如果正常则连接成功，否则连接失败。这样做的缺点同样是浪费很多无用的定时检测消耗，而且还无法保证能够即使检测到connect函数是否连接成功，还好，select函数可以帮我们自动检测指定指定文件描述符是否有数据可写，即TCP三次握手是否已经建立完毕，即connect函数是否连接成功。

如此等等，简而言之，如果你需要监听一组文件描述符(套接字)是否可读、可写或者出错，你可以使用select函数来轻松实现。