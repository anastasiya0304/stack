#include "iostream"
using namespace std;
template <typename T>
class stack
{
public:
	stack();
	size_t count() const;
	void push(T const &);
	T pop();
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};
template <template T>
stack<T>::stack() : array_(nullptr), array_size_(0)
{}
size_t stack<T>::count() const
{
	return count_;
}

template <typename T>
void stack <T> :: push(const T& b)
{
	
		if (!count_)
		{
			array_ = new T[1];
			array_[count_] = b;
			array_size_ = 1;
			count_++;
		}
		else if (count_ == array_size_)
		{
			array_[count_] = b;
			count_++;
		}
		else if (count_ < array_size_)
		{
			T * s_ = new T[array_size_];
			for (i = 0; i < array_size_; i++)
				s_[i] = array_[i];
			delete[] array_;
			array_size_ = array_size_ * 2;
			array_ = new T[array_size_];
			for (i = 0; i < count_; i++)
				array_[i] = s_[i];
			delete[] s_;
			array_[count_] = b;
			count_++;
		}


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

