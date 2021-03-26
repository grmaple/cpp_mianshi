#include<utility>
#include<cstdio>
// 共享计数
class shared_count {
public:
  shared_count() : count_(1) {}
  void add_count()
  {
    ++count_;
  }
  long reduce_count()
  {
    return --count_;
  }
  long get_count() const
  {
    return count_;
  }

private:
  long count_;
};

template <typename T>
class smart_ptr {
public:

	template <typename U>
	friend class smart_ptr;
	
	explicit smart_ptr(T* ptr = nullptr)
    : ptr_(ptr)
	{
		if (ptr) {
			shared_count_ = new shared_count();
		}
	}
	
	smart_ptr(const smart_ptr& other)//拷贝构造
	{
		ptr_ = other.ptr_;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}
	template <typename U>
	smart_ptr(const smart_ptr<U>& other)// 拷贝构造模板
	{
		ptr_ = other.ptr_;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}
	template <typename U>
	smart_ptr(smart_ptr<U>&& other)// 移动构造，计数不用加一
	{
		ptr_ = other.ptr_;
		if (ptr_) {
			shared_count_ = other.shared_count_;
			other.ptr_ = nullptr;
		}
	}
	// 类型转换
	template <typename U>
	smart_ptr(const smart_ptr<U>& other, T* ptr)
	{
		ptr_ = ptr;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}
	smart_ptr& operator=(smart_ptr rhs)
	{
		rhs.swap(*this);
		return *this;
	}
	~smart_ptr()
	{
		if (ptr_ && !shared_count_->reduce_count()) {//计数为0时才delete
			delete ptr_;
			delete shared_count_;
		}
	}
	
	long use_count() const// 返回引用计数
	{
		if (ptr_) {
			return shared_count_->get_count();
		} else {
			return 0;
		}
	}
	void swap(smart_ptr& rhs)
	{
		using std::swap;
		swap(ptr_, rhs.ptr_);
		swap(shared_count_, rhs.shared_count_);
	}
	
	T* get() const { return ptr_; }
	T& operator*() const { return *ptr_; }
	T* operator->() const { return ptr_; }
	operator bool() const { return ptr_; }
	
private:
	T* ptr_;
	shared_count* shared_count_;
};


template <typename T, typename U>
smart_ptr<T> dynamic_pointer_cast(const smart_ptr<U>& other)
{
	T* ptr = dynamic_cast<T*>(other.get());
	return smart_ptr<T>(other, ptr);
}
class shape {
public:
  virtual ~shape() {}
};

class circle : public shape {
public:
  ~circle() { puts("~circle()"); }
};

int main()
{
  smart_ptr<circle> ptr1(new circle());
  printf("use count of ptr1 is %ld\n",
         ptr1.use_count());
  smart_ptr<shape> ptr2;
  printf("use count of ptr2 was %ld\n",
         ptr2.use_count());
  ptr2 = ptr1;
  printf("use count of ptr2 is now %ld\n",
         ptr2.use_count());
		 
  smart_ptr<circle> ptr3 = dynamic_pointer_cast<circle>(ptr2);
  printf("use count of ptr3 is %ld\n",
         ptr3.use_count());
  if (ptr1) {
    puts("ptr1 is not empty");
  }
}