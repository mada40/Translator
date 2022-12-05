#include "tstack.h"

#include <gtest.h>

TEST(TDynamicStack, can_create)
{
	ASSERT_NO_THROW(TDynamicStack<int> q);
}

TEST(TDynamicStack, can_push)
{
	TDynamicStack<int> q;
	ASSERT_NO_THROW(q.push(5));
}

TEST(TDynamicStack, cant_pop_empty_stack)
{
	TDynamicStack<int> q;
	ASSERT_ANY_THROW(q.pop());
}

TEST(TDynamicStack, can_pop_stack)
{
	TDynamicStack<int> q;
	q.push(5);
	ASSERT_NO_THROW(q.pop());
}

TEST(TDynamicStack, top_is_equal_to_last_in)
{
	TDynamicStack<int> q;
	q.push(17);
	q.push(5);
	int tmp = q.top();
	EXPECT_EQ(tmp, 5);
}

TEST(TDynamicStack, can_check_is_empty)
{
	TDynamicStack<int> q;
	EXPECT_EQ(q.empty(), true);
}

TEST(TDynamicStack, can_get_size)
{
	TDynamicStack<int> q;
	for (int i = 0; i < 100; i++)
		q.push(2 * i + 100);
	EXPECT_EQ(q.size(), 100);
}

TEST(TDynamicStack, can_create_copied_queue)
{
	TDynamicStack<int> q;
	q.push(580);
	q.push(550);
	q.pop();
	q.push(32);
	ASSERT_NO_THROW(TDynamicStack<int> q1(q));
}

TEST(TDynamicStack, copied_stack_is_equal_to_source_one)
{
	TDynamicStack<int> q;
	q.push(580);
	q.push(550);
	q.pop();
	q.push(32);
	TDynamicStack<int> q1(q);
	EXPECT_EQ(q1, q);
}

TEST(TDynamicStack, copied_stack_has_its_own_memory)
{
	TDynamicStack<int> q1;
	q1.push(5);
	TDynamicStack<int> q2(q1);
	q2.pop(); q2.push(58);
	EXPECT_NE(q1.top(), q2.top());
}

TEST(TDynamicStack, can_assign_queue_to_itself)
{
	TDynamicStack<int> q;
	q.push(580);
	q.pop();
	q.push(32);
	ASSERT_NO_THROW(q = q);
}

TEST(TDynamicStack, pop_reduces_size)
{
	TDynamicStack<int> q;
	q.push(580);
	q.push(585);
	q.push(589);
	q.pop();
	EXPECT_EQ(q.size(), 2);
}

TEST(TDynamicStack, loop_1push1pop_after_100pop)
{
	TDynamicStack<int> q;
	const int N = 100;
	for (int i = 0; i < N; i++)
	{
		q.push(i - 100);
	}
	for (int i = 0; i < 1e7; i++)
	{
		q.push(i * 2 + 1);
		q.pop();
	}
	EXPECT_LE(q.capacity(), N * q.COEFF);
}


