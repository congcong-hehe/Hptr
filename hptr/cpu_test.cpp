#include "config.h"

#if CPU_TEST

#include <stdio.h>
#include "base.h"

int main()
{
	Hptr<A> hptr1(new A(1));
	hptr1->print();	// ����->
	A a = *hptr1;	// ����*
	a.print();

	// ����=
	Hptr<A> hptr2(new A(2));
	hptr2 = hptr1;

	// ����һ������������
	Hptr<Node> head(new Node(1));
	head->next_ = Hptr<Node>(new Node(2));
	head->next_->next_ = Hptr<Node>(new Node(3));
}

#endif