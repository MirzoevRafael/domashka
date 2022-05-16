#include <iostream>
#include <fstream>
#include "string.h"
#include "queue.h"

using namespace std;

client createElem(char* name, char* gender, char* age, char* job, char* wage, char* purp)
{
	client user;
	user.name = name;
	user.gender = gender;
	user.age = age;
	user.job = job;
	user.wage = wage;
	user.purp = purp;

	return user;
}

void enqueue(queue*& q, char* name, char* gender, char* age, char* job, char* wage, char* purp)
{
	client user = createElem(name, gender, age, job, wage, purp);
	elem* newElem = new elem;
	newElem->user = user;
	if (q->size == 0)
	{
		q->head = q->tail = newElem;
	}
	else
	{
		q->tail->next = newElem;
		q->tail = newElem;
	}
	q->size++;
}

bool dequeue(queue*& q, client& user)
{
	if (q->size == 0) return false;

	elem* rem = q->head;
	user = rem->user;
	q->head = q->head->next;
	delete rem;
	q->size--;

	return true;
}

void showQueue(queue*& q)
{
	int i = 0;
	if (q->size == 0) return;

	client user;
	while (dequeue(q, user))
	{
		cout << ++i << ". " << user.name << " " << user.gender << " " << user.age << " " << user.job << " " << user.wage << "<br>\n";
	}
}

void clear(queue*& q)
{
	while (q->size > 0)
	{
		elem* rem = q->head;
		q->head = q->head->next;
		q->size--;
		delete rem;
	}
}