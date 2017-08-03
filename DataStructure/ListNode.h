#ifndef LISTNODE
#define LISTNODE

typedef int Rank;

namespace sy
{
    #define ListNodePosi(T) ListNode<T>*
    template<typename T>
    struct ListNode
    {
        T data;
        ListNodePosi(T) pred;
        ListNodePosi(T) succ;
        ListNode(){};
        ListNode(const T &e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr)
            :data(e), pred(p), succ(s)
        {
            ;
        }
        ListNodePosi(T) insertAsPred(const T &e);
		ListNodePosi(T) insertAsSucc(const T &e);
    };

	template<typename T>ListNodePosi(T) ListNode<T>::insertAsPred(const T &e)
	{
		ListNodePosi(T) x = new ListNode<T>(e, pred, this);
		pred->succ = x;
		pred = x;
		return x;
	}

	template<typename T>ListNodePosi(T) ListNode<T>::insertAsSucc(const T &e)
	{
		ListNodePosi(T) x = new ListNode<T>(e, this, succ);
		succ->pred = x;
		succ = x;
		return x;
	}
}
#endif // LIST

