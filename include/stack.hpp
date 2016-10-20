#ifndef STACK_HPP
#define STACK_HPP
#include <cstdlib>
#include <iostream>
#include <memory>

template <typename T>
class allocator {
protected:
	allocator(size_t size = 0); 
	~allocator(); 
	auto swap(allocator & other) -> void; 

	allocator(allocator const &) = delete;
	auto operator=(allocator const &)->allocator & = delete;

	T * ptr_;
	size_t size_;
	size_t count_;
};

template <typename T>
class stack : private allocator<T>
{
public:
	stack();
	size_t count() const;
	void push(T const &elem);
	void pop();
	const T& top();
	~stack();
	stack(const stack &b);
	stack & operator=(const stack &b);
	bool operator==(stack const & _s);
	bool empty() const noexcept;
	void swap(stack &v);
private:
	size_t array_size_;
	size_t count_;
	T * array_;
};
template<typename T>
T*copy_new(const T*arr,size_t count,size_t array_size)
{

	T*l= new T[array_size];
	try
	{
		std::copy(arr,arr+count,l);
	}
	catch(...)
	{
		delete[] l;
		throw;
	}
	return l;
	
}
#include "stack.cpp"
#endif
