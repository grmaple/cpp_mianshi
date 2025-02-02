显然，这里有两种配置方式，一种是自动获取 ip 地址，一种是我们手动来设置，我相信大部分人都是通过**自动获取**的方式来得到 ip 的，那么问题来了，它是如何自动获得到的呢？

#### 客户端请求 ip

可能很多人都知道，是通过 DHCP 服务器来获取 ip 的，那么问题来了，你要给 DHCP 服务器发报文来获取 ip，那么你知道 DHCP 服务器的 ip 是多少吗？自己客户端的源 ip 又是多少呢？现在啥也不知道，该如何发送报文呢？

为了解决这个问题，客户端会发送一个广播，我们知道，广播报文是会发送局域网内的所有其他主机的，广播的目的 **ip 是 255.255.255.255，目的端口是 68**，为了让别人知道它是来请求一个 ip 的，我们的客户端会把 **0.0.0.0 作为自己的源 ip，源端口是 67**。意在告诉别人：我现在啥也没有，急需一个 ip，哪位老铁能给我提供一个 ip。

我们把这个请求 ip 的报文称之为 **discover 报文**。

> 这里提醒一些，这里发送的报文都是采用 UDP 报文，而不是 TCP 报文哈，下同。

#### DHCP响应

当 DHCP 服务器收到这个报文之后，一看源地址是 0.0.0.0，就知道生意来了，知道这是一个请求 ip 的报文，DHCP 服务器就会给它提供一个 ip，包括 **ip 地址，子码掩码，网关，ip 的有效期等信息**。

有人可能会问，只有源 ip 为 0.0.0.0 的信息，我们怎么把报文发送到它的手里呢？这不，我们每台电脑不都有 Mac 地址吗？在 discover 报文中，就会包含它的 MAC 地址了，DHCP 服务器，只需要发一个广播报文就可以了，广播报文的源ip是 DHCP 服务器自己的 ip，源端口是 67，目的地址是 255.255.255.255，目的端口是 68

我们把 DHCP 提供 ip 地址的报文称之为**offer报文**。

#### 客户端挑选 ip 地址

我们知道，有可能不知一台 DHCP 服务器收到了 discover 请求报文，也就是说，我们的主机可能会收到多个 offer 报文，所以呢，我们的主机会选择其中一个心仪的 offer 报文来作为自己的 ip，一般是选择最先收到的 offer 报文，选择好之后，会给对应的 DHCP 服务器次发送一个 **request 报文**，意在告诉它，我看中了你的报文。

DHCP 收到 request 报文之后，会给它回复一个 ACK 报文，并且把这个分配出去的 ip 进行登记（例如把这个 ip 标记为已使用状态）。

当我们的主机收到 ACK 报文之后，就可以开始冲浪在网上冲浪了。

#### 几点说明

这里可能有人会说，如果 DHCP 服务器没有在我们所在的局域网里怎么办？这个时候，这个 discover 报文 就会通过我们的网关来进行传递，并且会把源 ip 替换成网络的 ip，源端口是 68，这里涉及到 NAT 地址到转换

DHCP 服务器收到报文之后，就可以根据源端口 68 来判断这是一个 discover 请求报文了。就会把 offer 发给网关，网关再发给我们的主机

#### 租期

在DHCP客户端的租约时间到达 1/2 时，客户端会向为它分配 IP 地址的DHCP服务器发送 request 单播报文，以进行 IP 租约的更新。如果服务器判断客户端可以继续使用这个 IP 地址，就回复 ACK 报文，通知客户端更新租约成功。如果此IP地址不能再分配给客户端，则回复 NAK 报文，通知客户端续约失败。

如果客户端在租约到达 1/2 时续约失败，客户端会在租约到 7/8 时间时，广播发送 request 报文进行续约。DHCP服务器处理同首次分配 IP 地址的流程。

| 报文类型     | 描述                                                         |
| ------------ | ------------------------------------------------------------ |
| DHCP Discove | DHCP客户端请求地址时，并不知道DHCP服务器的位置，因此DHCP客户端会在本地网络内以广播方式发送请求报文，这个报文成为Discover报文，目的是发现网络中的DHCP服务器，所有收到Discover报文的DHCP服务器都会发送回应报文，DHCP客户端据此可以知道网络中存在的DHCP服务器的位置。 |
| DHCP Offer   | DHCP服务器收到Discover报文后，就会在所配置的地址池中查找一个合适的IP地址，加上相应的租约期限和其他配置信息（如网关、DNS服务器等），构造一个Offer报文，发送给用户 |
| DHCP Request | DHCP客户端可能会收到很多Offer，所以必须在这些回应中选择一个。Client通常选择第一个回应Offer报文的服务器作为自己的目标服务器，并回应一个广播Request报文，通告选择的服务器 |
| DHCP ACK     | DHCP服务器收到Request报文后，根据Request报文中携带的用户MAC来查找有没有相应的租约记录，如果有则发送ACK报文作为回应，通知用户可以使用分配的IP地址 |
| DHCP NAK     | 如果DHCP服务器收到Request报文后，没有发现有相应的租约记录或者由于某些原因无法正常分配IP地址，则发送NAK报文作为回应，通知用户无法分配合适的IP地址。 |
| DHCP Release | 当用户不再需要使用分配IP地址时，就会主动向DHCP服务器发送Release报文，告知服务器用户不再需要分配IP地址，DHCP服务器会释放被绑定的租约。 |
| DHCP Decline | DHCP客户端收到DHCP服务器回应的ACK报文后，通过地址冲突检测发现服务器分配的地址冲突或者由于其他原因导致不能使用，则发送Decline报文，通知服务器所分配的IP地址不可用。 |
| DHCP Inform  | DHCP客户端如果需要从DHCP服务器端获取更为详细的配置信息，则发送Inform报文向服务器进行请求，服务器收到该报文后，将根据租约进行查找，找到相应的配置信息后，发送ACK报文回应DHCP客户端 |