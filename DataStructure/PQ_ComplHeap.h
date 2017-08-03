#pragma once
#include "Vector.h"
#include "PQ.h"

bool InHeap(int n, int i)
{
	return i > -1 && i < n;
}

int Parent(int i)
{
	return (i - 1) >> 1;
}

int LastInternal(int n)
{
	return Parent(n - 1);
}

int LChild(int i)
{
	return (i << 1) + 1;
}

int RChild(int i)
{
	return (i + 1) << 1;
}

bool ParentValid(int i)
{
	return i > 0;
}

bool LChildValid(int n, int i)
{
	return InHeap(n, LChild(i));
}

bool RChildValid(int n, int i)
{
	return InHeap(n, RChild(i));
}

template<typename T>
int Bigger(const T pq, int i, int j)
{
	return sy::lt(pq[i], pq[j]) ? j : i;
}

template<typename T>
int ProperParent(const T pq, int n, int i)
{
	if (RChildValid(n, i))
	{
		return Bigger(pq, Bigger(pq, i, LChild(i)), RChild(i));//右孩子有效，左孩子一定有效
	}
	else if(LChildValid(n, i))
	{
		return Bigger(pq, i, LChild(i));
	}
	else
	{
		return i;
	}
}


namespace sy
{
	template<typename T>
	class PQ_ComplHeap : public PQ<T>, public Vector<T>
	{
	protected:
		Rank percolateDown(Rank n, Rank i);
		Rank percolateUp(Rank i);
		void heapify(Rank n); 

	public:
		PQ_ComplHeap(){}
		PQ_ComplHeap(T *A, Rank n) { copyFrom(A, 0, n); heapify(n); }

		void insert(const T &e);
		T getMax() const;
		T delMax();

		virtual void heapSort(int lo, int hi);
	};

	template<typename T>
	inline Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i)
	{
		Rank j;
		
		while (i != (j = ProperParent(_elem, n, i)))
		{
			Swap(_elem[i], _elem[j]);
			i = j;
		}

		return i;
	}

	template<typename T>
	inline Rank PQ_ComplHeap<T>::percolateUp(Rank i)
	{
		while (ParentValid(i))
		{
			Rank j = Parent(i);
			if (sy::lt(_elem[i], _elem[j]))
			{
				break;
			}

			Swap(_elem[i], _elem[j]);
			i = j;
		}

		return i;
	}

	template<typename T>
	inline void PQ_ComplHeap<T>::heapify(Rank n)
	{
		for (int i = LastInternal(n); InHeap(n, i); --i)
		{
			percolateDown(n, i);
		}
	}

	template<typename T>
	inline void PQ_ComplHeap<T>::insert(const T & e)
	{
		Vector<T>::insert(e);
		percolateUp(_size - 1);
	}

	template<typename T>
	inline T PQ_ComplHeap<T>::getMax() const
	{
		return _elem[0];
	}

	template<typename T>
	inline T PQ_ComplHeap<T>::delMax()
	{
		const T maxElement = _elem[0];
		_elem[0] = _elem[--_size];
		percolateDown(_size, 0);
		return maxElement;
	}

	template<typename T>
	inline void PQ_ComplHeap<T>::heapSort(int lo, int hi)
	{
		PQ_ComplHeap<T> pq(_elem + lo, hi);

		while (pq.empty())
		{
			_elem[--hi] = pq.delMax();
		}
	}
}