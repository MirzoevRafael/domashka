#include <iostream>
#include <fstream>
#include <cctype>
#include "cgi.h"
#include "trees.h"
using namespace std;

void showContent()
{
	cout << "<h1>Задание 5</h1>\n";
	cout << "<form method='get' action='task_five.cgi'>\n";
	cout << "Введите 1, если хотите отсортировать по фамилии, 2, если хотите отсортировать по баллу. Через пробел введите первую букву фамилии искомых студентов: <input type='text' name='choice' maxlength='128' size='128'><br>\n";
	cout << "<input type='submit' value='Отправить'>\n";
	cout << "</form>\n";
	char* data = nullptr;
	getFormData(data);
	if (data && strlen(data) > 0)
	{
		char* value = nullptr;
		getParamValue(value, "choice", data);
		cout << "<div>\n";
		int choice = value[0] - '0';
		char letter = (char)toupper(value[2]);
		tree students;
		node* head = nullptr;
		students.root = head;
		if (choice == 1) fill_by_name(head, students);
		else if (choice == 2) fill_by_mark(head, students);
		cout << "<br>Упорядоченный список студентов:<br>\n";
		show_tree_ordered(head);
		cout << "<br>Студенты с фамилией на " << letter << ":<br>\n";
		bool check = false;
		find_by_name(head, letter, check);
		if (!check) cout << "Нет студентов с фамилией на " << letter << endl;
		clear(head);
		cout << "</div>\n";
		delete[] value;
	}
	delete[] data;
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
	setlocale(LC_ALL, "Russian");
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