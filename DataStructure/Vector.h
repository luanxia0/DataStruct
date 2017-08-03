#ifndef VECTOR
#define VECTOR

#include "Utility.h"
#include <cstdlib>
namespace sy
{
    #define DEFAULT_CAPACITY 3
    typedef int Rank;
    template<typename T>
    class Vector
    {
    public:

//        Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
//        {
//            _elem = new T[c];
//            _size = 0;
//            for(; _size < s;)
//            {
//                _elem[_size++] = v;
//            }
//        }
// 		Vector(int s = 0)
// 		{
// 			_capacity = Max(s * 2, DEFAULT_CAPACITY);
// 			_elem = new T[_capacity];
// 			_size = 0;
// 		}

		Vector(int size = 0)
		{
			_capacity = Max(size * 2, DEFAULT_CAPACITY);
			_elem = new T[_capacity];
			_size = 0;
		}
        Vector(int size, const T &v)
        {
            _capacity = Max(size * 2, DEFAULT_CAPACITY);
            _elem = new T[_capacity];
            _size = 0;
            for(; _size < size; )
            {
                _elem[_size++] = v;
            }
        }

//         Vector(std::initializer_list<T> il)
//         {
//             _capacity = il.size() * 2;
//             _elem = new T[_capacity];
//             _size = 0;
//             for(auto it = il.begin(); _size < il.size();)
//             {
//                 _elem[_size++] = *it++;
//             }
//         }

        Vector(T const *elem, Rank low, Rank high) { copyFrom(elem, low, high); }

        Vector(T const *elem, Rank n) { copyFrom(elem, 0, n); }

        Vector(const Vector<T> &vec, Rank low, Rank high) { copyFrom(vec._elem, low, high); }

        Vector(const Vector<T> &vec) { copyFrom(vec._elem, 0, vec.size()); }

        ~Vector() { delete [] _elem; }

        //read-only
        Rank size() const { return _size; }

        bool empty() const { return !_size; }

        int disordered() const;

        Rank find(const T &e) const { return find(e, 0, _size); }

        Rank find(const T &e, Rank low, Rank high) const;

        Rank search(const T &e) const { return search(e, 0, _size); }

        Rank search(const T &e, Rank low, Rank high) const;

        //writable
        T &operator[](Rank r);

        Vector<T> &operator=(const Vector<T> &vec);

        T remove(const Rank r);

        int remove(Rank low, Rank high);

        Rank insert(Rank r, const T &e);

        Rank insert(const T &e) { return insert(_size, e); }

        void sort(Rank low, Rank high);

        void sort() { sort(0, _size); }

        void unsort(Rank low, Rank high);
        void unsort() { unsort(0, _size); }
        int deduplicate();
        int uniqutify();

        //traverse
        void traverse(void (*)(T &));
        template <typename VST> void traverse(VST &visit);

    protected:
        void copyFrom(T const *src, Rank low, Rank high)
        {
            _capacity = 2 * (high - low);
            _elem = new T[_capacity];
            _size = 0;
            for(int i = low; i < high; ++i)
            {
                _elem[_size++] = src[i];
            }
        }
        void expand();
        void shrink();
        int bubble(Rank low, Rank high);
        void bubbleSort(Rank low, Rank high);
        void selectionSort(Rank low, Rank high);
		Rank selectionMax(Rank low, Rank high);
        void merge(Rank low, Rank mid, Rank high);
        void mergeSrot(Rank low, Rank high);
        void partition(Rank low, Rank high);
        void quickSort(Rank low, Rank high);
        //virtual void heapSort(Rank low, Rank high);
		Rank _size;

		T *_elem;

		int _capacity;
    private:
        
    };

    template<typename T> void Vector<T>::expand()
    {
        if(_size < _capacity)
        {
            return;
        }
        _capacity = Max(_capacity , DEFAULT_CAPACITY);// ? _capacity : DEFAULT_CAPACITY;
        _capacity <<= 1;

        T *oldElem = _elem;
        _elem = new T[_capacity];

        for(int i = 0; i < _size; ++i)
        {
            _elem[i] = oldElem[i];
        }
        delete [] oldElem;
    }

    template<typename T> T& Vector<T>::operator[](Rank r)
    {
        return _elem[r];
    }

    template<typename T>
    Rank Vector<T>::insert(Rank r, const T &e)
    {
        expand();
        for(int i = _size; i > r; --i)
        {
            _elem[i] = _elem[i - 1];
        }
        _elem[r] = e;
        _size++;
        return r;
    }

    template<typename T>
    int Vector<T>::remove(Rank lo, Rank hi)
    {
        if(lo == hi)
            return 0;
        while(hi < _size)
        {
            _elem[lo++] = _elem[hi++];
        }
        _size = lo;
        shrink();
        return hi - lo;
    }
    template<typename T> T Vector<T>::remove(Rank r)
    {
        T e = _elem[r];
        remove(r, r + 1);
        return e;

    }
    template<typename T> Rank Vector<T>::find(const T &e, Rank low, Rank high) const
    {
        while((low < high--) && (e != _elem[high]));
        return high;
    }

    template<typename T> int Vector<T>::deduplicate()
    {
        int oldSize = _size;
        int i = 1;
        while(i < _size)
        {
            if(find(_elem[i], 0, i) < 0)
            {
                ++i;
            }
            else
            {
                remove(i);
            }
        }
        return oldSize - _size;
    }

    template<typename T> void Vector<T>::traverse(void (*visit)(T &))
    {
        for(int i = 0; i < _size; ++i)
        {
            visit(_elem[i]);
        }
    }

    template<typename T> template<typename VST> void Vector<T>::traverse(VST &visit)
    {
        for(int i = 0; i < _size; ++i)
        {
            visit(_elem[i]);
        }
    }

    template<typename T> int Vector<T>::disordered() const
    {
        int n = 0;
        for(int i = 1; i < _size; ++i)
        {
            n += (_elem[i - 1] > _elem[i]);
        }
        return n;
    }

    template<typename T> int Vector<T>::uniqutify()
    {

        int i = 0;
        int j = 0;
        while(++j < _size)
        {
            if(_elem[i] != _elem[j])
            {
                _elem[++i] = _elem[j];
            }
        }
        _size = ++i;
        shrink();
        return j - i;
    }

    template<typename T> void Vector<T>::shrink()
    {
		//????????????С????
		//?????_capacity??????, ???????С??2*???DEFAULT_CAPACITY
        if( _capacity < DEFAULT_CAPACITY << 1)
            return;
		//???С??25%
        if(_size << 2 > _capacity)
        {
            return ;
        }

        T * oldElem = _elem;
        _elem = new T[_capacity >>= 1];//_capacity???
        for(int i = 0; i < _size; ++i)
        {
            _elem[i] = oldElem[i];
        }
        delete [] oldElem;
    }

    template<typename T> static Rank binSearch(T *A, const T &e, Rank low, Rank high)
    {
        while(low < high)
        {
            int mid = (low + high) >> 1;
            if(A[mid] < e)
            {
                low = mid + 1;
            }
            else if(e < A[mid])
            {
                high = mid;
            }
            else
            {
                return mid;
            }
        }
        return -1;
    }

    template<typename T> static Rank binSearch2(T *A, const T &e, Rank low, Rank high)
    {
        while(high - low > 1)
        {
            Rank mid = (low + high) >> 1;
            if(e < A[mid])
            {
                high = mid;
            }
            else
            {
                low = mid;
            }
        }
        if(A[low] == e)
        {
            return low;
        }
        return -1;
    }

    template<typename T> static Rank binSearch3(T *A, const T &e, Rank low, Rank high)
    {
        while(low < high)
        {
            Rank mid = (high + low) >> 1;
            if(e < A[mid])
            {
                high = mid;
            }
            else
            {
                low = mid + 1;
            }
        }

        return --low;
    }

    template<typename T> static Rank fibSearch(T *A, const T &e, Rank low, Rank high)
    {
        Fibonacci fib(low, high);
        while(low < high)
        {
            while((high - low) < fib.get())
            {
                fib.prev();
            }
            Rank mid = low + fib.get() - 1;
            if(e < A[mid])
            {
                high = mid;
            }
            else if(A[mid] < e)
            {
                low = mid + 1;
            }
            else
            {
                return mid;
            }
        }
        return -1;
    }

    template<typename T> Rank Vector<T>::search(const T &e, Rank low, Rank high) const
    {

        return  rand() % 2 ?binSearch(_elem, e, low, high) : fibSearch(_elem, e, low, high);
//        return binSearch(_elem, e, low, high);//fibSearch(_elem, e, low, high);
        //return fibSearch(_elem, e, low, high);
    }

    template<typename T>void Vector<T>::sort(Rank low, Rank high)
    {
       switch (rand() % 3)
       {
       case 0:
		   bubbleSort(low, high);
           break;
       case 1:
		   mergeSrot(low, high);
           break;
       case 2:
		   selectionSort(low, high);
           break;
       default:
           break;
       }		
    }

    template<typename T> int Vector<T>::bubble(Rank low, Rank high)
    {
        //bool isSort = true;
        Rank last = low;
        while(++low < high)
        {
            if(_elem[low - 1] > _elem[low])
            {
                //isSort = false;
                last = low;
                Swap(_elem[low - 1], _elem[low]);
            }
        }
        return last;
    }

    template<typename T> void Vector<T>::bubbleSort(Rank low, Rank high)
    {
        while(low < high )
        {
            high = bubble(low, high);
        }
    }


	template<typename T>
	inline void Vector<T>::selectionSort(Rank low, Rank high)
	{
		int cur = high;
		while (--cur > low)
		{
			Swap(_elem[cur], _elem[selectionMax(low, cur)]);
		}
	}

	template<typename T>
	inline Rank Vector<T>::selectionMax(Rank low, Rank high)
	{
		Rank max = low;
		while (++low <= high)
		{
			if (_elem[max] <= _elem[low])
			{
				max = low;
			}
		}
		return max;
	}

    template<typename T> void Vector<T>::merge(Rank low, Rank mid, Rank high)
    {
        T *A = _elem + low;
        int lb = mid - low;
        T *B = new T[lb];
        for(Rank i = 0; i < lb; ++i)
        {
            B[i] = A[i];
        }
        T *C = _elem + mid;
        int lc = high - mid;
        for(int i = 0, j = 0, k = 0; j < lb; )
        {

            if(k >= lc || B[j] <= C[k])
            {
                A[i++] = B[j++];
            }

            if((k < lc) && (C[k] < B[j]))
            {
                A[i++] = C[k++];
            }
        }
        delete [] B;
    }

    template<typename T> void Vector<T>::mergeSrot(Rank low, Rank high)
    {
        if(high - low < 2)
        {
            return;
        }
        Rank mid = (low + high) >> 1;
        mergeSrot(low, mid);
        mergeSrot(mid, high);
        merge(low, mid, high);
    }

    template <typename T>
    Vector<T> &Vector<T>::operator=(const Vector<T> &vec)
    {
        T *oldElem = _elem;

        copyFrom(vec._elem, 0, vec.size());

        if(nullptr != oldElem)
        {
            delete oldElem;
        }

        return *this;
    }
}


#endif // VECTOR

