#pragma once

#include <cuda_runtime.h>

// 自己写的共享指针，主要目的是为了给cpu和gpu同时使用
// 不考虑继承和指针之间的转换
template<class T>
class Hptr
{
private:
	T* ptr_;
	int* count_;

public:
	__device__ __host__
	Hptr(T* ptr = nullptr) : ptr_(ptr), count_(new int(1)) {}
	
	// 拷贝构造函数
	__device__ __host__
	Hptr(const Hptr<T>& other) : ptr_(other.ptr_), count_(other.count_)
	{
		(*count_)++;
	}

	__device__ __host__
	~Hptr()
	{
		(*count_)--;
		if (0 == *count_)
		{
			delete ptr_;
			ptr_ = nullptr;
			delete count_;
			count_ = nullptr;
		}
	}

	__device__ __host__
	T& operator*()
	{
		return *ptr_;
	}

	__device__ __host__
	T* operator -> ()
	{
		return ptr_;
	}

	__device__ __host__
	Hptr<T>& operator = (const Hptr<T>& other)
	{
		if (this != &other)
		{
			if (--(*count_) == 0)
			{
				delete count_;
				count_ = nullptr;
				delete ptr_;
				ptr_ = nullptr;
			}
			ptr_ = other.ptr_;
			count_ = other.count_;
			(*count_)++;
		}
		return *this;
	}
	
};
