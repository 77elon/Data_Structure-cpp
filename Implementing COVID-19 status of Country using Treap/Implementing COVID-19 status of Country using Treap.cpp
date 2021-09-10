#include <iostream>
#include <string>

using namespace std;


class Corona_World
{
public:
	string world; // key 
	int infect;
	int death;
	double death_rate; // priority

	Corona_World(const string Iworld = " ", int Iinfect = 0, int Ideath = 0)
		:world(Iworld), infect(Iinfect), death(Ideath)
	{
		death_rate = ((double)death / (double)infect) * 100;
	}

};

template <class T>
class TreapNode
{
public:
	double priority = NULL;
	string key = " ";

	TreapNode* left, * right;

	TreapNode(const T& info)
	{
		left = NULL;
		right = NULL;
		priority = info.death_rate;
		key = info.world;
	}
};

template <class T>
class Treap // function
{
public:

	void Right_Rotate(TreapNode<T>*& node)
	{
		TreapNode<T>* temp1, * temp2;
		temp1 = node->left;
		temp2 = node->left->right;

		temp1->right = node;

		temp1->right->left = temp2;

		node = temp1;
	}

	void Left_Rotate(TreapNode<T>*& node)
	{
		TreapNode<T>* temp1, * temp2;
		temp1 = node->right;
		temp2 = node->right->left;

		temp1->left = node;

		temp1->left->right = temp2;

		node = temp1;
	}

	void Insert_Node(TreapNode<T>*& Inode, const T& info)
	{
		TreapNode<T>* node = new TreapNode<T>(info);
		if (Inode == NULL) // generate object
		{
			Inode = node;
		}
		else
		{
			if (Inode->key < node->key)
			{
				Insert_Node(Inode->right, info);
				//need left rotate
				if (Inode->right != NULL && Inode->priority < Inode->right->priority)
				{
					Left_Rotate(Inode);
				}
			}
			else
			{
				Insert_Node(Inode->left, info);
				//need right rotate
				if (Inode->left != NULL && Inode->priority < Inode->left->priority)
				{
					Right_Rotate(Inode);
				}
			}
		}
	}

	void Search_Node(TreapNode<T>*& node, string info)
	{
		if (node == NULL)
		{
			return;
		}
		if (node->key == info)
		{
			cout << node->key << " found." << endl;
			return;
		}
		else if (node->key < info)
		{
			cout << node->key << " found." << endl;
			Search_Node(node->right, info);
		}
		else
		{
			cout << node->key << " found." << endl;
			Search_Node(node->left, info);
		}
	}

	void Delete_Node(TreapNode<T>*& node)
	{
		if (node == NULL)
		{
			return;
		}
		else
		{
			if (node->left == NULL && node->right == NULL)
			{
				delete node;
				node = NULL;
			}
			else if (node->left != NULL && node->right != NULL)
			{
				node->priority = -INFINITY;

				if (node->left->priority < node->right->priority)
				{
					Left_Rotate(node);
					Delete_Node(node->left);
				}
				else
				{
					Right_Rotate(node);
					Delete_Node(node->right);
				}
			}
			else if (node->left == NULL)
			{
				TreapNode<T>* temp1 = node->right;
				node->right = node;
				node = temp1;

			}
			else if (node->right == NULL)
			{
				TreapNode<T>* temp1 = node->left;
				node->left = node;
				node = temp1;
			}
		}
	}
};

int main()
{
	Treap<Corona_World> Treap;
	TreapNode<Corona_World>* node = NULL;

	Treap.Insert_Node(node, Corona_World("China", 81171, 3277)); //priority : 5
	Treap.Insert_Node(node, Corona_World("Italy", 63927, 6077)); //priority : 9
	Treap.Insert_Node(node, Corona_World("USA", 43214, 533)); //priority : 2
	Treap.Insert_Node(node, Corona_World("Spain", 33089, 2182)); //priority : 7
	Treap.Insert_Node(node, Corona_World("Germany", 29056, 123)); //priority : 1
	Treap.Insert_Node(node, Corona_World("Iran", 23049, 1812));  //priority : 8
	Treap.Insert_Node(node, Corona_World("France", 19856, 860));  //priority : 6
	Treap.Insert_Node(node, Corona_World("Korea", 9037, 120)); //priority : 3
	Treap.Insert_Node(node, Corona_World("UAE", 12356, 423)); //priority : 4
	Treap.Insert_Node(node, Corona_World("Russia", 43241, 4345)); //priority : 10

	cout << "Please enter a country to search" << endl;
	string temp1, temp2, temp3;
	temp3 = node->key;

	cin >> temp1;
	Treap.Search_Node(node, temp1);

	cout << "Deleting Root Node " << node->key << endl;
	Treap.Delete_Node(node);

	while (true)
	{
		cout << "Please enter a country to search" << endl;
		cin >> temp2;
		if (temp2 != temp3)
		{
			break;
		}
	}
	Treap.Search_Node(node, temp2);
}