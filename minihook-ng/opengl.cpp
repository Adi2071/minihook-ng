#include "opengl.h"
#include "SDKInclude.h"
#include "TransInclude.h"
#include "client.h"
#include "Drawing.h"
#include "Calculations.h"

UINT		g_nClearMask;
UINT		g_nViewport = 0;

int team = -1;

// ============================= //
// glBegin						 //
// ============================= //
void WINAPI xglBegin( GLenum mode ) {
	glBegin(mode);
}

// ============================= //
// glClear						 //
// ============================= //
void WINAPI xglClear( GLbitfield mask ) {
	g_nClearMask = mask;
	glClear(mask);
}

// ============================= //
// glDisable					 //
// ============================= //
void WINAPI xglDisable( GLenum cap ) {	
	glDisable(cap);
}

void Draw(void) {

}

// ============================= //
// glViewport					 //
// ============================= //
void WINAPI xglViewport( GLint x, GLint y, GLsizei	width, GLsizei height ) {
	glViewport(x, y, width, height);
}

// ============================= //
// glVertex3f					 //
// ============================= //
void WINAPI xglVertex3f (GLfloat x,  GLfloat y,  GLfloat z) {

	/*if(cvar.lambert)
	{
		if(team == -1){}
		else if(team == TEAM_TERROR)
		{
			glColor3f(255, 0, 0);
		}
		else if(team == TEAM_CT)
		{
			glColor3f(0, 0, 255);
		}
	}*/

	glVertex3f(x, y, z);
} 

// ============================= //
// glReadPixels					 //
// ============================= //
void WINAPI xglReadPixels( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *data ) {
	glReadPixels(x, y, width, height, format,type, data);
}

// ============================= //
// glVertex3fv					//
// ============================= //
void WINAPI xglVertex3fv( const GLfloat * v ) {
	glVertex3fv(v);
}

// ============================= //
// glVertex2f					//
// ============================= //
void WINAPI xglVertex2f( GLfloat x, GLfloat y ) {
	glVertex2f(x, y);
}

// ============================= //
// glPopMatrix					 //
// ============================= //
void WINAPI xglPopMatrix( void ) {
	glPopMatrix();
}

// ============================= //
// glShadeModel         		 //
// ============================= //
void WINAPI xglShadeModel( GLenum mode ) {
	glShadeModel(mode);
}

FARPROC HookOpenGL(LPCSTR lpProcName, FARPROC fpProc) {
	#define HOOK(FUNCTION)  if(!strcmp(#FUNCTION, lpProcName)) return (FARPROC)x##FUNCTION;

	HOOK(glBegin)
	HOOK(glClear)
	HOOK(glViewport)
	HOOK(glVertex3f)
	HOOK(glDisable)
	HOOK(glReadPixels)
	HOOK(glVertex3fv)
	HOOK(glVertex2f)

	return fpProc;
}
