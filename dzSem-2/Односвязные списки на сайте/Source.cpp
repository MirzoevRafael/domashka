#include <iostream>
#include <fstream>
#include "cgi.h"
#include "sclist.h"
using namespace std;

void showContent()
{
	cout << "<h1>Задание 3</h1>\n";
	cout << "<form method='get' action='task_three.cgi'>\n";
	cout << "Введите числа через пробел: <input type='text' name='elements' maxlength='128' size='128'><br>\n";
	cout << "<input type='submit' value='Отправить'>\n";
	cout << "</form>\n";
	char* data = nullptr;
	getFormData(data);
	if (data && strlen(data) > 0)
	{
		char* value = nullptr;
		getParamValue(value, "elements", data);
		cout << "<p>Введенный числа:<br>\n";
		cout << value << endl;
		cout << "<div>";
		elem* list = nullptr;
		add_by_check(list, value);
		cout << "<p>Составленный список:<br>\n";
		show_list(list);
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