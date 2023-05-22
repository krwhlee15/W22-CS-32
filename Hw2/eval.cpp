#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int evaluate(string infix, const Map& values, string& postfix, int& result);
string removeSpaces(string infix);
int precedence(char c);
bool postfixGen(string infix, string& postfix);
int calc(const Map& values, string postfix, int& valid);

int main()
{
	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int  vals[] = { 3,  -9,   6,   2,   4,   1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
	{
		m.insert(vars[k], vals[k]);
	}

	string pf;
	int answer;
	
	assert(evaluate("a+ e", m, pf, answer) == 0 &&
		pf == "ae+" && answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);

	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()o", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(*o)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	// unary operators not allowed:
	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 && pf == "ab*" && answer == 999);
	assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
		pf == "yoau-*+" && answer == -1);
	
	answer = 999;
	assert(evaluate("o/(y-y)", m, pf, answer) == 3 && pf == "oyy-/" && answer == 999);
	assert(evaluate(" a  ", m, pf, answer) == 0 && pf == "a" && answer == 3);


	assert(evaluate("((a))", m, pf, answer) == 0 && pf == "a" && answer == 3);
	cout << "Passed all tests" << endl;
}

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
	string cleanInfix = removeSpaces(infix);
	int valid = -1;

	if (cleanInfix == "")
	{
		return 1;
	}

	int size = cleanInfix.size();

	for (int i = 0; i < size; i++)
	{
		if (isalpha(cleanInfix[i]))
		{
			if (!islower(cleanInfix[i]))
			{
				return 1;
			}
		}
	}

	if (!postfixGen(cleanInfix, postfix))
	{
		return 1;
	}

	for (int i = 0; i < size; i++)
	{
		if (isalpha(cleanInfix[i]))
		{
			if (!values.contains(cleanInfix[i]))
			{
				return 2;
			}
		}
	}

	int output = calc(values, postfix, valid);
	if (valid == 3)
	{
		return 3;
	}

	result = output;

	return 0;
}

bool postfixGen(string infix, string& postfix)
{
	postfix = "";
	stack<char> operatorStack;

	switch (infix[0])
	{
	case '*':
	case '/':
	case '+':
	case '-':
	case ')':
		return false;
	default:
		break;
	}

	switch (infix[infix.size() - 1])
	{
	case '*':
	case '/':
	case '+':
	case '-':
	case '(':
		return false;
	default:
		break;
	}

	int size = infix.size();
	for (int i = 0; i < size; i++)
	{
		char c = infix[i];
		if (isalpha(infix[i]))
		{
			if (i + 1 < size)
			{
				if (isalpha(infix[i + 1]) || infix[i + 1] == '(')
				{
					return false;
				}
			}
			postfix += c;
		}
		else
		{
			switch (infix[i])
			{
			case '(':
				if (i + 1 < size)
				{
					if (!isalpha(infix[i + 1]) && infix[i + 1] != '(')
					{
						return false;
					}
				}
				operatorStack.push(c);
				break;
			case ')':
				if (i + 1 < size)
				{
					if (isalpha(infix[i + 1]) || infix[i+1] == '(')
					{
						return false;
					}
				}
				while (!operatorStack.empty() && operatorStack.top() != '(')
				{
					postfix += operatorStack.top();
					operatorStack.pop();
				}
				if (operatorStack.empty())
				{
					return false;
				}
				operatorStack.pop();
				break;
			case '*':
			case '/':
			case '+':
			case '-':
				if (i + 1 < size)
				{
					switch (infix[i + 1])
					{
					case '*':
					case '/':
					case '+':
					case '-':
					case ')':
						return false;
					default:
						break;
					}
				}
				while (!operatorStack.empty() && operatorStack.top() != '(' && (precedence(c) <= precedence(operatorStack.top())))
				{
					postfix += operatorStack.top();
					operatorStack.pop();
				}
				operatorStack.push(c);
				break;
			default:
				return false;
			}
		}
	}
	while (!operatorStack.empty())
	{
		if (operatorStack.top() == '(' || operatorStack.top() == ')')
		{
			return false;
		}
		postfix += operatorStack.top();
		operatorStack.pop();
	}

	//cout << "postfix:" << postfix << endl;

	return true;
}

int calc(const Map& values, string postfix, int& valid)
{
	stack<char> operationStack;
	int matchingInt;

	int size = postfix.size();
	for (int i = 0; i < size; i++)
	{
		char c = postfix[i];

		if (isalpha(c))
		{
			values.get(c, matchingInt);
			operationStack.push(matchingInt);
		}
		else
		{
			int operand2 = operationStack.top();
			operationStack.pop();
			int operand1 = operationStack.top();
			operationStack.pop();

			switch (c)
			{
			case '*':
				operationStack.push(operand1 * operand2);
				break;
			case '/':
				if (operand2 == 0)
				{
					valid = 3;
					return 0;
				}
				operationStack.push(operand1 / operand2);
				break;
			case '+':
				operationStack.push(operand1 + operand2);
				break;
			case '-':
				operationStack.push(operand1 - operand2);
				break;
			}
		}
	}
	return operationStack.top();
}

string removeSpaces(string infix)
{
    string out = "";
	int size = infix.size();
    for (int i = 0; i < size; i++)
    {
        if (infix[i] != ' ')
        {
            out += infix[i];
        }
    }
    return out;
}

int precedence(char c)
{
	switch (c)
	{
	case '*':
	case '/':
		return 1;
	case '+':
	case '-':
		return 0;
	default:
		exit(1);
	}
}