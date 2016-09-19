#ifndef STACK_HPP
#define STACK_HPP
#include <cstdlib>
#include <iostream>
#include <memory>
using namespace std;

template <typename T>
class stack
{
public:
	stack();
	size_t count() const;
	void push(T const &);
	T pop();
	~stack();
	T top();
	stack(const stack &b);
	stack & operator=(const stack &b);
	bool operator==(stack const & _s);
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};
template<typename T>
T*copy_new(const T*arr,size_t count,size_t array_size)
{T*l=new T[array_size];
std::copy(arr,arr+count,l);
return;}
#include "stack.cpp"
#endif
