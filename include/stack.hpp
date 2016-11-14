#ifndef STACK_HPP
#define STACK_HPP
#include <cstdlib>
#include <iostream>
#include <memory>

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

template <typename T>
class stack
{
public:
explicit
stack( size_t size = 0 );
auto operator =( stack const & other ) /*strong*/ -> stack &;

auto empty() const /*noexcept*/ -> bool;
auto count() const /*noexcept*/ -> size_t;

auto push( T const & value ) /*strong*/ -> void;
auto pop() /*strong*/ -> void;
auto top() /*strong*/ -> T &;
auto top() const /*strong*/ -> T const &;

private:
allocator<T> allocator_;

auto throw_is_empty() const -> void;
};

#include "stack.cpp"
#endif
