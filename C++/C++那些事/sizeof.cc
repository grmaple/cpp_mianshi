#include<iostream>
using namespace std;



int main(void)
{
	char *c[] = {"ENTER","NEW","POINT","FIRST"};
	char** cp[] = {c+3,c+2,c+1,c};
	char***cpp = cp;
	printf("%s\n", **++cpp);// ++cpp 会改变 cpp 的值
	printf("%s\n", *--*++cpp+3);//
	printf("%s\n", *cpp[-2]+3);//-2 并没有改变 cpp
	printf("%s\n", cpp[-1][-1]+1);
	
    return 0;
}