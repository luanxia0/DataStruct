#pragma once
#include <string.h>
#include <memory>
#include <algorithm>


int match(char *p, char *t)
{
	int m = strlen(p);
	int n = strlen(t);
	int i = 0;
	int j = 0;

	while (i < n && j < m)
	{
		if (p[j] == t[i])
		{
			++j;
			++i;
		}
		else
		{
			i -= j - 1;
			j = 0;
		}
	}

	return i - j;
}

int match2(char *p, char *t)
{
	int m = strlen(p);
	int n = strlen(t);
	int i = 0;
	int j = 0;

	for (int i = 0; i < n - m + 1; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (p[j] != t[i + j])
			{
				break;
			}
		}
		
		if (j >= m)
		{
			break;
		}
	}

	return i;
}

std::unique_ptr<int[]> buildNext(const char *p)
{
	int m = strlen(p);
	int j = 0;
	std::unique_ptr<int[]> n(new int[m]);
	int t = n[0] = -1;
	while (j < m - 1)
	{
		if (t < 0 || p[j] == p[t])
		{
			++j;
			++t;
			n[j] = (p[j] != p[t]) ? t : n[t];
		}
		else
		{
			t = n[t];
		}
	}

	return n;
}

int matchKMP(const char *p, const char *t)
{
	int m = strlen(p);
	int n = strlen(t);

	int i = 0;
	int j = 0;

	auto next = buildNext(p);

	while (j < m && i < n)
	{
		if (j < 0 || p[j] == t[i])
		{
			++i;
			++j;
		}
		else
		{
			j = next[j];
		}
	}

	return j == m;
}