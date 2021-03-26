![image-20210228142459480](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20210228142459480.png)

![image-20210228142200594](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20210228142200594.png)

malloc()和new不能被重载，::operator new()可以被重载

```c++
void* p1 = malloc(512);// 512bytes
free(p1);

complex<int>* p2 = new complex<int>; // one object
delete p2;

void* p3 = ::operator new(512); //512 bytes
::operator delete(p3);

#ifdef _MSC_VER
	int* p4 = allocator<int>().allocate(3,(int*)0);//3 ints,注意(int*)0
	allocator<int>().deallocate(p4, 3);
#endif
#ifdef __BORLANDC__
	int* p4 = allocator<int>().allocate(5);//5 ints,不用(int*)0，有默认参数
	allocator<int>().deallocate(p4, 5);
#endif
#ifdef __GNUC__//2.9
	void* p4 = alloc::allocate(512);//512 bytes,和其他版本不一样，是分配字节，并且是static函数
	alloc::deallocate(p4, 512);
#endif
#ifdef __GNUC__//4.9
	void* p4 = allocator<int>().allocate(7);//7 ints，回归成和其他版本一样
	allocator<int>().deallocate((int*)p4, 7);

	void* p5 = __gnu_cxx::__pool_alloc<int>().allocate(9);//9 ints，原alloc改版
	__gnu_cxx::__piil_alloc<int>().deallocate((int*)p5, 9);
#endif
```

