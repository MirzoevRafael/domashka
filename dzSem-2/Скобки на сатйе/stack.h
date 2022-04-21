#pragma once
struct stack;

struct nums;

bool pop(stack*& text, char& value, int& count);

bool pop(nums*& elems, int& num);

void push(stack*& text, char value, int count);

void push(nums*& elems, int num);

char* peek(stack* text);

void showStruc(nums*& elems);

void clear(stack*& text);

void clear(nums*& elems);

void fillBrack(char ex[], stack*& text);

void checkBrack(stack*& text);