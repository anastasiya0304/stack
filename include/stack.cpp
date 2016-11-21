#include "stack.hpp"
#include <stdexcept>
#ifndef STACK_CPP
#define STACK_CPP

bitset::bitset(size_t size) : ptr_(std::make_unique<bool[]>(size)),size_(size),counter_(0) 
{}

auto bitset::set(size_t index)->void //инициализация всех битов единицами или изменение значения тдельного бита
{ 
	if (index >= 0 && index < size_) 
	{ 
		ptr_[index] = true; ++counter_; 
	}
	else throw("problem with index");
}

auto bitset::reset(size_t index) throw(std::out_of_range) -> void //обнуление указанных битов
{
	if (index >= size_)
	{
		throw (std::out_of_range("problem with index"));
	}
	ptr_[index] = false;
	--counter_;
}

auto bitset::test(size_t index) const throw(std::out_of_range) -> bool //возвращает значение указанного бита
{
	if (index >= size_) 
	{
		throw (std::out_of_range("problem with index"));
	}
	return ptr_[index];
}

auto bitset::size() const -> size_t 
{
	return size_;
}
auto bitset::counter() const -> size_t 
{
	return counter_;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
allocator<T>::allocator(size_t size) : ptr_((T*)operator new(size*sizeof(T))), size_(size), map_(std::make_unique<bitset>(size))//конструктор с параметром
{}

template<typename T>
allocator<T>::allocator(allocator const& other) : allocator<T>(other.size_) //конструктор копирования
{
	for (size_t i=0; i < size_; i++) 
	{ 
		if (map_->test(i)) 
		{ 
			destroy(prt_ +i); 
		}
	construct(ptr_ + i, other.ptr_[i]); 
}

template<typename T>
allocator<T>::~allocator()
{
	if (this->count() > 0) 
	{
		destroy(ptr_, ptr_ + size_());
	}
	operator delete(ptr_);
}

template<typename T> //увеличение памяти
auto allocator<T>::resize()->void
{
	allocator<T> alloc(size_ * 2 + (size_ == 0));
	for (size_t i = 0; i < size_; ++i) if(map_->test(i)) alloc.construct(alloc.get() + i, ptr_[i]);
	this->swap(alloc);
}

template<typename T>
auto allocator<T>::construct(T * ptr, T const & value)->void
{
	if (ptr >= ptr_&&ptr < ptr_ + size_)
	{
		new(ptr)T(value);
		map_->set(ptr - ptr_);
	}
	else { throw("error"); }
}

template<typename T>
auto allocator<T>::destroy(T * ptr)->void
{ 
if (ptr < ptr_ || ptr >= ptr_ + size_)
{
		throw std::out_of_range("Error");
} else
{
    if (map_->test(ptr-ptr_) == false)
{
	ptr->~T();
	map_->reset(ptr - ptr_);

}}

template<typename T> //получаем ptr_
auto allocator<T>::get()-> T* { return ptr_; }

template<typename T>
auto allocator<T>::get() const -> T const * { return ptr_; }

template<typename T>
auto allocator<T>::count() const -> size_t{ return map_->counter(); }

template<typename T> //заполненность 
auto allocator<T>::full() const -> bool { return (map_->counter() == size_); }

template<typename T>
auto allocator<T>::empty() const -> bool { return (map_->counter() == 0); }

template<typename T>
auto allocator<T>::destroy(T * first, T * last)->void
{
	if(first>=ptr_&&last<=ptr_+this->count())
		for (; first != last; ++first) 
		{
			destroy(&*first);
		}
}

template<typename T>
auto allocator<T>::swap(allocator & other)->void{
	std::swap(ptr_, other.ptr_);
	std::swap(size_, other.size_);
	std::swap(map_, other.map_);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
stack<T>::stack(size_t size) : allocator_(size)
{}

template<typename T>
auto stack<T>::operator =(stack const & other)-> stack &
{ 
	if (this != &other) 
	{
		(allocator<T>(other.allocator_)).swap(allocator_);
	}
	return *this;
}

template<typename T>
auto stack<T>::empty() const ->bool
{ 
return allocator_.empty(); 
}

template<typename T>
auto stack<T>::count()const->size_t
{
return allocator_.count(); 
}

template<typename T>
auto stack<T>::push(T const & value)->void
{
	if (allocator_.full()) allocator_.resize(); 
	allocator_.construct(allocator_.get() + this->count(), value);
}

template<typename T>
auto stack<T>::pop()->void 
{
	if (allocator_.count() == 0) throw std::logic_error("Empty");
	allocator_.destroy(allocator_.get() + (this->count() - 1));
}

template<typename T>
auto stack<T>::top()->T& 
{
	if (this->count() > 0) return(*(allocator_.get() + this->count() - 1));
	else this->throw_is_empty();
}

template<typename T>
auto stack<T>::top()const->T const & 
{
	if (this->count() > 0) return(*(allocator_.get() + this->count() - 1));
	else this->throw_is_empty();
}

template<typename T>
auto stack<T>::throw_is_empty()const->void
{
throw("Stack is empty");
}




#endif
