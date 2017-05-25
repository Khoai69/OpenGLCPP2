#pragma once
#include "EGL/egl.h"
#include "GLES2/gl2.h"

#define LOG printf
struct SysContext
{
	// Windows variables
	HWND				nativeWindow;
	HDC					deviceContext;

	// EGL variables
	EGLDisplay			eglDisplay;
	EGLConfig			eglConfig;
	EGLSurface			eglSurface;
	EGLContext			eglContext;

	// Callback funcs
	void (*renderFunc)	();
	void (*keyFunc)		(unsigned char, bool);
	void (*updateFunc)	(float deltaTime);
	void(*mouseDownFunc) (int x, int y);
	void(*mouseUpFunc)   (int x, int y);
	void(*mouseMoveFunc) (int x, int y);
};

void sysInit(SysContext* sysCtx, int screenW, int screenH);

void sysMainLoop(SysContext* sysCtx);

void sysRegisterRenderFunc(SysContext* sysCtx, void (*func)());
void sysRegisterUpdateFunc(SysContext* sysCtx, void (*func)(float));
void sysRegisterKeyFunc(SysContext* sysCtx, void (*func)(unsigned char, bool));
void sysRegisterMouseMoveFunc(SysContext* sysCtx, void(*func)(int, int));
void sysRegisterMouseUpFunc(SysContext* sysCtx, void(*func)(int, int));
void sysRegisterMouseDownFunc(SysContext* sysCtx, void(*func)(int, int));
void sysCleanUp();

void printSystemSpecs();



