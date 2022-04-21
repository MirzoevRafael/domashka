#include <iostream>
#include "stack.h"
using namespace std;

//Стэк для скобок
struct stack
{
	char value = NULL;
	int count = NULL;
	stack* next = nullptr;
};

//Стэк для неверно поставленных скобок
struct nums
{
	int num = NULL;
	nums* next = nullptr;
};

//Извлечение элемента из стэка
bool pop(stack*& text, char& value, int& count)
{
	if (!text) return false;

	stack* rem = text;
	value = text->value;
	count = text->count;
	text = text->next;

	delete rem;
	return true;
}

bool pop(nums*& elems, int& num)
{
	if (!elems) return false;

	nums* rem = elems;
	num = elems->num;
	elems = elems->next;

	delete rem;
	return true;
}

//Добавление элемента в стэк
void push(stack*& text, char value, int count)
{
	stack* newel = new stack;
	newel->value = value;
	newel->count = count;
	newel->next = text;
	text = newel;
}

void push(nums*& elems, int num)
{
	nums* newel = new nums;
	newel->num = num;
	newel->next = elems;
	elems = newel;
}

//"Подглядываем" элемент
char* peek(stack* text)
{
	if (!text) return nullptr;
	return &text->value;
}

//Выводим стэк
void showStruc(nums*& elems)
{
	int num;
	while (elems)
	{
		pop(elems, num);
		if (num != 0) cout << num << " ";
	}
	delete elems;
}

//Очищаем стэк
void clear(stack*& text)
{
	while (text)
	{
		stack* rem = text;
		text = rem->next;
		delete rem;
	}
}

void clear(nums*& elems)
{
	while (elems)
	{
		nums* rem = elems;
		elems = rem->next;
		delete rem;
	}
}

//Заполняем стэк скобками
void fillBrack(char ex[], stack*& text)
{
	for (int i = strlen(ex) - 1; i >= 0; i--)
	{
		if ((ex[i] == '(') || (ex[i] == '[') || (ex[i] == '{') || (ex[i] == '<') || (ex[i] == ')') || (ex[i] == ']') || (ex[i] == '}') || (ex[i] == '>'))
			push(text, ex[i], i + 1);
	}
}

//Проверяем правильность расставления скобок
void checkBrack(stack*& text)
{
	int lrdCount = 0, lsqCount = 0, lfgCount = 0, lagCount = 0, lrdNum = 0, lsqNum = 0, lfgNum = 0, lagNum = 0, trashNum = 0; //переменные указывающие количество и номер всех открывающих скобок
	int rrdCount = 0, rsqCount = 0, rfgCount = 0, ragCount = 0, rrdNum = 0, rsqNum = 0, rfgNum = 0, ragNum = 0; //переменные указывающие количество и номер всех закрывающих скобок
	char value, trash;
	bool check = true;
	nums* elems = new nums;

	cout << "Неверно поставленные скобки: ";

	while (text)
	{
		if (lrdCount < rrdCount) push(elems, rrdNum); rrdNum = lrdNum;
		if (lsqCount < rsqCount) push(elems, rsqNum); rsqNum = lsqNum;
		if (lfgCount < rfgCount) push(elems, rfgNum); rrdNum = lfgNum;
		if (lagCount < ragCount) push(elems, ragNum); rrdNum = lagNum;
		pop(text, value, trashNum);
		switch (value)
		{
		case '(':
			lrdNum = trashNum; lrdCount++;
			if ((text) && ((*peek(text) == ']') || (*peek(text) == '}') || (*peek(text) == '>')))
			{
				pop(text, trash, trashNum);
				push(elems, trashNum);
				check = false;
			}
			break;
		case '[':
			lsqNum = trashNum; lsqCount++;
			if ((text) && ((*peek(text) == ')') || (*peek(text) == '}') || (*peek(text) == '>')))
			{
				pop(text, trash, trashNum);
				push(elems, trashNum);
				check = false;
			}
			break;
		case '{':
			lfgNum = trashNum; lfgCount++;
			if ((text) && ((*peek(text) == ']') || (*peek(text) == ')') || (*peek(text) == '>')))
			{
				pop(text, trash, trashNum);
				push(elems, trashNum);
				check = false;
			}
			break;
		case '<':
			lagNum = trashNum; lagCount++;
			if ((text) && ((*peek(text) == ']') || (*peek(text) == '}') || (*peek(text) == ')')))
			{
				pop(text, trash, trashNum);
				push(elems, trashNum);
				check = false;
			}
			break;
		case ')':
			rrdNum = trashNum; rrdCount++;
			break;
		case ']':
			rsqNum = trashNum; rsqCount++;
			break;
		case '}':
			rfgNum = trashNum; rfgCount++;
			break;
		case '>':
			ragNum = trashNum; ragCount++;
			break;
		}
	}

	if (lrdCount > rrdCount) push(elems, lrdNum);
	if (lsqCount > rsqCount) push(elems, lsqNum);
	if (lfgCount > rfgCount) push(elems, lfgNum);
	if (lagCount > ragCount) push(elems, lagNum);

	if ((lrdCount == rrdCount) && (lsqCount == rsqCount) && (lfgCount == rfgCount) && (lagCount == ragCount) && check) cout << "отсутствуют";
	else showStruc(elems);
	delete text;
}