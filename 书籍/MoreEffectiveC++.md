1. 仔细区别 pointers 和 references（当你知道你需要指向某个东西，而且绝不会改变指向其他东西，或是当你实现一个操作符而其语法需求无法由 pointers 达成，你就应该选择 references；任何其他时候，请采用 pointers）
2. 最好使用 C++ 转型操作符（`static_cast`、`const_cast`、`dynamic_cast`、`reinterpret_cast`）
3. 绝不要以多态（polymorphically）方式处理数组（多态（polymorphism）和指针算术不能混用；数组对象几乎总是会涉及指针的算术运算，所以数组和多态不要混用）
4. 非必要不提供 default constructor（避免对象中的字段被无意义地初始化）
5. 对定制的 “类型转换函数” 保持警觉（单自变量 constructors 可通过简易法（explicit 关键字）或代理类（proxy classes）来避免编译器误用；隐式类型转换操作符可改为显式的 member function 来避免非预期行为）
6. 区别 increment/decrement 操作符的前置（prefix）和后置（postfix）形式（前置式累加后取出，返回一个 reference；后置式取出后累加，返回一个 const 对象；处理用户定制类型时，应该尽可能使用前置式 increment；后置式的实现应以其前置式兄弟为基础）
7. 千万不要重载 `&&`，`||` 和 `,` 操作符（`&&` 与 `||` 的重载会用 “函数调用语义” 取代 “骤死式语义”；`,` 的重载导致不能保证左侧表达式一定比右侧表达式更早被评估）
8. 了解各种不同意义的 new 和 delete（`new operator`、`operator new`、`placement new`、`operator new[]`；`delete operator`、`operator delete`、`destructor`、`operator delete[]`）
9. 利用 destructors 避免泄漏资源（在 destructors 释放资源可以避免异常时的资源泄漏）
10. 在 constructors 内阻止资源泄漏（由于 C++ 只会析构已构造完成的对象，因此在构造函数可以使用 try...catch 或者 auto_ptr（以及与之相似的 classes） 处理异常时资源泄露问题）
11. 禁止异常流出 destructors 之外（原因：一、避免 terminate 函数在 exception 传播过程的栈展开（stack-unwinding）机制种被调用；二、协助确保 destructors 完成其应该完成的所有事情）
12. 了解 “抛出一个 exception” 与 “传递一个参数” 或 “调用一个虚函数” 之间的差异（第一，exception objects 总是会被复制（by pointer 除外），如果以 by value 方式捕捉甚至被复制两次，而传递给函数参数的对象则不一定得复制；第二，“被抛出成为 exceptions” 的对象，其被允许的类型转换动作比 “被传递到函数去” 的对象少；第三，catch 子句以其 “出现于源代码的顺序” 被编译器检验对比，其中第一个匹配成功者便执行，而调用一个虚函数，被选中执行的是那个 “与对象类型最佳吻合” 的函数）
13. 以 by reference 方式捕获 exceptions（可避免对象删除问题、exception objects 的切割问题，可保留捕捉标准 exceptions 的能力，可约束 exception object 需要复制的次数）
14. 明智运用 exception specifications（exception specifications 对 “函数希望抛出什么样的 exceptions” 提供了卓越的说明；也有一些缺点，包括编译器只对它们做局部性检验而很容易不经意地违反，与可能会妨碍更上层的 exception 处理函数处理未预期的 exceptions）
15. 了解异常处理的成本（粗略估计，如果使用 try 语句块，代码大约整体膨胀 5%-10%，执行速度亦大约下降这个数；因此请将你对 try 语句块和 exception specifications 的使用限制于非用不可的地点，并且在真正异常的情况下才抛出 exceptions）
16. 谨记 80-20 法则（软件的整体性能几乎总是由其构成要素（代码）的一小部分决定的，可使用程序分析器（program profiler）识别出消耗资源的代码）
17. 考虑使用 lazy evaluation（缓式评估）（可应用于：Reference Counting（引用计数）来避免非必要的对象复制、区分 operator[] 的读和写动作来做不同的事情、Lazy Fetching（缓式取出）来避免非必要的数据库读取动作、Lazy Expression Evaluation（表达式缓评估）来避免非必要的数值计算动作）
18. 分期摊还预期的计算成本（当你必须支持某些运算而其结构几乎总是被需要，或其结果常常被多次需要的时候，over-eager evaluation（超急评估）可以改善程序效率）

19. 了解临时对象的来源——区别局部对象，临时对象是不可见的，只要产生一个non-heap object而没有命名，便诞生一个临时对象。通常发生于两种情况1、当隐式类型转换被施行起来以求函数调用能够成功。

20. 当函数返回对象时候。可以通过“返回值优化”见条款20。
    协助完成“返回值优化（RVO）”——如果返回值必须返回对象（如：operator*），那就返回对象。但是可以通过特殊写法，让编译器消除临时对象的成本。


利用重载技术（overload）避免隐式类型转换——利用重载技术时候需要注意，每一个重载的operator必须带有一个“用户定制类型”的参数。不要忘了80-20原则，增加一大堆重载函数不一定是件好事，除非使用重载函数后，程序的整体效率获得重大的改善。
考虑以操作符复合形式（op =）取代其独身形式（op）——要确保操作符的复合形式（operator+=）和其独身形式（operator+）之间的自然关系能够存在，一个好方法就是以前者为基础实现后者。

考虑使用其他程序库——不同的程序库即使提供相似的机能，也往往表现出不同性能取舍策略，所以一旦你找出程序的瓶颈，你应该考虑是否有可能因为该用另一个程序库而移除这些瓶颈。
了解 virtual functions、multiple inheritance（多继承）、virtual base classes、runtime type identification（运行时类型识别）的成本——1、vtbl通常是一个由“函数指针”架构而成的数组，某些编译器会以链表取代数组，但基本策略相同。尽量避免将虚函数声明为inline，方法一是探测式，类的虚函数一般产生于内含其第一个non-inline，non-pure虚函数定义式的目标文件中。2、多继承时，单个对象有多个vptrs，会增加对象体积大小。3、RTTI能让我们在运行时找到对象和类的有关信息，所以肯定有某个地方存储了这些信息让我们查询，这些信息被存储在类型为type_info的对象里。通常，RTTI被设计为在类的vbtl上实现。
