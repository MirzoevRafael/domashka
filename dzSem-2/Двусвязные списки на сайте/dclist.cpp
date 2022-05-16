#include <iostream>
#include "dclist.h"

using namespace std;

void add(list& sum, int data)
{
    elem* newel = new elem;
    newel->value = data;
    sum.count++;
    if (!sum.first)
    {
        sum.first = sum.last = newel;
    }
    else
    {
        newel->prev = sum.last;
        sum.last->next = newel;
        sum.last = newel;
    }
}

void clear(list& sum)
{
    elem* rem;
    while (sum.first)
    {
        rem = sum.first;
        sum.first = sum.first->next;
        delete rem;
    }
    sum.last = nullptr;
    sum.count = 0;
}

void show_list(const list& sum, bool reversed)
{
    elem* curr = reversed ? sum.last : sum.first;
    if (!curr) cout << "Список пуст\n";
    else while (curr)
    {
        elem* cmp = reversed ? sum.first : sum.last;
        cout << curr->value << ((curr == cmp) ? "\n" : "");
        curr = reversed ? curr->prev : curr->next;
    }
}

void fill_list(list& sum, char* num)
{
    for (int i = 0; i < strlen(num); i++) add(sum, num[i] - '0');
}

void addition(list& sum, char* num1, char* num2)
{
    fill_list(sum, num1);
    elem* curr = sum.last;
    int value;
    for (int i = strlen(num2) - 1; i >= 0; i--)
    {
        value = num2[i] - '0';
        curr->value = curr->value + value;
        if (curr->prev) curr->prev->value = curr->prev->value + (curr->value / 10);
        curr->value = curr->value % 10;
        curr = curr->prev;
    }
    if (sum.first->value == 0)
    {
        elem* del = sum.first;
        sum.first = sum.first->next;
        delete del;
    }
    cout << endl;
}