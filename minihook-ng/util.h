#ifndef __UTIL_H__
#define __UTIL_H__
#include <windows.h>
#include <fstream>
#include <cstdio>
using namespace std;

#define LOG_FILE "minihook-ng.log"

char *GetDirectoryFile(char *filename);

void init_log(HMODULE hDll);
void __cdecl add_log (const char *fmt, ...);
void deinit_log();

#endif
