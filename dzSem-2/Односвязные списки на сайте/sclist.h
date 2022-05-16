#pragma once

struct elem
{
	int value;
	elem* next = nullptr;
};

int parse_int(char* str);

void add(elem*& first, int value);

void clear(elem*& first);

void show_list(elem* list);

bool check_repeat(elem* list, int num);

void add_by_check(elem*& list, char* str);