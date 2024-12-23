#include "heap.h"
#include <gtest.h>
#include <random>

TEST(Heap, CreateHeap) {
	ASSERT_NO_THROW(heap<int> h);
}

TEST(Heap, CanPushInHeap) {
	heap<int> h;
	ASSERT_NO_THROW(h.push(1));
}

TEST(Heap, ThrowWhenCreateHeapWithNegativeSize) {
	ASSERT_ANY_THROW(heap<int> h(2, -1));
}

TEST(Heap, ThrowWhenCreateHeapWithNegativeWays) {
	ASSERT_ANY_THROW(heap<int> h(-1));
}

TEST(Heap, CanPushInHeapInCycle) {
	heap<int> h;
	for(int i = 0;i < 100;i++)
		ASSERT_NO_THROW(h.push(i));
}

TEST(Heap, CanPushInHeapDifferentPriority) {
	heap<int> h;
	h.push(7);
	h.push(4);
	h.push(5);
	h.push(2);
	EXPECT_EQ(2,h.top());
}

TEST(Heap, NoThrowWhenPop) {
	heap<int> h;
	h.push(7);
	h.push(4);
	h.push(5);
	h.push(2);
	for (int i = 0; i < 4; i++) {
		ASSERT_NO_THROW(h.pop());
	}
}

TEST(Heap, CanPushAndPopInHeapDifferentPriority) {
	heap<int> h;
	h.push(7);
	h.push(4);
	h.push(5);
	h.push(2);
	EXPECT_EQ(2,h.top());
	h.pop();
	EXPECT_EQ(4,h.top());
	h.pop();
	EXPECT_EQ(5,h.top());
	h.pop();
	EXPECT_EQ(7,h.top());
}

TEST(Heap, CanDecrasePriority) {
	heap<int> h;
	h.push(7);
	h.push(4);
	h.push(5);
	h.push(2);
	h.push(6);
	h.DecrasePriority(3, 1);
	EXPECT_EQ(1,h.top());
}

TEST(Heap, CanDecrasePriorityInTernaryHeap) {
	heap<int> h(3);
	h.push(7);
	h.push(4);
	h.push(5);
	h.push(2);
	h.push(6);
	h.DecrasePriority(3, 1);
	EXPECT_EQ(1,h.top());
}

TEST(Heap, CanDecrasePriorityInOneWayHeap) {
	heap<int> h(1);
	h.push(7);
	h.push(4);
	h.push(5);
	h.push(2);
	h.push(6);
	h.DecrasePriority(3, 1);
	EXPECT_EQ(1,h.top());
}

TEST(Heap, StressTest) {
	heap<int> h;
	std::vector<int> res;
	int i = 1;
	for (; i < 30; i++)
		h.push(i);

	for (int j = 0; j < 2000; j++) {
		int r = rand()%100;
		if (r < 70) {
			h.push(i);
			i++;
		}
		else {
			res.push_back(h.top());
			h.pop();
		}
	}

	for (int i = 1; i < res.size(); i++)
		EXPECT_LE(res[i - 1], res[i]);
}

TEST(Heap, StressTestForOneWayHeap) {
	heap<int> h(1);
	std::vector<int> res;
	int i = 1;
	for (; i < 30; i++)
		h.push(i);

	for (int j = 0; j < 2000; j++) {
		int r = rand()%100;
		if (r < 70) {
			h.push(i);
			i++;
		}
		else {
			res.push_back(h.top());
			h.pop();
		}
	}

	for (int i = 1; i < res.size(); i++)
		EXPECT_LE(res[i - 1], res[i]);
}

TEST(Heap, StressTestForFiveWayHeap) {
	heap<int> h(5);
	std::vector<int> res;
	int i = 1;
	for (; i < 30; i++)
		h.push(i);

	for (int j = 0; j < 2000; j++) {
		int r = rand()%100;
		if (r < 70) {
			h.push(i);
			i++;
		}
		else {
			res.push_back(h.top());
			h.pop();
		}
	}

	for (int i = 1; i < res.size(); i++)
		EXPECT_LE(res[i - 1], res[i]);
}

TEST(Heap, CanMakeHeap) {
	std::vector<int> a;
	a.push_back(4);
	a.push_back(2);
	a.push_back(7);
	a.push_back(5);
	a.push_back(3);
	ASSERT_NO_THROW(MakeHeap(a));
}

TEST(Heap, CanMakeCorrectlyHeap) {
	std::vector<int> a;
	a.push_back(4);
	a.push_back(2);
	a.push_back(7);
	a.push_back(6);
	a.push_back(5);
	a.push_back(3);
	heap<int> h = MakeHeap(a);
	for (int i = 0; i < 6; i++) {
		a[i] = h.top();
		h.pop();
	}
	for (int i = 1; i < a.size(); i++)
		EXPECT_LE(a[i - 1], a[i]);
}
