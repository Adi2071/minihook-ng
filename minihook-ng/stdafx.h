#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <tlhelp32.h>
#include <gl/gl.h>

// STL + stdlib
#pragma warning (disable:4786) // vc++ stl "truncated browser info"
#pragma warning (disable:4244) // float to int possible loss of data
#pragma warning (disable:4731) // evil asm code modifies ebp 

#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <fstream>
using namespace std;
