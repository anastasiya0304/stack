#include "stack.hpp"
#ifndef STACK_CPP
#define STACK_CPP

template <typename T>
stack<T>::stack() : count_(0), array_size_(1), array_(new T[array_size_])	/*strong*/
{}
template <typename T>
size_t stack<T> :: count() const	/*noexcept*/
{
	return count_;
}

template <typename T>
stack<T>::~stack()	/*noexcept*/
{
delete[] array_;
}

template <typename T> 
void stack <T> :: push(const T& b)	/*strong*/
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
stack<T>::stack(const stack&c) : array_size_(c.array_size_),count_(c.count_), array_(copy_new(c.array_, c.count_, c.array_size_ )) 	/*strong*/
{};
/*template<typename T>
T*stack<T>::copy_new(const T*arr,size_t count,size_t array_size)
{T*l=new T[array_size];
std::copy(arr,arr+count,l);
return;}*/
template <typename T>
stack<T>& stack<T>::operator=(const stack &b)	/*strong*/
{
	
	if (this != &b)
		{
			delete[] array_;
			array_size_ = b.array_size_;
			count_ = b.count_;
			array_ = copy_new(b.array_, count_, array_size_);
		}

	return *this;
}

template <typename T>
T stack<T>::pop()	/*strong*/
{
	if (!count_)
	{
		throw std::logic_error("Stack is empty!");
	}
 return array_[--count_];
}

template<typename T>
const T& stack<T>::top()	/*strong*/
{
	if (count_ == 0)
	{
		throw std::logic_error("Stack is empty!");
	}
	return array_[count_-1];
}

template<typename T>
bool stack<T>::operator==(stack const & _s)	/*noexcept*/
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
template<typename T>
bool stack<T>::empty() const noexcept
{
	return (count_==0);
}
void stack<T>::swap(stack &v)
{
	std::swap(v.array_size_,array_size_);
	std::swap(v.count_,count_);
	std::swap(v.array_,array_);
}
#endif
