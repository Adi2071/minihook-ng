#include "util.h"

ofstream ofile;	
char dlldir[320];

char *GetDirectoryFile(char *filename)
{
	static char path[320];
	strcpy(path, dlldir);
	strcat(path, filename);
	return path;
}

void init_log(HMODULE hDll) {
	GetModuleFileName(hDll, dlldir, 512);
	for(int i = strlen(dlldir); i > 0; i--) { if(dlldir[i] == '\\') { dlldir[i+1] = 0; break; } }
	ofile.open(GetDirectoryFile(LOG_FILE), ios::app);
	
	add_log("\n---------------------\nD3D8 Hack Started...\n---------------------");
}

void __cdecl add_log (const char *fmt, ...)
{
	if(ofile != NULL)
	{
		if(!fmt) { return; }

		va_list va_alist;
		char logbuf[256] = {0};

		va_start (va_alist, fmt);
		_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), fmt, va_alist);
		va_end (va_alist);

		ofile << logbuf << endl;
	}
}

void deinit_log() {
    add_log("\n---------------------\nD3D8 Hack Ending...\n---------------------");
    if(ofile) { ofile.close(); }
}
