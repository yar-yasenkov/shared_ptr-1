#include <iostream>

template <typename T>
class shared_ptr{
public:
	shared_ptr(); /*noexcept*/
	shared_ptr(T* ptr); /*strong*/
	shared_ptr(shared_ptr const&); /*strong*/
	shared_ptr(shared_ptr&&); /*noexcept*/
	~shared_ptr(); /*noexcept*/
	auto operator = (shared_ptr const&)->shared_ptr&; /*strong*/
	auto operator = (shared_ptr&&)->shared_ptr&; /*noexcept*/
	auto swap(shared_ptr&) -> void; /*noexcept*/
	auto reset() -> void; /*noexcept*/
	auto get() const->T*; /*noexcept*/
	auto operator *() const->T&; /*strong*/
	auto countref() const->size_t; /*noexcept*/
private:
	T *ptr_;
	size_t *counter_;
};

template <typename T>
auto make_shared(T&&)->shared_ptr<T>;



template <typename T>
shared_ptr<T>::shared_ptr() : ptr_(nullptr), counter_(nullptr) {}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr) : ptr_(ptr), counter_(new size_t(1)) {}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr const& x) : ptr_(x.ptr_), counter_(x.counter_) 
{
	if(counter_ != nullptr) ++(*counter_);
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& x) : ptr_(x.ptr_), counter_(x.counter_)
{
	x.ptr_ = nullptr;
	x.counter_ = nullptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr()
{
	if (ptr_ != nullptr && counter_ != nullptr && --(*counter_) == 0)
	{
		delete ptr_;
		delete counter_;
	}
}

template <typename T>
auto shared_ptr<T>::operator = (shared_ptr const& x) -> shared_ptr&
{
	if (this != &x)
	{
		(shared_ptr<T>(x)).swap(*this);
	}
	return *this;
}

template <typename T>
auto shared_ptr<T>::operator = (shared_ptr&& x) -> shared_ptr&
{
	if (this != &x) this->swap(x);
	return *this;
}

template <typename T>
auto shared_ptr<T>::swap(shared_ptr& x) -> void
{
	std::swap(ptr_, x.ptr_);
	std::swap(counter_, x.counter_);
}

template <typename T>
auto shared_ptr<T>::reset() -> void
{
	if (ptr_ != nullptr && counter_ != nullptr && --(*counter_) == 0)
	{
		delete ptr_;
		delete counter_;
	}
	ptr_ = nullptr;
	counter_ = nullptr;
}

template <typename T>
auto shared_ptr<T>::get() const -> T*
{
	return ptr_;
}

template <typename T>
auto shared_ptr<T>::operator *() const -> T&
{
	if (ptr_ != nullptr) return *ptr_;
	else throw ("nullptr...");
}

template <typename T>
auto shared_ptr<T>::countref() const -> size_t
{
	if (counter_ != nullptr) return *counter_;
	else return 0;
}

template <typename T>
auto make_shared(T&& x) -> shared_ptr<T>
{
	return shared_ptr<T>(new T(std::move(x)));
}
