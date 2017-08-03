#pragma once
namespace sy
{
	template<typename T>
	struct PQ
	{
		virtual void insert(const T &) = 0;
		virtual T getMax() const = 0;
		virtual T delMax() = 0;
	};
}