## resize和reserve的区别

**resize()**：改变当前容器内含有元素的数量(size())，eg: vector<int>v; v.resize(len);v的size变为len,如果原来v的size小于len，那么容器新增（len-size）个元素，元素的值为默认为0.当v.push_back(3);之后，则是3是放在了v的末尾，即下标为len，此时容器是size为len+1；如果原来v的size大于于len，则删除多出来的元素。
**reserve()**：改变当前容器的最大容量（capacity）,它不会生成元素，只是确定这个容器允许放入多少对象，如果reserve(len)的值大于当前的capacity()，那么会重新分配一块能存len个对象的空间，然后把之前v.size()个对象通过copy construtor复制过来，销毁之前的内存；
测试代码如下：

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> a;
    a.reserve(100);
    a.resize(50);
    cout<<a.size()<<"  "<<a.capacity()<<endl;
        //50  100
    a.resize(150);//resize变大，size则变，如果超出capacity，capacity就跟着变
    cout<<a.size()<<"  "<<a.capacity()<<endl;
        //150  150
    a.reserve(50);//reserve变小，capacity则不变
    cout<<a.size()<<"  "<<a.capacity()<<endl;
        //150  150
    a.resize(50);//resize变小，size则变
    cout<<a.size()<<"  "<<a.capacity()<<endl;
        //50  150  
    a.reserve(250);	//reserve变大，capacity则变
	cout<<a.size()<<"  "<<a.capacity()<<endl;
    	//50  250
}
```

### capacity（容量）与size（长度）的区别：

size指容器当前拥有的元素个数，而capacity则指容器在必须分配新存储空间之前可以存储的元素总数。**一般情况下，capacity是比size大的。**

c.size()	
返回容器c中元素个数。

capacity()

获取在容器需要分配更多的存储空间之前,能够存储的元素总数