#ifndef BINNODE_H_
#define BINNODE_H_

#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p)? (p)->height:-1)
typedef enum {RB_RED, RB_BLACK} RBColor;

//BinNode��״̬�������ж�
#define IsRoot(x) (!(x).parent)
#define IsLChild(x) (!IsRoot(x) && (& (x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (& (x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))


//��BinNode�����ض���ϵ�Ľڵ��ָ��
#define sibling(p) \
	(IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x) \
	(IsLChild(*(x)->parent) ? (x)->parent->parent->rc : (x)->parent->parent->lc)
#define FromParentTo(x) \
	(IsRoot(x) ? this->_root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))

template<typename T>
struct BinNode
{
	T data;
	BinNodePosi(T) parent;
	BinNodePosi(T) lc;
	BinNodePosi(T) rc;
	int height;
	int npl;
	RBColor color;

    //构造根结点
	BinNode()
		:parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), color(RB_RED) { }

	BinNode(const T &e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr,
		BinNodePosi(T) rc = nullptr, int h = 0, int l = 0, RBColor c = RB_RED)
		:data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) { }

	int size();//��ǰ�ڵ�������
	BinNodePosi(T) insertAsLC(const T &e);
	BinNodePosi(T) insertAsRC(const T &e);
	BinNodePosi(T) succ() const;
	template<typename VST>void traverseLevel(VST &);
	template<typename VST> void traversePre(VST &);
	template<typename VST>void traverseIn(VST &);
	template<typename VST>void traversePost(VST &);

	bool operator< (BinNode const &bn)
	{
		return data < bn.data;
	}
	bool operator==(BinNode const &bn)
	{
		return data == bn.data;
	}
};

template<typename T>
inline BinNodePosi(T) BinNode<T>::insertAsLC(const T & e)
{
	return lc = new BinNode<T>(e, this);
}

template<typename T>
inline BinNodePosi(T) BinNode<T>::insertAsRC(const T & e)
{
	return rc = new BinNode<T>(e, this);
}

template<typename T>
inline BinNodePosi(T) BinNode<T>::succ() const
{
	BinNodePosi(T) curNode = const_cast<BinNodePosi(T)>(this);
	if(rc)
	{
		curNode = curNode->rc;
		while(HasLChild(*curNode))
		{
			curNode = curNode->lc;
		}
	}
	else
	{
		while(IsRChild(*curNode))
		{
			curNode = curNode->parent;
		}
		curNode = curNode->parent;
	}
	return curNode;
}

template <typename T>
int BinNode<T>::size()
{
	int s = 1;
	if(lc)
	{
		s += lc->size();
	}
	if(rc)
	{
		s += rc->size();
	}
	return  s;
}

template <typename  T>
template <typename VST>
void BinNode<T>::traverseIn(VST &visit)
{
	;
}

template <typename T>
template <typename VST>
void BinNode<T>::traversePre(VST &)
{

}


#endif // !1



