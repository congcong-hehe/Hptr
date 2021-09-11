#include "config.h"

#if CPU_TEST

#include <stdio.h>
#include "base.h"

int main()
{
	Hptr<A> hptr1(new A(1));
	hptr1->print();	// 测试->
	A a = *hptr1;	// 测试*
	a.print();

	// 测试=
	Hptr<A> hptr2(new A(2));
	hptr2 = hptr1;

	// 构建一个链表来测试
	Hptr<Node> head(new Node(1));
	head->next_ = Hptr<Node>(new Node(2));
	head->next_->next_ = Hptr<Node>(new Node(3));
}

#endif