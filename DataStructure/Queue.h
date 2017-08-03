#ifndef QUEUE_H_
#define QUEUE_H_

#include "List.h"
namespace sy
{
	template<typename T>
	class Queue : public List<T>
	{
	public:
		void enqueue(const T &e)
		{
			this->insertAsLast(e);
		}

		T dequeue()
		{
			return this->remove(this->first());
		}

		T &front()
		{
			return this->first()->data;
		}
	};
}


//队列的应用
struct Customer
{
	int window;
	int time;
};

int bestWindow(sy::Queue<Customer> q[], int winNum)
{
	int minSize = q[0].size();
	int option = 0;
	for (int i = 0; i < winNum; ++i)
	{
		if (minSize > q[i].size())
		{
			minSize = q[i].size();
			option = i;
		}
	}
	return option;
}

void simulate(int winNum, int servTime)
{
	sy::Queue<Customer> *queue = new sy::Queue<Customer>[winNum];
	for (int now = 0; now < servTime; ++now)
	{
		if (rand() % (winNum + 1))
		{
			Customer c;
			c.time = rand() % 98;
			c.window = bestWindow(queue, winNum);

			
			queue[c.window].dequeue();
		}
		for (int i = 0; i < winNum; ++i)
		{
			if (!queue[i].empty())
			{
				if (--queue[i].front().time <= 0)
				{
					queue[i].dequeue();
				}
			}
		}
	}

}
#endif
