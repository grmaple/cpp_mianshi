## enum

- enum作用域不受限,会容易引起命名冲突。


例如下面无法编译通过的：

```cc
#include <iostream>
using namespace std;

enum Color {RED,BLUE};
enum Feeling {EXCITED,BLUE};

int main() 
{
    return 0;
}
```

- 枚举变量会隐式转换为int
- 用来表征枚举变量的实际类型不能明确指定，从而无法支持枚举类型的前向声明。

解决作用域不受限带来的命名冲突问题的一个简单方法是，给枚举变量命名时加前缀。

替代方案是命名空间

```cc
namespace Color 
{
    enum Type
    {
        RED=15,
        YELLOW,
        BLUE
    };
};

Color::Type c = Color::RED;//来定义新的枚举变量
using namespace Color;
Type c = RED;

```

不过，因为命名空间是可以随后被扩充内容的，所以它提供的作用域封闭性不高。
在大项目中，还是有可能不同人给不同的东西起同样的枚举类型名。

更“有效”的办法是用一个类或结构体来限定其作用域

```cc
struct Color1
{
    enum Type
    {
        RED=102,
        YELLOW,
        BLUE
    };
};
Color1::Type c11 = Color1::BLUE;
```

上面的做法解决了第一个问题，但对后两个仍然无能为力。

C++11引入使用枚举类。

- 新的enum的作用域不在是全局的
- 不能隐式转换成其他类型

```cc
// 下面等价于enum class Color2:int
enum class Color2
{
    RED=2,
    YELLOW,
    BLUE
};
Color2 c2 = Color2::RED;
cout << static_cast<int>(c2) << endl; //必须转！
```

- 可以指定用特定的类型来存储enum

```cc
enum class Color3:char;  // 前向声明

// 定义
enum class Color3:char 
{
    RED='r',
    BLUE
};
char c3 = static_cast<char>(Color3::RED);
```

### 类中的枚举类型

怎样才能建立在整个类中都恒定的常量呢？

由于#define 定义的宏常量是全局的，不能达到目的，于是想到实用const 修饰数据成员来实现。而const 数据成员的确是存在的，但其含义却不是我们所期望的。

```cc
class A 
{
  A(int size);  // 构造函数 
  const int SIZE ;    
}; 
A::A(int size) : SIZE(size)  // 构造函数的定义
{ 

} 
A  a(100); // 对象 a 的 SIZE 值为 100 
A  b(200); // 对象 b 的 SIZE 值为 200 
```

const 数据成员只在某个对象生存期内是常量，而对于整个类而言却是可变的，因为类可以创建多个对象，不同的对象其 const 数据成员的值可以不同，因为是在初始化列表时初始化的。

```cc
class Person{
public:
    typedef enum {
        BOY = 0,
        GIRL
    }SexType;
};
//访问的时候通过，Person::BOY或者Person::GIRL来进行访问。
```

枚举常量不会占用对象的存储空间，它们在编译时被全部求值。

枚举常量的缺点是：它的隐含数据类型是整数，其最大值有限，且不能表示浮点。