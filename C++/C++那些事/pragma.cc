//#pragma pack(push)  // 保存对齐状态
//#pragma pack(8)     // 设定为 4 字节对齐
#pragma pack(push,4)
struct test
{
    char m1;
	int m2;
	//char m5;
    double m4;
	//int m3;
    
};
#include<iostream>

int main(){
	std::cout<<sizeof(long)<<std::endl;
	std::cout<<sizeof(float)<<std::endl;
	std::cout<<sizeof(int)<<std::endl;
	std::cout<<sizeof(test)<<std::endl;
}
//#pragma pack(pop)   // 恢复对齐状态