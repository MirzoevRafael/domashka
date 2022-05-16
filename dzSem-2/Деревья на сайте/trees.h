#pragma once

struct node
{
	char* name = new char[128];
	int mark;
	node* left = nullptr;
	node* right = nullptr;
};

struct tree
{
	int* height = 0;
	node* root = nullptr;
};

int parse_int(char* num);

void add_by_mark(tree& students, node*& head, char* name, int mark);

void add_by_name(tree& students, node*& head, char* name, int mark);

void show_tree_ordered(node* head);

void clear(node*& head);

void fill_by_mark(node*& head, tree& students);

void fill_by_name(node*& head, tree& students);

void find_by_name(node* head, char letter, bool& check);