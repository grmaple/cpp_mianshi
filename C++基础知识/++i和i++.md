## ++i和i++

### ++i和i++的区别

++i先自增1，再返回，i++先返回i,再自增1

### ++i和i++的实现

++i

```cpp
//++i实现 最后本身值改变了,返回也是值本身
int&  int::operator++（）
{
    *this +=1；
    return *this；
}
```

i++

```cpp
//i++实现 最后虽然本身值改变了,但返回的是之前的值
const int  int::operator（int）
{
    int oldValue = *this；
    ++（*this）；
    return oldValue；
}
```

### 例子

```cpp
#include <iostream>
using namespace std;
 
int main()
{
	int i = 100;
	i += (i++);
	cout << i << endl;
 /*
	i += i;	//100+100 = 200
	i += 1;	//200+1 = 201
 */
	i = 100;
	i += (++i);
	cout << i << endl;
 /*
	i += 1;	//100+1 = 101
	i += i;	//101+101 = 202
 */ 
	return 0;
}
```

