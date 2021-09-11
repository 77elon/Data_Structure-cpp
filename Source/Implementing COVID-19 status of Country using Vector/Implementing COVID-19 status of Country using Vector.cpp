#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Corona_World
{
private:
	string world;
	string region;
	int infect, dead;
	double dead_rate;
	double infect_rate;
public:
	friend int main();

	Corona_World(const string Iworld = " ", int Iinfect = 0, int Idead = 0)
		: world(Iworld), infect(Iinfect), dead(Idead)
	{

	}
	void show_data()
	{
		if (world == "Iran" || world == "iran")
		{
			cout << region << "\t" << world << "\t" << infect << "  " << infect_rate << "\t" << dead << endl;
		}
		else
		{
			cout << region << "\t\t" << world << "\t" << infect << "  " << infect_rate << "\t" << dead << endl;
		}
	}
	string show_world()
	{
		return world;
	}
	string show_region()
	{
		return region;
	}
	int show_infect()
	{
		return infect;
	}
	int show_dead()
	{
		return dead;
	}
	double show_deadrate()
	{
		return dead_rate;
	}
	void Infectr_Check(const int allinfect)
	{
		infect_rate = (double)infect / (double)allinfect * 100;
	}
	void Deadr_Check(const int alldead)
	{
		dead_rate = (double)dead / (double)alldead * 100;
	}
	void World_Check()
	{
		if (world == "Korea" || world == "korea")
		{
			region = "Asia";
		}
		if (world == "China" || world == "china")
		{
			region = "Asia";
		}
		if (world == "Italy" || world == "italy")
		{
			region = "Europe";
		}
		if (world == "Spain" || world == "spain")
		{
			region = "Europe";
		}
		if (world == "Germany" || world == "germany")
		{
			region = "Europe";
		}
		if (world == "France" || world == "france")
		{
			region = "Europe";
		}
		if (world == "US" || world == "USA" || world == "us" || world == "usa")
		{
			region = "America";
		}
		if (world == "Iran" || world == "iran")
		{
			region = "Middle East";
		}
	}
};


void Vector_Print(vector<Corona_World>& v)
{

	cout << "Region" << "\t\tWorld" << "  Infector" << " Ratio" << "\tDead" << endl;
	vector<Corona_World> ::size_type i;
	for (i = 0; i < v.size(); i++)
	{
		v[i].show_data();
	}
}
void add_region(vector<Corona_World>& v)
{
	for (unsigned int i = 0; i < v.size(); i++)
	{
		v[i].World_Check();
	}
}
void add_deadrate(vector <Corona_World>& v)
{
	int result = 0;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		result += v[i].show_dead();
	}
	vector<Corona_World> ::size_type i = v.size();
	for (unsigned int n = 0; n < i; n++)
	{
		v[n].Deadr_Check(result);
	}
}
void add_infectrate(vector <Corona_World>& v)
{

	int result = 0;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		result += v[i].show_infect();
	}
	vector<Corona_World> ::size_type i = v.size();
	for (unsigned int n = 0; n < i; n++)
	{
		v[n].Infectr_Check(result);
	}
}


bool Region_Check(Corona_World c1, Corona_World c2)
{
	if (c1.show_region() == c2.show_region())
	{
		return c1.show_world() >  c2.show_world();
	}

	return c1.show_region() < c2.show_region();

}
bool Infect_Check(Corona_World c1, Corona_World c2)
{
	return c1.show_infect() > c2.show_infect();
}
bool Dead_Check(Corona_World c1, Corona_World c2)
{
	return c1.show_dead() > c2.show_dead();
}
bool Deadrate_Check(Corona_World c1, Corona_World c2)
{
	return c1.show_deadrate() > c2.show_deadrate();
}

void Region_Sort(vector <Corona_World>& v)
{
	sort(v.begin(), v.end(), Region_Check);
}
void Infect_Sort(vector<Corona_World>& v)
{
	sort(v.begin(), v.end(), Infect_Check);
}
void Dead_Sort(vector<Corona_World>& v)
{
	sort(v.begin(), v.end(), Dead_Check);
}
void Deadrate_Sort(vector<Corona_World>& v)
{
	sort(v.begin(), v.end(), Deadrate_Check);
}

void Check_world(vector<Corona_World>& v, const string& str)
{
	vector<Corona_World> ::size_type i;
	for (i = 0; i < v.size(); i++)
	{
		if (v[i].show_world() == str)
		{
			v.erase(v.begin() + i);
		}
	}
}


int main()
{
	int world_num;
	string check1;
	string Check_Iworld;
	cout << "How many countries do you want to enter?" << endl;
	cin >> world_num;
	Corona_World Itemp;
	vector<Corona_World> vworld;
	cout << "Please enter as many country, infector, and death as the initial number of declarations" << endl;

	for (int num1 = 0; num1 < world_num; num1++) 
	{
		cin >> Itemp.world >> Itemp.infect >> Itemp.dead;
		vworld.push_back(Itemp);
	}

	cout << "Calculate the mortality" << endl;
	add_deadrate(vworld);
	cout << "Calculate the infection rate" << endl;
	add_infectrate(vworld);
	cout << "Check the region" << endl;
	add_region(vworld);

	cout << "Print the calculated value" << endl;
	Vector_Print(vworld);

	cout << "Outputs in the calculated region order." << endl;
	Region_Sort(vworld);
	Vector_Print(vworld);
	cout << "Outputs in the calculated infector order." << endl;
	Infect_Sort(vworld);
	Vector_Print(vworld);
	cout << "Outputs in the calculated death order." << endl;
	Dead_Sort(vworld);
	Vector_Print(vworld);
	cout << "Outputs in the calculated dead rate order." << endl;
	Deadrate_Sort(vworld);
	Vector_Print(vworld);

	cout << "Do you want to delete the country? (Yes, No)" << endl;
	cin >> check1;
	if (check1 == "No")
	{
		return 0;
	}
	else if (check1 == "Yes")
	{
		while (true)
		{
			cout << "Please enter the country you want to delete" << endl;
			cin >> Check_Iworld;
			Check_world(vworld, Check_Iworld);
			Vector_Print(vworld);
			cout << "Do you want to delete more countries? (Yes, No)" << endl;
			cin >> check1;
			if (check1 == "Yes")
			{
				continue;
			}
			else if (check1 == "No")
			{
				vworld.clear();
				break;
			}
		}
	}
	find(vworld.begin(), vworld.end(), )
}
