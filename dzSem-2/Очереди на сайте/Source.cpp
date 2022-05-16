#include <iostream>
#include <fstream>
#include "string.h"
#include "queue.h"
using namespace std;

void showContent()
{
	cout << "<h1>������� 2</h1>\n";
	cout << "��� ��� � �� ���� �������� ���� �� ������������, ��������� �������� � ������, ������� ��� �� �������.<br>\n";
	cout << "<p>";
	queue* credit = new queue;
	queue* debit = new queue;
	ifstream f("_bank_clients");

	if (f.is_open())
	{
		while (!f.eof())
		{
			char* buff = new char[65536];
			f.getline(buff, 65536);
			char* context;
			char* name = strtok_s(buff, "|", &context);
			char* gender = strtok_s(NULL, "|", &context);
			char* age = strtok_s(NULL, "|", &context);
			char* job = strtok_s(NULL, "|", &context);
			char* wage = strtok_s(NULL, "|", &context);
			char* purp = strtok_s(NULL, "|", &context);

			if (!strcmp(purp, " ������")) enqueue(credit, name, gender, age, job, wage, purp);
			else if (!strcmp(purp, " �����")) enqueue(debit, name, gender, age, job, wage, purp);
		}
	}

	cout << "������:<br>\n";
	showQueue(credit);
	cout << "<p>";
	cout << "�����:<br>\n";
	showQueue(debit);
}

void showNav()
{
	ifstream f("_nav");
	if (f.is_open())
	{
		auto sz = 1024;
		auto buf = new char[sz];
		while (!f.eof())
		{
			f.getline(buf, sz);
			char* name = NULL;
			char* addr = strtok_s(buf, " ", &name);
			cout << "<div>"
				"<a href='" << addr << "' class=\"link\">" << name << "</a>"
				"</div>";
		}
	}
}

int main()
{
	cout << "Content-type: text/html; charset=Windows-1251\n\n";

	ifstream f("_index");
	if (f.is_open())
	{
		auto sz = 65536;
		auto buf = new char[sz];
		while (!f.eof())
		{
			f.getline(buf, sz);
			if (strcmp(buf, "<!--CONTENT-->") == 0)
			{
				showContent();
			}
			else if (strcmp(buf, "<!--NAV-->") == 0)
			{
				showNav();
			}
			cout << buf;
		}
		delete[] buf;
		f.close();
	}
	else
	{
		cout << "Not working :(";
	}

	return 0;
}