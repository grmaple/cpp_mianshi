template <typename T>
class smart_ptr {
public:
	explicit smart_ptr(T* ptr = nullptr)
    : ptr_(ptr) {}
	smart_ptr(smart_ptr& other)//拷贝构造函数
	{
		ptr_ = other.release();
	}
	template <typename U>
	smart_ptr(smart_ptr<U>& other)//拷贝构造函数模板
	{
		ptr_ = other.release();
	}
	// 子类指针向基类指针的转换
	template <typename U>
	smart_ptr(smart_ptr<U>&& other)//不是移动构造函数
	{
		ptr_ = other.release();
	}
	// 值传递省掉构造临时对象
	smart_ptr& operator=(smart_ptr rhs)
	{
		rhs.swap(*this);
		return *this;
	}
	~smart_ptr()
	{
		delete ptr_;
	}
	T* release()
	{
		T* ptr = ptr_;
		ptr_ = nullptr;
		return ptr;
	}
	void swap(smart_ptr& rhs)
	{
		using std::swap;
		swap(ptr_, rhs.ptr_);
	}
	
	
	
	T* get() const { return ptr_; }
	T& operator*() const { return *ptr_; }
	T* operator->() const { return ptr_; }
	operator bool() const { return ptr_; }
	
private:
  T* ptr_;
};
