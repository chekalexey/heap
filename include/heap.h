#ifndef __HEAP__
#define __HEAP__

#include <vector>

template <class T>
class heap {
	T* data = nullptr;
	int size = 0, capacity = 1;
	int d = 2;
public:
	heap(int k = 2, int s = 1) {
		if (s < 0) throw "size should be non negative";
		data = new T[s];
		for (int i = 0; i < s; i++)
			data[i] = -1;
		capacity = s;
		if (k <= 0) throw "invalid count";
		d = k;
	}

	heap(std::vector<int> a) {
		data = new int[a.size()];
		size = a.size();
		capacity = a.size();
		for (int i = 0; i < size; i++)
			data[i] = a[i];
		d = 2;
	}

	int MinChild(int i) {
		int mxpr = 100000000, k = d*i+1;
		if (k >= size)
			return -1;
		for (int j = d * i + 1; j <= d * i + d && j < size; j++)
			if (mxpr > data[j]) {
				mxpr = data[j];
				k = j;
			}
		return k;
	}

	int Parent(int i) {
		if (d == 1) return i - 1;
		return i / d;
	}

	void diving(int i) {
		int j1 = i;
		int j2 = MinChild(i);
		while (j2 != -1 && data[j1] > data[j2]) {
			std::swap(data[j1], data[j2]);
			j1 = j2;
			j2 = MinChild(j1);
		}
	}

	T top() {
		return data[0];
	}

	void Repacking() {
		T* tmp = new T[capacity * 2];
		for (int i = 0; i < capacity; i++)
			tmp[i] = data[i];
		
		delete[] data;
		data = tmp;
		capacity *= 2;
	}

	void emersion(int i) {
		int j1 = i;
		int j2 = Parent(i);
		
		while (data[j1] < data[j2]) {
			std::swap(data[j1], data[j2]);
			j1 = j2;
			j2 = Parent(j1);
		}
	}

	void push(int p) {
		if (capacity == size)
			Repacking();
		data[size] = p;
		size++;
		emersion(size - 1);
	}

	void pop() {
		std::swap(data[0], data[size - 1]);
		size--;
		data[size] = -1;
		diving(0);
	}

	void DecrasePriority(int i, T NewP) {
		data[i] = NewP;
		emersion(i);
	}

	int getsize() {
		return size;
	}
	
	void print() {
		for (int i = 0; i < size; i++)
			std::cout << data[i] << ' ';
		std::cout << std::endl;
	}
};

static heap<int> MakeHeap(std::vector<int> v) {
	int CurSize = 1;
	heap<int> h(v);
	while (CurSize != v.size()) {
		CurSize++;
		h.diving(v.size() - CurSize);
	}
	return h;
}

#endif
