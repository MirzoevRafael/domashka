#pragma once
struct client
{
	char* name = new char[100];
	char* gender = new char[10];
	char* age = new char[4];
	char* job = new char[100];
	char* wage = new char[100];
	char* purp = new char[9];
};

struct elem
{
	client user;
	elem* next = nullptr;
};

struct queue
{
	elem* head = nullptr;
	elem* tail = nullptr;
	size_t size = 0;
};

client createElem(char* name, char* gender, char* age, char* job, char* wage, char* purp);

void enqueue(queue*& q, char* name, char* gender, char* age, char* job, char* wage, char* purp);

bool dequeue(queue*& q, client& user);

void showQueue(queue*& q);

void clear(queue*& q);