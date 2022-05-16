#pragma once
bool isGet();
void getFormData(char*& data);
size_t getContentLength();
void getParamValue(char*& value, const char* paramName, const char* data);
void strDecode(char*& decStr, const char* encStr);