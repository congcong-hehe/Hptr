#include "config.h"

#if GPU_TEST

#include "base.h"
#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>

__global__ void kernel(void)
{
	Hptr<A> hptr1(new A(1));
	hptr1->print();	// 测试->
	A r = *hptr1;	// 测试*
	r.print();

	// 测试=
	Hptr<A> hptr2(new A(2));
	hptr2 = hptr1;

	// 构建一个链表来测试
	Hptr<Node> head(new Node(1));
	head->next_ = Hptr<Node>(new Node(2));
	head->next_->next_ = Hptr<Node>(new Node(3));
}

int main()
{
	int* d_a;
	// 必须添加， 不添加kernel不输出
	cudaMalloc((void**)&d_a, sizeof(int));

	cudaError_t err;
	kernel << <1, 1 >> > ();//(d_a, d_b, d_c);
	err = cudaGetLastError();
	if (err != cudaSuccess)
	{
		fprintf(stderr, "Failed to launch kernel (error code %s)!\n", cudaGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	cudaFree(d_a);
	return 0;
}

#endif GPU_TEST
