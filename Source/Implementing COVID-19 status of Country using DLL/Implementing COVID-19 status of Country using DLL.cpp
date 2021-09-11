#include <iostream>
#include <string>

using namespace std;


class Corona_World
{
private:

public:
	string world;
	int infect;
	int death;
	double death_rate;

	Corona_World(const string Iworld = " ", int Iinfect = 0, int Ideath = 0)
		:world(Iworld), infect(Iinfect), death(Ideath)
	{
		death_rate = ((double)death / (double)infect) * 100;
	}

};

template<class T>
class DLLNode
{
public:
	T info;
	DLLNode* next;
	DLLNode* prev;

	DLLNode()
	{
		next = NULL;
		prev = NULL;
	}
	DLLNode(const T& Index, DLLNode* Inext = NULL, DLLNode* Iprev = NULL)
	{
		info = Index;
		next = Inext;
		prev = Iprev;
	}


	void Print_Node()
	{
		cout.width(10);
		cout << info.world;
		cout.width(10);
		cout << info.infect;
		cout.width(10);
		cout << info.death;
		cout.width(15);
		cout << info.death_rate << endl;
	}
	bool World_Check(const string o1)
	{
		return info.world == o1;
	}
};

template <class T>
class DLL
{
public:
	DLLNode<T>* head = NULL, * tail = NULL;
	DLL()
	{
	}
	~DLL()
	{
		for (DLLNode<T>* p = NULL; !p;)
		{
			p = head -> next;
			delete head;
			head = p;
		}
	}

	void AddtoDLLSorted(const T& c1)
	{
		DLLNode <T>* temp = new DLLNode<T>(c1, NULL, NULL);
		DLLNode<T>* check1 = head;
		
		if (head == NULL)
		{
			head = tail = temp;
			head->next = NULL; //allocation
			head->prev = NULL;
		}
		else
		{
			if (check1->next == NULL) // Initialize 
			{
				if (check1->info.world < temp->info.world)
				{
					check1->next = temp;
					check1->next->prev = check1;
					return;
				}
				else
				{
					temp->next = check1;
					temp->next->prev = temp;
					head = temp;
					return;
				}
			}

			while (check1->next != NULL && check1->info.world < temp->info.world) // check1 < temp, scan
			{
				check1 = check1->next;
			}

			if (check1->info.world == head->info.world) // check1 > temp
			{
				temp->next = check1;
				temp->next->prev = temp;

				temp->prev = NULL;

				head = temp;

			}

			else if (check1 -> next == NULL && check1->info.world < temp->info.world) //check1 < temp, Logic
			{
				temp->next = NULL;

				check1->next = temp;
				check1->next->prev = check1;

			}

			else
			{
				temp->prev = check1->prev;

				temp->next = check1;
				temp->next->prev = temp;
				
				if (temp->prev != NULL)
				{
					temp->prev->next = temp;
				}
			}
		}
	}

	void deleteDLLSorted(const string& name)
	{

		DLLNode <T>* Temp = head;

		while (Temp != NULL)
		{

			if(Temp->World_Check(name)) //if(head -> info == name)
			{
				if (Temp->prev == NULL) // 1st element
				{
					if (Temp->next != NULL)
					{
						Temp->next->prev = NULL;
						head = Temp->next;
					}
				}
				else if (Temp->next == NULL) // last element
				{
					Temp->prev->next = NULL;
				}
				else
				{
					Temp->next->prev = Temp->prev;
					Temp->prev->next = Temp->next;
				}
			}
			Temp = Temp->next;
		}
	}


	void printDLLSorted()
	{	
		DLLNode <T>* print = head;
		while (print != NULL)
		{
			print->Print_Node();
			print = print->next;
		}
	}
};

void DLL_Print(DLL<Corona_World>& T)
{
	cout.width(10);
	cout << "Country";
	cout.width(10);
	cout << "Infected";
	cout.width(10);
	cout << "Death";
	cout.width(15);
	cout << "Death_Rate" << endl;
}


int main()
{
	string Temp1;
	string Temp2;
	DLL<Corona_World> DLLData;
	cout << "Please enter a country" << endl;

	DLLData.AddtoDLLSorted(Corona_World("China", 81171, 3277));
	DLLData.AddtoDLLSorted(Corona_World("Italy", 63927, 6077));
	DLLData.AddtoDLLSorted(Corona_World("USA", 43214, 533));
	DLLData.AddtoDLLSorted(Corona_World("Spain", 33089, 2182));
	DLLData.AddtoDLLSorted(Corona_World("Germany", 29056, 123));
	DLLData.AddtoDLLSorted(Corona_World("Iran", 23049, 1812));
	DLLData.AddtoDLLSorted(Corona_World("France", 19856, 860));
	DLLData.AddtoDLLSorted(Corona_World("Korea", 9037, 120));
	cout << "Print DLList" << endl;
	DLL_Print(DLLData);
	DLLData.printDLLSorted();

	for (; Temp2 != "No";)
	{
		cout << "Please enter a country you want to delete" << endl;
		cin >> Temp1;
		DLLData.deleteDLLSorted(Temp1);
		DLL_Print(DLLData);
		DLLData.printDLLSorted();

		cout << "Do you want to delete more countries? (Yes, No)" << endl;
		cin >> Temp2;

	}

}