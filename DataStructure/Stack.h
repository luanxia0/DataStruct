#ifndef STACK
#define STACK
#include "Vector.h"
#include "float.h"
namespace sy
{
	template<typename T>
	class Stack : public Vector<T>
	{
	public:
		void push(const T &e);
		T pop();
		T& top();
	};

	template<typename T>
	inline void Stack<T>::push(const T & e)
	{
		this->insert(this->size(), e);
	}

	template<typename T>
	inline T Stack<T>::pop()
	{
		return this->remove(this->size() - 1);
	}

	template<typename T>
	inline T & Stack<T>::top()
	{
		return (*this)[this->size() - 1];
	}

	template<typename T> 
	class LinkedStack : public List<T>
	{
	public:
		void push(const T &e);
		T pop();
		T& top();
	};
	
	template<typename T>
	inline void LinkedStack<T>::push(const T & e)
	{
		this->insertAsLast(e);
	}

	template<typename T>
	inline T LinkedStack<T>::pop()
	{
		return this->remove(this->last());
	}

	template<typename T>
	inline T & LinkedStack<T>::top()
	{
		return this->last()->data;
	}

}


void convert(sy::Stack<char> &s, long long n, int base)
{
	static char digit[] = 
	{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	while (n > 0)
	{
		s.push(digit[n % base]);
		n = n / base;
	}
}

bool paren(const char exp[], int lo, int hi)
{
	sy::Stack<char> s;
	for (int i = lo; i <= hi; ++i)
	{
		switch (exp[i])
		{
		case '(':
		case '{':
		case '[':
			s.push(exp[i]);
			break;
		case ')':
			if (s.empty() || s.pop() != '(')
			{
				return false;
			}
			break;
		case '}':
			if (s.empty() || s.pop() != '{')
			{
				return false;
			}
			break;
		case ']':
			if (s.empty() || s.pop() != '[')
			{
				return false;
			}
			break;
		default:
			break;
		}
	}
	return s.empty();
}

#define N_OPTR 9
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, _EOF} Operator; 

//[ջ��][��ǰ]
const char pri[N_OPTR][N_OPTR] =
{
	/*       +    -    *    /    ^    !    (    )   \0*/
	/*+*/	'>', '>', '<', '<', '<', '<', '<', '>', '>',
	/*-*/   '>', '>', '<', '<', '<', '<', '<', '>', '>',
	/***/   '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/*/*/   '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/*^*/   '>', '>', '>', '>', '>', '<', '<', '>', '>',
	/*!*/   '>', '>', '>', '>', '>', '>', ' ', '>', '>',
	/*(*/   '<', '<', '<', '<', '<', '<', '<', '=', ' ',
	/*)*/   ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	/*\0*/  '<', '<', '<', '<', '<', '<', '<', '<', '='
};

#include <cmath>
#include <cstring>
#include <ctype.h>
void readNumber(char *s, sy::Stack<float> &opnd)
{
	float integer = 0;
	while (*s == ' ' || *s == '\n' || *s == '\t')
	{
		++s;
	}
	float sign = 1.0f;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
		{
			sign = -1.0f;
		}
		++s;
	}
	while (isdigit(*s))
	{
		integer *= 10;
		integer += (*s - '0');
		++s;
	}
	float fraction = 0;
	if (*s++ == '.')
	{
		int i = 0;
		while (isdigit(*s))
		{
			fraction *= 10;
			fraction += (*s - '0');
			++i;
			++s;
		}
		fraction /= (float)pow(10, i);
	}
	opnd.push((integer + fraction) * sign);
}



char orderBetween(char stackTop, char s)
{
	static const char Opnd[] = {'+', '-', '*', '/', '^', '!', '(', ')'};

	int i = 0;
	for (; i < N_OPTR; ++i)
	{
		if (stackTop == Opnd[i])
		{
			break;
		}
	}
	int j = 0; 
	for (; j < N_OPTR; ++j)
	{
		if (s == Opnd[j])
		{
			break;
		}
	}
	return pri[i][j];
	
}

float Pow_R(float base, int exp)
{
	if (exp == 0)
	{
		return 1.0f;
	}
	if (exp % 2 == 1)
	{
		return Pow_R(base * base, exp / 2) * base;
	}

    return Pow_R(base * base, exp / 2);


}

float Pow_NR(float base, int exp)
{
	unsigned int _exp = 0;
	if (exp >= 0)
	{
		 _exp = static_cast<unsigned int>(exp);
	}
	else
	{
		_exp = static_cast<unsigned int>(-exp);
	}
	
	for (float result = static_cast<float>(1);; base *= base)
	{
		if ((_exp & 1) != 0)
		{
			result *= base;
		}
		if ((_exp >>= 1) == 0)
		{
			return (exp < 0 ? static_cast<float>(1) / result : result);
		}
	}
}
float calculate(float left, char optr, float right)
{
	switch (optr)
	{
	case '+':
		return left + right;

	case '-':
		return left - right;

	case '*':
		return left * right;

	case '/':
		if (fabs(right) > 0.0000001)
		{
			return left / right;
		}
		break;
	case '^':
		return Pow_NR(left, static_cast<int>(right));
	case '(':
		break;
	case ')':
		break;
	case '\0':
		break;
	default:
		break;
	}
    return FLT_MIN;
}

float calculate(char optr, float opnd)
{
	float result = 1;
	
	switch (optr)
	{
	case '!':
		for (int i = 2; i <= opnd; ++i)
		{
			result *= i;
		}
		break;
	default:
		break;
	}
	return result;
}

float evaluate(char *s, sy::Vector<char> &rpn)
{
	sy::Stack<float> opnd;
	sy::Stack<char> optr;
	optr.push('\0');
	while (!optr.empty())
	{
		if (isdigit(*s))
		{
			readNumber(s, opnd);
			rpn.insert(*s);
			++s;
		}
		else
		{
			switch (orderBetween(optr.top(), *s))
			{
			case '>':
			{
				char op = optr.pop();
				rpn.insert(op);

				if ('!' == op)
				{
					float pOpnd = opnd.pop();
					opnd.push(calculate(op, pOpnd));
				}
				else
				{
					float right = opnd.pop();
					float left = opnd.pop();
					opnd.push(calculate(left, op, right));
				}
			}
				break;
			case '<':
				optr.push(*s);
				s++;
				break;
			case '=':
				optr.pop();
				s++;
				break;
			default:
				exit(-1);
			}
		}
	}
	return opnd.pop();
}


float rpnEvaluate(char *s)
{
	sy::Stack<float> result;
	while (*s != '\0')
	{
		if (isdigit(*s))
		{
			readNumber(s, result);
			++s;
		}
		else
		{
			if (*s == '!')
			{
				float pOpnd = result.pop();
				result.push(calculate('!', pOpnd));
			}
			else
			{
				float right = result.pop();
				float left = result.pop();
				result.push(calculate(left, *s, right));
			}
			++s;
		}
	}
	return result.pop();
}

struct Queen
{
	int x;
	int y;
	Queen(int _x = 0, int _y = 0) :x(_x), y(_y) {};
	bool operator==(const Queen &q) const
	{
		return (x == q.x) || (y == q.y) || (x + y == q.x + q.y) || (x - y == q.x - q.y);
	}
	bool operator!=(const Queen &q) const
	{
		return !((*this) == q);
	}
};

int nCheck;
int nSlolu;
void placeQueens(int N)
{
	sy::Stack<Queen> solution;
	Queen q(0, 0);
	do
	{
		//������Χ
		if (N <= solution.size() || N <= q.y)
		{
			q = solution.pop();
			q.y++;
		}
		else
		{
			//����Ƿ��ͻ
			while ((q.y < N) && (0 <= solution.find(q)))
			{
				q.y++;
				nCheck++;
			}
			if (N > q.y)
			{
				solution.push(q);
				if (N <= solution.size())
				{
					nSlolu++;
				}
				q.x++;
				q.y = 0;
			}
		}
	} while ((0 < q.x) || (q.y < N));
}

void placeQueen(int n, int &solu, int &check)
{
	sy::Stack<Queen> stack;
	Queen q;
	do
	{
		
		if (q.x >= n || q.y >= n)
		{
			q = stack.pop();
			q.y++;
		}
		else
		{
			while ((q.y < n) && (stack.find(q) >= 0))
			{
				q.y++;
				check++;
			}
			if (q.y < n)
			{
				stack.push(q);
				if (stack.size() == n)
				{
					++solu;
				}
				q.x++;
				q.y = 0;
			}
		}
	} while ((q.x > 0) || (q.y < n));
}
void placeQueen_R(int n, Queen q, int &solu)
{

	if (q.x >= n || q.y >= n)
	{
		return;
	}
	;
	
}

typedef enum {AVAILABLE, ROUTE, BACKTRACKED, WALL} Status;
typedef enum {UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY} ESWN;
inline ESWN nextESWN(ESWN eswn)
{
	return ESWN(eswn + 1);

}

struct Cell
{
	int x, y;
	Status status;
	ESWN incoming, outgoing;
};

#define LABY_MAX 24
Cell laby[LABY_MAX][LABY_MAX];

inline Cell *neighbor(Cell *cell)
{
	switch (cell->outgoing)
	{
	case EAST:
		return cell + LABY_MAX;
	case SOUTH:
		return cell + 1;
	case WEST:
		return cell - LABY_MAX;
	case NORTH:
		return cell - 1;
	default:
		exit(-1);
	}
}

inline Cell *advance(Cell *cell)
{
	Cell *next;
	switch (cell->outgoing)
	{
	case EAST:
		next = cell + LABY_MAX;
		next->incoming = WEST;
		break;
	case SOUTH:
		next = cell + 1;
		next->incoming = NORTH;
	case WEST:
		next = cell - LABY_MAX;
		next->incoming = EAST;
	case NORTH:
		next = cell - 1;
		next->incoming = SOUTH;
	default:
		exit(-1);

	}
	return next;
}

bool labyrinth(Cell Laby[LABY_MAX][LABY_MAX], Cell *s, Cell *t)
{
	if ((AVAILABLE != s->status) || (AVAILABLE != t->status))
	{
		return false;
	}
	sy::Stack<Cell*> path;
	s->incoming = UNKNOWN;
	s->status = ROUTE;
	path.push(s);
	do 
	{
		Cell *c = path.top();
		if (c == t)
		{
			return true;
		}
		while (NO_WAY > (c->outgoing = nextESWN(c->outgoing)))
		{
			if (AVAILABLE == neighbor(c)->status)
			{
				break;
			}
		}
		if (NO_WAY <= c->outgoing)
		{
			c->status = BACKTRACKED;
			c = path.top();
		}
		else
		{
			path.push(c = advance(c));
			c->outgoing = UNKNOWN;
			c->status = ROUTE;
		}
		
	} while (!path.empty());
	return false;
}

#endif
