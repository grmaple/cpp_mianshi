## Day3

### UDP

- UDP是一个简单的**面向数据报**的运输层协议：进程的每个输出操作都正好产生一个UDP数据报，并组装成一份待发送的IP数据报。

- 这与**面向流字符(字节流)**的协议不同，如TCP，应用程序产生的全体数据与真正发送的单个IP数据报可能没有什么联系。
- UDP不提供可靠性：它把应用程序传给 I P层的数据发送出去，但是并不保证它们能到达目的地。
- 应用程序必须关心IP数据报的长度。如果它超过网络的MTU，那么就要对IP数据报进行分片。

![image-20200907115421266](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200907115421266.png)

##### UDP三大应用

- 查询类：DNS
  - 没有TCP三次握手
  - 多个DNS同时查询
- 数据传输：TFTP
  - 停止等待协议，慢（需应用层确认数据）
  - 适合无盘工作站，小
- 语音视频流
  - 支持广播和组播
  - 支持丢包，保障效率

##### UDP首部

![image-20200907120652248](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200907120652248.png)

- 端口号表示发送进程和接收进程。
- TCP端口号与UDP端口号是相互独立的。(rsh和syslog = 514)
- 尽管相互独立，如果TCP和UDP同时提供某种知名服务，两个协议通常选择相同的端口号。这纯粹是为了使用方便，而不是协议本身的要求。
- UDP长度字段指的是UDP首部和UDP数据的字节长度。该字段的最小值为 8字节

##### UDP检验和

- UDP检验和覆盖UDP首部和UDP数据。
- IP首部的检验和，它只覆盖IP的首部
- UDP的检验和是可选的，而TCP的检验和是必需的。
- UDP检验和计算与IP首部检验和计算存在不同的地方。首先， UDP数据报的**长度可以为奇数字节**，但是检验和算法是把若干个 16 bit字相加。解决方法是必要时在最后增加填充字节0，这只是为了检验和的计算（也就是说，可能增加的填充字节不被传送）。
- 其次，UDP数据报和TCP段都包含一个**12字节长的伪首部**，它是为了计算检验和而设置的。伪首部包含IP首部一些字段。其目的是让UDP两次检查数据是否已经正确到达目的地（例如，IP没有接受地址不是本主机的数据报，以及IP没有把应传给另一高层的数据报传给UDP）。

![image-20200907121545908](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200907121545908.png)

##### IP分片

- IP把MTU与数据报长度进行比较(出接口)
- 如果需要则进行分片，分片可以发生在原始发送端主机上，也可以发生在中间路由器上。
- 把一份IP数据报分片以后，只有到达目的地才进行重新组装。
- 重新组装由目的端的IP层来完成，其目的是使分片和重新组装过程**对运输层（TCP和UDP）是透明的**。
- 已经分片过的数据报有可能会再次进行分片（可能不止一次）。

![image-20200907123834157](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200907123834157.png)

- 对于发送端发送的每份 I P数据报来说，其标识字段都包含一个唯一值。该值在数据报分片时被复制到每个片中。
- 标志字段中第一个比特CD，当前没有使用。
- 标志字段中第二个比特DF称作“不分片”位。如果将这一比特置 1，IP将不对数据报进行分片。相反把数据报丢弃并发送一个ICMP差错报文“需要进行分片但设置了不分片比特”给起始端。
- 标志字段中第三个比特MF来表示“更多的片”。除了最后一片外，其他每个组成数据报的片都要把该比特置 1。
- 片偏移字段指的是该片偏移原始数据报开始处的位置(方便重组)。另外，当数据报被分片后，每个片的总长度值要改为该片的长度值。

- 当IP数据报被分片后，每一片都成为一个分组，具有自己的IP首部，并在选择路由时与其他分组独立。这样，当数据报的这些片到达目的端时**有可能会失序**，但是在IP首部中有足够的信息让接收端能正确组装这些数据报片。
- **即使只丢失一片数据也要重传整个数据报。**
- IP层本身没有超时重传的机制——由更高层来负责超时和重传（TCP有超时和重传机制，但UDP没有。一些UDP应用程序本身也执行超时和重传）。当来自TCP报文段的某一片丢失后，TCP在超时后会重发整个TCP报文段，该报文段对应于一份IP数据报。**没有办法只重传数据报中的一个数据报片。**
- 如果对数据报分片的是中间路由器，而不是起始端系统，那么起始端系统就无法知道数据报是如何被分片的。就这个原因，经常要避免分片。

##### 例子

一个ICMP数据报。如果MTU = 500。

IP+ICMP+DATA = 1000字节，即ICMP数据报长度为980字节。

第一片：IP(20)+ICMP(8)+DATA(472) = 500，剩下DATA(500)

第二片：IP(20)+DATA(480) = 500，剩下DATA(20)

第三片：IP(20)+DATA(20)+PAD(6) = 46

1. 只有第一片有TCP/UDP头部信息。
2. 除了最后一片，其他片数据部分需要是8的倍数
3. 最后一片长度不足46需要补齐。

#####  ICMP不可达差错（需要分片）

![image-20200907130003983](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200907130003983.png)

发生ICMP不可达差错的另一种情况是，当路由器收到一份需要分片的数据报，而在 I P首部又设置了不分片（DF）的标志比特。如果某个程序需要判断到达目的端的路途中最小MTU是多少—称作路径MTU发现机制，那么这个差错就可以被该程序使用。

如果路由器没有提供这种新的ICMP差错报文格式，那么下一站的MTU就设为0。

##### 最大UDP数据报长度

- I P数据报的最大长度是65535字节，这是由IP首部16比特总长度字段所限制的。但是，大多数实现所提供的长度比这个最大值小，我们将遇到两个限制因素。
- 第一，应用程序可能会受到其程序接口的限制。 **socket API**提供了一个可供应用程序调用的函数，以设置接收和发送缓存的长度。对于 UDP socket，这个长度与应用程序可以读写的最大 UDP数据报的长度直接相关。现在的大部分系统都默认提供了可读写大于8192字节的UDP数据报（使用这个默认值是因为8192是NFS读写用户数据数的默认值）。
- 第二个限制来自于**TCP/IP的内核实现**。可能存在一些实现特性（或差错），使IP数据报长度小于65535字节。
- 很显然，这个限制**与源端和目的端的实现有关**。
- 要求主机必须能够接收最短为576字节的I P数据报。在许多UDP应用程序的设计中，其应用程序数据被限制成 512字节或更小，因此比这个限制值小。例

##### 数据报截断

- 由于I P能够发送或接收特定长度的数据报并不意味着接收应用程序可以读取该长度的数据。因此，UDP编程接口允许应用程序指定每次返回的最大字节数。如果接收到的数据报长度大于应用程序所能处理的长度，那么会发生什么情况呢？
- 不幸的是，该问题的答案取决于**编程接口和实现**。

##### 每个端口有多个接收者

大多数的系统在某一时刻只允许一个程序端点与某个本地IP地址及UDP端口号相关联。当目的地为该IP地址及端口号的UDP数据报到达主机时，就复制一份传给该端点。

### 广播和多播

- 有三种IP地址：单播地址、广播地址和多播地址。
- 广播和多播仅应用于UDP，它们对需将报文同时传往多个接收者的应用来说十分重要。
- TCP是一个面向连接的协议，它意味着分别运行于两主机（由IP地址确定）内的两进程（由端口号确定）间存在一条连接。只支持单播。
- 有时一个主机要向网上的所有其他主机发送帧，这就是广播。通过ARP和RARP可以看到这一过程。
- 多播(multicast) 处于单播和广播之间：帧仅传送给属于多播组的多个主机。
- 多个主机。

![image-20200907132501234](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200907132501234.png)

- 外界和接口卡的交互
  - 通常网卡仅接收那些目的地址为网卡物理地址或广播地址的帧。
  - 多数接口均被设置为混合模式，这种模式能接收每个帧的一个复制。
  - 丢弃：如果帧检验和错
- 接口卡和设备驱动程序的交互
  - 帧类型中必须指定要使用的协议（ I P、A R P等等）。
  - 进行多播过滤来检测该主机是否属于多播地址说明的多播组。
  - 丢弃：没有上层信息或者不属于某个多播地址
- 设备驱动程序和IP的交互
  - IP根据IP地址中的源地址和目的地址进行更多的过滤检测
  - 丢弃：根据IP地址如ACL进行过滤
- UDP和IP交互
  - UDP收到由IP传送来的数据报，就根据目的端口号，有时还有源端口号过滤。如果当前没有进程使用该目的端口号，就丢弃该数据报并产生一个ICMP不可达报文（TCP根据它的端口号作相似的过滤）。如果UDP数据报存在检验和错，将被丢弃。
  - 丢弃：没有上层的应用程序和广播在此丢弃

使用广播的问题在于它增加了对广播数据不感兴趣主机的处理负荷。

多播的出现减少了对应用不感兴趣主机的处理负荷。

##### 广播

受限的广播地址是 255 . 255 . 255 . 255。

指向网络的广播地址是主机号为全1的地址。10.255.255.255

指向子网的广播地址为主机号为全1且有特定子网号的地址。10.1.1.255

指向所有子网的广播地址的子网号及主机号为全1。10.255.255.255

主机处理的地址。192.168.255.255(cisco路由器支持)

路由器支持255.255.255.255，主机不支持(当主机处理)