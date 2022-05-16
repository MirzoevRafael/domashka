#include  <iostream>
#include <fstream>
#include "trees.h"

using namespace std;

int parse_int(char* num)
{
	if (!num) return NULL;
	int x = 0;
	for (int i = 0; i < strlen(num); i++)
	{
		if (num[i] == ' ') i++;
		x += (num[i] - '0') * pow(10, strlen(num) - i - 1);
	}
	return x;
}

void add_by_mark(tree& students, node*& head, char* name, int mark)
{
	node* elem = new node;
	elem->name = name;
	elem->mark = mark;
	if (!head)
	{
		head = elem;
		return;
	}

	node* curr = head;
	while (curr)
	{
		if (mark == curr->mark)
		{
			if (strcmp(name, curr->name) > 0)
			{
				elem->right = curr->right;
				curr->right = elem;
				students.height++;
				return;
			}
			if (strcmp(name, curr->name) < 0)
			{
				elem->left = curr->left;
				curr->left = elem;
				students.height++;
				return;
			}
		}
		if (mark > curr->mark)
		{
			if (curr->right)
			{
				curr = curr->right;
			}
			else
			{
				curr->right = elem;
				students.height++;
				return;
			}
		}
		if (mark < curr->mark)
		{
			if (curr->left)
			{
				curr = curr->left;
			}
			else
			{
				curr->left = elem;
				students.height++;
				return;
			}
		}
	}
}

void add_by_name(tree& students, node*& head, char* name, int mark)
{
	node* elem = new node;
	elem->name = name;
	elem->mark = mark;
	if (!head)
	{
		head = elem;
		return;
	}

	node* curr = head;
	while (curr)
	{
		if (strcmp(name, curr->name) == 0)
		{
			if (mark > curr->mark)
			{
				elem->right = curr->right;
				curr->right = elem;
				students.height++;
				return;
			}
			if (mark < curr->mark)
			{
				elem->left = curr->left;
				curr->left = elem;
				students.height++;
				return;
			}
		}
		if (strcmp(name, curr->name) > 0)
		{
			if (curr->right)
			{
				curr = curr->right;
			}
			else
			{
				curr->right = elem;
				students.height++;
				return;
			}
		}
		if (strcmp(name, curr->name) < 0)
		{
			if (curr->left)
			{
				curr = curr->left;
			}
			else
			{
				curr->left = elem;
				students.height++;
				return;
			}
		}
	}
}

void show_tree_ordered(node* head)
{
	if (!head) return;
	show_tree_ordered(head->left);
	cout << head->name << head->mark << "<br>\n";
	show_tree_ordered(head->right);
}

void clear(node*& head)
{
	if (!head) return;
	if (head->left) clear(head->left);
	if (head->right) clear(head->right);
	delete head;
}

void fill_by_mark(node*& head, tree& students)
{
	ifstream f;
	f.open("_students");
	while (!f.eof())
	{
		char* buff = new char[256];
		char* temp;
		f.getline(buff, 256);
		char* name = strtok_s(buff, "|", &temp);
		int mark = parse_int(strtok_s(NULL, "|", &temp));
		add_by_mark(students, head, name, mark);
	}
}

void fill_by_name(node*& head, tree& students)
{
	ifstream f;
	f.open("_students");
	while (!f.eof())
	{
		char* buff = new char[256];
		char* temp;
		f.getline(buff, 256);
		char* name = strtok_s(buff, "|", &temp);
		int mark = parse_int(strtok_s(NULL, "|", &temp));
		add_by_name(students, head, name, mark);
	}
}

void find_by_name(node* head, char letter, bool& check)
{
	if (!head) return;
	find_by_name(head->left, letter, check);
	if ((head->name[0]) == letter)
	{
		check = true;
		cout << head->name << head->mark << "<br>\n";
	}
	find_by_name(head->right, letter, check);
}