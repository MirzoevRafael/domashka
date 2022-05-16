#include "cgi.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>

//Метод вызова скрипта
bool isGet()
{
	size_t realsize;
	char* value = new char[5];
	getenv_s(&realsize, value, 5, "REQUEST_METHOD");
	bool res = !_strcmpi(value, "GET");
	delete[] value;
	return res;
}

//Длина сообщения, переданного методом post
size_t getContentLength()
{
	size_t realsize;
	char* value = new char[11];
	getenv_s(&realsize, value, 11, "CONTENT_LENGTH");
	size_t size;
	if (!realsize) size = 0;
	else sscanf_s(value, "%d", &size);
	delete[] value;
	return size;
}

//Получение данных в необработанном виде
void getFormData(char*& data)
{
	delete[] data;
	if (isGet())
	{
		size_t realsize;
		char* value = new char[65536];
		getenv_s(&realsize, value, 65536, "QUERY_STRING");
		data = new char[realsize + 1];
		strcpy_s(data, realsize + 1, value);
		delete[] value;
	}
	else
	{
		size_t bufSize = getContentLength();
		data = new char[bufSize + 1];
		fread_s(data, bufSize + 1, sizeof(char), bufSize, stdin);
		data[bufSize] = 0;
	}
}

//Получение значения конкретного параметра
void getParamValue(char*& value, const char* paramName, const char* data)
{
	delete[] value;
	value = nullptr;
	char* str = _strdup(data);
	char* tmp = str;
	char* cont;
	while (char* part = strtok_s(tmp, "&", &cont))
	{
		tmp = nullptr;
		char* val;
		char* key = strtok_s(part, "=", &val);
		if (!_strcmpi(paramName, key))
		{
			strDecode(value, val);
			delete[] str;
			return;
		}
	}
	delete[] str;
	value = new char[1];
	value[0] = 0;
}


//Декодирование
void strDecode(char*& decStr, const char* encStr)
{
	char* res = new char[strlen(encStr) + 1];
	int i = 0, j = 0;
	while (encStr[i])
	{
		if (encStr[i] == '+') res[j] = ' ';
		else
		{
			if (encStr[i] == '%')
			{
				char ch[3] = { encStr[i + 1], encStr[i + 2], 0 };
				int c;
				sscanf_s(ch, "%X", &c);
				res[j] = c;
				i += 2;
			}
			else res[j] = encStr[i];
		}
		i++;
		j++;
	}
	res[j] = 0;
	size_t len = strlen(res) + 1;
	delete[] decStr;
	decStr = new char[len];
	strcpy_s(decStr, len, res);
	delete[] res;
}