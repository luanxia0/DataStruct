#pragma once
#ifndef _H_GRAPHMTRIX_
#define _H_GRAPHMTRIX_
#include "Vector.h"
#include "Graph.h"

namespace sy
{
	template<typename Tv>
	struct Vertex
	{
		Tv data;
		int inDegree;
		int outDegree;
		VertexStatus status;
		int dTime, fTime;
		int parent;
		int priority;

		Vertex(const Tv &vertexData = (Tv)0)
			: data(vertexData)
			, inDegree(0)
			, outDegree(0)
			, status(UNDISCOVERED)
			, dTime(-1)
			, fTime(-1)
			, parent(-1)
			, priority(-1){}
	};

	template <typename Te>
	struct Edge
	{
		Te data;
		int weight;
		EdgeType type;

		Edge(const Te &edgeData, int weight)
			: data(edgeData)
			, weight(0)
			, type(UNDETERMINED){}
	};

	template <typename Tv, typename Te>
	class GraphMatrix : public sy::Graph<Tv, Te>
	{
	private:
		sy::Vector<sy::Vertex<Tv>> vertices;
		sy::Vector<sy::Vector<sy::Edge<Te> *>> edges;

	public:
		GraphMatrix() { this->n = this->e = 0; }
		~GraphMatrix();

		//�������
		virtual Tv& vertex(int i) { return  vertices[i].data; }
		virtual int inDegree(int i) { return vertices[i].inDegree; }
		virtual int outDegree(int i) { return vertices[i].outDegree; }
		virtual int firstNbr(int i) { return nextNbr(i, this->n); }
		virtual int nextNbr(int i, int j) { while (-1 < j && !exists(i, --j)); return j; }
		virtual sy::VertexStatus &status(int i) { return vertices[i].status; }
		virtual int& dTime(int i) { return vertices[i].dTime; }
		virtual int& fTime(int i) { return vertices[i].fTime; }
		virtual int& parent(int i) { return vertices[i].parent; }
		virtual int& priority(int i) { return vertices[i].priority; }

		//����Ķ�̬����
		virtual int insert(const Tv& vertexData)
		{
			for (int i = 0; i < this->n; ++i)
			{
				edges[i].insert(nullptr);
			}
			++this->n;
			edges.insert(sy::Vector<sy::Edge<Te>*>(this->n, (sy::Edge<Te>*)nullptr));
			return vertices.insert(sy::Vertex<Tv>(vertexData));
		}

		virtual Tv remove(int i)
		{
			for (int j = 0; j < this->n; ++j)
			{
				if (exists(i, j))
				{
					delete edges[i][j];
					edges[i][j] = nullptr;
					vertices[j].inDegree--;
				}
			}
			edges.remove(i);
			this->n--;


			Tv vertexBak = vertices.remove(i).data;
			for (int k = 0; k < this->n; ++k)
			{
				sy::Edge<Te> *e = nullptr;
				if (e = edges[k].remove(i))
				{
					delete e;
					vertices[k].outDegree--;
				}
			}

			return vertexBak;
		}

		virtual bool exists(int i, int j)
		{
			return (0 <= i) && (0 <= j) && (j < this->n) && edges[i][j] != nullptr;
		}

		virtual sy::EdgeType &type(int i, int j) { return edges[i][j]->type; }
		virtual Te& edge(int i, int j) { return edges[i][j]->data; }
		virtual int& weight(int i, int j) { return edges[i][j]->weight; }


		virtual void insert(const Te& edge, int weight, int i, int j)
		{
			if (exists(i, j))
			{
				return;
			}
			edges[i][j] = new sy::Edge<Te>(edge, weight);
			this->e++;
			vertices[i].outDegree++;
			vertices[j].inDegree++;
		}

		virtual Te remove(int i, int j)
		{
			Te eBak = edge(i, j);
			delete edges[i][j];
			edges[i][j] = nullptr;
			vertices[i].outDegree--;
			vertices[j].inDegree--;

			return eBak;
		}
	};

	template<typename Tv, typename Te>
	inline GraphMatrix<Tv, Te>::~GraphMatrix()
	{
		for (int i = 0; i < this->n; ++i)
		{
			for (int j = 0; j < this->n; ++j)
			{
				delete edges[i][j];
			}
		}
	}
}



#endif // !1


