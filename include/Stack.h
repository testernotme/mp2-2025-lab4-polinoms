#include <string>
#pragma once
#include <stdexcept>


template<typename T>
class TStack {
private:
	size_t size;
	size_t capacity;
	T* pmem;

	void memrlc() {
		capacity = capacity + capacity + 1;
		T* tpmem = new T[capacity];
		std::copy(pmem, pmem + size, tpmem);
		delete[] pmem;
		pmem = tpmem;
	}
public:
	TStack(size_t n) : size(0), capacity(n), pmem(new T[n]) {};
	TStack() {
		size = 0;
		capacity = 0;
		pmem = nullptr;
	};
	TStack(int n) {
		size = 0;
		capacity = n;
		pmem = new T[n];
	}
	TStack(const TStack& heap) {
		size = heap.size;
		capacity = heap.capacity;
		pmem = new T[capacity];
		std::copy(heap.pmem, heap.pmem + size, pmem);
	};
	TStack& operator=(TStack&& other) noexcept {
		if (this != &other) {
			delete[] pmem;
			pmem = other.pmem;
			size = other.size;
			capacity = other.capacity;
			other.pmem = nullptr;
			other.size = 0;
			other.capacity = 0;
		}
		return *this;
	}
	TStack(TStack&& other) noexcept
		: size(other.size), capacity(other.capacity), pmem(other.pmem) {
		other.pmem = nullptr;
		other.size = 0;
		other.capacity = 0;
	}
	TStack& operator=(const TStack& other) {
		if (this != &other) {
			delete[] pmem;
			size = other.size;
			capacity = other.capacity;
			pmem = new T[capacity];
			std::copy(other.pmem, other.pmem + size, pmem);
		}
		return *this;
	}

	~TStack() {
		delete[] pmem;
	};
	bool is_full() {
		return (size == capacity);
	}
	bool is_empty() {
		return size == 0;
	}
	size_t StSize() { return size; }
	void clr() { size = 0; capacity = 0; delete[]pmem; pmem = nullptr; }
	void push(const T& t) {
		if (is_full()) {
			memrlc();
		}
		pmem[size] = t;
		++size;
	}
	T pop() {
		if (is_empty())
		{
			throw std::out_of_range("13");
		}
		--size;
		return pmem[size];

	}
	T& see() {
		if (is_empty())
		{
			throw std::out_of_range("12");
		}
		return pmem[size - 1];
	}

	void reverse() {
		for (size_t i = 0; i < size / 2; i++)
		{
			T t = pmem[i];
			pmem[i] = pmem[size - i - 1];
			pmem[size - i - 1] = t;

		}
	}
};