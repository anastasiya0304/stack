#include <iostream>
#include <new>  
#include <stdexcept>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>

class bitset
{
public:
explicit
bitset( size_t size ) /*strong*/;

bitset( bitset const & other ) = delete;
auto operator =( bitset const & other ) -> bitset & = delete;

bitset( bitset && other ) = delete;
auto operator =( bitset && other ) -> bitset & = delete;

auto set( size_t index ) /*strong*/ -> void;
auto reset( size_t index ) throw(std::out_of_range)/*strong*/ -> void;
auto test( size_t index ) const throw(std::out_of_range)/*strong*/ -> bool;

auto size() const /*noexcept*/ -> size_t;
auto counter() const /*noexcept*/ -> size_t;

private:
std::unique_ptr<bool[]> ptr_;
size_t size_;
size_t counter_;
};
bitset::bitset(size_t size) : ptr_(std::make_unique<bool[]>(size)),size_(size),counter_(0) 
{}

auto bitset::set(size_t index)->void //инициализация всех битов единицами или изменение значения отдельного бита
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

template <typename T>
class allocator
{
public:
explicit
allocator( std::size_t size = 0 ) /*strong*/;
allocator( allocator const & other ) /*strong*/;
auto operator =( allocator const & other ) -> allocator & = delete;
~allocator();

auto resize() /*strong*/ -> void;

auto construct(T * ptr, T const & value ) /*strong*/ -> void;
auto destroy( T * ptr ) /*noexcept*/ -> void;

auto get() /*noexcept*/ -> T *;
auto get() const /*noexcept*/ -> T const *;

auto count() const /*noexcept*/ -> size_t;
auto full() const /*noexcept*/ -> bool;
auto empty() const /*noexcept*/ -> bool;
private:
auto destroy( T * first, T * last ) /*noexcept*/ -> void;
auto swap( allocator & other ) /*noexcept*/ -> void;

private:
  
T * ptr_;
size_t size_;
std::unique_ptr<bitset> map_;
};
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
			destroy(ptr_, ptr_ +i); 
		}
	construct(ptr_ + i, other.ptr_[i]); 
}}

template<typename T>
allocator<T>::~allocator()
{
	if (this->count() > 0) 
	{
		destroy(ptr_, ptr_ + size_);
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
template <typename T>
auto allocator<T>::destroy(T * ptr)->void
{ 
if (ptr < ptr_ || ptr >= ptr_ + size_ || map_->test(ptr-ptr_) == false)
{
		throw std::out_of_range("Error");
}
	ptr->~T();
	map_->reset(ptr - ptr_);

}

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

template <typename T>
class stack
{
public:
explicit
stack( size_t size = 0 );
stack (stack const & other);
auto operator =( stack const & other ) /*strong*/ -> stack &;

auto empty() const /*noexcept*/ -> bool;
auto count() const /*noexcept*/ -> size_t;

auto push( T const & value ) /*strong*/ -> void;
auto pop() /*strong*/ -> void;
auto top() /*strong*/ -> T &;
auto top() const /*strong*/ -> T const &;

private:
allocator<T> allocator_;
mutable std::mutex mutex_;

auto throw_is_empty() const -> void;
};

template<typename T>
stack<T>::stack(size_t size) : allocator_(size),mutex_() {};


template <typename T>		
 stack<T>::stack(stack const & other) : allocator_(0), mutex_() 
 {		
 	std::lock_guard<std::mutex> lock(other.mutex_);		
 	allocator<T>(other.allocator_).swap(allocator_);		
}

template <typename T>
auto stack<T>::operator=(const stack &other)->stack&  
{
	if (this != &other) 
	{
		std::lock(mutex_, other.mutex_);		
 		std::lock_guard<std::mutex> lock_a(mutex_, std::adopt_lock);		
 		std::lock_guard<std::mutex> lock_b(other.mutex_, std::adopt_lock);
		stack(other).allocator_.swap(allocator_);
	}
	return *this;
}

template<typename T>
auto stack<T>::empty() const->bool 
{
	std::lock_guard<std::mutex> lock(mutex_);
	return (allocator_.count() == 0);
}

template<typename T>
auto stack<T>::count()const->size_t
{
return allocator_.count(); 
}

template<typename T>
auto stack<T>::push(T const & value)->void
{	
	std::lock_guard<std::mutex> lock(mutex_);
	if (allocator_.full()) allocator_.resize(); 
	allocator_.construct(allocator_.get() + this->count(), value);
}

template <typename T>
auto stack<T>::pop()->std::shared_ptr<T> 
{
	std::lock_guard<std::mutex> lock(mutex_);
			if(allocate.empty()) throw std::logic_error("Empty!"); 
				std::shared_ptr<T> const res(std::make_shared<T>(std::move(allocate.get()[allocate.count()-1])));
			allocate.destroy(allocate.get() + allocate.count() - 1);
			return result;
}



