#include <iostream>
#include <stack>

using namespace std;

template <class T>
void Inumber(stack<T> &o1, int Input)
{
	int a;
	int check1 = 1;
	while (Input > 1)
	{
		while (Input > check1)
		{
			check1 *= 10;
		}
		check1 /= 10;
		while (check1 >= 1)
		{
			a = Input / check1;
			o1.push(a);
			Input = Input - (a * check1);
			check1 /= 10;
		}
	}
}

template <class T>
void calc(stack<T>& o1, stack<T>& o2, stack<T>& o3)
{
	int result, temp = 0;

	while(true)
	{
		if (o1.empty() && o2.empty())
		{
			break;
		}
		else if (o1.empty())
		{
			result = o2.top() + temp;
			o3.push(result);
			o2.pop();
			continue;
		}
		else if (o2.empty())
		{
			result = o1.top() + temp;
			o3.push(result);
			o1.pop();
			continue;
		}

		if (o1.top() + o2.top() >= 10)
		{
			result = ((o1.top() + o2.top()) % 10) + temp;
			o3.push(result);
			temp = 1;
			o1.pop();
			o2.pop();
		}
		else if (temp == 1)
		{
			result = ((o1.top() + o2.top()) + temp);
			o3.push(result);
			temp = 0;
			o1.pop();
			o2.pop();
		}
		else
		{
			result = (o1.top() + o2.top());
			o3.push(result);
			o1.pop();
			o2.pop();
		}
	}
}

template <class T>
void Print_Stack(stack <T>& o1)
{
	while (!o1.empty())
	{
		cout << o1.top() << endl;
		o1.pop();
	}
}

int main()
{
	//stack1 = integer1, stack2 = integer2, stack3 = result;
	stack <int> Int1;
	stack <int> Int2;
	stack <int> Result;
	int num1 = 0, num2 = 0;

	while (true)
	{
		cout << "Please Input Numbers" << endl;

		cin >> num1;
		cin >> num2;

		if (num1 > 141006540 || num2 > 141006540)
		{
			cout << "The number is too large" << endl;
			cin.clear();
			continue;
		}
		else
		{
			Inumber(Int1, num1);
			Inumber(Int2, num2);
			cout << "Calculating." << endl;
			calc(Int1, Int2, Result);
			cout << "Print the stack." << endl;
			Print_Stack(Result);
			break;
		}
	}
}