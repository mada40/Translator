#ifndef __TDynamicQUEUE_H__
#define __TDynamicQUEUE_H__

#include<algorithm>
#include<stdexcept>


template<typename T>
class TDynamicQueue
{

	//комментарий
protected:
	int sz;
	int memSize;
	T* pMem;
	T* head, *tail;

public:
	static const int COEFF = 2;
	TDynamicQueue()
	{
		sz = 0;
		memSize = 0;
		pMem = nullptr;
		head = pMem;
		tail = pMem;
	}

	TDynamicQueue(const TDynamicQueue& q)
	{
		sz = q.sz;
		memSize = q.memSize;

		pMem = new T[memSize];
		head = pMem;
		tail = pMem + sz;
		std::copy(q.pMem, q.pMem + sz, pMem);
	}
	
	~TDynamicQueue()
	{
		if (pMem) delete[] pMem;
	}

	friend void swap(TDynamicQueue& lhs, TDynamicQueue& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
		std::swap(lhs.head, rhs.head);
		std::swap(lhs.tail, rhs.tail);
	}
	TDynamicQueue& operator=(const TDynamicQueue& v)
	{
		if (this == &v)
			return *this;

		TDynamicQueue tmp(v);
		swap(*this, tmp);
		return *this;
	}

	int size() const noexcept { return sz; }
	int capacity() const noexcept{ return memSize; }
	bool empty() const noexcept { return sz == 0; }

	
	///// сравнение
	bool operator==(const TDynamicQueue& v) const noexcept
	{
		if (sz != v.sz)
			return false;

		for (int i = 0; i < sz; i++)
		{
			if (pMem[i] != v.pMem[i])
				return false;
		}

		return true;
	}
	bool operator!=(const TDynamicQueue& v) const noexcept
	{
		return !(*this == v);
	}

	T front() const
	{
		if (sz == 0)
			throw std::out_of_range("queue is empty");

		return *head;
	}
	void pop() 
	{ 
		if (sz == 0)
			throw std::out_of_range("queue is empty");

		head = pMem + (head - pMem + 1) % memSize;
		sz--; 
	}

	void push(const T& el)
	{

		if (tail == head)
		{
			int newSize = (memSize + 1) * COEFF;
			T* tmp = new T[newSize];
			memSize = newSize;
			for (int i = 0; i < sz; i++)
			{
				tmp[i] = *(pMem + (head - pMem + i) % sz);
			}
			if(pMem) delete[] pMem;
			pMem = tmp;
			head = pMem;
			tail = pMem + sz;
		}

		*tail = el;
		tail = pMem + (tail - pMem + 1) % memSize;
		sz++;
	}




};


#endif
