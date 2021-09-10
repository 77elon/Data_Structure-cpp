#include <iostream>
#include <stack>
 
using namespace std;

class Whiteboard
{
private:
	int n = 0;
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
	char **ary;
public:
	friend int main();
	void Input_Num(int input);
	void initializeBoard();
	void Print_Array();
	void Find_WhiteBlock(int n1, int n2);
	void Calc_Array();
};

void Whiteboard::Input_Num(int input)
{
	n = input;
}

void Whiteboard :: initializeBoard()
{
	char** block = new char* [n + 2]; // creating array
	for (int i = 0; i < n + 2; i++)
	{
		block[i] = new char[n + 2]; 
		//memset(block[i], 0, sizeof(char) * n + 2);
	}

	for (int num1 = 0; num1 < n + 2; num1++) // element set
	{
		for (int num2 = 0; num2 < n + 2; num2++)
		{
			if (num1 == 0 || num1 == n + 1 || num2 == 0 || num2 == n + 1)
			{
				block[num1][num2] = 'B';
			}
			else
			{
				if (rand() % 2)
				{
					block[num1][num2] = 'W';
				}
				else
				{
					block[num1][num2] = 'B';
				}
			}
		}
	}
	ary = block;
}

void Whiteboard::Print_Array() 
{
	for (int num1 = 0; num1 < n + 2; num1++) // Black -> ■, White -> □
	{
		for (int num2 = 0; num2 < n + 2; num2++)
		{
			if (ary[num1][num2] == 'B')
			{
				cout.width(2);
				cout << "■";
			}
			else
			{
				cout.width(2);
				cout << "□";
			}
			//cout << ary[num1][num2]; //■ □
		}
		cout << endl;
	}
	cout << endl;
}

void Whiteboard::Find_WhiteBlock(int n1, int n2)
{
	if (ary[n1][n2] == 'W') //find White
	{
		ary[n1][n2] = 'B'; //White -> Black
		Find_WhiteBlock(n1 + 1, n2);
		Find_WhiteBlock(n1 - 1, n2);
		Find_WhiteBlock(n1, n2 + 1);
		Find_WhiteBlock(n1, n2 - 1);
		count1++; //White Element Check
	}
}

void Whiteboard::Calc_Array()
{
	stack <int> result, result1; //dynamic element
	int temp1 = 0;
	int temp2 = 0;
	for (int num1 = 1; num1 < n + 2; num1++)
	{
		for (int num2 = 1; num2 < n + 2; num2++)
		{
			temp1 = count3; //check count3 
			temp2 = count1; //check count1, For any array calculation
			if (ary[num1][num2] == 'W')
			{
				count4++;
				count2 = count1;
			}

			Find_WhiteBlock(num1, num2); //element find

			count3 = count1 - count2;
			if (temp1 != count3 || temp2 != count1)
			{
				result.push(count3); //white element result push
			}
		}
	}

	while(!result.empty())
	{
		result1.push(result.top()); //stack reverse
		result.pop();
	}
	cout << count4 << " white areas of ";
	while(result1.size() != 2)
	{
		cout << result1.top() << ", ";
		result1.pop();
	}

	cout << result1.top();
	result1.pop();

	cout <<" and ";
	cout << result1.top();
	cout << " cells." << endl;

}

int main()
{
	Whiteboard Object1;
	int ary_size;
	int chk1 = 0;
	cout << "Please Input Array Size!" << endl;
	cin >> ary_size;
	Object1.Input_Num(ary_size);
	cout << "Creating Array" << endl;
	Object1.initializeBoard();
	cout << "Printing Array" << endl; 
	Object1.Print_Array();
	cout << "Calculating Array" << endl;
	Object1.Calc_Array();
	cout << "Printing Result" << endl;
	Object1.Print_Array();

}


