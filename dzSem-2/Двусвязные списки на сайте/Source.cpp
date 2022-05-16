#include <iostream>
#include <fstream>
#include "cgi.h"
#include "dclist.h"
using namespace std;

void showContent()
{
	cout << "<h1>Задание 4</h1>\n";
	cout << "<form method='get' action='task_four.cgi'>\n";
	cout << "Введите числа: <input type='text' name='equation' maxlength='128' size='128'><br>\n";
	cout << "<input type='submit' value='Отправить'>\n";
	cout << "</form>\n";
	char* data = nullptr;
	getFormData(data);
	if (data && strlen(data) > 0)
	{
		char* temp;
		char* value = nullptr;
		getParamValue(value, "equation", data);
		char* num1 = strtok_s(value, " ", &temp);
		char* num2 = strtok_s(NULL, " ", &temp);
		cout << "<p><div>";
		list sum;
		add(sum, 0);
		if (strlen(num1) > strlen(num2)) addition(sum, num1, num2);
		else addition(sum, num2, num1);
		cout << num1 << " + " << num2 << " = ";
		show_list(sum, false);
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