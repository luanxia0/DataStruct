#ifndef LIST
#define LIST

#include "ListNode.h"

namespace sy
{
    template<typename T>class List
    {
    private:
        int _size;
        ListNodePosi(T) _header;
        ListNodePosi(T) _trailer;

    protected:
        void init();
        int clear();
		void swap(ListNodePosi(T) &p, ListNodePosi(T) &q);
        void copyNode(ListNodePosi(T), int);
        void merge(ListNodePosi(T) &, int , List<T> &, ListNodePosi(T)& , int);
        void mergeSort(ListNodePosi(T) &, int);
		ListNodePosi(T) selectMax(ListNodePosi(T), int) const;
        void selectionSort(ListNodePosi(T), int);
        void insertionSort(ListNodePosi(T), int);

    public:
		List() { init(); };
        List(const List<T> &L);
        List(const List<T> &L, Rank r, int n);
        List(ListNodePosi(T)& p, int n);
        ~List();

    //read-only
        Rank size() const { return _size; }

        bool empty() const { return _size <= 0; }

        T& operator[](Rank r);

        ListNodePosi(T)& first() const { return _header -> succ; }

        ListNodePosi(T)& last() const { return _trailer -> pred; }

        bool valid(ListNodePosi(T) &p) const { return p && (_header != p) && (_trailer != p); }

        int disordered() const;

        ListNodePosi(T) find(const T &e) const { return find(e, _size, _trailer); }

        ListNodePosi(T) find(const T &e, int n, ListNodePosi(T) p) const;

        ListNodePosi(T) search(const T &e) const { return search(e, _size, _trailer); }

        ListNodePosi(T) search(const T &e, int n, ListNodePosi(T) p) const;

        ListNodePosi(T) selectMax() const { return selectMax(_header->succ, _size); }

        //writable
        ListNodePosi(T) insertAsFirst(const T &e);
        ListNodePosi(T) insertAsLast(const T &e);

        ListNodePosi(T) insertBefore(ListNodePosi(T) p, const T &e);
        ListNodePosi(T) insertAfter(ListNodePosi(T) p, const T &e);

        T remove(ListNodePosi(T) p);

        void merge(List<T> L) { merge(first(), _size, L, L.first(),  L._size); }

		void sort(ListNodePosi(T) p, int n) { mergeSort(p, _size); }

        void sort() { sort(first(), _size); }

        int deduplicate();
        int uniquify();

        void reverse();

        void traverse(void(*)(T &));

        template<typename VST>void traverse(VST &);
    };


    template<typename T>void List<T>::init()
    {
        _header = new ListNode<T>();
        _trailer = new ListNode<T>();
        _header->succ = _trailer;
        _header->pred = nullptr;
        _trailer->pred = _header;
        _trailer->succ = nullptr;
        _size = 0;
    }

	template<typename T>int List<T>::clear()
	{
		int oldSize = _size;
		while (_size > 0)
		{
			remove(_header->succ);
		}
		return oldSize;
	}

	template<typename T>
	inline void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T)& q, int m)
	{
		ListNodePosi(T) head = p->pred;
		//这里限定的是处理完m
		while (0 < m)
		{
			if ((0 < n) && (p->data <= q->data))//p仍在区间内且v(p) <= v(q)
			{
				//直接后继
				//相邻且已经有序
				//需要将q插入到p的后面
				if (q == (p = p->succ))
				{
					break;
				}
				//p = p->succ;
				n--;
			}
			else //if(p->data > q->data)//v(q) < v(p)或者n<=0
			{
				insertBefore(p, L.remove((q = q->succ)->pred));
				--m;
			}
// 			else
// 			{
// 				--m;
// 			}
		}
		p = head->succ;
	}

	template<typename T>
	inline void List<T>::mergeSort(ListNodePosi(T)& p, int n)
	{
		if (n < 2)
		{
			return;
		}
		int mid = n >> 1;
		ListNodePosi(T) q = p;
		for (int i = 0; i < mid; ++i)
		{
			q = q->succ;
		}
		mergeSort(p, mid);
		mergeSort(q, n - mid);
		merge(p, mid, *this, q, n - mid);
	}

    template<typename T>
	ListNodePosi(T) List<T>::find(const T &e, int n, ListNodePosi(T) p) const
    {
        while(0 < n--)
        {
            p = p->pred;
            if(e == p->data)
            {
                return p;
            }
        }
        return nullptr;
    }

	//ordered list find
	//no-down-sort
	template<typename T>
	inline ListNodePosi(T) List<T>::search(const T & e, int n, ListNodePosi(T) p) const
	{
		//这里的>=0是因为p = p->pred是循环的第一个指令
		//如果是>0，需要从p->pred开始
		while (0 <= n--)
		{
			p = p->pred;
			if (p->data <= e)
			{
				break;
			}
		}
		return p;
	}

    template<typename T>T &List<T>::operator[](Rank r)
    {
        ListNodePosi(T) p = first();
        while(0 < r--)
        {
            p = p->succ;
        }
        return p->data;
    }

    template<typename T>ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, const T &e)
    {
        ++_size;
		return p->insertAsPred(e);
    }

	template<typename T>ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, const T &e)
	{
		++_size;
		return p->insertAsSucc(e);
	}

	template<typename T>void List<T>::copyNode(ListNodePosi(T) p , int n)
	{
		init();
		while ( n--)
		{
			insertAsLast(p->data);
			p = p->succ;
		}
	}

	template<typename T>List<T>::List(ListNodePosi(T)& p, int n)
	{
		copyNode(p, n);
	}

	template<typename T>List<T>::List(const List<T> &L, Rank r, int n)
	{
        ListNodePosi(T) first = L.first();
        while(r > 0)
        {
            first = first->succ;
            --r;
        }
		copyNode(first, n);
	}

	template<typename T>List<T>::List(const List<T> &L)
	{
		copyNode(L.first(), L._size);
	}

	template<typename T>ListNodePosi(T) List<T>::insertAsLast(const T &e)
	{
		return insertBefore(_trailer, e);
	}

	template<typename T>ListNodePosi(T) List<T>::insertAsFirst(const T &e)
	{
		return insertAfter(_header, e);
	}

	template<typename T>T List<T>::remove(ListNodePosi(T) p)
	{
		T e = p->data;
		p->pred->succ = p->succ;
		p->succ->pred = p->pred;
		delete p;
		--_size;
		return e;
	}

	template<typename T>List<T>::~List()
	{
		clear();
		delete _header;
		delete _trailer;
	}

	template<typename T>int List<T>::deduplicate()
	{
		if (2 > _size)
		{
			return 0;
		}
		int oldSize = _size;
		ListNodePosi(T) p = first()->succ;
		Rank r = 1;
		while (p != _trailer)
		{
			ListNodePosi(T) q = find(p->data, r, p);
			if (q)
			{
				remove(q);
			}
			else
			{
				++r;
			}
			p = p->succ;
		}

		return oldSize - _size;
	}

	template<typename T> void List<T>::traverse(void(*visit)(T &))
	{
		ListNodePosi(T) p = first();
		while (_trailer != p)
		{
			visit(p->data);
			p = p->succ;
		}
	}

	template<typename T> template<typename VST>void List<T>::traverse(VST &visit)
	{
		ListNodePosi(T) p = first();
		while (_trailer != p)
		{
			visit(p->data);
			p = p->succ;
		}
	}

	//ordered list 
	template<typename T>int List<T>::uniquify()
	{
		if (2 > _size)
		{
			return 0;
		}
		int oldSize = _size;
		ListNodePosi(T) p = first();
		ListNodePosi(T) q = p->succ;
		while (_trailer != p)
		{
			if (p->data == q->data)
			{
				remove(q);
			}
			else
			{
				p = q;
			}
			q = p->succ;
		}
		return oldSize - _size;
	}

	//valid(p) && Rank(p) + n <= _size;
	template<typename T> void List<T>::selectionSort(ListNodePosi(T) p, int n)
	{
		ListNodePosi(T) head = p->pred;
		ListNodePosi(T) tail = p;
		for (int i = 0; i < n; ++i)
		{
			tail = tail->succ;
		}
		while (1 < n)
		{
			insertBefore(tail, remove(selectMax(head->succ, n)));
			tail = tail->pred;
			--n;
		}
	}
	
	template<typename T>ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) const
	{
		ListNodePosi(T) max = p;
		ListNodePosi(T) cur = p->succ;
		while (n > 1)
		{
			//<=使算法稳定
			if (max->data <= cur->data)
			{
				max = cur;
			}
			cur = cur ->succ;
			--n;
		}
		return max;
	}

	template<typename T>void List<T>::insertionSort(ListNodePosi(T) p, int n)
	{
		for (int r = 0; r < n; ++r)
		{
			insertAfter(search(p->data, r, p), p->data);
			p = p->succ;
			remove(p->pred);
		}
// 		ListNodePosi(T) head = p;
// 		ListNodePosi(T) tail = p;
// 		for (int i = 1; i < n; ++i)
// 		{
// 			tail = tail->succ;
// 		}
// 		for (int i = 1; i < n; ++i)
// 		{
// 			int j = 0;
// 			p = head;
// 			while (j < i && p->data <= tail->data)
// 			{
// 				p = p->succ;
// 				++j;
// 			}
// 			if (head == p)
// 			{
// 				head = insertBefore(p, tail->data);
// 			}
// 			else
// 			{
// 				insertBefore(p, tail->data);
// 			}
// 			tail = tail->pred;
// 			remove(tail->succ);
// 		}
		
	}
}
#endif // LIST

