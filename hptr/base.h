#pragma once

#include <stdio.h>
#include "hptr.h"
#include <cuda_runtime.h>

using namespace std;

class A
{
private:
	int num_;
public:
	__device__ __host__
	A(int num) : num_(num)
	{
		printf("construct A %d\n", num_);
	}
	__device__ __host__
	~A()
	{
		printf("destruct A %d\n", num_);
	}
	__device__ __host__
	void print()
	{
		printf("%d\n", num_);
	}
};

struct Node
{
	int num_;
	Hptr<Node> next_;

	__device__ __host__
	Node(int num) : num_(num)
	{
		printf("construct node %d\n", num_);
	}
	__device__ __host__
	~Node()
	{
		printf("destruct node %d\n", num_);
	}
};