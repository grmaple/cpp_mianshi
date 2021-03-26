## namespace

namespace主要是把一些东西区隔开来。

一个部门把自己的代码包装进一个namespace a，另一个部门把自己的代码包装进另一个namespace b。这样两个namespace里面有重名函数，变量也不会影响对方。

```cpp
#include<iostream>
#include<memory>
namespace jj01
{
    void test_member_template(){}
}
```

```cpp
#include<iostream>
#include<list>
namespace jj02
{
    template<typename T>
    using Lst = list<T,allocator<T>>;
    void test_member_template_param(){}
}
```

```cpp
int main(int argc, char** argv) {
    jj01::test_member_template();
    jj02::test_member_template_param();
}
```

