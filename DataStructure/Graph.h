#pragma once
#ifndef _H_GRAPH_
#define _H_GRAPH_

#include "Stack.h"
#include "limits.h"
#include "Utility.h"
namespace sy
{
	typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VertexStatus;
	typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EdgeType;
	template <typename Tv, typename Te>
	class Graph
	{
	private:
		
		//Reset all vertex and edges 
		void reset()
		{
			for (int i = 0; i < n; ++i)
			{
				//vertex status
				status(i) = UNDISCOVERED;

				//time tag
				dTime(i) = -1;
				fTime(i) = -1;

				//parent node
				parent(i) = -1;
				
				//priority
				priority(i) = INT_MAX;

				//all edges
				for (int j = 0; j < n; j++)
				{
					if (exists(i, j))
					{
						type(i, j) = UNDETERMINED;
					}
				}
			}
		}

		void BFS(int, int &);//广度优先搜索
		void DFS(int, int &);//深度优先搜索
		void BCC(int, int &, sy::Stack<int> &);//基于DFS的双连通分量分解
		bool TSort(int, int &, sy::Stack<Tv>*);//基于DFS的拓扑排序

		template<typename PU>
		void PFS(int, PU);//优先级搜索框架

	public:
		int n;//顶点总数
		virtual int insert(const Tv &) = 0;//插入顶点返回编号
		virtual Tv remove(int) = 0;//删除顶点及其关联边，返回顶点信息
		virtual Tv& vertex(int) = 0;//获得顶点数据
		virtual int inDegree(int) = 0;//顶点的入度
		virtual int outDegree(int) = 0;//顶点的出度
		virtual int firstNbr(int) = 0;//顶点v的首个邻接点
		virtual int nextNbr(int, int) = 0;//顶点v的下一邻接点
		virtual VertexStatus &status(int) = 0;//定点v的状态
		virtual int &dTime(int) = 0;//顶点v的标签时间dTime
		virtual int &fTime(int) = 0;//定点v的标签时间fTime
		virtual int &parent(int) = 0;//顶点v在遍历树中的父亲
		virtual int &priority(int) = 0;//顶点v在遍历树中的优先级
		
		int e;//边的个数
		virtual bool exists(int, int) = 0;//边(u,v)是否存在
		virtual void insert(const Te&, int, int, int) = 0;//在定点v和u之间插入权重为w的边
		virtual Te remove(int, int) = 0;//删除v和u之间的边
		virtual EdgeType &type(int, int) = 0;//边(u, v)的类型
		virtual Te& edge(int, int) = 0;//边(u,v)的数据
		virtual int &weight(int, int) = 0;//边(u, v)的权重

		void bfs(int);
		void dfs(int);
		void bcc(int);
		sy::Stack<Tv>* tSort(int);
		void prim(int);
		void dijkstra(int);
		template <typename PU>
		void pfs(int, PU);
	};

	template <typename Tv, typename Te>
	void Graph<Tv, Te>::bfs(int s)
	{
		reset();
		int clock = 0;
		int v = s;
		do
		{
			if(UNDISCOVERED == status(v))
			{
				BFS(v, clock);
			}

		}while(s != (v = (++v % n)));
	}

	template <typename Tv, typename Te>
	void Graph<Tv, Te>::BFS(int v, int &clock)
	{
		sy::Queue<int> queue;
		status(v) = DISCOVERED;
		queue.enqueue(v);

		while(!queue.empty())
		{
			int v = queue.dequeue();
			dTime(v) = ++clock;
			for(int u = firstNbr(v); u > -1; u = nextNbr(v, u))
			{
				if(UNDISCOVERED == status(u))
				{
					status(u) = DISCOVERED;
					queue.enqueue(u);
					type(v, u) = TREE;
					parent(u) = v;
				}
				else
				{
					type(v, u) = CROSS;
				}
			}

			std::cout << vertex(v) << std::endl;
			status(v) = VISITED;
		}
	}

	template <typename Tv, typename Te>
	void Graph<Tv, Te>::dfs(int s)
	{
		reset();
		int clock= 0;
		int v = s;
		do
		{
			if(UNDISCOVERED == status(v))
			{
				DFS(v, clock);
			}

		}while(s != (v = (++v % n)));

	}

	template <typename Tv, typename Te>
	void Graph<Tv, Te>::DFS(int v, int &clock)
	{
		dTime(v) = ++clock;
		status(v) = DISCOVERED;
		for(int u = firstNbr(v); u > -1; u = nextNbr(v, u))
		{
			switch (status(u))
			{
				case UNDISCOVERED:
				{
					type(v, u) = TREE;
					parent(u) = v;
					DFS(u, clock);
				}
					break;
				case DISCOVERED:
				{
					type(v, u) = BACKWARD;
				}
					break;
				case VISITED:
				{
					type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
				}
					break;
			}

		}
		std::cout << vertex(v) << std::endl;
		status(v) = VISITED;
		fTime(v) = ++clock;
	}

#define  hca(x) (fTime(x))
	template <typename Tv, typename Te>
	void Graph<Tv, Te>::BCC(int v, int &clock, Stack<int> &stack)
	{
		hca(v) = dTime(v) = ++clock;
		status(v) = DISCOVERED;
		stack.push(v);

		for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
		{
			switch (status(u))
			{
				case UNDISCOVERED:
					parent(u) = v;
					type(v, u) = TREE;
					BCC(u, clock, stack);
					if(hca(u) < dTime(v))
					{
						hca(v) = Min(hca(v), hca(u));
					}
					else
					{
						while (v != stack.pop());
						stack.push(v);
					}
					break;
				case DISCOVERED:
					type(v, u) = BACKWARD;
					if(u != parent(v))
					{
						hca(v) = Min(hca(v), dTime(u));
					}
					break;
				default:
					type(v, u) = (dTime(v) < dTime(u)) ? FORWARD:CROSS;
					break;

			}
		}
		status(v) = VISITED;
	}

#undef hca

	template <typename Tv, typename Te>
	void Graph<Tv, Te>::bcc(int s)
	{
		reset();
		int v = s;
		int clock = 0;
		sy::Stack<int> stack;
		do
		{
			if(status(v) == UNDISCOVERED)
			{
				BCC(v, clock, stack);
				stack.pop();
			}
		}while (s != (v = ++v % n));

	}

	template <typename Tv, typename Te>
	bool Graph<Tv, Te>::TSort(int v, int &clock, Stack <Tv> *stack)
	{
		dTime(v) = ++clock;
		status(v) = DISCOVERED;
		for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
		{
			switch (status(u))
			{
				case UNDISCOVERED:
				{
					parent(u) = v;
					type(v, u) = TREE;
					if(!TSort(u ,clock, stack))
					{
						return false;
					}
				}
					break;
				case DISCOVERED:
				{
					type(v, u) = BACKWARD;
					return false;
				}
					break;
				case VISITED:
				{
					type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
				}
					break;
			}
		}
		status(v) = VISITED;
		stack->push(vertex(v));
		return true;

	}

	template <typename Tv, typename Te>
	sy::Stack<Tv> *Graph<Tv, Te>::tSort(int s)
	{
		reset();
		int v = s;
		int clock = 0;
		sy::Stack<Tv> *stack = new sy::Stack<Tv>();

		do
		{
			if(status(v) == UNDISCOVERED)
			{
				if(!TSort(v, clock, stack))
				{
					//empty the stack
					while(!stack->empty())
					{
						stack->pop();
					}
				}
			}
		}while(s != (v = ++v % n));
		return stack;
	}




	template <typename Tv, typename Te>
	struct DijkstraPU
	{
		virtual void operator()(Graph<Tv, Te> *graph, int uk, int v)
		{
			if(UNDISCOVERED == graph->status(v))
			{
				if(graph->priority(v) > graph->priority(uk) + graph->weight(uk, v))
				{
					graph->priority(v) = graph->priority(uk) + graph->weight(uk, v);
					graph->parent(v) = uk;
				}
			}
		}
	};

	template <typename Tv, typename Te>
	struct primPriorityUpdater
	{
		virtual  void operator()(sy::Graph<Tv, Te> *graph, int uk, int v)
		{
			Tv vertexData = graph->vertex(v);

			if(UNDISCOVERED == graph->status(v))
			{
				if(graph->priority(v) > graph->weight(uk, v))
				{
					graph->priority(v) = graph->weight(uk, v);
					graph->parent(v) = uk;
				}
			}
		}

	};

	template<typename Tv, typename Te>
	inline void Graph<Tv, Te>::prim(int v)
	{
		pfs(v, primPriorityUpdater<Tv, Te>());
	}
	template <typename Tv, typename Te>
	template<typename PU>
	void Graph<Tv, Te>::PFS(int i, PU prioUpdater)
	{
		priority(i) = 0;
		status(i) = VISITED;
		parent(i) = -1;
		std::cout << vertex(i) << "---";
		while(1)
		{
			for(int w = firstNbr(i); w > -1; w = nextNbr(i, w))
			{
				prioUpdater(this, i, w);
			}

			int shortest = INT_MAX;
			for(int w = 0; w < n; w++)
			{
				if(UNDISCOVERED == status(w))
				{
					if(shortest > priority(w))
					{
						shortest = priority(w);
						i = w;
					}
				}
			}

			if(VISITED == status(i))
			{
				break;
			}
			
			Tv vertexData = vertex(i);
			////////////////////////////
			std::cout << vertex(i) << "---";
			///////////////////////////

			status(i) = VISITED; type(parent(i), i) = TREE;
		}

	}

	template <typename Te, typename Tv>
	template<typename PU>
	void Graph<Te,Tv>::pfs(int i, PU pu)
	{
		reset();
		int v = i;
		do
		{
			if(status(v) == UNDISCOVERED)
			{
				PFS(v, pu);
			}

		}while(i != (v = ++v % n));

	}

	template <typename Tv, typename Te>
	void Graph<Tv, Te>::dijkstra(int i)
	{
		pfs(i, DijkstraPU<Tv, Te>());
	}
}

#endif