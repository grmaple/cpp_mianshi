/*************************************************************************
	> 作者: grmaple
	> 名字：类模板实现数组类
	> 功能: 可以对内置数据类型以及自定义数据类型的数据进行存储
			将数组中的数据存储到堆区
			构造函数中可以传入数组的容量
			提供对应的拷贝构造函数以及拷贝赋值函数防止浅拷贝问题
			提供尾插法和尾删法对数组中的数据进行增加和删除
			可以通过下标的方式访问数组中的元素
			可以获取数组中当前元素个数和数组的容量
	> 时间: 2020.9.3
 ************************************************************************/

#include<iostream>
using namespace std;
#include<string>
template<typename T>
class MyArray {
public:
	MyArray(int capacity) {
		m_Capacity = capacity; 
		m_Size = 0;
		pAddress = new T[m_Capacity];
	}
	~MyArray() {
		if (pAddress != NULL) {
			delete[] pAddress;
			pAddress = NULL;
		}
	}
	MyArray(const MyArray& arr) {
		m_Capacity = arr.m_Capacity;
		m_Size = arr.m_Size;
		pAddress = new T[arr.m_Capacity];//深拷贝
		for (int i = 0; i < m_Size; i++) {
			pAddress[i] = arr.pAddress[i];
		}
	}
	MyArray& operator=(const MyArray& arr) {
		//先判断原来堆区是否有数据，如果有先释放
		if (pAddress != NULL) {
			delete[] pAddress;
			pAddress = NULL;
			m_Capacity = 0;
			m_Size = 0;
		}
		//深拷贝
		m_Capacity = arr.m_Capacity;
		m_Size = arr.m_Size;
		pAddress = new T[arr.m_Capacity];
		for (int i = 0; i < m_Size; i++) {
			pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}
	//尾插法
	void Push_back(const T& val) {
		//判断容量是否等于大小
		if (m_Capacity == m_Size) {
			cout<<"数组已满"<<endl;
			return ;
		}
		pAddress[m_Size] = val;
		m_Size++;
	}
	//尾删法
	void Pop_Back() {
		if (m_Size == 0) {
			cout<<"数组为空"<<endl;
			return ;
		}
		m_Size--;//让用户访问不到最后一个元素，实现逻辑删除
	}
	//下标访问
	T& operator[](int index) {
		return pAddress[index];
	}
	//返回数组容量
	int getCapacity(){
		return m_Capacity;
	}
	//返回数组大小
	int getSize() {
		return m_Size;
	}
private:
	T* pAddress;//指针指向堆区开辟的真实数组
	int m_Capacity;//数组容量
	int m_Size;//数组大小
};
void print(MyArray<int>& arr){
	for (int i = 0; i < arr.getSize(); i++) {
		cout<<arr[i]<<endl;
	}
}


class Person {
public:
	Person(){}
	Person(string name, int age):m_Name(name),m_Age(age){
		//m_Name = name;
		//m_Age = age;
	}
	string m_Name;
	int m_Age;
};
void printPerson(MyArray<Person>& arr){
	for (int i = 0; i < arr.getSize(); i++) {
		cout<<arr[i].m_Name<<"\t";
		cout<<arr[i].m_Age<<endl;
	}
}
int main() {
	MyArray<int> arr1(5);
	
	for (int i = 0; i < 5; i++) {
		arr1.Push_back(i);
	}
	print(arr1);
	arr1.Pop_Back();
	print(arr1);
	//自定义类型
	MyArray<Person> arr2(5);
	Person p1("数据",29);
	Person p2("十三点",22);
	Person p3("是",23);
	Person p4("是否",36);
	Person p5("计算",23);
	arr2.Push_back(p1);
	arr2.Push_back(p2);
	arr2.Push_back(p3);
	arr2.Push_back(p4);
	arr2.Push_back(p5);
	printPerson(arr2);
	
	return 0;
}