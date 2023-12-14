#include "StdAfx.h"

#include <locale.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>

#include "Log.hpp"

#define LOGNAME "log.txt"

using namespace ShaderPlayground;

Log* Log::_instance = nullptr;

Log::Log() {
    if (!_instance) {
        _file = nullptr;
        _instance = this;
        Initialize();
    } else {
        Err("Log уже был создан");
    }
}

Log::~Log() {
    Close();

    _instance = nullptr;
}

void Log::Initialize() {
    setlocale(LC_ALL, "rus");

    if (fopen_s(&_file, LOGNAME, "w") == 0) {
        char timer[9];
        _strtime_s(timer, 9);
        char date[9];
        _strdate_s(date, 9);
        fprintf(_file, "Лог создан: %s %s.\n", date, timer);
        fprintf(_file, "---------------------------------------\n\n");
    } else {
        printf("Ошибка при создании файла лога...\n");
        _file = nullptr;
    }
}

void Log::Close() {
    if (!_file) {
        return;
    }

    char timer[9];
    _strtime_s(timer, 9);
    char date[9];
    _strdate_s(date, 9);
    fprintf(_file, "\n---------------------------------------\n");
    fprintf(_file, "Конец лога: %s %s.", date, timer);
    fclose(_file);
}

void Log::Print(const char* message, ...) {
    va_list args;
    va_start(args, message);
    int len = _vscprintf(message, args) + 1;
    char* buffer = static_cast<char*>(malloc(len * sizeof(char)));
    vsprintf_s(buffer, len, message, args);
    Print("", buffer);
    va_end(args);
    free(buffer);
}

void Log::Debug(const char* message, ...) {
#ifdef _DEBUG
    va_list args;
    va_start(args, message);
    int len = _vscprintf(message, args) + 1;
    char* buffer = static_cast<char*>(malloc(len * sizeof(char)));
    vsprintf_s(buffer, len, message, args);
    Print("*DEBUG: ", buffer);
    va_end(args);
    free(buffer);
#endif
}

void Log::Err(const char* message, ...) {
    va_list args;
    va_start(args, message);
    int len = _vscprintf(message, args) + 1;
    char* buffer = static_cast<char*>(malloc(len * sizeof(char)));
    vsprintf_s(buffer, len, message, args);
    Print("*ERROR: ", buffer);
    va_end(args);
    free(buffer);
}

void Log::Print(const char* levtext, const char* text) {
    char timer[9];
    _strtime_s(timer, 9);
    clock_t cl = clock();

    printf("%s::%d: %s%s\n", timer, cl, levtext, text);
    if (_file)
    {
        fprintf(_file, "%s::%d: %s%s\n", timer, cl, levtext, text);
        fflush(_file);
    }
}
