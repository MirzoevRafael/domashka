#pragma once

struct elem
{
    int value;
    elem* next = nullptr;
    elem* prev = nullptr;
};

struct list
{
    elem* first = nullptr;
    elem* last = nullptr;
    int count = 0;
};

void add(list& sum, int data);

void clear(list& sum);

void show_list(const list& sum, bool reversed);

void fill_list(list& sum, char* num);

void addition(list& sum, char* num1, char* num2);