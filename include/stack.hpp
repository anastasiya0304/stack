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
	stack(size_t size = 0);
	size_t count() const;
	void push(T const &elem);
	size_t pop();
	const T& top();
	~stack();
	stack(const stack &b);
	stack & operator=(const stack &b);
	bool operator==(stack const & _s);
	bool empty() const noexcept;
};

#include "stack.cpp"
#endif
