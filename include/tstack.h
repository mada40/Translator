#ifndef __TDynamicSTACK_H__
#define __TDynamicSTACK_H__

#include<algorithm>
#include<stdexcept>


template<typename T>
class TDynamicStack
{

	//комментарий
protected:
	int sz;
	int memSize;
	T* pMem;
	T*tail;

public:
	static const int COEFF = 2;
	TDynamicStack()
	{
		sz = 0;
		memSize = 0;
		pMem = nullptr;
		tail = pMem;
	}

	TDynamicStack(const TDynamicStack& q)
	{
		sz = q.sz;
		memSize = q.memSize;

		pMem = new T[memSize];
		tail = pMem + sz;
		std::copy(q.pMem, q.pMem + sz, pMem);
	}
	
	~TDynamicStack()
	{
		if (pMem) delete[] pMem;
	}

	friend void swap(TDynamicStack& lhs, TDynamicStack& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}
	TDynamicStack& operator=(const TDynamicStack& v)
	{
		if (this == &v)
			return *this;

		TDynamicStack tmp(v);
		swap(*this, tmp);
		return *this;
	}

	int size() const noexcept { return sz; }
	int capacity() const noexcept{ return memSize; }
	bool empty() const noexcept { return sz == 0; }

	
	///// сравнение
	bool operator==(const TDynamicStack& v) const noexcept
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
	bool operator!=(const TDynamicStack& v) const noexcept
	{
		return !(*this == v);
	}

	T top() const
	{
		if (sz == 0)
			throw std::out_of_range("stack is empty");

		return *(tail - 1);
	}
	void pop() 
	{ 
		if (sz == 0)
			throw std::out_of_range("stack is empty");

		tail--;
		sz--; 
	}

	void push(const T& el)
	{

		if (sz == memSize)
		{
			int newSize = (memSize + 1) * COEFF;
			T* tmp = new T[newSize];
			memSize = newSize;
			std::copy(pMem, pMem + sz, tmp);
			if(pMem) delete[] pMem;
			pMem = tmp;
			tail = pMem + sz;
		}

		*tail = el;
		tail++;
		sz++;
	}




};


#endif
