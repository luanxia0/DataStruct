#ifndef SOMEMESS
#define SOMEMESS



template<typename T>
void Swap(T &fir, T &sec)
{
    T tmp = fir;
    fir = sec;
    sec = tmp;
}

template <typename T>
T Max(const T &lhs, const T &rhs)
{
    return lhs < rhs ? rhs : lhs;
}

template <typename T>
T Min(const T&lhs, const T& rhs)
{
    return lhs < rhs ? lhs : rhs;
}

//template<typename T>
//T Max(const T &fir,  const T &sec, const T &thir)
//{
//    if(fir < sec)
//    {
//        Swap(fir, sec);
//    }
//    if(fir < thir)
//    {
//        Swap(fir, thir);
//    }
//    return fir;
//}

int countOnes(unsigned int n)
{
    int ones = 0;
    while(0 < n)
    {
        ones += (1 & n);
        n >>= 1;
    }
    return ones;
}

template<typename T>
void Max2(T a[], int lo, int hi, int &x1, int &x2)
{
    if(lo + 2 == hi)
    {
        x1 = lo;
        x2 = lo + 1;
        if(a[x1] < a[x2])
        {
            Swap(x1, x2);
        }
//        if(a[hi] > a[x1])
//        {
//            x2 = x1;
//            x1 = hi;
//        }
//        else if(a[hi] > a[x2])
//        {
//            x2 = hi;
//        }
        return;
    }
    if(lo + 3 == hi)
    {
//        int x1L = lo;
//        int x2L = lo + 1;
//        if(a[x1L] < a[x2L])
//        {
//            Swap(x1L, x2L);
//        }
//        int x1R = lo + 2;
//        int x2R = hi;
//        if(a[x1R] < a[x2R])
//        {
//            Swap(x1R, x2R);
//        }

//        if(a[x1L] > a[x1R])
//        {
//            x1 = x1L;
//            x2 = a[x2L] > a[x1R] ? x2L : x1R;
//        }
//        else
//        {
//            x1 = x1R;
//            x2 = a[x2R] > a[x1L] ? x2R : x1L;
//        }
        x1 = lo;
        x2 = lo + 1;
        if(a[x1] < a[x2])
        {
            Swap(x1, x2);
        }
        if(a[lo + 2] > a[x1])
        {
            x2 = x1;
            x1 = hi;
        }
        else if(a[lo + 2] > a[x2])
        {
            x2 = hi;
        }
        return;
    }
    int mi = (lo + hi)/2;
    int x1L, x2L;
    Max2(a, lo, mi, x1L, x2L);
    int x1R, x2R;
    Max2(a, mi, hi, x1R, x2R);

    if(a[x1L] > a[x1R])
    {
        x1 = x1L;
        x2 = (a[x2L] > a[x1R]) ? x2L : x1R;
    }
    else /*if(a[x1L] < a[x1R])*/
    {
        x1 = x1R;
        x2 = (a[x1L] > a[x2R]) ? x1L : x2R;
    }
}


class Fibonacci
{
    #define DEFAULT_SIZE 2
public:
    Fibonacci(int low, int high):_index(0)
    {
        while(_elem[_index] < (high - low))
        {
            ++_index;
        }
    }
    Fibonacci(const Fibonacci & f) = delete;
    Fibonacci & operator=(const Fibonacci &f) = delete;

    void prev()
    {
        --_index;
    }

    long long get() const
    {
        return _elem[_index];
    }

    void next()
    {
        ++_index;
    }

    bool isEnd() const
    {
        return _index > 50 || _index < 0;
    }

private:
    static const int _elem[51];
    int _index;
};
const int Fibonacci::_elem[51] =
{
    1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903
};

namespace sy
{
	template <typename T>
	bool lt(const T *a, const T *b)
	{
		return lt(*a, *b);
	}

	template <typename T>
	bool lt(const T &a, const T &b)
	{
		return a < b;
	}

	template <typename T>
	bool eq(const T *a, const T *b)
	{
		return eq(*a, *b);
	}

	template <typename T>
	bool eq(const T &a, const T &b)
	{
		return a < b;
	}
}


#endif // SOMEMESS

