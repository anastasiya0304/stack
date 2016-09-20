#include "stack.hpp"
#ifndef STACK_CPP
#define STACK_CPP

template <typename T>
stack<T>::stack() : count_(0), array_size_(1), array_(new T[array_size_])
{}
template <typename T>
size_t stack<T> :: count() const
{
	return count_;
}

template <typename T>
stack<T>::~stack()
{
delete[] array_;
}

template <typename T> 
void stack <T> :: push(const T& b)
{
if(count_==array_size_)
	{
	array_size_*=2;
	T*l=copy_new(array_,count_,array_size_);
	delete[] array_;
	array_=l;
	l=nullptr;
		
	}
	
	array_[count_]=b;
	count_++;
}
template <typename T>
stack<T>::stack(const stack&c) : array_size_(c.array_size_),count_(c.count_), array_(copy_new(c.array_, c.count_, c.array_size_ )) 
{};
/*template<typename T>
T*stack<T>::copy_new(const T*arr,size_t count,size_t array_size)
{T*l=new T[array_size];
std::copy(arr,arr+count,l);
return;}*/

template <typename T>
stack<T>& stack<T>::operator=(const stack &b) 
{
	array_size_ = b.array_size_;
	count_ = b.count_;
	array_ = new T[array_size_];
	if (this != &b)
	{
		for (size_t i = 0; i < count_; i++)
			array_[i] = b.array_[i];
	}

	return *this;
}
template <typename T>
T stack<T>::pop()
{
	if (!count_)
	{
		throw std::logic_error("Stack is empty!");
	}
  --count_;
}

template<typename T>

bool stack<T>::operator==(stack const & _s)
{
	if ((_s.count_ != count_) || (_s.array_size_ != array_size_)) {
		return false;
	}
	else {
		for (size_t i = 0; i < count_; i++) {
			if (_s.array_[i] != array_[i]) {
				return false;
			}
		}
	}
	return true;
}
#endif
