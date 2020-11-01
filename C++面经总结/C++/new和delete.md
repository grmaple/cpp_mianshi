## new与malloc的区别，delet和free的区别？

free和malloc匹配：释放malloc出来动态内存;

delete和new匹配：释放new出来的动态内存空间。

1.new和delete是关键字，需要编译器的支持；malloc和free是库函数，需要包含库头文件。

2.malloc/free是c/c++标准库的函数，new/delete除了分配空间还会调用构造函数和析构函数进行初始化和清理（清理成员）。

3.malloc/free需要手动计算类型大小且返回值是void*，new/delete可以自己计算类型大小，返回对应的指针。

4.对于自定义类型new会先调用operator new函数，申请足够的内存（通常底层使用malloc实现）。然后调用类型的构造函数，初始化成员变量，最后返回自定义类型指针。delete先调用析构函数，然后调用operator delete函数释放内存（通常底层使用free实现）。（对malloc和free进行了封装）。malloc/free是库函数，只能动态的申请和释放内存，无法强制要求其做自定义类型对象构造和析构工作。

5.在类和对象的时候会有很大区别。在使用malloc和free来处理动态内存的时候，仅仅是释放了这个对象所占的内存，而不会调用这个对象的析构函数；使用new和delete就可以既释放对象的内存的同时，调用这个对象的析构函数。

**如果问到malloc，还有可能问你memcpy等realloc函数能不能在C++中使用，绝对不能，因为这些函数进行的都是内存值拷贝（也就是对象的浅拷贝），会发生浅拷贝这个严重的问题！**