#include "stack.hpp"
using namespace std;

template <typename T>
stack<T>::stack() : array_(nullptr), array_size_(0)
{}
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
	{array_size_*=2;
	T*l=copy_new(array_,count_,array_size_);
	delete[] array_;
	array_=l;
	l=nullptr;}
	array_[count_]=b;
	count_++;
}
template<typename T>
T*stack<T>::copy_new(const T*arr,size_t count,size_t array_size)
{T*l=new T[array_size];
std::copy(arr,arr+count,l);
return;}

template<typename T>
stack<T>::top() T& {
	if (count_ == 0) {
		throw std::range_error("stack is empty");
	}
	return array_[count_ - 1];
}

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
stack<T>::pop() -> T
{
	if(!count_)
{   
 throw "\nSTACK IS EMPTY!";
}

else 
{
return array_[count_--];
}
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
