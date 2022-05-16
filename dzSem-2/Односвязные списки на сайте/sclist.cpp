#include <iostream>
#include "sclist.h"

using namespace std;

int parse_int(char* str)
{
	if (!str) return NULL;

	int res = 0, rank = -1;

	for (int i = strlen(str) - 1; i >= 0; i--)
	{
		rank++;
		res += (str[i] - '0') * pow(10, rank);
	}
	return res;
}

void add(elem*& first, int value)
{
	elem* newel = new elem;
	newel->value = value;
	if (first)
	{
		elem* curr = first;
		while (curr->next)
		{
			curr = curr->next;
		}
		curr->next = newel;
	}
	else
	{
		first = newel;
	}
}

void clear(elem*& first)
{
	while (first)
	{
		elem* del = first;
		first = first->next;
		delete del;
	}
}

void show_list(elem* list)
{
	elem* curr = list;
	if (!curr) return;
	else while (curr)
	{
		cout << curr->value << (curr->next ? " " : "\n");
		curr = curr->next;
	}
}

bool check_repeat(elem* list, int num)
{
	elem* curr = list;
	while (curr)
	{
		if (num == curr->value) return false;
		curr = curr->next;
	}
	return true;
}

void add_by_check(elem*& list, char* str)
{

	char* value;
	char* temp;
	value = strtok_s(str, " ", &temp);
	while (value)
	{
		if (check_repeat(list, parse_int(value))) add(list, parse_int(value));
		value = strtok_s(NULL, " ", &temp);
	}
}