// Win32Project2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
LRESULT CALLBACK Events(HWND, UINT, WPARAM, LPARAM);
HDC hdc;
HWND hwndmain;
//Windows Procedure Variables
HMENU menu, popup;
int x, y;
int mouseX, mouseY;
float posX=0, posY=-3.0f, posZ=0;
FILE *console;
DWORD pid;
HANDLE hp;
int WINAPI WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                      LPSTR    lpCmdLine,
                      int       nCmdShow)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen_s(&console,"CON", "w", stdout);
	 
	WNDCLASSEX wnd;
	MSG msg;
	ZeroMemory(&wnd, sizeof(WNDCLASSEX));
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = Events;
	wnd.lpszClassName = L"MainWin";
	wnd.hbrBackground =(HBRUSH) COLOR_BACKGROUND;
	wnd.hCursor = LoadCursor(0,IDC_ARROW);
	wnd.hIcon = LoadIcon(0, IDI_APPLICATION);
	wnd.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wnd.style = CS_DBLCLKS;
	RegisterClassEx(&wnd);
	hwndmain = CreateWindowEx(0, L"MainWin", L"Programa", WS_POPUPWINDOW, CW_USEDEFAULT, CW_USEDEFAULT
		, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
		HWND_DESKTOP, 0, hInstance, 0);
	ShowWindow(hwndmain, nCmdShow);
	hdc = GetDC(hwndmain);
	PIXELFORMATDESCRIPTOR pfd;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iPixelType = LPD_TYPE_RGBA;
	pfd.nVersion = 2;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
	int iFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, iFormat, &pfd);
	HGLRC glrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, glrc);
	ShowCursor(FALSE);
	while (GetMessage(&msg, hwndmain, 0, 0)==TRUE) {	
		
				TranslateMessage(&msg);
				DispatchMessage(&msg);
		 
	}
	TerminateThread(hp, 0);
	wglDeleteContext(glrc);
 

	return 0;
}
Graphic graph;
Camera cam(&mouseX,&mouseY);
Object obj,obj2;
Physic physic;
RigidBody p;
 
float fovy,dist=1.5f,heightVision = 1.0f;
GLfloat diffuse[] = { 1.0f,0.9f, 0.1f,1.0f };
GLfloat amb[] = { 1,1, 1.0f,1.0f };
GLfloat lightpos[] = { 1.0f ,-1.0f,1.0f,1};
GLfloat color[] = {1,1,1,0};
MOUSEHOOKSTRUCT *ms;
LRESULT CALLBACK Mouse(UINT msg, WPARAM w, LPARAM l) {
	ms = (MOUSEHOOKSTRUCT*)l;
	if (ms != NULL) {

		mouseX = ms->pt.x;
		mouseY = ms->pt.y;

	}
		return CallNextHookEx(0, msg, w, l);
	
}
LRESULT CALLBACK Keyboard(UINT msg, WPARAM w, LPARAM l) {
	 
		if (w == VkKeyScan('w')) {
			posX -= sin(cam.AngleByPositionY()*3.14f / 180.0f) / 10;
			posZ += cos(cam.AngleByPositionY()*3.14f / 180.0f) / 10;
			posY += sin(cam.AngleByPositionX()*3.14f / 180.0f) / 10;
		}
		if (w == VkKeyScan('s')) {
			posX += sin(cam.AngleByPositionY()*3.14f / 180.0f) / 100;
			posZ -= cos(cam.AngleByPositionY()*3.14f / 180.0f) / 100;
		}
		if (w == VkKeyScan('d')) {
			posX -= cos(cam.AngleByPositionY()*3.14f / 180.0f) / 100;
			posZ -= sin(cam.AngleByPositionY()*3.14f / 180.0f) / 100;
		}
		if (w == VkKeyScan('a')) {
			posX += cos(cam.AngleByPositionY()*3.14f / 180.0f) / 100;
			posZ += sin(cam.AngleByPositionY()*3.14f / 180.0f) / 100;
		}
		 
	return CallNextHookEx(0, msg, w, l);
}
DWORD WINAPI physicfunc(LPVOID lp) {
	for (;;) {
		physic.AddGravity(&p);
		physic.AddCollision(&obj2, &p);
 
	}
	 
}
LRESULT CALLBACK Events(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {

	switch (msg) {
	case WM_CREATE:
		menu = CreateMenu();
		popup = CreateMenu();
		AppendMenu(menu, MF_POPUP, (UINT_PTR)popup, L"Opcoes");
		AppendMenu(popup, MF_STRING, (UINT_PTR)1001, L"Sair");
		//SetMenu(hwnd, menu);
		SetWindowsHook(WH_MOUSE, (HOOKPROC)Mouse);			//Create a thread just to mouse events
		SetWindowsHook(WH_KEYBOARD, (HOOKPROC)Keyboard);	//Create a thread just to keyboard events
	
		graph.ReadShapeObject(&obj, "Untitled5.obj");
		graph.ReadShapeObject(&obj2, "Untitled6.obj");
		graph.ReadMaterialObject(&obj, "Untitled5.mtl");
		graph.ReadMaterialObject(&obj2, "Untitled6.mtl");
		physic.SetGround(&obj);
		cout << obj.mat.at(0).Ka[0] << endl;
		cout << obj2.mat.at(0).Kd[0] << endl;
		hp = CreateThread(0, 0, physicfunc, 0, 0, &pid);
		p.z = 1.189f;
		p.y = p.x = 0;
		cam.SetScreenSize(&x, &y);
		cam.SetSensibility(20.0f);
		fovy = 180.0f * (2.0f * atan(heightVision / dist)) / 3.14f;
		
		break;
	case WM_COMMAND:
		if (wParam == 1001) { 
			PostQuitMessage(0);
		}
		break;
	case WM_SIZE:
				x = LOWORD(lParam);
				y = HIWORD(lParam);
		break;
 
	case WM_PAINT:
			
		    glClearColor(0, 0, 0, 0);
			
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
		

			gluPerspective( fovy, x/y, 0.1f, 10.0f);
			
		
			
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glRotatef(cam.AngleByPositionX(),1.0f, 0, 0);
			glRotatef(cam.AngleByPositionY(), 0, 1.0f, 0);
			glTranslatef(posX, posY, posZ);
		
			glViewport(0, 0, x, y);
			glShadeModel(GL_SMOOTH);
			glEnable(GL_LINE_SMOOTH);
			glBegin(GL_LINES);
			glColor3ub(255, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(1.0f, 0, 0);
			glColor3ub(0, 255, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 1.0f, 0);
			glColor3ub(0, 0, 255);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 1.0f);
			glEnd();
			glDisable(GL_LINE_SMOOTH);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, diffuse);
			glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
			glLightf(GL_LIGHT0, GL_SHININESS, 128);
		
	 
			
			glMaterialfv(GL_BACK, GL_AMBIENT,obj.mat.at(0).Ka);
			glMaterialfv(GL_BACK, GL_DIFFUSE, obj.mat.at(0).Kd);
			glMaterialfv(GL_BACK, GL_SPECULAR, obj.mat.at(0).Ks);
			
			glEnableClientState(GL_VERTEX_ARRAY);
			//glEnableClientState(GL_NORMAL_ARRAY);
			//glNormalPointer(GL_FLOAT, 0, obj.normals.data());
			glVertexPointer(3, GL_FLOAT, 0,obj.vertices.data());
			glDrawElements(GL_TRIANGLES, obj.indices.size(), GL_UNSIGNED_INT, obj.indices.data());


			glTranslatef(p.x, p.y, p.z);
			//Erro aqui
			glVertexPointer(3, GL_FLOAT, 0, obj2.vertices.data());
			glDrawElements(GL_TRIANGLES, obj2.indices.size(), GL_UNSIGNED_INT, obj2.indices.data());
			

			glDisableClientState(GL_VERTEX_ARRAY);
			//glDisableClientState(GL_NORMAL_ARRAY);
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0); 
			glDisable(GL_DEPTH_TEST);
			 
			
		
			wglSwapLayerBuffers(hdc, WGL_SWAP_MAIN_PLANE);
			
			 
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}






