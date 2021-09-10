#include <iostream> 
#include <stdlib.h>
#include <string>
#include <libxl.h>
#include <atlbase.h> 
#include <atlstr.h> 
#include <comutil.h>
#include <locale.h>
#include <vector>

#pragma comment(lib, "libxl.lib")

using namespace libxl;
using namespace std;

#define V 121
#define Trans 1

char* ConvertWCtoC(const wchar_t* str)
{
	char* pStr;
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	pStr = new char[strSize];
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}

wchar_t* ConverCtoWC(const char* str)
{
	wchar_t* pStr;
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
	pStr = new WCHAR[strSize];
	MultiByteToWideChar(CP_ACP, 0, str, (int)strlen(str) + 1, pStr, strSize);
	return pStr;
}

struct Station
{
	string station;
	int num = 0;
	int lane = 1;
	void show_data()
	{
		cout << station;
		cout.width(5);
		cout << num;
		cout.width(3);
		cout << lane << endl;
	}
}station;

vector<Station> stor;
int Index;
int Dest_index;
int Time[V][V];
const char* cmp1 = "◇";
wchar_t* cmp = ConverCtoWC(cmp1);
vector<int> transfer = { 0, 1, 3, 5, 7, 10, 12, 14, 20, 32, 35, 43, 53, 54, 58, 59, 74, 75, 76, 85, 107, 108, 109, 112, 119 };
int lane1, lane2;

int Transfer_Point(int ary[], int src)
{
	int min = 0;
	int temp1 = 30;
	for (int i = 0; i < 25; i++)
	{
		if (ary[transfer[i]] < temp1 && ary[transfer[i]] != 0 && lane1 == stor[transfer[i]].lane)
		{
			temp1 = ary[transfer[i]];
			min = transfer[i];
		}
	}
	return min;
}

int Radway_return(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
	{
		if (sptSet[v] == false && dist[v] <= min)
		{
			static_cast<void>(min = dist[v]);
			min_index = v;
		}
	}
	return min_index;
}

void Print_Way(int parent[], int src, int dest)
{
	if (parent[dest] == -1)
	{
		return;
	}
	Print_Way(parent, src, parent[dest]);// transfer after output...
	if (stor[dest].station != stor[parent[dest]].station)
	{
		cout << stor[dest].station << "  ";
	}
}

void Print_Weight(int dist[], int parent[], int src, int dest)
{
	if (lane1 == lane2)
	{
		cout << "The travel time between " << stor[src].station << " and " << stor[dest].station << " is " << dist[dest] << " minutes." << endl;
		cout << "There is no transfer. Two stations are Line " << lane1 << "." << endl;
		Print_Way(parent, src, dest);
	}
	else
	{
		//dist[dest] + 6 == Transfer time
		cout << "The travel time between " << stor[src].station << " and " << stor[dest].station << " is " << dist[dest] + 6 << " minutes." << endl;
		int point = Transfer_Point(dist, src);
		int point2 = 0;
		cout << stor[src].station << "  ";
		Print_Way(parent, src, point);
		if (stor[point].lane != lane1)
		{
			point2 = Transfer_Point(dist, point);
		}
		Print_Way(parent, src, dest);
		cout << endl;
		if (point2 == 0)
		{
			cout << "You have to transfer at " << stor[point].station << " station." << endl;
		}
		else
		{
			Print_Way(parent, src, point2);
			cout << "You have to transfer at " << stor[point].station << ", " << stor[point2].station << " station." << endl;
		}
	}
}

void dijkstra(int graph[V][V], int src, int dest)
{
	int dist[V];

	bool sptSet[V];

	int parent[V];

	for (int i = 0; i < V; i++)
	{
		parent[i] = -1;
		static_cast<void>(dist[i] = INT_MAX);
		sptSet[i] = false;
	}

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++)
	{

		int u = Radway_return(dist, sptSet);
		sptSet[u] = true;

		if (dist[0] < dist[112])
		{
			dist[112] = dist[0];
		}
		else
		{
			dist[0] = dist[112];
		}
		if (dist[1] < dist[10])
		{
			if (dist[10] > dist[53])
			{
				if (dist[53] > dist[1])
				{
					dist[53] = dist[1];
					dist[10] = dist[1];
				}
				else
				{
					dist[1] = dist[53];
					dist[10] = dist[53];
				}
			}
		}
		else //dist[1] > dist[10]
		{
			if (dist[1] > dist[53])
			{
				if (dist[10] > dist[53])
				{
					dist[1] = dist[53];
					dist[10] = dist[53];
				}
				else //dist[10] < dist[53]
				{
					dist[1] = dist[10];
					dist[53] = dist[10];
				}
			}
		}
		if (dist[12] < dist[75])
		{
			dist[75] = dist[12];
		}
		else
		{
			dist[12] = dist[75];
		}

		if (dist[5] < dist[107])
		{
			dist[107] = dist[5];
		}
		else
		{
			dist[5] = dist[107];
		}
		if (dist[14] < dist[108])
		{
			dist[108] = dist[14];
		}
		else
		{
			dist[14] = dist[108];
		}
		if (dist[20] < dist[54])
		{
			dist[54] = dist[20];
		}
		else
		{
			dist[20] = dist[54];
		}
		if (dist[32] < dist[85])
		{
			dist[85] = dist[32];
		}
		else
		{
			dist[32] = dist[85];
		}
		if (dist[35] < dist[119])
		{
			dist[119] = dist[35];
		}
		else
		{
			dist[35] = dist[119];
		}
		if (dist[43] < dist[59])
		{
			dist[59] = dist[43];
		}
		else
		{
			dist[43] = dist[59];
		}
		if (dist[76] < dist[109])
		{
			dist[109] = dist[76];
		}
		else
		{
			dist[76] = dist[109];
		}
		if (dist[3] < dist[74])
		{
			dist[74] = dist[3];
		}
		else
		{
			dist[3] = dist[74];
		}
		if (dist[7] < dist[58])
		{
			dist[58] = dist[7];
		}
		else
		{
			dist[7] = dist[58];
		}
		for (int v = 0; v < V; v++)
		{
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
			{
				if (v == 75 || v == 108)
				{
					parent[v] = u;
					dist[v] = dist[u] + graph[u][v] + stor[v].num;
					continue;
				}
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];
			}
		}
	}
	Print_Weight(dist, parent, src, dest);
}

void Iterator_return(const string I1, const string I2)
{
	unsigned int i = 0;
	int temp1 = 0, temp2 = 0;
	while (true)
	{
		if (i > V)
		{
			Index = temp1;
			Dest_index = temp2;
			break;
		}
		else if (lane1 == lane2)
		{
			if (stor[i].station == I1)
			{
				temp1 = i;
				i++;
				continue;
			}
			else if (stor[i].station == I2 && stor[i].lane == stor[temp1].lane)
			{
				Index = temp1;
				Dest_index = i;
				break;
			}
			if (stor[i].station == I2)
			{
				temp2 = i;
				i++;
				continue;
			}
			else if (stor[i].station == I1 && stor[i].lane == stor[temp2].lane)
			{
				Index = i;
				Dest_index = temp2;
				break;
			}
			else
			{
				i++;
				continue;
			}
		}
		else
		{
			if (stor[i].station == I1)
			{
				temp1 = i;
				i++;
				continue;
			}
			else if (stor[i].station == I2)
			{
				temp2 = i;
				i++;
				continue;
			}
			if (stor[i].station == I1 && stor[i].lane == stor[temp2].lane)
			{
				Index = i;
				Dest_index = temp2;
				break;
			}
			if (stor[i].station == I2 && stor[i].lane == stor[temp1].lane)
			{
				Index = temp1;
				Dest_index = i;
				break;
			}
			else
			{
				i++;
				continue;
			}
		}
	}
}

void Trans_connectivity(int ary[V][V], int num1, int num2)
{
	ary[num1][num2] = Trans;
	ary[num2][num1] = Trans;
}

void init()
{
	Book* book = xlCreateBook();
	_wsetlocale(LC_ALL, L"korean");

	if (book->load(L"1.xls"))
	{
		Sheet* sheet = book->getSheet(0);
		if (sheet)
		{
			int temp = 0;
			for (int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
			{
				int col = sheet->firstCol();
				CellType cellType = sheet->cellType(row, col);
				const wchar_t* s = sheet->readStr(row, col);
				if (!wcsncmp(s, cmp, 1))
				{
					temp++;
					continue;
				}
				switch (cellType)
				{
				case CELLTYPE_STRING:
				{

					station.station = ConvertWCtoC(s);
					if (temp == 3 || temp == 4)
					{
						station.lane = 2;
					}
					else if (temp > 4)
					{
						station.lane = temp - 2;
					}
					else
					{
						station.lane = temp;
					}
					double d = sheet->readNum(row, col + 3);
					station.num = (int)d;
					stor.push_back(station);
					break;
				}
				case CELLTYPE_BLANK: std::wcout << "[blank]"; break;
				case CELLTYPE_ERROR: std::wcout << "[error]"; break;
				}
			}
		}
	}

	book->release();

	int n = 0;
	int m = 0;
	while (n < V) // array reset;
	{
		Time[n][n] = 0;
		n++;
	}

	n = 1;
	while (n < V)
	{
		Time[m][n] = stor[n].num;
		Time[n][m] = stor[n].num;
		m++;
		n++;
	}

	Trans_connectivity(Time, 0, 112);

	Trans_connectivity(Time, 1, 10);
	Trans_connectivity(Time, 10, 53);

	Trans_connectivity(Time, 3, 74);

	Trans_connectivity(Time, 12, 75);

	Trans_connectivity(Time, 5, 107);

	Trans_connectivity(Time, 7, 58);

	Trans_connectivity(Time, 14, 108);

	Trans_connectivity(Time, 20, 54);

	Trans_connectivity(Time, 32, 85);

	Trans_connectivity(Time, 35, 119);

	Trans_connectivity(Time, 43, 59);

	Trans_connectivity(Time, 76, 109);
}

int main()
{
	init();
	string input1;
	string input2;
	string station1, station2;

	cout << "Please enter Source Point. ex) 2호선 시청 " << endl;
	cin >> input1; cin >> station1;
	lane1 = (int)input1.front() - 48;

	cout << "Please enter Destination Point. ex) 2호선 신도림 " << endl;
	cin >> input2; cin >> station2;
	lane2 = (int)input2.front() - 48;

	Iterator_return(station1, station2);

	dijkstra(Time, Index, Dest_index);
}
